import { ReactNode } from "react";

export function PanelGrid({ children }: { children?: ReactNode }) {
  return (
    <div className="w-fit mx-auto grid grid-cols-[repeat(10,7rem)] grid-rows-[repeat(100,7rem)] gap-3">
      {children}
    </div>
  );
}
