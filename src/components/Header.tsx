import { NavLink, useMatches } from "react-router-dom";
import { isPageHandle, Pages } from "@/pages/Pages.ts";

export function Header() {
  return (
    <div>
      <Breadcrumbs />
    </div>
  );
}

const Breadcrumbs = () => {
  const matches = useMatches();

  return (
    <>
      {matches.map((match) => {
        const handle = match.handle;
        if (!isPageHandle(handle)) {
          return null;
        }

        const page = Pages[handle];

        return (
          <NavLink key={page.id} to={page.path}>
            <span className="text-2xl">/{page.title}</span>
          </NavLink>
        );
      })}
    </>
  );
};
