import { createBrowserRouter, RouterProvider } from "react-router-dom";
import { DEBUGGER_PAGE, HOME_PAGE, PLAY_PAGE } from "../pages/Pages.ts";
import { Home } from "../pages/Home.tsx";
import { PageLayout } from "@/layout/PageLayout.tsx";
import { Debug } from "@/pages/Debug.tsx";
import { Play } from "@/pages/Play.tsx";

const router = createBrowserRouter([
  {
    path: "/",
    element: <PageLayout />,
    children: [
      {
        path: HOME_PAGE.path,
        element: <Home />,
        handle: HOME_PAGE.id,
      },
      {
        path: DEBUGGER_PAGE.path,
        element: <Debug />,
        handle: DEBUGGER_PAGE.id,
      },
      {
        path: PLAY_PAGE.path,
        element: <Play />,
        handle: PLAY_PAGE.id,
      },
    ],
  },
]);

export const Routes = () => <RouterProvider router={router} />;
