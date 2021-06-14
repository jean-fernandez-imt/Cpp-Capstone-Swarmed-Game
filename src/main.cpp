#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "parameters.h"
#include "renderer.h"
#include "texture.h"
#include "aim.h"
#include "player.h"
#include "gun.h"
#include "army.h"
#include "game.h"

int main(int argc, char* args[]) {
  constexpr std::size_t kScreenWidth{MAIN_SCREEN_WIDTH};
  constexpr std::size_t kScreenHeight{MAIN_SCREEN_HEIGHT};

  Renderer renderer(kScreenWidth, kScreenHeight);
  SDL_Renderer* rendererPtr = renderer.getRenderer();

  // Prepare Texture objects
  Texture markTexture(rendererPtr);
  Texture spaceshipTexture(rendererPtr);
  Texture bulletTexture(rendererPtr);
  Texture enemyArmyTexture(rendererPtr);

  //Load SDL_Texture from files
  markTexture.loadFromFile("../textures/aim.png");
  spaceshipTexture.loadFromFile("../textures/spaceship.png");
  bulletTexture.loadFromFile("../textures/bullet.png");
  enemyArmyTexture.loadFromFile("../textures/enemy.png");

  Aim mark(std::move(markTexture));

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

  Army enemyArmy(
    kScreenWidth, 
    kScreenHeight,
    &spaceship,
    std::move(enemyArmyTexture));
  
  Game swarmed(
    &renderer, 
    &mark,
    &spaceship,
    &spaceshipGun,
    &enemyArmy);

  swarmed.run();

  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << swarmed.getScore() << "\n";

  return 0;
}