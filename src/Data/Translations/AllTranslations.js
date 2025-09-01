import { projectTranslations, gameStateTranslations } from "./ProjectTranslations";
import { aboutTranslations, menuTranslations } from "./PagesTranslations";
import { navbarTranslations, footerTranslations } from "./ComponentTranslations";
const translationType = 
{
    gameState: "gameState",
    projectInfo: "projectInfo",
    navbar: "navbar",
    about: "about",
    mainMenu: "mainMenu",
    footer: "footer",
}

const allTranslations = {
    gameState: gameStateTranslations,
    projectInfo: projectTranslations,
    about: aboutTranslations,
    navbar: navbarTranslations,
    footer: footerTranslations,
}


function GetTranslationByType(translationType, type, language)
{
    let translations = allTranslations[translationType];

    if (!translations)
    {
        console.log("Não foi encontrado a tradução para esse item")
        return null;
    }

    if (type == "all")
        return translations[type];

    if (!translations[type])
    {
        console.log(`${type} não foi encontrado nas traduções!`);
        return null;
    }

    if (!translations[type][language])
    {
        console.log(`${type} não foi encontrado nesse idioma! ${language}`);
        return null;
    }
    return translations[type][language];
}

export {translationType, GetTranslationByType};
