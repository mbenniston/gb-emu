import { createContext, useContext } from "react";
import GBEmu from "../gbemu";

export type EmulatorContext = {
  emulator: GBEmu.Emulator;
};

export const emulatorContext = createContext<EmulatorContext | null>(null);

export function useEmulator() {
  const context = useContext(emulatorContext);
  if (!context) throw new Error("useGBEmu: useGBEmu");
  return context;
}
