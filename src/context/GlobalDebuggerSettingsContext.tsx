import { createContext, Dispatch, SetStateAction } from "react";
import { updateFrequencyOptions } from "@/context/updateFrequencyOptions.ts";

export type GlobalDebuggerSettings = {
  updateFrequency:
    | (typeof updateFrequencyOptions)[number]["value"]
    | "no-update"
    | "every-frame";
};

export const globalDebuggerSettingsContext = createContext<{
  settings: GlobalDebuggerSettings;
  setSettings: Dispatch<SetStateAction<GlobalDebuggerSettings>>;
}>({
  settings: { updateFrequency: "no-update" },
  setSettings: () => {},
});
