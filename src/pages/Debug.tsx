import { useEffect, useRef, useState } from "react";
import { EmulatorProvider } from "@/context/EmulatorContext.tsx";
import { PanelGrid } from "@/components/PanelGrid.tsx";
import { Panel } from "@/components/Panel.tsx";
import { useUpdateBreakpoints } from "@/hooks/useBreakpoints.ts";
import { ControlsPanel } from "@/components/panels/ControlsPanel.tsx";
import { DisassemblyPanel } from "@/components/panels/DisassemblyPanel.tsx";
import { TileDataPanel } from "@/components/panels/TileDataPanel.tsx";
import { useGameboy } from "@/hooks/useGameboy.ts";
import { CPURegistersPanel } from "@/components/panels/CPURegistersPanel.tsx";
import { TimersPanel } from "@/components/panels/TimersPanel.tsx";
import { MemoryPanel } from "@/components/panels/MemoryPanel.tsx";
import { InterruptsPanel } from "@/components/panels/InterruptsPanel.tsx";
import { GlobalDebuggerSettingsProvider } from "@/context/GlobalDebuggerSettingsContext.tsx";
import { FrequencyChangeButton } from "@/components/FrequencyChangeButton.tsx";

export function Debug() {
  const [cartridgeData, setCartridgeData] = useState<Uint8Array | null>(null);

  return (
    <GlobalDebuggerSettingsProvider>
      {!cartridgeData && (
        <div className="flex h-dvh items-center justify-center">
          <label className="form-control w-full max-w-xs">
            <div className="label">
              <span className="label-text">Select a ROM</span>
            </div>
            <input
              accept=".gb"
              type="file"
              className="file-input file-input-bordered w-full max-w-xs"
              onChange={(e) => {
                const file = e.target?.files?.[0];
                if (!file) return;
                const loadFile = async () => {
                  const data = await file.arrayBuffer();
                  const buffer = new Uint8Array(data);
                  setCartridgeData(buffer);
                };
                void loadFile();
              }}
            />
          </label>
        </div>
      )}
      {cartridgeData && (
        <EmulatorProvider cartridgeData={cartridgeData}>
          <DebuggerGrid />
        </EmulatorProvider>
      )}
    </GlobalDebuggerSettingsProvider>
  );
}

function DebuggerGrid() {
  const canvasRef = useRef<HTMLCanvasElement>(null);
  const { playMode, setPlayMode, step, handleKeyDown, handleKeyUp } =
    useGameboy({ canvasRef });
  const updateBreakpointsMutation = useUpdateBreakpoints();
  const [breakpoints, setBreakpoints] = useState<number[]>([]);

  useEffect(() => {
    updateBreakpointsMutation.mutate({ breakpoints });
  }, [breakpoints]);

  return (
    <div>
      <DebugToolbar />
      <PanelGrid>
        <Panel className="col-span-4 row-span-4">
          <canvas
            ref={canvasRef}
            className="object-contain w-full h-full focus-visible:outline-none"
            tabIndex={0}
            width={160}
            height={144}
            style={{ imageRendering: "pixelated" }}
            onKeyDown={(event) => {
              const k = event.key;
              if (handleKeyDown(k)) event.preventDefault();
            }}
            onKeyUp={(event) => {
              const k = event.key;
              if (handleKeyUp(k)) event.preventDefault();
            }}
          />
        </Panel>
        <DisassemblyPanel
          breakpoints={breakpoints}
          setBreakpoints={setBreakpoints}
        />
        <CPURegistersPanel />
        <InterruptsPanel />
        <ControlsPanel
          reset={() => {}}
          step={step}
          run={() => {
            setPlayMode("playing");
          }}
          stop={() => {
            setPlayMode("single-step");
          }}
          isPlaying={playMode === "playing"}
        />
        <TimersPanel />

        <TileDataPanel />
        <MemoryPanel />
      </PanelGrid>
    </div>
  );
}

function DebugToolbar() {
  return (
    <div className="flex gap-2 justify-end">
      <FrequencyChangeButton />
    </div>
  );
}
