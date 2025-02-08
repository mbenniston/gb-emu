import { useRef, useState } from "react";
import { useGameboy } from "@/hooks/useGameboy.ts";
import { EmulatorProvider } from "@/context/EmulatorContext.tsx";

export function Play() {
  const [file, setFile] = useState<Uint8Array | null>(null);
  return (
    <>
      {!file && <RomSelect onSelect={setFile} />}
      {file && (
        <EmulatorProvider cartridgeData={file}>
          <Gameboy />
        </EmulatorProvider>
      )}
    </>
  );
}

function RomSelect({ onSelect }: { onSelect: (data: Uint8Array) => void }) {
  return (
    <div className="flex h-dvh items-center justify-center">
      <label className="form-control w-full max-w-xs">
        <div className="label">
          <span className="label-text">Select a ROM</span>
        </div>
        <input
          type="file"
          accept=".gb"
          className="file-input file-input-bordered w-full max-w-xs"
          onChange={(e) => {
            const file = e.target?.files?.[0];
            if (!file) return;
            const loadFile = async () => {
              const data = await file.arrayBuffer();
              const buffer = new Uint8Array(data);
              onSelect(buffer);
            };
            void loadFile();
          }}
        />
      </label>
    </div>
  );
}

function Gameboy() {
  const canvasRef = useRef<HTMLCanvasElement>(null);
  const { handleKeyDown, handleKeyUp } = useGameboy({
    canvasRef,
    initialPlayState: "playing",
  });

  return (
    <canvas
      ref={canvasRef}
      className="object-contain w-full h-full container mx-auto max-h-dvh focus-visible:outline-none"
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
  );
}
