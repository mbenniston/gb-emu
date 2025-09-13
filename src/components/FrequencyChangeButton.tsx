import { Cog6ToothIcon } from "@heroicons/react/16/solid";
import { useGlobalDebuggerSettings } from "@/context/useGlobalDebuggerSettings.ts";
import { updateFrequencyOptions } from "@/context/updateFrequencyOptions.ts";

export function FrequencyChangeButton() {
  const { settings, setSettings } = useGlobalDebuggerSettings();
  return (
    <details className="dropdown dropdown-bottom dropdown-end">
      <summary className="btn btn-sm btn-ghost m-1" title="Change frequency">
        Refresh frequency
        <Cog6ToothIcon className="size-4" />
      </summary>
      <ul
        role="group"
        radioGroup="frequency"
        className="menu dropdown-content bg-base-100 rounded-box z-10 w-52 p-2 shadow-sm "
      >
        {updateFrequencyOptions.map((option) => (
          <li key={option.value}>
            <label key={option.value} className="label">
              <input
                type="radio"
                className="radio radio-sm"
                value={option.title}
                title={option.title}
                checked={option.value === settings.updateFrequency}
                onChange={(e) => {
                  const value = updateFrequencyOptions.find(
                    (o) => o.title === e.target.value,
                  )?.value;

                  if (value) {
                    setSettings((prev) => ({
                      ...prev,
                      updateFrequency: value,
                    }));
                  }
                }}
              />
              <span className="label-text">{option.title}</span>
            </label>
          </li>
        ))}
      </ul>
    </details>
  );
}
