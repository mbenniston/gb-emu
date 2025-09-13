#include "ppu.h"

#include <stdio.h>
#include <string.h>

#include "bus.h"
#include "interrupt_controller.h"
#include "lcd.h"

void ppu_create(ppu_t *ppu) {
  ppu->register_scx = 0;
  ppu->register_scy = 0;
  ppu->register_wx = 0;
  ppu->register_wy = 0;
  ppu->register_bgp = 0xFC;
  ppu->register_obp0 = 0;
  ppu->register_obp1 = 0;
  ppu->pending_dots = 0;
  memset(ppu->vram, 0, VRAM_LENGTH);
  memset(ppu->oam, 0, OAM_LENGTH);
}

static const int SCREEN_PALETTE[5][3] = {
    {232, 252, 204}, {172, 212, 144}, {84, 140, 112}, {20, 40, 56}, {0, 0, 0},
};

void get_background(ppu_t *ppu, lcd_t *lcd, int screen_x, int screen_y,
                    int *palette_index, int *color) {
  // apply scroll,
  int tile_x = ((screen_x + ppu->register_scx) % 256) / 8;
  int tile_y = ((screen_y + ppu->register_scy) % 256) / 8;

  int tile_map_address =
      ((lcd->register_lcdc & LCDC_BG_TILE_MAP) > 0 ? 0x9C00 : 0x9800) -
      VRAM_ADDRESS;
  uint16_t tile_address = tile_map_address + tile_x + tile_y * 32;
  uint8_t tile = ppu->vram[tile_address];

  int tile_start = 0x8000 + tile * 16;
  if ((lcd->register_lcdc & LCDC_BG_AND_WINDOW_TILES) == 0) {
    tile_start =
        (tile < 128 ? tile * 16 + 0x9000 : ((tile - 128) * 16 + 0x8800));
  }

  // draw individual tile
  int tile_pixel_x = ((screen_x + ppu->register_scx) % 256) % 8;
  int tile_pixel_y = ((screen_y + ppu->register_scy) % 256) % 8;

  int row_index = tile_start + tile_pixel_y * 2;
  int low_value =
      (ppu->vram[row_index - VRAM_ADDRESS] >> (7 - tile_pixel_x)) & 0b1;
  int high_value =
      (ppu->vram[row_index + 1 - VRAM_ADDRESS] >> (7 - tile_pixel_x)) & 0b1;
  *palette_index = (low_value | high_value << 1) & 0b11;

  *color =
      (ppu->register_bgp & (0b11 << *palette_index * 2)) >> *palette_index * 2;
}

void get_window(ppu_t *ppu, lcd_t *lcd, int screen_x, int screen_y,
                int *palette_index, int *color) {
  // apply scroll,
  int tile_x = ((screen_x) % 256) / 8;
  int tile_y = ((screen_y) % 256) / 8;

  int tile_map_address =
      ((lcd->register_lcdc & LCDC_WINDOW_TILE_MAP) > 0 ? 0x9C00 : 0x9800) -
      VRAM_ADDRESS;
  uint16_t tile_address = tile_map_address + tile_x + tile_y * 32;
  uint8_t tile = ppu->vram[tile_address];

  int tile_start = 0x8000 + tile * 16;
  if ((lcd->register_lcdc & LCDC_BG_AND_WINDOW_TILES) == 0) {
    tile_start =
        (tile < 128 ? tile * 16 + 0x9000 : ((tile - 128) * 16 + 0x8800));
  }

  // draw individual tile
  int tile_pixel_x = ((screen_x) % 256) % 8;
  int tile_pixel_y = ((screen_y) % 256) % 8;

  int row_index = tile_start + tile_pixel_y * 2;
  int low_value =
      (ppu->vram[row_index - VRAM_ADDRESS] >> (7 - tile_pixel_x)) & 0b1;
  int high_value =
      (ppu->vram[row_index + 1 - VRAM_ADDRESS] >> (7 - tile_pixel_x)) & 0b1;
  *palette_index = (low_value | high_value << 1) & 0b11;
  *color =
      (ppu->register_bgp & (0b11 << *palette_index * 2)) >> *palette_index * 2;
}

