import { useEffect, useRef } from "react";
import {
  Panel,
  PanelBody,
  PanelContent,
  PanelHeader,
} from "@/components/Panel.tsx";
import { useTileData } from "@/hooks/useTileData.ts";

export function TileDataPanel() {
  const ref = useRef<HTMLCanvasElement>(null);

  const tileSetQuery = useTileData();
  const tileSetQueryData = tileSetQuery.data;

  useEffect(() => {
    if (tileSetQueryData) {
      const { width, height, data } = tileSetQueryData;
      const context = ref.current?.getContext("2d");
      if (!context) return;

      void (async () => {
        const imageData = context.createImageData(width, height);

        imageData.data.set(data);
        const bitmap = await createImageBitmap(imageData);

        context.imageSmoothingEnabled = false;
        context.drawImage(bitmap, 0, 0, bitmap.width, bitmap.height);
      })();
    }
  }, [tileSetQueryData]);

  if (!tileSetQuery.isSuccess) {
    return <></>;
  }

  return (
    <Panel className="col-span-4 row-span-4">
      <PanelContent>
        <PanelHeader>Tile data</PanelHeader>
        <PanelBody>
          <canvas
            ref={ref}
            className="block object-contain w-full h-full"
            width={tileSetQuery.data.width}
            height={tileSetQuery.data.height}
          />
        </PanelBody>
      </PanelContent>
    </Panel>
  );
}
