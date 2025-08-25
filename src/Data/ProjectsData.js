import { PiCableCar } from "react-icons/pi";

class Project
{
  constructor(title, description, link, logo, category, targetPlatforms, distributionPlatforms, status)
  {
    this.title = title;
    this.description = description;
    this.link = link;
    this.logo = logo;
    this.category = category;
    this.targetPlatforms = targetPlatforms;
    this.distributionPlatforms = distributionPlatforms;
    this.status = status;
  }
}

let categories = {
  experimental : "experimental",
  team : "team",
  solo: "solo",
}
let targetPlatforms = {
  PC: "pc",
  Mobile: "Mobile",

}

let distributionPlatforms = 
{
  github : "github",
  itchio : "itchio",
  exe:"exe",
  playStore: "playStore",
}

let gameState =
{
  Finished: "Concluido",
  Soon: "Em breve",
  OpenBeta: "Beta aberto",
  ClosedBeta: "Beta fechado",
  ClosedAlpha: "Alpha fechado",

} 

const experimentalProjects = [
  new Project(
        "Space Odyssey",
        "Jogo 2D feito em C, Baseado no Space Invaders Atari. Além disso, o jogo conta com um menu criado " + 
        "utilizando a tecnica raycast, a mesma usada no jogo doom e wolfenstein 3D.",
        "https://github.com/JoaoArgento/Raycast-C.git",
        "./assets/Images/SpaceOdyssey.png",
        categories.experimental,
        [targetPlatforms.PC],
        [distributionPlatforms.github],
        gameState.Finished,
    ),

  new Project(
      "Fish Ops",
      "Jogo de sobrevivência 2.5D feito em uma GAME JAM em duplas. Minha dupla foi o artista Jorge Azevedo.",
      "",
      "./assets/Images/FishOps.gif",
      categories.experimental,
      [targetPlatforms.PC],
      [distributionPlatforms.exe, distributionPlatforms.github],
      gameState.Soon,
    ),

  new Project(
      "Guns and skulls",
      "Jogo top-down 3D baseado no modo zumbi do jogo call of duty. feito utilizando game engine Unity, em conjunto com mais 3 pessoas",
      "",
      "./assets/Images/GunsAndSkulls.png",
      categories.experimental,
      [targetPlatforms.PC],
      [distributionPlatforms.exe, distributionPlatforms.github, distributionPlatforms.itchio],
      gameState.Soon,
    ),

  new Project(
      "Guitar game",
      "Minigame de guitarra inspirado no jogo Guitar hero em conjunto com mais 3 pessoas",
      "",
      "./assets/Images/UltimaChance.png",
      categories.experimental,
      [targetPlatforms.PC],
      [distributionPlatforms.exe, distributionPlatforms.github],
      gameState.Finished,
    ),
]

const teamProjects = [
  
    new Project(
        "Idle Miner",
        "Jogo de Idle 2D",
        "",
        "./assets/Images/IdleMiner.png",
        categories.team,
        [targetPlatforms.Mobile],
        [distributionPlatforms.playStore],
        gameState.ClosedAlpha,
    ),

    new Project(
      "Última chance",
      "Jogo de exploração feito utilizando game engine Unity, em conjunto com mais 3 pessoas",
      "",
      "./assets/Images/UltimaChance.png",
      categories.team,
      [targetPlatforms.PC],
      [distributionPlatforms.itchio, distributionPlatforms.exe],
      gameState.Soon,
    ),

]

const soloProjects = [
  new Project(
    "Pong Multiplayer",
    "Replica do jogo pong de 1972, Porém em multiplayer local. Fiz esse jogo para praticar minhas habilidades "+
    "em netcode for gameObjects",
    "",
    "./assets/Images/...AColocar!!!",
    categories.solo,
    [targetPlatforms.PC],
    [distributionPlatforms.exe, distributionPlatforms.github],
    gameState.Soon,
  ),
]

const categorizedProjects = 
{
  experimental: experimentalProjects,
  team: teamProjects,
  solo: soloProjects,
}
export {categorizedProjects};


