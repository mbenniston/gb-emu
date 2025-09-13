import { useGlobalDebuggerSettings } from "@/context/useGlobalDebuggerSettings.ts";

export function useDebugRefetchInterval() {
  const {
    settings: { updateFrequency },
  } = useGlobalDebuggerSettings();

  return typeof updateFrequency === "number" ? updateFrequency : undefined;
}