void get_sprite(ppu_t *ppu, lcd_t *lcd, int actual_screen_x,
                int actual_screen_y, int *palette_index, int *color,
                int *sprite_found, int *priority) {
  int screen_x = actual_screen_x + 8;
  int screen_y = actual_screen_y + 16;
  *sprite_found = 0;

  int sprite_height = (lcd->register_lcdc & LCDC_OBJ_SIZE) > 0 ? 16 : 8;

  int sprites_on_ly[10];
  int sprites_on_ly_count = 0;

  for (int s = 0; s < 40; s++) {
    uint16_t sprite_start_address = s * 4;
    uint8_t sprite_y = ppu->oam[sprite_start_address];
    if (screen_y >= sprite_y && screen_y < sprite_y + sprite_height &&
        sprites_on_ly_count < 10) {
      sprites_on_ly[sprites_on_ly_count++] = s;
    }
  }

  int sprite = 0;
  int sprite_x = 0;

  for (int s = 0; s < sprites_on_ly_count; s++) {
    uint16_t possible_sprite_start_address = sprites_on_ly[s] * 4;
    uint8_t possible_sprite_x = ppu->oam[possible_sprite_start_address + 1];

    if (screen_x >= possible_sprite_x && screen_x < possible_sprite_x + 8) {
      if (!*sprite_found) {
        sprite = sprites_on_ly[s];
        sprite_x = possible_sprite_x;
        *sprite_found = 1;
      } else {
        int replace_sprite =
            possible_sprite_x > sprite_x ||
            (possible_sprite_x == sprite_x && sprites_on_ly[s] < sprite);
        if (replace_sprite) {
          sprite = sprites_on_ly[s];
          sprite_x = possible_sprite_x;
          *sprite_found = 1;
        }
      }
    }
  }

  if (*sprite_found) {
    uint16_t sprite_start_address = sprite * 4;
    uint8_t sprite_y = ppu->oam[sprite_start_address];
    uint8_t tile = ppu->oam[sprite_start_address + 2];
    uint8_t attributes = ppu->oam[sprite_start_address + 3];
    int y_flip = attributes & (1 << 6);
    int x_flip = attributes & (1 << 5);
    *priority = (attributes & 0b10000000) > 0;
    int palette = (attributes & 0b10000) > 0;

    // get sprite colour
    int y = screen_y - sprite_y;
    int x = screen_x - sprite_x;

    if (x_flip) {
      x = 7 - x;
    }
    if (y_flip) {
      y = sprite_height - 1 - y;
    }

    int tile_start = 0x8000 + tile * 16;
    int row_index = tile_start + y * 2;
    int low_value = (ppu->vram[row_index - VRAM_ADDRESS] >> (7 - x)) & 0b1;
    int high_value = (ppu->vram[row_index + 1 - VRAM_ADDRESS] >> (7 - x)) & 0b1;
    *palette_index = (low_value | high_value << 1) & 0b11;
    *color = ((palette ? ppu->register_obp1 : ppu->register_obp0) &
              (0b11 << *palette_index * 2)) >>
             *palette_index * 2;
  }
}

void draw_scanline(ppu_t *ppu, lcd_t *lcd) {
  if (lcd->register_ly > 143)
    return; // only draw on screen

  for (int x = 0; x < FB_WIDTH; x++) {
    int fb_index = (lcd->register_ly * FB_WIDTH + x) * 4;

    // get background
    int pixel;
    int pixel_palette_index;
    get_background(ppu, lcd, x, lcd->register_ly, &pixel_palette_index, &pixel);

    // get window
    int window_enabled = lcd->register_lcdc & LCDC_WINDOW_ENABLE;
    if (window_enabled && x + 7 >= ppu->register_wx &&
        lcd->register_ly >= ppu->register_wy) {
      get_window(ppu, lcd, x, lcd->register_ly, &pixel_palette_index, &pixel);
    }

    // get objects
    int sprite_color, sprite_palette_index, sprite_found, sprite_priority;
    get_sprite(ppu, lcd, x, lcd->register_ly, &sprite_palette_index,
               &sprite_color, &sprite_found, &sprite_priority);

    if (sprite_found) {
      if (sprite_palette_index != 0) {
        if (!sprite_priority || (pixel_palette_index == 0))
          pixel = sprite_color;
      }
    }

    // draw pixel
    lcd->framebuffer[fb_index] = SCREEN_PALETTE[pixel][0];
    lcd->framebuffer[fb_index + 1] = SCREEN_PALETTE[pixel][1];
    lcd->framebuffer[fb_index + 2] = SCREEN_PALETTE[pixel][2];
    lcd->framebuffer[fb_index + 3] = 255;
  }
}

