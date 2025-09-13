#include "lcd.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "instructions/instructions.h"
#include "ppu.h"

void lcd_create(lcd_t *lcd) {
  memset(lcd->framebuffer, 0x00, FB_WIDTH * FB_HEIGHT * FB_CHANNELS);
  lcd->register_lcdc = 0x91;
  lcd->register_ly = 0;
  lcd->register_lyc = 0;
  lcd->register_stat = 0x85;
}

const int TILES_PER_COL = 24;
const int TILES_PER_ROW = 16;

void lcd_update_framebuffer(lcd_t *lcd, ppu_t *ppu) {
  if (lcd->frame_ready) {
    lcd->frame_ready = 0;
  }
}
