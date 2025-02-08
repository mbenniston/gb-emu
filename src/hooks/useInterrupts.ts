import { useGBEmu } from "../context/GBEmuContext.tsx";
import { useEmulator } from "../context/EmulatorContext.tsx";
import { useQuery } from "@tanstack/react-query";
import { useDebugRefetchInterval } from "@/hooks/useDebugRefetchInterval.ts";

export function useInterrupts() {
  const { module } = useGBEmu();
  const { emulator } = useEmulator();
  const refetchInterval = useDebugRefetchInterval();

  return useQuery({
    refetchInterval,
    queryKey: ["deubg", "panels", "interrupts"],
    queryFn: () => {
      const cpu_state = emulator.get_debug_interrupts_state();
      const {
        ime,
        register_if,
        register_ie,
        joypad_requested,
        serial_requested,
        timer_requested,
        lcd_requested,
        vblank_requested,
        joypad_enabled,
        serial_enabled,
        timer_enabled,
        lcd_enabled,
        vblank_enabled,
      } = cpu_state;
      module.destroy(cpu_state);
      return {
        ime,
        register_if,
        register_ie,
        joypad_requested,
        serial_requested,
        timer_requested,
        lcd_requested,
        vblank_requested,
        joypad_enabled,
        serial_enabled,
        timer_enabled,
        lcd_enabled,
        vblank_enabled,
      };
    },
  });
}
