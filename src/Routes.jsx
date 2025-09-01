import {Route, Routes, BrowserRouter, HashRouter} from "react-router-dom"
import App from "./Pages/App"
import Projects from "./Pages/Projects"
import About from "./Pages/About"
import { LanguageProvider } from "./Components/LanguageProvider"

export default function MainRoutes()
{
    return <BrowserRouter basename="/">
        <LanguageProvider>
            <Routes>
                <Route path = "/" element = {<App/>}></Route>
                <Route path = "/projects" element = {<Projects/>}></Route>
                <Route path = "/about" element = {<About/>}></Route>
            </Routes>
        </LanguageProvider>
    </BrowserRouter>
}