int next_state(ppu_mode_e mode, int dots, uint8_t ly, uint8_t stat, lcd_t *lcd,
               ppu_t *ppu, interrupt_controller_t *interrupt_controller,
               ppu_mode_e *next_mode, int *next_dots, uint8_t *next_ly) {
  switch (mode) {
  case PPU_MODE_OAM_SCAN:
    if (dots >= PPU_MODE_OAM_SCAN_DURATION_DOTS) {
      *next_dots = dots - PPU_MODE_OAM_SCAN_DURATION_DOTS;
      *next_mode = PPU_MODE_DRAWING_PIXELS;
      return 1;
    }
    break;
  case PPU_MODE_DRAWING_PIXELS:
    if (dots >= PPU_MODE_DRAWING_PIXELS_DURATION_DOTS) {
      /* draw scanline */
      draw_scanline(ppu, lcd);

      *next_mode = PPU_MODE_HBLANK;
      if (stat & STAT_MODE_0_INT_SELECT) {
        interrupt_controller_set_lcd_flag(interrupt_controller);
      }
      return 1;
    }
    break;
  case PPU_MODE_HBLANK:
    if (dots >= PPU_MODE_HBLANK_DURATION_DOTS) {
      *next_dots = dots - PPU_MODE_HBLANK_DURATION_DOTS;
      if (ly >= PPU_LINE_COUNT) {
        lcd->frame_ready = 1;
        *next_mode = PPU_MODE_VBLANK;
        *next_ly = ly + 1;
        if (stat & STAT_MODE_1_INT_SELECT) {
          interrupt_controller_set_lcd_flag(interrupt_controller);
        }
        interrupt_controller_set_vblank_flag(interrupt_controller);
      } else {
        *next_mode = PPU_MODE_OAM_SCAN;
        *next_ly = ly + 1;
        if (stat & STAT_MODE_2_INT_SELECT) {
          interrupt_controller_set_lcd_flag(interrupt_controller);
        }
      }
      return 1;
    }
    break;
  case PPU_MODE_VBLANK:
    if (dots >= PPU_MODE_LINE_DURATION_DOTS) {
      *next_dots = dots - PPU_MODE_LINE_DURATION_DOTS;

      if (ly >= PPU_TOTAL_LINE_COUNT) {
        memset(lcd->framebuffer, 0x00, FB_WIDTH * FB_HEIGHT * FB_CHANNELS);
        *next_ly = 0;
        *next_mode = PPU_MODE_OAM_SCAN;
        if (stat & STAT_MODE_2_INT_SELECT) {
          interrupt_controller_set_lcd_flag(interrupt_controller);
        }
      } else {
        *next_ly = ly + 1;
      }

      return 1;
    }
    break;
  }

  return 0;
}

void ppu_tick(ppu_t *ppu, lcd_t *lcd, bus_t *bus,
              interrupt_controller_t *interrupt_controller,
              int machine_cycles_elapsed) {
  ppu->pending_dots += machine_cycles_elapsed * 4;

  ppu_mode_e mode = lcd->register_stat & STAT_PPU_MODE;

  while (next_state(mode, ppu->pending_dots, lcd->register_ly,
                    lcd->register_stat, lcd, ppu, interrupt_controller, &mode,
                    &ppu->pending_dots, &lcd->register_ly)) {
  }

  if ((lcd->register_stat & STAT_LYC_EQUALS_LY) &&
      lcd->register_ly == lcd->register_lyc) {
    interrupt_controller_set_lcd_flag(interrupt_controller);
  }

  if (ppu->pending_dma_machine_cycles > 0) {
    ppu->pending_dma_machine_cycles -= machine_cycles_elapsed;
    if (ppu->pending_dma_machine_cycles <= 0) {
      // transfer data
      for (int i = 0; i < 160; i++) {
        bus_write(bus, 0xFE00 + i, bus_read(bus, ppu->dma_source_address + i));
      }
    }
  }

  lcd->register_stat &= ~STAT_PPU_MODE;
  lcd->register_stat |= mode;
}

void ppu_dma_write(ppu_t *ppu, uint8_t data) {
  ppu->dma_source_address = data * 0x100;
  ppu->pending_dma_machine_cycles = PPU_DMA_DURATION_MACHINE_CYCLES;
}
