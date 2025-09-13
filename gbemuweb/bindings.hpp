#pragma once
#include <vector>

#include "gbemu.hpp"

struct JoypadState {
  bool selectPressed;
  bool startPressed;
  bool downPressed;
  bool upPressed;
  bool leftPressed;
  bool rightPressed;
  bool aPressed;
  bool bPressed;
};

struct DebugCPUState {
  int AF;
  int BC;
  int DE;
  int HL;
  int PC;
  int SP;
};

struct DebugTimerControllerState {
  int div;
  char tima;
  char tma;
  char tac;
  bool tac_enabled;
  int tac_increment;
};

struct DebugInstruction {
  char *mnemonic;
  int opcode;
  bool isPrefix;

  ~DebugInstruction();
};

struct DebugInstructionTable {
  DebugInstruction **instructions;
  int instructions_length;

  DebugInstruction **extended_instructions;
  int extended_instructions_length;

  ~DebugInstructionTable();
};

struct DebugMemoryDump {
  char *data;
  int data_length;

  ~DebugMemoryDump();
};

struct DebugTileSetDump {
  char *data;
  int data_length;
  int width;
  int height;
  int channels;

  DebugTileSetDump();

  ~DebugTileSetDump();
};

struct DebugBreakpoints {
  int *breakpoints;
  int breakpoints_length;

  DebugBreakpoints(int length);

  ~DebugBreakpoints();
};
struct DebugInterruptsState {
  bool ime;
  char register_if;
  char register_ie;
  bool joypad_requested;
  bool serial_requested;
  bool timer_requested;
  bool lcd_requested;
  bool vblank_requested;
  bool joypad_enabled;
  bool serial_enabled;
  bool timer_enabled;
  bool lcd_enabled;
  bool vblank_enabled;
};

class Emulator {
public:
  Emulator(char *data, int data_length);

  void tick(JoypadState *joypadState);

  void tick_single();

  void *get_framebuffer_ptr();

  int get_framebuffer_width();

  int get_framebuffer_height();

  int get_framebuffer_channels();

  int debug_tick(JoypadState *joypadState);

  DebugCPUState *get_debug_cpu_state();
  DebugTimerControllerState *get_debug_timer_controller_state();
  DebugInterruptsState *get_debug_interrupts_state();
  DebugInstructionTable *get_debug_instruction_table();

  int get_debug_memory_max();

  DebugMemoryDump *get_debug_dump_memory_range(long range_start,
                                               long range_length);

  DebugBreakpoints *get_debug_breakpoints();

  void set_debug_breakpoints(DebugBreakpoints *breakpoints);

  /* Dumps image of tile set */
  DebugTileSetDump *get_debug_dump_tileset();

private:
  emulator_t emulator;
  cartridge_t cartridge;

  std::vector<uint16_t> breakpoints;
};
