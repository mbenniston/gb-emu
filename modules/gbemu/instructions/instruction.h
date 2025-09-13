#ifndef GBEMU_INSTRUCTION_H
#define GBEMU_INSTRUCTION_H

#include "../bus.h"
#include "../cpu.h"

typedef struct {
  /* Other timing information or state changes like invoking dma */
  int cycle_count;
} instruction_result_t;

typedef instruction_result_t (*instruction_handler_t)(cpu_t *, bus_t *);

typedef struct {
  const char *name;
  instruction_handler_t handler;
} instruction_t;

#endif
