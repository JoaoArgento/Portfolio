let availableLanguages = ["en", "pt_br"]
let currentLanguage = "pt_br";


function SetCurrentLanguage(newLanguage)
{
    if (!availableLanguages.includes(newLanguage))
    {
        console.log("este idioma não está disponivel!");
    }
    currentLanguage = newLanguage;
}

function GetCurrentLanguage() { return currentLanguage; }

export {SetCurrentLanguage, GetCurrentLanguage};