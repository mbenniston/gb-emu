#ifndef GBEMU_LCD_H
#define GBEMU_LCD_H

#include <stdint.h>

#define FB_WIDTH 160
#define FB_HEIGHT 144
#define FB_CHANNELS 4

#define LCDC_LCD_ENABLE 0b10000000
#define LCDC_WINDOW_TILE_MAP 0b01000000
#define LCDC_WINDOW_ENABLE 0b00100000
#define LCDC_BG_AND_WINDOW_TILES 0b00010000
#define LCDC_BG_TILE_MAP 0b00001000
#define LCDC_OBJ_SIZE 0b00000100
#define LCDC_OBJ_ENABLE 0b00000010
#define LCDC_BG_AND_WINDOW_ENABLE 0b00000001

#define STAT_LCDY_INT_SELECT 0b01000000
#define STAT_MODE_2_INT_SELECT 0b00100000
#define STAT_MODE_1_INT_SELECT 0b00010000
#define STAT_MODE_0_INT_SELECT 0b00001000
#define STAT_LYC_EQUALS_LY 0b00000100
#define STAT_PPU_MODE 0b00000011

#define LCDC_ADDRESS 0xFF40
#define LY_ADDRESS 0xFF44
#define LYC_ADDRESS 0xFF45
#define STAT_ADDRESS 0xFF41

typedef struct {
    uint8_t framebuffer[FB_WIDTH * FB_HEIGHT * FB_CHANNELS];

    int frame_ready;
    uint8_t register_lcdc;
    uint8_t register_ly;
    uint8_t register_lyc;
    uint8_t register_stat;
} lcd_t;

void lcd_create(lcd_t *lcd);

struct ppu;

void lcd_update_framebuffer(lcd_t *lcd, struct ppu *ppu);

#endif
