import { PointerEvent, useRef, useState } from "react";
import { GameboyButton, useGameboy } from "@/hooks/useGameboy.ts";
import clsx from "clsx";
import { EmulatorProvider } from "@/context/EmulatorProvider.tsx";

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
            const file = e.target.files?.[0];
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
  const { handleKeyDown, handleKeyUp, handleButtonDown, handleButtonUp } =
    useGameboy({
      canvasRef,
      initialPlayState: "playing",
    });

  return (
    <div className="flex overscroll-none touch-none gap-4 h-dvh w-full landscape:px-4 items-stretch justify-evenly portrait:flex-col">
      <DPad
        handleButtonDown={handleButtonDown}
        handleButtonUp={handleButtonUp}
        landscape
      />
      <canvas
        ref={canvasRef}
        className="object-contain focus-visible:outline-none shrink grow basis-0 min-w-0"
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
      <Buttons
        handleButtonDown={handleButtonDown}
        handleButtonUp={handleButtonUp}
        landscape
      />
      <div className="hidden portrait:flex w-full justify-evenly shrink-0 grow items-stretch">
        <DPad
          handleButtonDown={handleButtonDown}
          handleButtonUp={handleButtonUp}
        />
        <Buttons
          handleButtonDown={handleButtonDown}
          handleButtonUp={handleButtonUp}
        />
      </div>
    </div>
  );
}

function Buttons({
  handleButtonDown,
  handleButtonUp,
  landscape,
}: {
  handleButtonDown: (b: GameboyButton) => void;
  handleButtonUp: (b: GameboyButton) => void;
  landscape?: boolean;
}) {
  return (
    <div
      className={clsx(
        "flex flex-col [@media(pointer:fine)]:hidden",
        landscape && "hidden landscape:flex",
      )}
    >
      <div className="grow" />
      <div className="flex gap-2">
        <button
          className="btn btn-square"
          onPointerDown={() => {
            handleButtonDown("aPressed");
          }}
          onPointerUp={() => {
            handleButtonUp("aPressed");
          }}
        >
          A
        </button>
        <div className="pt-4">
          <button
            className="btn btn-square"
            onPointerDown={() => {
              handleButtonDown("bPressed");
            }}
            onPointerUp={() => {
              handleButtonUp("bPressed");
            }}
          >
            B
          </button>
        </div>
      </div>
      <div className="grow" />
      <div>
        <button
          className="btn"
          onPointerDown={() => {
            handleButtonDown("selectPressed");
          }}
          onPointerUp={() => {
            handleButtonUp("selectPressed");
          }}
        >
          SELECT
        </button>
        <button
          className="btn"
          onPointerDown={() => {
            handleButtonDown("startPressed");
          }}
          onPointerUp={() => {
            handleButtonUp("startPressed");
          }}
        >
          START
        </button>
      </div>
    </div>
  );
}

function DPad({
  handleButtonDown,
  handleButtonUp,
  landscape,
}: {
  handleButtonDown: (b: GameboyButton) => void;
  handleButtonUp: (b: GameboyButton) => void;
  landscape?: boolean;
}) {
  const rightRef = useRef<HTMLButtonElement>(null);
  const leftRef = useRef<HTMLButtonElement>(null);
  const downRef = useRef<HTMLButtonElement>(null);
  const upRef = useRef<HTMLButtonElement>(null);

  const [rightDown, setRightDown] = useState(false);
  const [leftDown, setLeftDown] = useState(false);
  const [upDown, setUpDown] = useState(false);
  const [downDown, setDownDown] = useState(false);

  return (
    <div
      className={clsx(
        "grid grid-cols-3 grid-rows-3 w-fit h-fit place-self-center [@media(pointer:fine)]:hidden",
        landscape && "hidden landscape:grid",
      )}
      onPointerMove={(e) => {
        if (leftRef.current && isInside(e, leftRef.current)) {
          setLeftDown(true);
          handleButtonDown("leftPressed");
        } else {
          setLeftDown(false);
          handleButtonUp("leftPressed");
        }
        if (rightRef.current && isInside(e, rightRef.current)) {
          handleButtonDown("rightPressed");
          setRightDown(true);
        } else {
          setRightDown(false);
          handleButtonUp("rightPressed");
        }
        if (upRef.current && isInside(e, upRef.current)) {
          setUpDown(true);
          handleButtonDown("upPressed");
        } else {
          setUpDown(false);
          handleButtonUp("upPressed");
        }
        if (downRef.current && isInside(e, downRef.current)) {
          setDownDown(true);
          handleButtonDown("downPressed");
        } else {
          setDownDown(false);
          handleButtonUp("downPressed");
        }
      }}
      onPointerLeave={() => {
        handleButtonUp("leftPressed");
        handleButtonUp("rightPressed");
        handleButtonUp("upPressed");
        handleButtonUp("downPressed");

        setRightDown(false);
        setLeftDown(false);
        setDownDown(false);
        setUpDown(false);
      }}
    >
      <div />
      <button
        ref={upRef}
        className={clsx(
          "w-16  h-16 select-none rounded-t-btn",
          !upDown ? "bg-base-200" : "bg-base-200/80",
        )}
        onPointerDown={() => {
          handleButtonDown("upPressed");
        }}
        onPointerUp={() => {
          handleButtonUp("upPressed");
        }}
      ></button>
      <div />

      <button
        ref={leftRef}
        className={clsx(
          "w-16  h-16 select-none rounded-l-btn",
          !leftDown ? "bg-base-200" : "bg-base-200/80",
        )}
        onPointerDown={() => {
          handleButtonDown("leftPressed");
        }}
        onPointerUp={() => {
          handleButtonUp("leftPressed");
        }}
      ></button>
      <div className={"bg-base-200"} />
      <button
        ref={rightRef}
        className={clsx(
          "w-16  h-16 select-none rounded-r-btn",
          !rightDown ? "bg-base-200" : "bg-base-200/80",
        )}
        onPointerDown={() => {
          handleButtonDown("rightPressed");
        }}
        onPointerUp={() => {
          handleButtonUp("rightPressed");
        }}
      ></button>
      <div />
      <button
        ref={downRef}
        className={clsx(
          "w-16 h-16 select-none rounded-b-btn",
          !downDown ? "bg-base-200" : "bg-base-200/80",
        )}
        onPointerDown={() => {
          handleButtonDown("downPressed");
        }}
        onPointerUp={() => {
          handleButtonUp("downPressed");
        }}
      ></button>
      <div />
    </div>
  );
}

function isInside(
  event: PointerEvent<HTMLDivElement>,
  button: HTMLButtonElement,
) {
  const rect = button.getBoundingClientRect();
  return (
    event.clientX >= rect.left &&
    event.clientX <= rect.right &&
    event.clientY >= rect.top &&
    event.clientY <= rect.bottom
  );
}
