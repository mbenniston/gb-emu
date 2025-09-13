import { ReactNode, useEffect, useState } from "react";
import { useGBEmu } from "@/context/GBEmuContext.tsx";
import GBEmu from "@/gbemu";
import { emulatorContext } from "@/context/EmulatorContext.tsx";

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
  }, [cartridgeData, module]);

  if (emulator === null) return null;

  return (
    <emulatorContext.Provider value={{ emulator }}>
      {children}
    </emulatorContext.Provider>
  );
}
