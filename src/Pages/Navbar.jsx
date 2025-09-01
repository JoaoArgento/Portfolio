import React from "react";
import { Link } from "react-router-dom";
import { LuCode } from "react-icons/lu"; 
import {navbarTranslations} from "../Data/Translations/ComponentTranslations.js";
import { UseLanguage } from "../Components/LanguageProvider.jsx";
import LanguageDropdown from "../Components/LanguageDropdown.jsx"
const pages = {
    home: {name: "home", url: "/"},
    projects: {name: "projects", url: "/projects"},
    about: {name: "about", url: "/about"}

}

export default function Navbar(props)
{
    const {currentLanguage, ChangeLanguage} = UseLanguage();


    return <nav className = "w-full px-6 py-4 flex justify-between items-center bg-black bg-opacity-10 text-white fixed top-0 left-0 z-50 shadow-md backdrop-blur-md">
            <div className= {`bg-black ${props.IsMatrixMode ? "text-green-400" : "text-indigo-400"} transition-text-color duration-300 font-mono text-xl p-4`}>
            <span onClick={() => props.SetMatrixMode() } 
            className={`mr-2 text-white inline-block transition-rotate duration-300 ${props.IsMatrixMode ? "rotate-90" : "rotate-0"}`} 
            style = {{cursor: "default"}} >❯</span>joao.dev<span className="animate-pulse">_</span>
            </div>
                 <ul className="hidden md:flex gap-6 font-medium">
                    {
                        Object.entries(pages).map(([index, page]) =>
                        {
                            const pageInfo = navbarTranslations[page.name][currentLanguage];
                            let pageName = page.name;

                            if (pageInfo)
                            {
                                pageName = pageInfo;
                            }
                            
                           return <li key = {index}><Link to = {page.url} className = "text-xl hover:text-gray-400 flex items-center gap-2 group transition-all">
                                    <LuCode className="scale-0 group-hover:scale-100 opacity-100 transition duration-300"/>{pageInfo}</Link>
                                </li>
                        })
                    }
                    <LanguageDropdown/>
                </ul>
            </nav>
}