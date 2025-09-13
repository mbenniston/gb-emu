export default GBEmu;
declare function GBEmu<T>(target?: T): Promise<T & typeof GBEmu>;
declare module GBEmu {
    function destroy(obj: any): void;
    function _malloc(size: number): number;
    function _free(ptr: number): void;
    function wrapPointer<C extends new (...args: any) => any>(ptr: number, Class: C): InstanceType<C>;
    function getPointer(obj: unknown): number;
    function castObject<C extends new (...args: any) => any>(object: unknown, Class: C): InstanceType<C>;
    function compare(object1: unknown, object2: unknown): boolean;
    const HEAP8: Int8Array;
    const HEAP16: Int16Array;
    const HEAP32: Int32Array;
    const HEAPU8: Uint8Array;
    const HEAPU16: Uint16Array;
    const HEAPU32: Uint32Array;
    const HEAPF32: Float32Array;
    const HEAPF64: Float64Array;
    class JoypadState {
        constructor();
        get_selectPressed(): boolean;
        set_selectPressed(selectPressed: boolean): void;
        selectPressed: boolean;
        get_startPressed(): boolean;
        set_startPressed(startPressed: boolean): void;
        startPressed: boolean;
        get_downPressed(): boolean;
        set_downPressed(downPressed: boolean): void;
        downPressed: boolean;
        get_upPressed(): boolean;
        set_upPressed(upPressed: boolean): void;
        upPressed: boolean;
        get_leftPressed(): boolean;
        set_leftPressed(leftPressed: boolean): void;
        leftPressed: boolean;
        get_rightPressed(): boolean;
        set_rightPressed(rightPressed: boolean): void;
        rightPressed: boolean;
        get_aPressed(): boolean;
        set_aPressed(aPressed: boolean): void;
        aPressed: boolean;
        get_bPressed(): boolean;
        set_bPressed(bPressed: boolean): void;
        bPressed: boolean;
    }
    class DebugCPUState {
        constructor();
        get_AF(): number;
        set_AF(AF: number): void;
        AF: number;
        get_BC(): number;
        set_BC(BC: number): void;
        BC: number;
        get_DE(): number;
        set_DE(DE: number): void;
        DE: number;
        get_HL(): number;
        set_HL(HL: number): void;
        HL: number;
        get_PC(): number;
        set_PC(PC: number): void;
        PC: number;
        get_SP(): number;
        set_SP(SP: number): void;
        SP: number;
    }
    class DebugTimerControllerState {
        get_div(): number;
        set_div(div: number): void;
        div: number;
        get_tima(): number;
        set_tima(tima: number): void;
        tima: number;
        get_tma(): number;
        set_tma(tma: number): void;
        tma: number;
        get_tac(): number;
        set_tac(tac: number): void;
        tac: number;
        get_tac_enabled(): boolean;
        set_tac_enabled(tac_enabled: boolean): void;
        tac_enabled: boolean;
        get_tac_increment(): number;
        set_tac_increment(tac_increment: number): void;
        tac_increment: number;
    }
    class DebugInstruction {
        constructor();
        get_mnemonic(): string;
        set_mnemonic(mnemonic: string): void;
        mnemonic: string;
        get_opcode(): number;
        set_opcode(opcode: number): void;
        opcode: number;
        get_isPrefix(): boolean;
        set_isPrefix(isPrefix: boolean): void;
        isPrefix: boolean;
    }
    class DebugInstructionTable {
        get_instructions(index: number): DebugInstruction;
        set_instructions(index: number, instructions: DebugInstruction): void;
        instructions: DebugInstruction;
        get_instructions_length(): number;
        set_instructions_length(instructions_length: number): void;
        instructions_length: number;
        get_extended_instructions(index: number): DebugInstruction;
        set_extended_instructions(index: number, extended_instructions: DebugInstruction): void;
        extended_instructions: DebugInstruction;
        get_extended_instructions_length(): number;
        set_extended_instructions_length(extended_instructions_length: number): void;
        extended_instructions_length: number;
    }
    class DebugMemoryDump {
        get_data(index: number): number;
        set_data(index: number, data: number): void;
        data: number;
        get_data_length(): number;
        set_data_length(data_length: number): void;
        data_length: number;
    }
    class DebugTileSetDump {
        get_data(index: number): number;
        set_data(index: number, data: number): void;
        data: number;
        get_data_length(): number;
        set_data_length(data_length: number): void;
        data_length: number;
        get_width(): number;
        set_width(width: number): void;
        width: number;
        get_height(): number;
        set_height(height: number): void;
        height: number;
        get_channels(): number;
        set_channels(channels: number): void;
        channels: number;
    }
    class DebugBreakpoints {
        constructor(length: number);
        get_breakpoints(index: number): number;
        set_breakpoints(index: number, breakpoints: number): void;
        breakpoints: number;
        get_breakpoints_length(): number;
        set_breakpoints_length(breakpoints_length: number): void;
        breakpoints_length: number;
    }
    class DebugInterruptsState {
        get_ime(): boolean;
        set_ime(ime: boolean): void;
        ime: boolean;
        get_register_if(): number;
        set_register_if(register_if: number): void;
        register_if: number;
        get_register_ie(): number;
        set_register_ie(register_ie: number): void;
        register_ie: number;
        get_joypad_requested(): boolean;
        set_joypad_requested(joypad_requested: boolean): void;
        joypad_requested: boolean;
        get_serial_requested(): boolean;
        set_serial_requested(serial_requested: boolean): void;
        serial_requested: boolean;
        get_timer_requested(): boolean;
        set_timer_requested(timer_requested: boolean): void;
        timer_requested: boolean;
        get_lcd_requested(): boolean;
        set_lcd_requested(lcd_requested: boolean): void;
        lcd_requested: boolean;
        get_vblank_requested(): boolean;
        set_vblank_requested(vblank_requested: boolean): void;
        vblank_requested: boolean;
        get_joypad_enabled(): boolean;
        set_joypad_enabled(joypad_enabled: boolean): void;
        joypad_enabled: boolean;
        get_serial_enabled(): boolean;
        set_serial_enabled(serial_enabled: boolean): void;
        serial_enabled: boolean;
        get_timer_enabled(): boolean;
        set_timer_enabled(timer_enabled: boolean): void;
        timer_enabled: boolean;
        get_lcd_enabled(): boolean;
        set_lcd_enabled(lcd_enabled: boolean): void;
        lcd_enabled: boolean;
        get_vblank_enabled(): boolean;
        set_vblank_enabled(vblank_enabled: boolean): void;
        vblank_enabled: boolean;
    }
    class Emulator {
        constructor(data: ReadonlyArray<number>, data_length: number);
        tick(joypadState: JoypadState): void;
        tick_single(): void;
        get_framebuffer_ptr(): unknown;
        get_framebuffer_width(): number;
        get_framebuffer_height(): number;
        get_framebuffer_channels(): number;
        debug_tick(joypadState: JoypadState): number;
        get_debug_cpu_state(): DebugCPUState;
        get_debug_timer_controller_state(): DebugTimerControllerState;
        get_debug_interrupts_state(): DebugInterruptsState;
        get_debug_instruction_table(): DebugInstructionTable;
        get_debug_memory_max(): number;
        get_debug_dump_memory_range(range_start: number, range_length: number): DebugMemoryDump;
        get_debug_dump_tileset(): DebugTileSetDump;
        get_debug_breakpoints(): DebugBreakpoints;
        set_debug_breakpoints(breakpoints: DebugBreakpoints): void;
    }
}