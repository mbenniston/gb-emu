import { useVirtualizer } from "@tanstack/react-virtual";
import {
  Dispatch,
  SetStateAction,
  useCallback,
  useEffect,
  useRef,
  useState,
} from "react";
import clsx from "clsx";
import {
  Panel,
  PanelBody,
  PanelContent,
  PanelHeader,
} from "@/components/Panel.tsx";
import { MemoryDump, useDisassembles } from "@/hooks/useDisassembly.ts";
import { useInstructions } from "@/hooks/useInstructions.ts";
import { UseQueryResult } from "@tanstack/react-query";
import { useCPURegisters } from "@/hooks/useCPURegisters.ts";
import { ViewModeSelectButton } from "@/components/panels/CPURegistersPanel.tsx";

export function DisassemblyPanel({
  // memory,
  // registers,
  breakpoints,
  setBreakpoints,
}: {
  // registers: RegistersState;
  // memory: MemoryState;
  breakpoints: number[];
  setBreakpoints: Dispatch<SetStateAction<number[]>>;
}) {
  const ref = useRef<HTMLDivElement>(null);
  const virtualizer = useVirtualizer({
    count: 0xffff + 1,
    getScrollElement: () => ref.current,
    estimateSize: () => 16,
  });
  const items = virtualizer.getVirtualItems();
  const range = virtualizer.range;

  const disassemblyQuery = useDisassembles({
    range: range
      ? {
          rangeStart: range.startIndex,
          rangeLength: range.endIndex - range.startIndex,
        }
      : null,
  });

  const onToggleBreakpoint = useCallback(
    (index: number) => {
      setBreakpoints((prev) => {
        if (prev.includes(index)) {
          return prev.filter((p) => p !== index);
        }

        return [...prev, index];
      });
    },
    [setBreakpoints],
  );

  const registersQuery = useCPURegisters();
  const pc = registersQuery.data?.PC;

  const [shouldTrackPC, setShouldTrackPC] = useState(true);

  useEffect(() => {
    if (pc !== undefined && shouldTrackPC)
      virtualizer.scrollToIndex(pc, { align: "center" });
  }, [pc, shouldTrackPC, virtualizer]);

  return (
    <Panel className="col-span-4 row-span-4">
      <PanelContent>
        <PanelHeader>Disassembly</PanelHeader>
        <DisassemblyActions
          shouldTrackPC={shouldTrackPC}
          toggleShouldTrackPC={() => {
            setShouldTrackPC((prev) => !prev);
          }}
          // registers={registersQuery.data}
          scrollTo={(i) => {
            virtualizer.scrollToIndex(i, {
              align: "start",
            });
          }}
          onClearBreakpoint={() => {
            setBreakpoints([]);
          }}
        />
        <PanelBody ref={ref}>
          <div
            style={{
              height: `${virtualizer.getTotalSize().toString()}px`,
              width: "100%",
              position: "relative",
            }}
          >
            {items.map((item) => (
              <div
                data-index={item.index}
                ref={virtualizer.measureElement}
                key={item.key}
                style={{
                  position: "absolute",
                  top: 0,
                  left: 0,
                  height: 16,
                  width: "100%",
                  transform: `translateY(${item.start.toString()}px)`,
                }}
              >
                <InstructionView
                  index={item.index}
                  memory={disassemblyQuery}
                  // registers={registers}
                  breakpoints={breakpoints}
                  onToggleBreakpoint={onToggleBreakpoint}
                />
              </div>
            ))}
          </div>
        </PanelBody>
      </PanelContent>
    </Panel>
  );
}

