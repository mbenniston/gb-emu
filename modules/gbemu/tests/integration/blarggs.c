#include "../../../../deps/unity/src/unity.h"
#include "emulator.h"

#include <stdlib.h>
#include <string.h>

void run_test_rom(const char *path, const char *expected_serial);

void blarggs_inst_01(void) {
  run_test_rom(ROMS_LOCATION "01-special.gb", "01-special\n\n\nPassed\n");
}

void blarggs_inst_02(void) {
  run_test_rom(ROMS_LOCATION "02-interrupts.gb", "02-interrupts\n\n\nPassed\n");
}

void blarggs_inst_03(void) {
  run_test_rom(ROMS_LOCATION "03-op sp,hl.gb", "03-op sp,hl\n\n\nPassed\n");
}

void blarggs_inst_04(void) {
  run_test_rom(ROMS_LOCATION "04-op r,imm.gb", "04-op r,imm\n\n\nPassed\n");
}

void blarggs_inst_05(void) {
  run_test_rom(ROMS_LOCATION "05-op rp.gb", "05-op rp\n\n\nPassed\n");
}

void blarggs_inst_06(void) {
  run_test_rom(ROMS_LOCATION "06-ld r,r.gb", "06-ld r,r\n\n\nPassed\n");
}

void blarggs_inst_07(void) {
  run_test_rom(ROMS_LOCATION "07-jr,jp,call,ret,rst.gb",
               "07-jr,jp,call,ret,rst\n\n\nPassed\n");
}

void blarggs_inst_08(void) {
  run_test_rom(ROMS_LOCATION "08-misc instrs.gb",
               "08-misc instrs\n\n\nPassed\n");
}

void blarggs_inst_09(void) {
  run_test_rom(ROMS_LOCATION "09-op r,r.gb", "09-op r,r\n\n\nPassed\n");
}

void blarggs_inst_10(void) {
  run_test_rom(ROMS_LOCATION "10-bit ops.gb", "10-bit ops\n\n\nPassed\n");
}

void blarggs_inst_11(void) {
  run_test_rom(ROMS_LOCATION "11-op a,(hl).gb", "11-op a,(hl)\n\n\nPassed\n");
}

int main(void) {
  UNITY_BEGIN();

  RUN_TEST(blarggs_inst_01);
  RUN_TEST(blarggs_inst_02);
  RUN_TEST(blarggs_inst_03);
  RUN_TEST(blarggs_inst_04);
  RUN_TEST(blarggs_inst_05);
  RUN_TEST(blarggs_inst_06);
  RUN_TEST(blarggs_inst_07);
  RUN_TEST(blarggs_inst_08);
  RUN_TEST(blarggs_inst_09);
  RUN_TEST(blarggs_inst_10);
  RUN_TEST(blarggs_inst_11);

  return UNITY_END();
}

#define MAX_CYCLES 20000000

cartridge_t *load_rom(const char *path) {
  FILE *rom = fopen(path, "rb");
  fseek(rom, 0, SEEK_END);
  int length = ftell(rom);
  fseek(rom, 0, SEEK_SET);
  uint8_t *buffer = (uint8_t *)malloc(length);
  fread(buffer, 1, length, rom);
  fclose(rom);

  cartridge_t *cart = malloc(sizeof(cartridge_t));
  cartridge_load(cart, buffer, length);
  free(buffer);
  return cart;
}

typedef struct {
  emulator_t *emulator;
  int serial_buffer_length;
  char serial_buffer[256];
} test_context_t;

void setUp(void) {}

void tearDown(void) {}

static void callback_hook(void *user, uint16_t address, uint8_t data) {
  if (address == 0xFF01) {
    test_context_t *test_context = user;
    test_context->emulator->bus.memory[0xFF01] = data;
  }

  if (address == 0xFF02 && data == 0x81) {
    test_context_t *test_context = user;

    if (test_context->serial_buffer_length == 256) {
      TEST_FAIL();
    }
    char character = test_context->emulator->bus.memory[0xFF01];
    test_context->serial_buffer[test_context->serial_buffer_length++] =
        character;
  }
}

void run_test_rom(const char *path, const char *expected_serial) {
  cartridge_t *rom = load_rom(path);
  test_context_t context;
  emulator_t emulator;
  emulator_create(&emulator, rom);

  context.emulator = &emulator;
  context.serial_buffer_length = 0;
  emulator.bus.user_write_callback = callback_hook;
  emulator.bus.user_data = &context;
  memset(context.serial_buffer, 0, sizeof(context.serial_buffer));

  int cycles;
  int total_cycles = 0;
  int expected_length = strlen(expected_serial);
  while (memcmp(context.serial_buffer, expected_serial, expected_length) != 0) {
    emulator_step(&emulator, (joypad_state_t){.a_pressed = 0}, &cycles);
    total_cycles += cycles;
    if (total_cycles >= MAX_CYCLES) {
      TEST_FAIL_MESSAGE("Exceeded maximum amount of cycles");
    }
  }

  cartridge_destroy(rom);
  free(rom);
}