#include <iostream>

#include "keyboard.h"
#include "game.h"
#include "renderer.h"

int main(int argc, char* args[]) {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{700};
  constexpr std::size_t kScreenHeight{700};
  constexpr std::size_t kGridWidth{70};
  constexpr std::size_t kGridHeight{70};

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);

  Keyboard controller;
  Game game(kGridWidth, kGridHeight);
  game.Run(controller, renderer, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";
  return 0;
}