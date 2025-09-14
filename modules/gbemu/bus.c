#include "bus.h"

#include "lcd.h"
#include "ppu.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

void bus_create(bus_t *bus, interrupt_controller_t *interrupt_controller,
                timer_controller_t *timer_controller, lcd_t *lcd, ppu_t *ppu,
                joypad_t *joypad, cartridge_t *cartridge) {
  memset(bus->memory, 0, 0x10000);
  bus->interrupt_controller = interrupt_controller;
  bus->timer_controller = timer_controller;
  bus->lcd = lcd;
  bus->ppu = ppu;
  bus->joypad = joypad;
  bus->cartridge = cartridge;
  bus->user_write_callback = NULL;
  bus->user_data = NULL;
}

void bus_write(bus_t *bus, uint16_t address, uint8_t data) {
  if (bus->user_write_callback != NULL) {
    bus->user_write_callback(bus->user_data, address, data);
  }

  // cartridge
  if (address <= CARTRIDGE_ROM_END_ADDRESS) {
    cartridge_write(bus->cartridge, address, data);
    return;
  }

  if (address >= CARTRIDGE_RAM_START_ADDRESS &&
      address <= CARTRIDGE_RAM_END_ADDRESS) {
    cartridge_write(bus->cartridge, address, data);
    return;
  }

  // interrupt controller
  if (address == IF_ADDRESS) {
    bus->interrupt_controller->register_if = data;
    return;
  }
  if (address == IE_ADDRESS) {
    bus->interrupt_controller->register_ie = data;
    return;
  }

  // timer controller
  if (address == DIV_ADDRESS) {
    bus->timer_controller->register_div = 0;
    return;
  }
  if (address == TIMA_ADDRESS) {
    bus->timer_controller->register_tima = data;
    return;
  }
  if (address == TMA_ADDRESS) {
    bus->timer_controller->register_tma = data;
    return;
  }
  if (address == TAC_ADDRESS) {
    bus->timer_controller->register_tac = data;
    return;
  }

  // lcd
  if (address == LCDC_ADDRESS) {
    bus->lcd->register_lcdc = data;
    return;
  }
  if (address == LY_ADDRESS) {
    return;
  }
  if (address == LYC_ADDRESS) {
    bus->lcd->register_lyc = data;
    return;
  }
  if (address == STAT_ADDRESS) {
    bus->lcd->register_stat = data;
    return;
  }

  // ppu
  if (address == SRCX_ADDRESS) {
    bus->ppu->register_scx = data;
    return;
  }
  if (address == SRCY_ADDRESS) {
    bus->ppu->register_scy = data;
    return;
  }
  if (address == WX_ADDRESS) {
    bus->ppu->register_wx = data;
    return;
  }
  if (address == WY_ADDRESS) {
    bus->ppu->register_wy = data;
    return;
  }
  if (address == BGP_ADDRESS) {
    bus->ppu->register_bgp = data;
    return;
  }
  if (address == OBP0_ADDRESS) {
    bus->ppu->register_obp0 = data;
    return;
  }
  if (address == OBP1_ADDRESS) {
    bus->ppu->register_obp1 = data;
    return;
  }
  if (address >= VRAM_ADDRESS && address <= 0x9FFF) {
    bus->ppu->vram[address - VRAM_ADDRESS] = data;
    return;
  }
  if (address == PPU_DMA_ADDRESS) {
    ppu_dma_write(bus->ppu, data);
    return;
  }
  if (address >= OAM_ADDRESS && address <= 0xFE9F) {
    bus->ppu->oam[address - OAM_ADDRESS] = data;
    return;
  }

  // joypad
  if (address == JOYPAD_ADDRESS) {
    joypad_register_write(bus->joypad, data);
    return;
  }

  // work ram
  if (address >= WORK_RAM_START_ADDRESS && address <= WORK_RAM_END_ADDRESS) {
    bus->memory[address] = data;
    return;
  }
  // echo work ram
  if (address >= ECHO_WORK_RAM_START_ADDRESS &&
      address <= ECHO_WORK_RAM_END_ADDRESS) {
    bus->memory[WORK_RAM_START_ADDRESS + address -
                ECHO_WORK_RAM_START_ADDRESS] = data;
    return;
  }

  // high ram
  if (address >= HIGH_RAM_START_ADDRESS && address <= HIGH_RAM_END_ADDRESS) {
    bus->memory[address] = data;
    return;
  }

  // bus->memory[address] = data;
}

