import { useRef } from "react";
import { useVirtualizer } from "@tanstack/react-virtual";
import { MemoryDump, useDisassembles } from "@/hooks/useDisassembly.ts";
import {
  Panel,
  PanelBody,
  PanelContent,
  PanelHeader,
} from "@/components/Panel.tsx";
import { UseQueryResult } from "@tanstack/react-query";
import { ViewModeSelectButton } from "@/components/panels/CPURegistersPanel.tsx";

export function MemoryPanel() {
  const ref = useRef<HTMLDivElement>(null);
  const virtualizer = useVirtualizer({
    count: (0xffff + 1) / 16,
    getScrollElement: () => ref.current,
    estimateSize: () => 16,
  });

  const items = virtualizer.getVirtualItems();
  const range = virtualizer.range;

  const disassemblyQuery = useDisassembles({
    range: range
      ? {
          rangeStart: range.startIndex * 16,
          rangeLength: (range.endIndex - range.startIndex) * 16,
        }
      : null,
  });

  return (
    <Panel className="col-span-6 row-span-3">
      <PanelContent>
        <PanelHeader>Memory</PanelHeader>
        <MemoryActions
          scrollTo={(i) => {
            virtualizer.scrollToIndex(Math.floor(i / 16), {
              align: "start",
            });
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
                <InstructionRow memory={disassemblyQuery} index={item.index} />
              </div>
            ))}
          </div>
        </PanelBody>
      </PanelContent>
    </Panel>
  );
}

function getByte(memory: UseQueryResult<MemoryDump>[], index: number) {
  for (const dump of memory) {
    if (!dump.data) continue;
    const dumpIndex = index - dump.data.start;
    if (dumpIndex < 0 || dumpIndex >= dump.data.length) continue;

    return dump.data.memory[dumpIndex];
  }

  return 0;
}

function InstructionRow({
  index,
  memory,
}: {
  memory: UseQueryResult<MemoryDump>[];
  index: number;
}) {
  return (
    <div className="w-full flex items-end gap-2 h-[16px] leading-tight ">
      <div className="font-mono flex-grow-0 flex-shrink-0 text-xs ">
        {getAddressLabel(index * 16).padStart(4, "-")}
      </div>
      <div className="font-mono flex-grow-0 flex-shrink-0 text-xs">
        {(index * 16).toString(16).padStart(4, "0")}
      </div>
      <div className="flex-grow-0 flex-shrink-0">
        {[...Array<undefined>(16)].map((_, i) => (
          <span key={i} className="font-mono text-xs">
            {getByte(memory, index * 16 + i)
              .toString(16)
              .padStart(2, "0")}{" "}
          </span>
        ))}
      </div>
      <span className="select-none">|</span>
      <div className="flex-grow-0 flex-shrink-0">
        {[...Array<undefined>(16)].map((_, i) => (
          <span key={i} className="font-mono text-xs">
            {String.fromCharCode(getByte(memory, index * 16 + i)).trim() === ""
              ? "."
              : String.fromCharCode(getByte(memory, index * 16 + i))}
          </span>
        ))}
      </div>
    </div>
  );
}

function MemoryActions({ scrollTo }: { scrollTo: (index: number) => void }) {
  return (
    <div className="text-sm flex gap-1 flex-wrap">
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
          scrollTo(0x8000);
        }}
      >
        VRAM
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
          scrollTo(0xfe00);
        }}
      >
        OAM
      </ViewModeSelectButton>
      <ViewModeSelectButton
        onClick={() => {
          scrollTo(0xff00);
        }}
      >
        IO
      </ViewModeSelectButton>

      <ViewModeSelectButton
        onClick={() => {
          scrollTo(0xff80);
        }}
      >
        HRAM
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

export function getAddressLabel(address: number) {
  if (address < 0x4000) {
    // ROM bank 0
    return "ROM0";
  }
  if (address < 0x8000) {
    return "ROMN";
  }
  if (address < 0xa000) {
    return "VRAM";
  }
  if (address < 0xc000) {
    return "ERAM";
  }
  if (address < 0xe000) {
    return "WRAM";
  }
  if (address < 0xfe00) {
    return "ECHO";
  }
  if (address < 0xfea0) {
    return "OAM";
  }
  if (address < 0xff00) {
    return "-";
  }
  if (address < 0xff80) {
    return "IO";
  }

  if (address < 0xffff) {
    return "HRAM";
  }

  if (address === 0xffff) {
    return "IR";
  }

  return "UKWN";
}
