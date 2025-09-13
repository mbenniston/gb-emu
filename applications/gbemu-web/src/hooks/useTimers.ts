import { useGBEmu } from "../context/GBEmuContext.tsx";
import { useEmulator } from "../context/EmulatorContext.tsx";
import { useQuery } from "@tanstack/react-query";
import { useDebugRefetchInterval } from "@/hooks/useDebugRefetchInterval.ts";

export function useTimers() {
  const { module } = useGBEmu();
  const { emulator } = useEmulator();
  const refetchInterval = useDebugRefetchInterval();

  return useQuery({
    refetchInterval,
    queryKey: ["debug", "panels", "timers"],
    queryFn: () => {
      const cpu_state = emulator.get_debug_timer_controller_state();
      const { div, tac, tima, tma, tac_enabled, tac_increment } = cpu_state;
      module.destroy(cpu_state);
      return { div, tac, tima, tma, tac_enabled, tac_increment };
    },
  });
}