uint8_t bus_read(bus_t *bus, uint16_t address) {
  // cartridge
  if (address <= CARTRIDGE_ROM_END_ADDRESS ||
      (address >= CARTRIDGE_RAM_START_ADDRESS &&
       address <= CARTRIDGE_RAM_END_ADDRESS)) {
    return cartridge_read(bus->cartridge, address);
  }

  // interrupt controller
  if (address == IF_ADDRESS) {
    return bus->interrupt_controller->register_if;
  }
  if (address == IE_ADDRESS) {
    return bus->interrupt_controller->register_ie;
  }

  // timer controller
  if (address == DIV_ADDRESS) {
    return bus->timer_controller->register_div;
  }
  if (address == TIMA_ADDRESS) {
    return bus->timer_controller->register_tima;
  }
  if (address == TMA_ADDRESS) {
    return bus->timer_controller->register_tma;
  }
  if (address == TAC_ADDRESS) {
    return bus->timer_controller->register_tac;
  }

  // lcd
  if (address == LCDC_ADDRESS) {
    return bus->lcd->register_lcdc;
  }
  if (address == LY_ADDRESS) {
    return bus->lcd->register_ly;
  }
  if (address == LYC_ADDRESS) {
    return bus->lcd->register_lyc;
  }
  if (address == STAT_ADDRESS) {
    return bus->lcd->register_stat;
  }

  // ppu
  if (address == SRCX_ADDRESS) {
    return bus->ppu->register_scx;
  }
  if (address == SRCY_ADDRESS) {
    return bus->ppu->register_scy;
  }
  if (address == WX_ADDRESS) {
    return bus->ppu->register_wx;
  }
  if (address == WY_ADDRESS) {
    return bus->ppu->register_wy;
  }
  if (address == BGP_ADDRESS) {
    return bus->ppu->register_bgp;
  }
  if (address == OBP0_ADDRESS) {
    return bus->ppu->register_obp0;
  }
  if (address == OBP1_ADDRESS) {
    return bus->ppu->register_obp1;
  }
  if (address >= VRAM_ADDRESS && address < VRAM_ADDRESS + VRAM_LENGTH &&
      address <= 0x9FFF) {
    return bus->ppu->vram[address - VRAM_ADDRESS];
  }
  if (address >= OAM_ADDRESS && address < OAM_ADDRESS + OAM_LENGTH &&
      address <= 0xFE9F) {
    return bus->ppu->oam[address - OAM_ADDRESS];
  }

  // joypad
  if (address == JOYPAD_ADDRESS) {
    return bus->joypad->register_joyp;
  };
  // work ram
  if (address >= WORK_RAM_START_ADDRESS && address <= WORK_RAM_END_ADDRESS) {
    return bus->memory[address];
  }

  // echo work ram
  if (address >= ECHO_WORK_RAM_START_ADDRESS &&
      address <= ECHO_WORK_RAM_END_ADDRESS) {
    return bus->memory[WORK_RAM_START_ADDRESS + address -
                       ECHO_WORK_RAM_START_ADDRESS];
  }

  // high ram
  if (address >= HIGH_RAM_START_ADDRESS && address <= HIGH_RAM_END_ADDRESS) {
    return bus->memory[address];
  }

  // ALU stubs
  if (address == 0xFF10)
    return 0x00;
  if (address == 0xFF11)
    return 0x00;
  if (address == 0xFF12)
    return 0x00;
  if (address == 0xFF13)
    return 0x00;
  if (address == 0xFF14)
    return 0x00;
  if (address == 0xFF16)
    return 0x00;
  if (address == 0xFF17)
    return 0x00;
  if (address == 0xFF18)
    return 0x00;
  if (address == 0xFF19)
    return 0x00;
  if (address == 0xFF1A)
    return 0x00;
  if (address == 0xFF1B)
    return 0x00;
  if (address == 0xFF1C)
    return 0x00;
  if (address == 0xFF1D)
    return 0x00;
  if (address == 0xFF1E)
    return 0x00;
  if (address == 0xFF20)
    return 0x00;
  if (address == 0xFF21)
    return 0x00;
  if (address == 0xFF22)
    return 0x00;
  if (address == 0xFF23)
    return 0x00;
  if (address == 0xFF24)
    return 0x00;
  if (address == 0xFF25)
    return 0x00;
  if (address == 0xFF26)
    return 0x00;
  return bus->memory[address];
}
