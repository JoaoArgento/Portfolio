import { motion } from "framer-motion";
import { SiUnity, SiGodotengine, SiC, SiCplusplus, SiJavascript,  } from "react-icons/si";
import { TbBrandCSharp, TbRadar } from "react-icons/tb";
import { useTypewriter } from "react-simple-typewriter";
import typewriterInfo from "../functions/TextDatabase.js"
import { useRef, useState } from "react";

export default function Hero()
{
    const originalText = ["Game Programmer", "Game Designer"]
    const [currentText, SetCurrentText] = useState(originalText);
    const nextTechRef = useRef(null);
    const typedText = useRef("");
    
    const handleMouseEnter = (lang) => {
        nextTechRef.current = lang;
    };
  
    const handleMouseLeave = () => {
        nextTechRef.current = null;
    };

    const handleLoopDone = () =>
    {
        typedText.current = typedText.current.slice(0, typedText.current.length-1);
       

        if (typedText.current.length === 0 && nextTechRef.current)
        {
            console.log("tem lang");
            SetCurrentText(typewriterInfo.programmingTexts[nextTechRef.current]);
            nextTechRef.current = null;
        }
    };
    const [text, count] = useTypewriter({
        words: currentText,
        loop:false,
        cursorStyle: "_",
        typeSpeed: 60,
        deleteSpeed: 40,
        delaySpeed: 1500,
        onDelete: () => {handleLoopDone()},

        onType: (char) =>
        {
            typedText.current += char;
        }
    })
    return <div className = {`flex flex-col items-center justify-center px-4 min-h-[calc(100vh-5rem)]`}>

        <div className = "max-w-2xl text-center">
            <h1 className = "text-2xl font-extrabold mb-7">
                <p className = "min-h-[1.5rem] inline-block min-w-[200px] text-center ">
                    {text || <span className = "invisible">Pai ficou off</span>}
                </p>
            </h1>

        
            <a href ="./projects" className = "bg-indigo-600 hover:bg-hover-700 text-white px-6 py-3 rounded-lg font-medium transtion duration 300">
                Ver meus projetos
            </a>

        </div>
        <div className = "mt-10 flex flex-wrap justify-center gap-4">
            <span onMouseEnter = {() => {handleMouseEnter("Unity")}} className = "flex items-center gap-2 bg-white/10 px-3 py-1 rounded-full text-sm hover:scale-[1.1] transition-transform duration-200">
                <SiUnity/>
            </span>
            
            <span onMouseEnter = {() => {handleMouseEnter("Godot")}}className = "flex items-center gap-2 bg-white/10 px-3 py-1 rounded-full text-sm hover:scale-[1.1] transition-transform duration-200">
                <SiGodotengine/>
            </span>

            <span onMouseEnter = {() => {handleMouseEnter("C")}} className = "flex items-center gap-2 bg-white/10 px-3 py-1 rounded-full text-sm hover:scale-[1.1] transition-transform duration-200">
                <SiC/>
            </span>

            <span onMouseEnter = {() => {handleMouseEnter("Cplusplus")}} className = "flex items-center gap-2 bg-white/10 px-3 py-1 rounded-full text-sm hover:scale-[1.1] transition-transform duration-200">
                <SiCplusplus/>
            </span>

            <span onMouseEnter = {() => {handleMouseEnter("Csharp")}} className = "flex items-center gap-2 bg-white/10 px-3 py-1 rounded-full text-sm hover:scale-[1.1] transition-transform duration-200">
                <TbBrandCSharp/>
            </span>

            <span onMouseEnter = {() => {handleMouseEnter("Javascript")}} className = "flex items-center gap-2 bg-white/10 px-3 py-1 rounded-full text-sm hover:scale-[1.1] transition-transform duration-200">
                <SiJavascript/>
            </span>
        </div>

    </div>
}