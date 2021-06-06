#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "game.h"

int main(int argc, char* args[]) {
  constexpr std::size_t kScreenWidth{700};
  constexpr std::size_t kScreenHeight{700};

  Renderer renderer(kScreenWidth, kScreenHeight);
  SDL_Renderer* rendererPtr = renderer.getRenderer();

  // Prepare Texture objects
  Texture markTexture(rendererPtr);
  Texture spaceshipTexture(rendererPtr);

  //Load SDL_Texture from files
  markTexture.loadFromFile("../textures/aim.png");
  spaceshipTexture.loadFromFile("../textures/Spaceship.png");

  Aim mark(std::move(markTexture));

  //Create Game elements
  Player spaceship(
    kScreenWidth, 
    kScreenHeight,
    std::move(spaceshipTexture));

  Game untitled(rendererPtr, &mark, &spaceship);
  untitled.run();
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << untitled.getScore() << "\n";

  return 0;
}