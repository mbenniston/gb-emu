import { useGBEmu } from "../context/GBEmuContext.tsx";
import { useEmulator } from "../context/EmulatorContext.tsx";
import { skipToken, useQueries, useQuery } from "@tanstack/react-query";
import { useDebugRefetchInterval } from "@/hooks/useDebugRefetchInterval.ts";

export type MemoryDump = {
  memory: Uint8Array;
  start: number;
  length: number;
};

export function useDisassembly(
  range: { rangeStart: number; rangeLength: number } | null,
) {
  const { module } = useGBEmu();
  const { emulator } = useEmulator();

  return useQuery({
    queryKey: [
      "debug",
      "disassembly",
      "start",
      range?.rangeStart,
      "length",
      range?.rangeLength,
    ],
    queryFn:
      range !== null
        ? () => {
            const memoryDump = emulator.get_debug_dump_memory_range(
              range.rangeStart,
              range.rangeLength,
            );
            const data = new Uint8Array(memoryDump.data_length);
            for (let i = 0; i < memoryDump.data_length; i++) {
              data[i] = memoryDump.get_data(i);
            }
            module.destroy(memoryDump);
            return {
              memory: data,
              start: range.rangeStart,
              length: range.rangeLength,
            };
          }
        : skipToken,
  });
}

const PAGE_SIZE = 128;

/**
 * Fetch memory in a given range aligned to 128 byte pages
 */
export function useDisassembles({
  range,
  pageSize = PAGE_SIZE,
}: {
  range: { rangeStart: number; rangeLength: number } | null;
  pageSize?: number;
}) {
  const { module } = useGBEmu();
  const { emulator } = useEmulator();
  const refetchInterval = useDebugRefetchInterval();

  const pages: { rangeStart: number; rangeLength: number }[] = [];
  if (range) {
    for (
      let i = range.rangeStart;
      i < range.rangeStart + range.rangeLength;
      i += pageSize
    ) {
      pages.push({
        rangeStart: Math.floor(i / pageSize) * pageSize,
        rangeLength: pageSize,
      });
    }
  }
  return useQueries({
    queries: pages.map((page) => ({
      refetchInterval,
      queryKey: [
        "debug",
        "panels",
        "disassembly",
        "pageSize",
        pageSize,
        "start",
        page.rangeStart,
        "length",
        page.rangeLength,
      ],
      queryFn: (): MemoryDump => {
        const memoryDump = emulator.get_debug_dump_memory_range(
          page.rangeStart,
          page.rangeLength,
        );
        const data = new Uint8Array(memoryDump.data_length);
        for (let i = 0; i < memoryDump.data_length; i++) {
          data[i] = memoryDump.get_data(i);
        }

        module.destroy(memoryDump);

        return {
          memory: data,
          start: page.rangeStart,
          length: page.rangeLength,
        };
      },
    })),
  });
}
