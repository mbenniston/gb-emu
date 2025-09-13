import { useGBEmu } from "../context/GBEmuContext.tsx";
import { useEmulator } from "../context/EmulatorContext.tsx";
import { useQuery } from "@tanstack/react-query";
import { useDebugRefetchInterval } from "@/hooks/useDebugRefetchInterval.ts";

export function useCPURegisters() {
  const { module } = useGBEmu();
  const { emulator } = useEmulator();
  const refetchInterval = useDebugRefetchInterval();

  return useQuery({
    refetchInterval,
    queryKey: ["debug", "panels", "cpu-registers"],
    queryFn: () => {
      const cpu_state = emulator.get_debug_cpu_state();
      const { SP, PC, AF, BC, DE, HL } = cpu_state;
      module.destroy(cpu_state);
      return { SP, PC, AF, BC, DE, HL };
    },
  });
}
