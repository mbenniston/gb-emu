import { useState } from "react";
import {
  Panel,
  PanelBody,
  PanelContent,
  PanelHeader,
} from "@/components/Panel.tsx";
import { useInterrupts } from "@/hooks/useInterrupts.ts";
import {
  EditRegisterRow,
  ViewModeSelectButton,
} from "@/components/panels/CPURegistersPanel.tsx";

type ViewMode = "decimal" | "hexadecimal";

export function InterruptsPanel() {
  const registersQuery = useInterrupts();
  const [viewMode, setViewMode] = useState<ViewMode>("hexadecimal");

  if (!registersQuery.data) return;

  const registers = registersQuery.data;

  return (
    <Panel className={"col-span-2 row-span-2"}>
      <PanelContent>
        <PanelHeader>Interrupts</PanelHeader>
        <PanelBody>
          <ViewModeSelect viewMode={viewMode} onSelectViewMode={setViewMode} />
          <div className="p-0.5" />
          <fieldset className="flex flex-col w-full gap-1">
            <EditRegisterRow
              register="IME"
              value={registers.ime}
              viewMode={viewMode}
            />
            <EditRegisterRow
              register="IE"
              value={registers.register_ie}
              viewMode={viewMode}
            />
            <EditRegisterRow
              register="IF"
              value={registers.register_if}
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
