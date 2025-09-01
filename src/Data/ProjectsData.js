import { PiCableCar } from "react-icons/pi";
let gameTypeEnum = 
{
    UltimaChance: "UltimaChance",
    FishOps: "FishOps",
    SpaceOdyssey: "SpaceOdyssey",
    PongMultiplayer: "PongMultiplayer",
    GunsAndSkulls: "GunsAndSkulls",
    IdleMiner: "IdleMiner",
    Fishmon: "Fishmon",
}
class Project
{
  constructor(title, description, link, logo, category, targetPlatforms, distributionPlatforms, gameState, gameType)
  {
    this.title = title;
    this.description = description;
    this.link = link;
    this.logo = logo;
    this.category = category;
    this.targetPlatforms = targetPlatforms;
    this.distributionPlatforms = distributionPlatforms;
    this.gameState = gameState;
    this.gameType = gameType;
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
  Finished: "Finished",
  Soon: "Soon",
  OpenBeta: "OpenBeta",
  ClosedBeta: "ClosedBeta",
  ClosedAlpha: "ClosedAlpha",

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
        gameTypeEnum.SpaceOdyssey,
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
      gameTypeEnum.FishOps,
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
      gameTypeEnum.GunsAndSkulls,
    ),

  // new Project(
  //     "Guitar game",
  //     "Minigame de guitarra inspirado no jogo Guitar hero feito em conjunto com mais 3 pessoas",
  //     "",
  //     "./assets/Images/UltimaChance.png",
  //     categories.experimental,
  //     [targetPlatforms.PC],
  //     [distributionPlatforms.exe, distributionPlatforms.github],
  //     gameState.Finished,
  //   ),
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
        gameTypeEnum.IdleMiner,
    ),

    new Project(
      "Última chance",
      "Jogo de exploração feito utilizando game engine Unity, feito em conjunto com mais 3 pessoas",
      "",
      "./assets/Images/UltimaChance.png",
      categories.team,
      [targetPlatforms.PC],
      [distributionPlatforms.itchio, distributionPlatforms.exe],
      gameState.Soon,
      gameTypeEnum.UltimaChance,
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
    gameTypeEnum.PongMultiplayer,
  ),

   new Project(
    "Fishmon",
    "Fishmon é um jogo de pesca inspirado em clássicos de captura e batalhas por turnos." + 
    "Explore rios, lagos e mares em busca de criaturas aquáticas únicas, cada uma com habilidades próprias. Use suas redes de pesca para capturar, monte sua equipe e enfrente batalhas estratégicas no melhor estilo RPG!",
    "https://joaozera1.itch.io/fishmon",
    "./assets/Images/Fishmon.png",
    categories.solo,
    [targetPlatforms.PC],
    [distributionPlatforms.github, distributionPlatforms.itchio],
    gameState.OpenBeta,
    gameTypeEnum.Fishmon,
  ),
]

const categorizedProjects = 
{
  experimental: experimentalProjects,
  team: teamProjects,
  solo: soloProjects,
}
export {categorizedProjects};


