# GB-EMU (React + TypeScript + C/C++ (Emscripten))

A GameBoy emulator for the web written in C and compiled into Web Assembly using Emscripten (see Dockerfile for
compilation steps).

Passes all the Blarggs test roms for CPU instructions.

This project is purely for educational purposes and has a lot of inaccuracies.

Demo hosted at: https://gameboy.m4dx.com/

## Features

- No MBC and MBC3 support
- Scanline graphics renderer
- Widget based debugger with support for visualizing:
    - CPU registers
    - VRAM
    - Disassembled memory
    - Interrupts state
    - Timer state
    - Memory state
- PWA frontend with offline support

## Implementation details

- `/gbemu` C source code of the emulator. Designed to be able to be used independently of the front end.
- `/gbemuweb` C++ bindings used for typesafe communication between C and JavaScript. Types and bindings are generated
  from a `.idl` file.
- `/src` React front end for the application. Uses Tailwind and DaisyUI for styles along with VitePWA for PWA support.

## Screenshots

![Debugger](./docs/screenshot-1.PNG)

## Upcoming enhancements

- Saving and loading cartridge ram saves ('.sav')
- Cartridge widget
- Audio support
- Accurate FIFO PPU renderer
- Various hardware bugs
- Cloud saves (via optional third party sign-in)

## Source material

- [Pandocs](https://gbdev.io/pandocs), Incredible resource for emulator development.
- [Blarggs test roms](https://github.com/retrio/gb-test-roms), Test ROMs that were extremely useful for implementing the
  CPU before any other components where implemented using the serial interface.
- [GBDev Opcodes table](https://gbdev.io/gb-opcodes/optables/), For quickly checking instruction machine cycles.
- [RGDBS](https://rgbds.gbdev.io/docs/v0.9.0), For working out what each instruction does.
- [BGB emulator](https://bgb.bircd.org/), For single step debugging. 