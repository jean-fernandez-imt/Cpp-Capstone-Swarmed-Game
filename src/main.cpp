#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>

#include "parameters.h"
#include "renderer.h"
#include "texture.h"
#include "aim.h"
#include "player.h"
#include "gun.h"
#include "army.h"
#include "game.h"
#include "background.h"
#include "font.h"

int main(int argc, char* args[]) {
  constexpr std::size_t kScreenWidth{MAIN_SCREEN_WIDTH};
  constexpr std::size_t kScreenHeight{MAIN_SCREEN_HEIGHT};

  Renderer renderer(kScreenWidth, kScreenHeight);
  SDL_Renderer* rendererPtr = renderer.getRenderer();

  //Prepare Texture objects
  Texture markTexture(rendererPtr);
  Texture spaceshipTexture(rendererPtr);
  Texture bulletTexture(rendererPtr);

  Texture enemyArmyTexture1(rendererPtr);
  Texture enemyArmyTexture2(rendererPtr);
  Texture enemyArmyTexture3(rendererPtr);
  Texture enemyArmyTexture4(rendererPtr);
  Texture enemyArmyTexture5(rendererPtr);
  Texture enemyArmyTexture6(rendererPtr);

  Texture backgroundTexture1(rendererPtr);
  Texture backgroundTexture2(rendererPtr);
  Texture backgroundTexture3(rendererPtr);
  Texture backgroundTexture4(rendererPtr);
  Texture backgroundTexture5(rendererPtr);

  //Load SDL_Texture from files
  markTexture.loadFromFile("../textures/aim.png");
  spaceshipTexture.loadFromFile("../textures/spaceship.png");
  bulletTexture.loadFromFile("../textures/bullet.png");

  enemyArmyTexture1.loadFromFile("../textures/enemy1.png");
  enemyArmyTexture2.loadFromFile("../textures/enemy2.png");
  enemyArmyTexture3.loadFromFile("../textures/enemy3.png");
  enemyArmyTexture4.loadFromFile("../textures/enemy4.png");
  enemyArmyTexture5.loadFromFile("../textures/enemy5.png");
  enemyArmyTexture6.loadFromFile("../textures/enemy6.png");

  backgroundTexture1.loadFromFile("../textures/space1.png");
  backgroundTexture2.loadFromFile("../textures/space2.png");
  backgroundTexture3.loadFromFile("../textures/space3.png");
  backgroundTexture4.loadFromFile("../textures/space4.png");
  backgroundTexture5.loadFromFile("../textures/space5.png");

  //Prepare Fonts (WIP)
  Font titleFont(
    "../fonts/space-mavericks/SpaceMavericks-qZo91.ttf",
    MAIN_TITLE_FONT_SIZE);
  Font highscoresFont(
    "../fonts/press-start-2p/PressStart2P.ttf",
    MAIN_HIGHSCORES_FONT_SIZE);

  //Create Game elements
  Player spaceship(
    kScreenWidth, 
    kScreenHeight,
    std::move(spaceshipTexture));
  
  Gun spaceshipGun(
    kScreenWidth, 
    kScreenHeight,
    std::move(bulletTexture),
    &spaceship);

  Aim mark(std::move(markTexture));

  Army enemyArmy(
    kScreenWidth, 
    kScreenHeight,
    &spaceship,
    std::move(enemyArmyTexture1),
    std::move(enemyArmyTexture2),
    std::move(enemyArmyTexture3),
    std::move(enemyArmyTexture4),
    std::move(enemyArmyTexture5),
    std::move(enemyArmyTexture6));

  Background background(
    std::move(backgroundTexture1),
    std::move(backgroundTexture2),
    std::move(backgroundTexture3),
    std::move(backgroundTexture4),
    std::move(backgroundTexture5));
  
  Game swarmed(
    &renderer, 
    &mark,
    &spaceship,
    &spaceshipGun,
    &enemyArmy,
    &background,
    &titleFont);

  swarmed.run();

  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << swarmed.getScore() << "\n";

  return 0;
}