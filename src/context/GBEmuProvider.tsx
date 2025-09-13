import { ReactNode, useEffect, useState } from "react";
import GBEmu from "@/gbemu";
import { gBEmuContext } from "@/context/GBEmuContext.tsx";
import gbemuWasm from "../gbemu.wasm?url";

export function GBEmuProvider({ children }: { children?: ReactNode }) {
  const [emulator, setEmulator] = useState<typeof GBEmu | null>(null);

  useEffect(() => {
    async function initModule() {
      const module = await GBEmu({
        locateFile(path: string, prefix: string) {
          if (path === "gbemu.wasm") {
            return gbemuWasm;
          }
          return prefix + path;
        },
      });
      setEmulator(module);
    }

    void initModule();
  }, []);

  if (emulator === null) return null;

  return (
    <gBEmuContext.Provider value={{ module: emulator }}>
      {children}
    </gBEmuContext.Provider>
  );
}
