import { Panel, PanelBody, PanelContent } from "@/components/Panel.tsx";
import {
  ArrowPathIcon,
  ArrowUturnDownIcon,
  PlayIcon,
  StopIcon,
} from "@heroicons/react/24/outline";
import clsx from "clsx";

export function ControlsPanel({
  step,
  run,
  reset,
  stop,
  isPlaying,
}: {
  reset: () => void;
  step: () => void;
  run: () => void;
  stop: () => void;
  isPlaying: boolean;
}) {
  return (
    <Panel className="col-span-4 row-span-1">
      <PanelContent>
        <PanelBody>
          <div className="flex gap-1">
            <button
              className="btn btn-square btn-sm btn-ghost"
              onClick={run}
              title="Play / Continue"
            >
              <span className="sr-only">play</span>
              <PlayIcon className="size-6" />
            </button>
            <button
              className="btn btn-square btn-sm btn-ghost"
              onClick={stop}
              title="Pause"
            >
              <span className="sr-only">stop</span>
              <StopIcon
                className={clsx("size-6", isPlaying && "fill-primary")}
              />
            </button>

            <button
              className="btn btn-square btn-sm btn-ghost"
              onClick={step}
              title="Step over"
            >
              <span className="sr-only">step over</span>
              <ArrowUturnDownIcon className="size-6 -scale-x-100" />
            </button>
            <button
              className="btn btn-square btn-sm btn-ghost"
              onClick={reset}
              title="Reset"
            >
              <span className="sr-only">reset</span>
              <ArrowPathIcon className="size-6 -scale-x-100" />
            </button>
          </div>
        </PanelBody>
      </PanelContent>
    </Panel>
  );
}
