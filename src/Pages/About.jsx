import { Link } from "react-router-dom";
import Layout from "./Layout";

function AboutSection()
{
    return <section className = "flex flex-col justify-center items-center px-6 py-16 text-white">
        <div className="max-w-4xl w-full h-full ">
            <h2 className = "text-4xl font-bold mb-6 text-center"> 
                Sobre mim
            </h2>
            <p className ="text-lg leading-relaxed text-zinc-300">
               Trabalho profissionalmente na área há mais de quatro anos, com foco no desenvolvimento de jogos, utilizando o Unity como minha principal ferramenta.
                <br/>
                <br/>
                Sempre fui movido pela curiosidade, especialmente por sistemas complexos e como eles funcionam por debaixo dos panos.
                <br/>
                <br/>
                Essa motivação me levou a aprofundar meus conhecimentos em programação e arquitetura de código.
                Atualmente, meu principal foco é continuar desenvolvendo minha capacidade de resolver problemas complexos com soluções simples, mantendo o projeto organizado e fácil de manter.

            </p>
            
            <h3 className="text-2xl font-semibold mt-10 mb-4 text-indigo-300">
                Experiências
            </h3>

            <ul className = "space-y-2 text-zinc-200">
                <li>Unity - C#</li>
                <li>Godot - GDScript </li>
                <li>Linguagens de programação: C, C++, C#, Python, Javascript</li>
                
            </ul>
                
            <h3 className="text-2xl font-semibold mt-10 mb-4 text-indigo-300">
                Minha jornada
            </h3>
            
            <ul className = "space-y-2 text-zinc-200">
                <li><strong>2021 - presente:</strong> Instrutor de desenvolvimento de jogos na SuperGeeks </li>
                <li><strong>2020 - presente:</strong> Desenvolvimento de projetos pessoais </li>
                <li><strong>2022 - 2025: </strong> Tecnólogo em jogos digitais - FATEC São Caetano do sul</li>

            </ul>

            <div className="flex flex-col items-center">
                <a  href = "./assets/Curriculos/Curriculo.pdf"
                download
                className = "mt-10 inline-block bg-green-600 hover:bg-green-700 text-white font-bold py-2 px-4 rounded transition duration-300"
                >
                Baixar CV
            </a>

            </div>
          
        </div>
    </section>
}

export default function About()
{
    return <Layout mainContent={AboutSection}/>
}