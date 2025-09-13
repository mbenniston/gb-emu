import { useGBEmu } from "../context/GBEmuContext.tsx";
import { useEmulator } from "../context/EmulatorContext.tsx";
import { useMutation, useQuery, useQueryClient } from "@tanstack/react-query";

export function useBreakpoints() {
  const { module } = useGBEmu();
  const { emulator } = useEmulator();

  return useQuery({
    queryKey: ["breakpoints"],
    queryFn: () => {
      const debugBreakpoints = emulator.get_debug_breakpoints();
      const breakpoints = new Array<number>(
        debugBreakpoints.breakpoints_length,
      );
      for (let i = 0; i < debugBreakpoints.breakpoints_length; i++) {
        breakpoints[i] = debugBreakpoints.get_breakpoints(i);
      }
      module.destroy(debugBreakpoints);
      return breakpoints;
    },
  });
}

export function useUpdateBreakpoints() {
  const { module } = useGBEmu();
  const { emulator } = useEmulator();
  const queryClient = useQueryClient();

  return useMutation({
    mutationFn: ({ breakpoints }: { breakpoints: number[] }) => {
      const debugBreakpoints = new module.DebugBreakpoints(breakpoints.length);

      for (let i = 0; i < breakpoints.length; i++) {
        debugBreakpoints.set_breakpoints(i, breakpoints[i]);
      }

      emulator.set_debug_breakpoints(debugBreakpoints);

      module.destroy(debugBreakpoints);

      return Promise.resolve();
    },
    onSettled: () => {
      void queryClient.invalidateQueries({ queryKey: ["breakpoints"] });
    },
  });
}
