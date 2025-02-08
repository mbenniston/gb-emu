import { Pages } from "@/pages/Pages.ts";
import { NavLink } from "react-router-dom";

export const Home = () => {
  return (
    <div className=" mx-auto w-fit">
      <h2 className="text-5xl mb-4 mt-10 text-center">GB-EMU</h2>
      <div className="flex flex-col items-start gap-1">
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
    </div>
  );
};
