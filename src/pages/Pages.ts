export const HOME_PAGE = {
  id: "home",
  title: "Home",
  path: "/",
  hasBreadcrumb: false,
  hasLink: false,
} as const;

export const DEBUGGER_PAGE = {
  id: "debugger",
  title: "Debugger",
  path: "/debugger",
} as const;

export const PLAY_PAGE = {
  id: "play",
  title: "Play",
  path: "/play",
} as const;

export const Pages = {
  [HOME_PAGE.id]: HOME_PAGE,
  [PLAY_PAGE.id]: PLAY_PAGE,
  [DEBUGGER_PAGE.id]: DEBUGGER_PAGE,
} as const;

export const isPageHandle = (handle: unknown): handle is keyof typeof Pages => {
  return typeof handle === "string" && Object.keys(Pages).includes(handle);
};