function InstructionView({
  index,
  memory,
  // registers,
  breakpoints,
  onToggleBreakpoint,
}: {
  index: number;
  memory: UseQueryResult<MemoryDump>[];
  // registers: RegistersState;
  breakpoints: number[];
  onToggleBreakpoint: (index: number) => void;
}) {
  const address = index.toString(16);
  let b1 = 0;
  const b2 = 0;
  for (const dump of memory) {
    if (!dump.data) continue;
    const dumpIndex = index - dump.data.start;
    if (dumpIndex < 0 || dumpIndex >= dump.data.length) continue;

    b1 = dump.data.memory[dumpIndex];
  }
  const b2Index = index + 1;
  for (const dump of memory) {
    if (!dump.data) continue;
    const dumpIndex = b2Index - dump.data.start;
    if (dumpIndex < 0 || dumpIndex >= dump.data.length) continue;

    b1 = dump.data.memory[dumpIndex];
  }
  const registers = useCPURegisters();

  const instructions = useInstructions();
  if (!instructions.data) return null;

  let instruction = instructions.data.instructions[b1];
  if (instruction.isPrefix)
    instruction = instructions.data.prefixed_instructions[b2];

  return (
    <button
      className={clsx(
        "btn flex rounded-none min-w-0 h-full min-h-0 gap-2 items-stretch w-full text-left m-0 box-border px-1 text-xs font-extralight uppercase font-mono no-animation transition-all",
        registers.data?.PC === index ? "btn-secondary" : "btn-ghost",
      )}
      onClick={() => {
        onToggleBreakpoint(index);
      }}
      tabIndex={-1}
    >
      <span
        className={clsx(
          "bg-red-600 self-center inline-block w-2 h-2 rounded-full",
          !breakpoints.includes(index) && "invisible",
        )}
      />

      <span className="w-[4ch]">{address.toString().padStart(4, "0")}</span>

      <span>{instruction.mnemonic}</span>

      <div className="flex-grow" />
      <span
        className={clsx(
          "badge badge-sm badge-secondary min-h-0 h-full",
          index !== registers.data?.SP && "invisible",
        )}
      >
        sp
      </span>
      <span
        className={clsx(
          "badge badge-sm badge-primary min-h-0 h-full",
          index !== registers.data?.PC && "invisible",
        )}
      >
        pc
      </span>
    </button>
  );
}

function DisassemblyActions({
  scrollTo,
  onClearBreakpoint,
  // registers,
  toggleShouldTrackPC,
  shouldTrackPC,
}: {
  scrollTo: (index: number) => void;
  onClearBreakpoint: () => void;
  // registers: RegistersState;
  toggleShouldTrackPC: () => void;
  shouldTrackPC: boolean;
}) {
  const registersQuery = useCPURegisters();

  return (
    <div className="text-sm flex gap-1 flex-wrap">
      <ViewModeSelectButton onClick={onClearBreakpoint}>
        Clear breakpoints
      </ViewModeSelectButton>
      <ViewModeSelectButton
        onClick={() => {
          scrollTo(0);
        }}
      >
        ROM bank 1
      </ViewModeSelectButton>
      <ViewModeSelectButton
        onClick={() => {
          scrollTo(0x4000);
        }}
      >
        ROM bank N
      </ViewModeSelectButton>
      <ViewModeSelectButton
        onClick={() => {
          scrollTo(0xc000);
        }}
      >
        WRAM
      </ViewModeSelectButton>
      <ViewModeSelectButton
        onClick={() => {
          scrollTo(0xff80);
        }}
      >
        HRAM
      </ViewModeSelectButton>
      <ViewModeSelectButton
        onClick={() => {
          if (registersQuery.data) scrollTo(registersQuery.data.PC);
        }}
      >
        PC
      </ViewModeSelectButton>
      <ViewModeSelectButton
        onClick={() => {
          if (registersQuery.data) scrollTo(registersQuery.data.SP);
        }}
      >
        SP
      </ViewModeSelectButton>
      <ViewModeSelectButton
        selected={shouldTrackPC}
        onClick={() => {
          toggleShouldTrackPC();
        }}
      >
        Follow PC
      </ViewModeSelectButton>
      <div className="flex-grow" />
      <div>
        <input
          placeholder="Goto"
          size={16}
          inputMode="numeric"
          className="input input-xs pl-2 transition-colors ease-out duration-200"
          onBlur={(e) => {
            const i = Number.parseInt(e.target.value, 16);
            if (!isNaN(i)) {
              scrollTo(i);
            }
            e.target.value = "";
          }}
        />
      </div>
    </div>
  );
}
