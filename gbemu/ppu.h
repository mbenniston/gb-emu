#ifndef GBEMU_PPU_H
#define GBEMU_PPU_H
#include <stdint.h>

#include "interrupt_controller.h"
#include "lcd.h"

// TODO: Implement VRAM OAM dumping, then starting implementing scanline LCD

#define SRCY_ADDRESS 0xFF42
#define SRCX_ADDRESS 0xFF43
#define WY_ADDRESS 0xFF4A
#define WX_ADDRESS  0xFF4B
#define BGP_ADDRESS 0xFF47
#define OBP0_ADDRESS 0xFF48
#define OBP1_ADDRESS 0xFF49
#define VRAM_ADDRESS 0x8000
#define VRAM_LENGTH 0x2004

#define OAM_ADDRESS 0xFE00
#define OAM_LENGTH 160

typedef enum {
    PPU_MODE_OAM_SCAN = 0b10,
    PPU_MODE_DRAWING_PIXELS = 0b11,
    PPU_MODE_HBLANK = 0b00,
    PPU_MODE_VBLANK = 0b01,
} ppu_mode_e;

#define PPU_MODE_OAM_SCAN_DURATION_DOTS 80
#define PPU_MODE_DRAWING_PIXELS_DURATION_DOTS 172
#define PPU_MODE_HBLANK_DURATION_DOTS 376
#define PPU_MODE_VBLANK_DURATION_DOTS 4560
#define PPU_MODE_LINE_DURATION_DOTS (PPU_MODE_HBLANK_DURATION_DOTS +PPU_MODE_DRAWING_PIXELS_DURATION_DOTS +PPU_MODE_OAM_SCAN_DURATION_DOTS)

#define PPU_LINE_COUNT 144
#define PPU_TOTAL_LINE_COUNT 154

#define PPU_DMA_ADDRESS 0xFF46
#define PPU_DMA_DURATION_MACHINE_CYCLES 160

typedef struct ppu {
    uint8_t vram[VRAM_LENGTH];
    uint8_t oam[OAM_LENGTH];
    uint8_t register_scx;
    uint8_t register_scy;
    uint8_t register_wx;
    uint8_t register_wy;
    uint8_t register_bgp;
    uint8_t register_obp0;
    uint8_t register_obp1;

    int pending_dots;

    int pending_dma_machine_cycles;
    uint16_t dma_source_address;
} ppu_t;

void ppu_create(ppu_t *ppu);

struct bus;

void ppu_tick(ppu_t *ppu, lcd_t *lcd, struct bus *bus, interrupt_controller_t *interrupt_controller,
              int machine_cycles_elapsed);

void ppu_dma_write(ppu_t *ppu, uint8_t data);

#endif
