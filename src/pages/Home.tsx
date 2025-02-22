import { Pages } from "@/pages/Pages.ts";
import { NavLink } from "react-router-dom";
import { ReleaseNotePreview } from "@/components/ReleaseNotesPreview.tsx";

export const Home = () => {
  return (
    <div className="mx-auto w-fit">
      <h1 className="text-5xl mt-10 text-center">GB-EMU</h1>
      <h2 className="text-2xl mb-4 text-center">Web GameBoy emulator</h2>
      <div className="flex flex-col items-start gap-1 mx-auto w-fit">
        {Object.values(Pages).map((page) => {
          return (
            (("hasLink" in page && page.hasLink) || !("hasLink" in page)) && (
              <NavLink className=" btn btn-wide" to={page.path} key={page.id}>
                {page.title}
                <br />
              </NavLink>
            )
          );
        })}
      </div>
      <div className="pt-10" />
      <ReleaseNotePreview />
    </div>
  );
};
