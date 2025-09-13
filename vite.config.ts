import { defineConfig } from "vite";
import react from "@vitejs/plugin-react";
import { VitePWA } from "vite-plugin-pwa";
import tsconfigPaths from "vite-tsconfig-paths";
import tailwindcss from "@tailwindcss/vite";

// https://vite.dev/config/
export default defineConfig({
  plugins: [
    tailwindcss(),
    tsconfigPaths(),
    react(),
    VitePWA({
      registerType: "autoUpdate",
      devOptions: { enabled: true },
      manifest: { theme_color: "#ffffff" },
      pwaAssets: {
        image: "./public/old-gameboy-console-svgrepo-com.svg",
        preset: "minimal-2023",
      },
    }),
  ],
});
