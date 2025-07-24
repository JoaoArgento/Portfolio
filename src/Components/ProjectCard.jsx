import { color } from "framer-motion";
import React from "react";

const buttonTypes = 
{
  playStore: 
  {
      color: "bg-gradient-to-r from-[#0f9d58] to-[#34a853]",
      innerText: "Play store",
  },
  itchio: 
  {
    color: "bg-[#C71585]",
    innerText: "Itch.io",
  },
  github:
  {
    color: "bg-[#FF8C00]",
    innerText: "Source code",
  },

  exe:
  {
    color: "bg-[#1E90FF]",
    innerText: "EXE",
  }
}

export default function ProjectCard(props)
{
    return  <a key = {props.key}
            href = {props.project.link}
            target = "_blank"
            rel ="noopener noreferrer"
            className ="card-shine bg-gradient-to-t from-[#1e1e2] to-[#2c2c3c] rounded-lg shadow-md p-4 max-w-sm transition-transform duration-300 hover: scale-[1.02] shadow-md">
                        
                        <div className = "w-full h-full flex flex-col items-center justify-between">
                           <h3 className ={`text-xl font-semibold ${props.fontColor}`}>{props.project.title}</h3>

                            <h3 className = "text-md text-cyan-300">
                              {props.project.platforms.join(", ")}
                            </h3>

                          <div className = "overflow-hidden rounded-md my-2">
                            <img src = {props.project.logo}
                                alt ="gameLogo"
                              className="rounded-md -w-full h-40 object-cover transition-transform duration-300 hover:scale-105"
                            
                            />
                          </div>

                          <p className="text-white-400">{props.project.description}</p>

                         {
                          props.project.availablePlatforms.map((platform, index) =>
                          {
                            const buttonStyle = buttonTypes[platform]
                            const nameWithoutSpace = props.project.title.replace(" ", "");
                              if (platform == "exe")
                              {
                                  return <a key = {index} 
                                  href = {`./src/assets/EXEs/${nameWithoutSpace}Exe.zip`}
                                  download
                                  rel = "noopener noreferrer"
                                  className = {`disabled inline-block align-center mt-4 px-4 py-2 text-white rounded hover:brightness-104 transition ${buttonStyle.color}`}
                                >
                                {`${buttonStyle.innerText}`}
                                </a> 
                              }
                              return <a key = {index} 
                                      href = {props.project.link} 
                                      target = "_blank"
                                      rel = "noopener noreferrer"
                                      className = {` disabled inline-block align-center mt-4 px-4 py-2 text-white rounded hover:brightness-104 transition ${buttonStyle.color}`}
                                    >
                                    {`${buttonStyle.innerText} (${props.project.status})`}
                                    </a> 

                          })
                        } 
                       
                        </div>
                  </a>
}