import { StrictMode } from "react";
import { createRoot } from "react-dom/client";
import "./index.css";
import { QueryClient, QueryClientProvider } from "@tanstack/react-query";
import { Routes } from "@/routes/Routes.tsx";
import { GBEmuProvider } from "@/context/GBEmuContext.tsx";

const queryClient = new QueryClient();

createRoot(document.getElementById("root")!).render(
  <StrictMode>
    <QueryClientProvider client={queryClient}>
      <GBEmuProvider>
        <Routes />
      </GBEmuProvider>
    </QueryClientProvider>
  </StrictMode>,
);
