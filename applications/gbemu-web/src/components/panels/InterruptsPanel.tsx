import { useId } from "react";
import {
  Panel,
  PanelBody,
  PanelContent,
  PanelHeader,
} from "@/components/Panel.tsx";
import { useInterrupts } from "@/hooks/useInterrupts.ts";

export function InterruptsPanel() {
  const registersQuery = useInterrupts();

  if (!registersQuery.data) return;

  const registers = registersQuery.data;

  return (
    <Panel className={"col-span-2 row-span-2"}>
      <PanelContent>
        <PanelHeader>Interrupts</PanelHeader>
        <PanelBody>
          <div className="p-0.5" />
          <fieldset className="">
            <div className="grid grid-cols-3 w-full gap-x-1 gap-y-0.5">
              <span className="text-xs">Name</span>
              <span className="text-xs place-self-end">Enabled</span>
              <span className="text-xs place-self-end">Requested</span>
              <InterruptRow
                shorthand="IME"
                name="Interrupt master enable"
                enabled={registers.ime}
                requested={null}
              />
              <InterruptRow
                shorthand="Joypad"
                enabled={registers.joypad_enabled}
                requested={registers.joypad_requested}
              />
              <InterruptRow
                shorthand="Serial"
                enabled={registers.serial_enabled}
                requested={registers.serial_requested}
              />
              <InterruptRow
                shorthand="Timer"
                enabled={registers.timer_enabled}
                requested={registers.timer_requested}
              />
              <InterruptRow
                shorthand="LCD"
                enabled={registers.lcd_enabled}
                requested={registers.lcd_requested}
              />
              <InterruptRow
                shorthand="VBlank"
                enabled={registers.vblank_enabled}
                requested={registers.vblank_requested}
              />
            </div>
          </fieldset>
        </PanelBody>
      </PanelContent>
    </Panel>
  );
}

function InterruptRow({
  name,
  shorthand,
  requested,
  enabled,
}: {
  name?: string;
  shorthand: string;
  requested: boolean | null;
  enabled: boolean;
}) {
  const labelId = useId();
  return (
    <>
      <label id={labelId} title={name} className="label-text uppercase">
        {shorthand}
      </label>
      <input
        aria-labelledby={labelId}
        type="checkbox"
        className="checkbox checkbox-xs place-self-end"
        readOnly
        checked={enabled}
      />
      {requested !== null && (
        <input
          aria-labelledby={labelId}
          type="checkbox"
          className="checkbox checkbox-xs place-self-end"
          readOnly
          checked={requested}
        />
      )}
      {requested === null && <span />}
    </>
  );
}
