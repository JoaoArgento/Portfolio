
class Project
{
  constructor(title, description, link, logo, category, platforms, availablePlatforms, status)
  {
    this.title = title;
    this.description = description;
    this.link = link;
    this.logo = logo;
    this.category = category;
    this.platforms = platforms;
    this.availablePlatforms = availablePlatforms;
    this.status = status;
  }
}

const projects = [
    new Project(
      "Última chance",
      "Jogo de exploração feito utilizando game engine Unity, em conjunto com mais 3 pessoas",
      "",
      "./assets/Images/UltimaChance.png",
      "team",
      ["PC"],
      ["itchio"],
      "Em breve",
    ),
    new Project(
      "Guns and skulls",
      "Jogo top-down 3D baseado no modo zumbi do jogo call of duty. feito utilizando game engine Unity, em conjunto com mais 3 pessoas",
      "",
      "./assets/Images/GunsAndSkulls.png",
      "team",
      ["PC"],
      ["itchio"],
      "Em breve",
    ),

    new Project(
      "Fish Ops",
      "Jogo de sobrevivência 2.5D feito em uma GAME JAM",
      "",
      "./assets/Images/FishOps.gif",
      "indie",
      ["PC"],
      ["exe", "github"],
      "Em breve",
    ),

    new Project(
        "Idle Miner",
        "Jogo de Idle 2D",
        "",
        "./assets/Images/IdleMiner.png",
        "team",
        ["Mobile"],
        ["playStore"],
        "Beta fechado",
    ),

    new Project(
        "Space Odyssey",
        "Jogo 2D feito em C, Baseado no Space Invaders Atari. Além disso, o jogo conta com um menu criado " + 
        "utilizando a tecnica raycast, a mesma usada no jogo doom e wolfenstein 3D.",
        "https://github.com/JoaoArgento/Raycast-C.git",
        "./assets/Images/SpaceOdyssey.png",
        "indie",
        ["PC"],
        ["github"],
        "Concluido",
    ),
]

export {projects};


