import { createContext, useState, useContext } from "react";

const availableLanguages = ["en", "pt_br"]

const LanguageContext = createContext();


export function LanguageProvider({children})
{
    const [currentLanguage, SetCurrentLanguage] = useState("pt_br");
    
    function ChangeLanguage(newLanguage)
    {
        if (!availableLanguages.includes(newLanguage))
        {
            console.warn("Idioma não disponivel!");
            return;
        }
        SetCurrentLanguage(newLanguage);
        
    }

    return (
        <LanguageContext.Provider value = {{currentLanguage, ChangeLanguage}}>
            {children}
        </LanguageContext.Provider>

    )
}

export function UseLanguage()
{
    return useContext(LanguageContext);
}