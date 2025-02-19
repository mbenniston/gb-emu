import { RefObject, useCallback, useEffect, useRef, useState } from "react";
import { useGBEmu } from "@/context/GBEmuContext.tsx";
import { useEmulator } from "@/context/EmulatorContext.tsx";
import GBEmu from "@/gbemu";
import { useQueryClient } from "@tanstack/react-query";
import { useGlobalDebuggerSettings } from "@/context/GlobalDebuggerSettingsContext.tsx";

export const MAX_SPEED = 1000;

export const useGameboy = ({
  canvasRef,
  initialPlayState = "single-step",
}: {
  canvasRef: RefObject<HTMLCanvasElement>;
  initialPlayState?: "single-step" | "playing";
}) => {
  const { module } = useGBEmu();
  const { emulator } = useEmulator();
  const joypadRef = useRef<GBEmu.JoypadState | null>(null);
  const [playMode, setPlayMode] = useState<"single-step" | "playing">(
    initialPlayState,
  );
  const queryClient = useQueryClient();

  const handleKeyDown = useCallback((k: string) => {
    const joypad = joypadRef.current;
    if (k in keymap && joypad !== null) {
      joypad[keymap[k]] = true;
      return true;
    }
    return false;
  }, []);

  const handleKeyUp = useCallback((k: string) => {
    const joypad = joypadRef.current;
    if (k in keymap && joypad !== null) {
      joypad[keymap[k]] = false;
      return true;
    }
    return false;
  }, []);

  const handleButtonDown = useCallback((k: (typeof keymap)[string]) => {
    const joypad = joypadRef.current;
    if (joypad !== null) {
      joypad[k] = true;
      return true;
    }
    return false;
  }, []);

  const handleButtonUp = useCallback((k: (typeof keymap)[string]) => {
    const joypad = joypadRef.current;
    if (joypad !== null) {
      joypad[k] = false;
      return true;
    }
    return false;
  }, []);

  const { settings } = useGlobalDebuggerSettings();

  const step = useCallback(
    async function () {
      const width = emulator.get_framebuffer_width(),
        height = emulator.get_framebuffer_height(),
        channels = emulator.get_framebuffer_channels();

      const ptr = emulator.get_framebuffer_ptr() as { ptr: number };
      const view = module.HEAPU8.subarray(
        ptr.ptr,
        ptr.ptr + width * height * channels,
      );
      const context = canvasRef.current?.getContext("2d");
      if (!context) return;
      const imageData = context.createImageData(width, height);

      emulator.tick_single();

      imageData.data.set(view);
      const bitmap = await createImageBitmap(imageData);

      if (context) {
        context.imageSmoothingEnabled = false;
        context.drawImage(bitmap, 0, 0);
      }

      void queryClient.invalidateQueries({
        queryKey: ["debug"],
        refetchType: "all",
      });
    },
    [module, emulator],
  );

  useEffect(() => {
    if (playMode === "playing") {
      const width = emulator.get_framebuffer_width(),
        height = emulator.get_framebuffer_height(),
        channels = emulator.get_framebuffer_channels();

      const context = canvasRef.current?.getContext("2d");
      if (!context) return;
      const imageData = context.createImageData(width, height);

      const joypadState = new module.JoypadState();
      joypadRef.current = joypadState;

      const cancelledRef: { cancelled: boolean } = { cancelled: false };

      requestAnimationFrame(() => {
        async function runFrame() {
          if (cancelledRef.cancelled) return;
          const start = performance.now();

          const hit_breakpoint = emulator.debug_tick(joypadState);
          const ptr = emulator.get_framebuffer_ptr() as { ptr: number };
          const view = module.HEAPU8.subarray(
            ptr.ptr,
            ptr.ptr + width * height * channels,
          );
          imageData.data.set(view);
          const bitmap = await createImageBitmap(imageData);

          if (context) {
            context.imageSmoothingEnabled = false;
            context.drawImage(bitmap, 0, 0);
          }
          if (hit_breakpoint) {
            setPlayMode("single-step");
            cancelledRef.cancelled = true;
          }
          if (hit_breakpoint || settings.updateFrequency === "every-frame") {
            void queryClient.invalidateQueries({
              queryKey: ["debug"],
              refetchType: "all",
            });
          }

          const end = performance.now();

          const elapsed = end - start;
          const timeout = Math.max(0, 16.67 - elapsed);

          setTimeout(() => requestAnimationFrame(runFrame), timeout);
        }

        void runFrame();
      });

      return () => {
        cancelledRef.cancelled = true;
        joypadRef.current = null;
        module.destroy(joypadState);
      };
    }
  }, [playMode, settings]);

  return {
    step,
    playMode,
    setPlayMode,
    handleKeyDown,
    handleKeyUp,
    handleButtonDown,
    handleButtonUp,
  };
};
const keymap: Record<
  string,
  | "selectPressed"
  | "startPressed"
  | "downPressed"
  | "upPressed"
  | "leftPressed"
  | "rightPressed"
  | "aPressed"
  | "bPressed"
> = {
  d: "selectPressed",
  s: "startPressed",
  j: "downPressed",
  k: "upPressed",
  h: "leftPressed",
  l: "rightPressed",
  a: "aPressed",
  b: "bPressed",
} as const;

export type GameboyButton = (typeof keymap)[string];
