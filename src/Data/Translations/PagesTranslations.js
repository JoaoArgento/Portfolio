const menuTranslations = 
{
    projectButton: 
    {
        en: "See my projects",
        pt_br: "Ver meus projetos",
    }

}

class Journey 
{
    constructor(occupation, date)
    {
        this.occupation = occupation;
        this.date = date;
    }
}

const aboutTranslations = {
    aboutMe:
    {
        en: 
        {
            title: "About me",
            text: "I've been working professionally in this field for over four years, focusing on game development, using Unity as my primary tool." +
            " I've always been driven by curiosity, especially about complex systems and how they work under the hood." +
            "This motivation led me to deepen my knowledge of programming and code architecture. " + 
            "Currently, my main focus is to continue developing my ability to solve complex problems with simple solutions, keeping the project organized and maintainable.",
        },
        pt_br:
        {
            title: "Sobre mim",
            text: " Trabalho profissionalmente na área há mais de quatro anos, com foco no desenvolvimento de jogos, utilizando o Unity como minha principal ferramenta." +
                "Sempre fui movido pela curiosidade, especialmente por sistemas complexos e como eles funcionam por debaixo dos panos." +
                "Essa motivação me levou a aprofundar meus conhecimentos em programação e arquitetura de código." +
                "Atualmente, meu principal foco é continuar desenvolvendo minha capacidade de resolver problemas complexos com soluções simples, mantendo o projeto organizado e fácil de manter.",
        }, 
    },

    experience:
    {
        en: 
        {
            title: "Experience",
            programmingLanguageText: "Programming languages"
            
        },
        pt_br:
        {
            title: "Experiências",
            programmingLanguageText: "Linguagens de programação"

        }, 
    },
    journey:
    {
        en: 
        {
            title: "Journey",
            journeys: [new Journey("Game Development Instructor at SuperGeeks", "2021 - present"),
                        new Journey("Personal projects development", "2020 - present"),
                        new Journey("Technologist in digital games - FATEC São Caetano do sul", "2022 - present"),
                        ]
        },
        pt_br:
        {
            title: "Minha jornada",
            journeys: [new Journey("Instrutor de desenvolvimento de jogos na SuperGeeks", "2021 - presente"),
            new Journey("Desenvolvimento de projetos pessoais", "2020 - presente"),
            new Journey("Tecnólogo em jogos digitais - FATEC São Caetano do sul", "2022 - presente"),
            ]
           
        }, 
    },
    cvButton:
    {
        en: 
        {
            text: "Download CV",
            link: "./assets/Curriculos/CurriculoIngles.pdf",
        },
        
        pt_br: 
        {
            text: "Baixar CV",
            link: "./assets/Curriculos/Curriculo.pdf",
        },
    },

    programmingLanguage:
    {
        en: "Programming Languages",
        pt_br: "Linguagens de programação",
    },

    present:
    {
        en: "Present",
        pt_br: "Presente",
    }

}


export {menuTranslations, aboutTranslations}
