import releaseNotes from "@/data/releaseNotes.gen.json";
import dayjs from "dayjs";
import localizedFormat from "dayjs/plugin/localizedFormat";
import { NavLink } from "react-router-dom";

dayjs.extend(localizedFormat);
type ReleaseNoteData = { when: string; title: string };

const RELEASE_NOTES_PAGE_SIZE = 5;

export function ReleaseNotePreview() {
  return (
    <div className="card bg-base-200 shadow-xl">
      <div className="card-body">
        <div className="card-title">Release notes</div>
        <div></div>
        <ul className="timeline timeline-vertical timeline-compact">
          {releaseNotes.slice(0, RELEASE_NOTES_PAGE_SIZE).map((data, index) => (
            <ReleaseNote
              key={index}
              isStart={index === 0}
              isEnd={index === releaseNotes.length - 1}
              data={data}
            />
          ))}
        </ul>
        <div className="card-actions">
          <NavLink to="/release-notes" className="link">
            Show more
          </NavLink>
        </div>
      </div>
    </div>
  );
}

function ReleaseNote({
  data,
  isEnd,
  isStart,
}: {
  data: ReleaseNoteData;
  isEnd: boolean;
  isStart: boolean;
}) {
  const parsedTime = dayjs(data.when);
  const formattedTime = parsedTime.format("LLLL");

  return (
    <li>
      {!isStart && <hr />}
      <div className={"timeline-middle"}>
        <div className="h-3 w-3 rounded-full border-2 border-secondary" />
      </div>
      <div className="timeline-end timeline-box">
        <time className="text-xs" dateTime={parsedTime.toISOString()}>
          {formattedTime}
        </time>
        <p className="text-sm">{data.title}</p>
      </div>
      {!isEnd && <hr />}
    </li>
  );
}
