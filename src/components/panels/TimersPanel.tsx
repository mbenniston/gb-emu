import { useState } from "react";
import {
  Panel,
  PanelBody,
  PanelContent,
  PanelHeader,
} from "@/components/Panel.tsx";
import { useTimers } from "@/hooks/useTimers.ts";
import {
  EditRegisterRow,
  ViewModeSelectButton,
} from "@/components/panels/CPURegistersPanel.tsx";

type ViewMode = "decimal" | "hexadecimal";

export function TimersPanel() {
  const registersQuery = useTimers();
  const [viewMode, setViewMode] = useState<ViewMode>("hexadecimal");

  if (!registersQuery.data) return;

  const registers = registersQuery.data;

  return (
    <Panel className={"col-span-2 row-span-2"}>
      <PanelContent>
        <PanelHeader>Timers</PanelHeader>
        <PanelBody>
          <ViewModeSelect viewMode={viewMode} onSelectViewMode={setViewMode} />
          <div className="p-0.5" />
          <fieldset className="flex flex-col w-full gap-1">
            <EditRegisterRow
              register="DIV"
              value={registers.div}
              viewMode={viewMode}
            />
            <EditRegisterRow
              register="TIMA"
              value={registers.tima}
              viewMode={viewMode}
            />
            <EditRegisterRow
              register="TMA"
              value={registers.tma}
              viewMode={viewMode}
            />
            <EditRegisterRow
              register="TAC"
              value={registers.tac}
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
