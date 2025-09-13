import { useContext } from "react";
import { globalDebuggerSettingsContext } from "@/context/GlobalDebuggerSettingsContext.tsx";

export function useGlobalDebuggerSettings() {
  return useContext(globalDebuggerSettingsContext);
}
