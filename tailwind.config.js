/** @type {import('tailwindcss').Config} */
export default {
  content: ["./index.html", "./src/**/*.{js,ts,jsx,tsx}"],
  plugins: [require("daisyui")],
  daisyui: {
    themes: [
      {
        light: {
          ...require("daisyui/src/theming/themes")["retro"],
        },
        dark: {
          ...require("daisyui/src/theming/themes")["black"],
        },
      },
    ],
  },
};
