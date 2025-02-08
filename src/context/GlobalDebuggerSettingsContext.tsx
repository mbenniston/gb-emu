import {
  createContext,
  Dispatch,
  ReactNode,
  SetStateAction,
  useContext,
  useState,
} from "react";

export const updateFrequencyOptions = [
  { title: "Disabled", value: "no-update" },
  {
    title: "100ms",
    value: 100,
  },
  {
    title: "300ms",
    value: 300,
  },
  {
    title: "500ms",
    value: 500,
  },
  { title: "1000ms", value: 1000 },
  { title: "2000ms", value: 2000 },
  { title: "Every frame", value: "every-frame" },
] as const;

export type GlobalDebuggerSettings = {
  updateFrequency:
    | (typeof updateFrequencyOptions)[number]["value"]
    | "no-update"
    | "every-frame";
};

const globalDebuggerSettingsContext = createContext<{
  settings: GlobalDebuggerSettings;
  setSettings: Dispatch<SetStateAction<GlobalDebuggerSettings>>;
}>({
  settings: { updateFrequency: "no-update" },
  setSettings: () => {},
});

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

export function useGlobalDebuggerSettings() {
  const context = useContext(globalDebuggerSettingsContext);
  if (context == null) {
    throw new Error("No global debugger settings");
  }
  return context;
}
