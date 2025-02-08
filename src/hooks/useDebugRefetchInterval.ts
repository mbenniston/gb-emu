import { useGlobalDebuggerSettings } from "@/context/GlobalDebuggerSettingsContext.tsx";

export function useDebugRefetchInterval() {
  const {
    settings: { updateFrequency },
  } = useGlobalDebuggerSettings();

  return typeof updateFrequency === "number" ? updateFrequency : undefined;
}
