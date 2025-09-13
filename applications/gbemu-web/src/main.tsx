import { StrictMode } from "react";
import { createRoot } from "react-dom/client";
import "./index.css";
import { QueryClient, QueryClientProvider } from "@tanstack/react-query";
import { Routes } from "@/routes/Routes.tsx";
import { GBEmuProvider } from "@/context/GBEmuProvider.tsx";

const queryClient = new QueryClient();

// eslint-disable-next-line @typescript-eslint/no-non-null-assertion
createRoot(document.getElementById("root")!).render(
  <StrictMode>
    <QueryClientProvider client={queryClient}>
      <GBEmuProvider>
        <Routes />
      </GBEmuProvider>
    </QueryClientProvider>
  </StrictMode>,
);
