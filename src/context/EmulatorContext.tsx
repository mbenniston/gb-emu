import {
  createContext,
  ReactNode,
  useContext,
  useEffect,
  useState,
} from "react";
import GBEmu from "../gbemu";
import { useGBEmu } from "./GBEmuContext.tsx";

export type EmulatorContext = {
  emulator: GBEmu.Emulator;
};

export const emulatorContext = createContext<EmulatorContext | null>(null);

export function useEmulator() {
  const context = useContext(emulatorContext);
  if (!context) throw new Error("useGBEmu: useGBEmu");
  return context;
}

export function EmulatorProvider({
  cartridgeData,
  children,
}: {
  cartridgeData: Uint8Array;
  children?: ReactNode;
}) {
  const { module } = useGBEmu();
  const [emulator, setEmulator] = useState<GBEmu.Emulator | null>(null);

  useEffect(() => {
    const currentModule = module;
    const newEmulator = new module.Emulator(
      [...cartridgeData],
      cartridgeData.byteLength,
    );
    setEmulator(newEmulator);
    return () => {
      currentModule.destroy(newEmulator);
    };
  }, [cartridgeData]);

  if (emulator === null) return null;

  return (
    <emulatorContext.Provider value={{ emulator }}>
      {children}
    </emulatorContext.Provider>
  );
}
