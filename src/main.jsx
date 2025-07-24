import { Root } from "postcss";
import React from "react";
import { createRoot } from "react-dom/client";
import App from "./Pages/App";
import Hero from "./Pages/Hero";
import MainRoutes from "./Routes";

const ROOT_DIV = document.querySelector("#root");
const ROOT = createRoot(ROOT_DIV);
ROOT.render(<MainRoutes/>);
