import { ReactNode, useState } from "react";
import {
  GlobalDebuggerSettings,
  globalDebuggerSettingsContext,
} from "@/context/GlobalDebuggerSettingsContext.tsx";

export function GlobalDebuggerSettingsProvider({
  children,
}: {
  children?: ReactNode;
}) {
  const [settings, setSettings] = useState<GlobalDebuggerSettings>({
    updateFrequency: 500,
  });

  return (
    <globalDebuggerSettingsContext.Provider value={{ settings, setSettings }}>
      {children}
    </globalDebuggerSettingsContext.Provider>
  );
}
