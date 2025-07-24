import React, {useState} from "react";
import Footer from "./Footer";
import Hero from "./Hero";
import Navbar from "./Navbar";
import MatrixRain from "../Components/MatrixRain";
import MatrixTerminal from "../Components/MatrixTerminal";


export default function Layout({mainContent: MainContent})
{
    const [matrixMode, SetMatrixMode] = useState(false);

    const gradientClass = {
            purple: "from-[#8E2DE2] via-[#4A00E0] to-[#8E2DE2]",
            orange: "from-[#ff416c] via-[#ff4b2b] to-[#ff416c]",
            eletricPurple: "from-[#8e2de2] via-[#4a00e0] to-[#8e2de2]"
            }["eletricPurple"];
    
    return <div className={`${matrixMode ? "bg-black" :  `bg-gradient-to-r ${gradientClass}`}  text-white h-full pt-20 w-full`}>
                <div className = "w-full h-full relative">
                        <Navbar SetMatrixMode = {() => {SetMatrixMode(!matrixMode)}} IsMatrixMode = {matrixMode}/>
                
                        {MainContent && <MainContent/>}

                        {matrixMode && (<>
                        <MatrixTerminal DisableMatrixMode = {() => {SetMatrixMode(false)}}/>
                        <MatrixRain isActive={matrixMode}/></>
                        )}
                        <Footer />

                </div>
            </div>
  
}