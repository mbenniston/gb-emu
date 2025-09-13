import releaseNotes from "@/data/releaseNotes.gen.json";
import dayjs from "dayjs";
import localizedFormat from "dayjs/plugin/localizedFormat";
import { useState } from "react";

dayjs.extend(localizedFormat);
type ReleaseNoteData = { when: string; title: string };

const RELEASE_NOTES_PAGE_SIZE = 10;

export function ReleaseNotes() {
  const [releaseNotesToShow, setReleaseNotesToShow] = useState(
    RELEASE_NOTES_PAGE_SIZE,
  );
  return (
    <div className="container mx-auto px-2">
      <h1 className="text-3xl mt-2 mb-1">Release notes</h1>
      <ul className="timeline timeline-vertical timeline-compact">
        {releaseNotes.slice(0, releaseNotesToShow).map((data, index) => (
          <ReleaseNote
            key={index}
            isStart={index === 0}
            isEnd={index === releaseNotes.length - 1}
            data={data}
          />
        ))}
      </ul>
      {releaseNotesToShow < releaseNotes.length && (
        <button
          type="button"
          className="btn btn-primary max-w-sm mt-2"
          onClick={() => {
            setReleaseNotesToShow((count) => count + RELEASE_NOTES_PAGE_SIZE);
          }}
        >
          Show more
        </button>
      )}
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
        <div className="h-5 w-5 rounded-full border-2 border-secondary" />
      </div>
      <div className="timeline-end timeline-box">
        <time className="text-sm" dateTime={parsedTime.toISOString()}>
          {formattedTime}
        </time>
        <p>{data.title}</p>
      </div>
      {!isEnd && <hr />}
    </li>
  );
}
