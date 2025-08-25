import React from "react";
import {Link} from "react-router-dom";
import Layout from "./Layout";
import { FaItchIo } from "react-icons/fa";
import {categorizedProjects} from "../Data/ProjectsData.js"
import ProjectCard from "../Components/ProjectCard.jsx";


function RenderSection(title, titleColor, items) 
{
  const targetColor = {
      white: "text-white-500",
      yellow: "text-yellow-500",
      orange: "text-orange-500",
      blue: "text-blue-500",

  }[titleColor]

  return <>
        <h3 className = "text-2xl font-bold text-white mt-10 mb-4">{title}</h3>
        <div className = "grid gap-6 md:grid-cols-2 lg:grid-cols-3 max-w-5xl">
            {
              items.map((project, index) => 
              {
                // const targetPlatform = project.distributionPlatforms[0];
                // const targetPlatformstyle = styleByPlatform[targetPlatform];

                return   <ProjectCard 
                            key = {index}
                            project = {project}
                            fontColor = {targetColor}/>
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