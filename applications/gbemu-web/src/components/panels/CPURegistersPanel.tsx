import { ReactNode, useEffect, useState } from "react";
import clsx from "clsx";
import { useCPURegisters } from "@/hooks/useCPURegisters.ts";
import {
  Panel,
  PanelBody,
  PanelContent,
  PanelHeader,
} from "@/components/Panel.tsx";

type ViewMode = "decimal" | "hexadecimal";

export function CPURegistersPanel() {
  const registersQuery = useCPURegisters();
  const [viewMode, setViewMode] = useState<ViewMode>("hexadecimal");

  if (!registersQuery.data) return;

  const registers = registersQuery.data;

  return (
    <Panel className={"col-span-2 row-span-2"}>
      <PanelContent>
        <PanelHeader>Registers</PanelHeader>
        <PanelBody>
          <ViewModeSelect viewMode={viewMode} onSelectViewMode={setViewMode} />
          <div className="p-0.5" />
          <fieldset className="flex flex-col w-full gap-1">
            <EditRegisterRow
              register="AF"
              value={registers.AF}
              viewMode={viewMode}
            />
            <EditRegisterRow
              register="BC"
              value={registers.BC}
              viewMode={viewMode}
            />
            <EditRegisterRow
              register="DE"
              value={registers.DE}
              viewMode={viewMode}
            />
            <EditRegisterRow
              register="HL"
              value={registers.HL}
              viewMode={viewMode}
            />
            <EditRegisterRow
              register="PC"
              value={registers.PC}
              viewMode={viewMode}
            />
            <EditRegisterRow
              register="SP"
              value={registers.SP}
              viewMode={viewMode}
            />
          </fieldset>
        </PanelBody>
      </PanelContent>
    </Panel>
  );
}

function ViewModeSelect({
  viewMode,
  onSelectViewMode,
}: {
  viewMode: ViewMode;
  onSelectViewMode: (vm: ViewMode) => void;
}) {
  return (
    <div role="radiogroup" className="text-sm flex gap-1">
      <ViewModeSelectButton
        selected={viewMode === "hexadecimal"}
        onClick={() => {
          onSelectViewMode("hexadecimal");
        }}
      >
        Hex
      </ViewModeSelectButton>
      <ViewModeSelectButton
        selected={viewMode === "decimal"}
        onClick={() => {
          onSelectViewMode("decimal");
        }}
      >
        Dec
      </ViewModeSelectButton>
    </div>
  );
}

export function ViewModeSelectButton({
  children,
  selected,
  onClick,
}: {
  selected?: boolean;
  onClick: () => void;
  children?: ReactNode;
}) {
  return (
    <div
      role="radio"
      aria-checked={selected}
      className={clsx("btn btn-xs", selected ? "btn-primary" : "btn-outline")}
      onClick={onClick}
    >
      {children}
    </div>
  );
}

export function EditRegisterRow({
  register,
  value,
  viewMode,
}: {
  register: string;
  value: number;
  viewMode: ViewMode;
}) {
  const [prev, setPrev] = useState(value);
  const [recentlyChanged, setRecentlyChanged] = useState(false);

  useEffect(() => {
    if (prev !== value) {
      const timeout = setTimeout(() => {
        setRecentlyChanged(false);
      }, 250);
      setRecentlyChanged(true);
      setPrev(prev);
      return () => {
        clearTimeout(timeout);
      };
    }
  }, [prev, value]);

  const valueString = value.toString(viewMode === "hexadecimal" ? 16 : 10);

  return (
    <label className="flex gap-2">
      <input
        size={4}
        inputMode="numeric"
        className={clsx(
          "input input-xs pl-2 flex-grow transition-colors ease-out min-w-0 w-auto max-w-full rounded text-sm",
          recentlyChanged
            ? "bg-secondary text-secondary-content duration-75"
            : "duration-200",
        )}
        value={
          viewMode === "hexadecimal"
            ? valueString.padStart(4, "0")
            : valueString
        }
        readOnly
      />
      <div className="uppercase flex-shrink-0">{register}</div>
    </label>
  );
}
