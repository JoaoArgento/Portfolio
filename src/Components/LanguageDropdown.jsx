import React, {useState} from "react";
import { UseLanguage } from "./LanguageProvider";

export default function LanguageDropdown()
{
    const {currentLanguage, ChangeLanguage} = UseLanguage();
    const [isOpen, SetIsOpen] = useState(false);

    const languages = [
        {
             code: "en", 
             label: "English"
        },
        {
            code: "pt_br",
            label: "Português"
        }
    ]
    
    return (<div className = "relative">
        <button onClick={() => SetIsOpen(!isOpen)}
        className = "px-3 py-2 bg-gray-800 text-white rounded-md flex items-center gap-2 hover:bg-gray-700 transition">

            🌐 {languages.find((l) => l.code === currentLanguage)?.label}
        </button>

        {isOpen && (
            <ul className = "absolute right-0 mt-2 w-40 bg-gray-900 border border-gray-700 rounded-lg shadow-lg z-50">
                {
                    languages.map((language) =>
                    {
                        return <li key = {language.code}>
                            <button
                            onClick={() =>
                            {
                                ChangeLanguage(language.code);
                                SetIsOpen(false);
                            }}
                            className = {`block w-full text-left px-4 py-2 hover:bg-gray-700 transition ${
                                currentLanguage == language.code ? "bg-gray-800 text-indigo-400" : "text-white"
                            }`}>
                            {language.label}
                            </button>
                        </li> 
                    })
                }
            </ul>
        )}

    </div>);
}
