import { useGBEmu } from "../context/GBEmuContext.tsx";
import { useEmulator } from "../context/EmulatorContext.tsx";
import { useQuery } from "@tanstack/react-query";
import { useDebugRefetchInterval } from "@/hooks/useDebugRefetchInterval.ts";

export function useTileData() {
  const { module } = useGBEmu();
  const { emulator } = useEmulator();
  const refetchInterval = useDebugRefetchInterval();

  return useQuery({
    refetchInterval,
    queryKey: ["debug", "panels", "tile-data"],
    queryFn: () => {
      const tileSet = emulator.get_debug_dump_tileset();
      const data = new Uint8Array(tileSet.data_length);
      for (let i = 0; i < tileSet.data_length; i++) {
        data[i] = tileSet.get_data(i);
      }
      const object = {
        data,
        width: tileSet.width,
        height: tileSet.height,
        channels: tileSet.channels,
      };
      module.destroy(tileSet);
      return object;
    },
  });
}
