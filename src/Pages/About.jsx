import { Link } from "react-router-dom";
import Layout from "./Layout";
import { GetCurrentLanguage } from "../Data/Translations/TranslationInfo";
import { aboutTranslations } from "../Data/Translations/PagesTranslations";
import { UseLanguage } from "../Components/LanguageProvider";
function AboutSection()
{
    const {currentLanguage, ChangeLanguage} = UseLanguage();
    
    return <section className = "flex flex-col justify-center items-center px-6 py-16 text-white">
        <div className="max-w-4xl w-full h-full ">
            <h2 className = "text-4xl font-bold mb-6 text-center"> 
                {aboutTranslations.aboutMe[currentLanguage].title}
            </h2>
            <p className ="text-lg leading-relaxed text-zinc-300">
              {aboutTranslations.aboutMe[currentLanguage].text}
            </p>
            
            <h3 className="text-2xl font-semibold mt-10 mb-4 text-indigo-300">
                {aboutTranslations.experience[currentLanguage].title}
            </h3>

            <ul className = "space-y-2 text-zinc-200">
                <li>Unity - C#</li>
                <li>Godot - GDScript </li>
                <li>{aboutTranslations.experience[currentLanguage]["programmingLanguageText"]}: C, C++, C#, Python, Javascript</li>
                
            </ul>
                
            <h3 className="text-2xl font-semibold mt-10 mb-4 text-indigo-300">
                {aboutTranslations.journey[currentLanguage].title}
            </h3>
            
            <ul className = "space-y-2 text-zinc-200">
                {/* <li><strong>2021 - presente:</strong> Instrutor de desenvolvimento de jogos na SuperGeeks </li>
                <li><strong>2020 - presente:</strong> Desenvolvimento de projetos pessoais </li>
                <li><strong>2022 - 2025: </strong> Tecnólogo em jogos digitais - FATEC São Caetano do sul</li> */}
                {
                    aboutTranslations.journey[currentLanguage].journeys.map((journey, index) =>
                    {
                        return <li><strong>{journey.date}: </strong>{journey.occupation}</li>
                    })
                }
            </ul>

            <div className="flex flex-col items-center">
                <a  href = {aboutTranslations.cvButton[currentLanguage].link}
                download
                className = "mt-10 inline-block bg-green-600 hover:bg-green-700 text-white font-bold py-2 px-4 rounded transition duration-300"
                >
                {aboutTranslations.cvButton[currentLanguage].text}
            </a>

            </div>
          
        </div>
    </section>
}

export default function About()
{
    return <Layout mainContent={AboutSection}/>
}