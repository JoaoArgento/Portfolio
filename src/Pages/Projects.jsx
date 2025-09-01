import React from "react";
import {Link} from "react-router-dom";
import Layout from "./Layout";
import { FaItchIo } from "react-icons/fa";
import {categorizedProjects} from "../Data/ProjectsData.js"
import ProjectCard from "../Components/ProjectCard.jsx";
import { translationType, GetTranslationByType } from "../Data/Translations/AllTranslations.js";
import { UseLanguage } from "../Components/LanguageProvider.jsx";

function RenderSection(title, titleColor, items) 
{
  const targetColor = {
      white: "text-white-500",
      yellow: "text-yellow-500",
      orange: "text-orange-500",
      blue: "text-blue-500",

  }[titleColor]

  const {currentLanguage, ChangeLanguage} = UseLanguage();


  return <>
        <h3 className = "text-2xl font-bold text-white mt-10 mb-4">{title}</h3>
        <div className = "grid gap-6 md:grid-cols-2 lg:grid-cols-3 max-w-5xl">
            {
              items.map((project, index) => 
              {
            
                const projectInfo = GetTranslationByType(translationType.projectInfo, project.gameType, currentLanguage);
                const projectState = GetTranslationByType(translationType.gameState, project.gameState, currentLanguage);
                                
                let projectDescription = ""
                if (projectInfo != null)
                {
                  projectDescription = projectInfo.description;
                }

                return   <ProjectCard 
                            key = {index}
                            project = {project}
                            fontColor = {targetColor}
                            projectDescription = {projectDescription}
                            projectState = {projectState}/>
              })
            }
        </div>
  
  </> 
}

function RenderAllProjects()
{
 return <div className = "w-full h-full relative">
       <section className="text-white min-h-screen flex flex-col items-center py-10 px-5">

          {RenderSection("EXPERIMENTAL", "orange", categorizedProjects.experimental)}
          {RenderSection("SOLO", "orange", categorizedProjects.solo)}
          {RenderSection("PÓLEN STUDIOS", "orange", categorizedProjects.team)}
      </section>
  </div>
}

export default function Projects()
{ 
  return <Layout mainContent={RenderAllProjects}/>
}