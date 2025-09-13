import { createContext, useContext } from "react";
import GBEmu from "../gbemu";

export type GBEmuContext = {
  module: typeof GBEmu;
};

export const gBEmuContext = createContext<GBEmuContext | null>(null);

export function useGBEmu() {
  const context = useContext(gBEmuContext);
  if (!context) throw new Error("useGBEmu: useGBEmu");
  return context;
}
