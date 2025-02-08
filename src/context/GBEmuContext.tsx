import {
  createContext,
  ReactNode,
  useContext,
  useEffect,
  useState,
} from "react";
import GBEmu from "../gbemu";
import gbemuWasm from "../gbemu.wasm?url";

export type GBEmuContext = {
  module: typeof GBEmu;
};

export const gBEmuContext = createContext<GBEmuContext | null>(null);

export function useGBEmu() {
  const context = useContext(gBEmuContext);
  if (!context) throw new Error("useGBEmu: useGBEmu");
  return context;
}

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
