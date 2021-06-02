#include <iostream>

#include "keyboard.h"
#include "game.h"
#include "renderer.h"
#include "media.h"

int main(int argc, char* args[]) {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{700};
  constexpr std::size_t kScreenHeight{700};
  constexpr std::size_t kGridWidth{70};
  constexpr std::size_t kGridHeight{70};

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  SDL_Renderer* rendererPtr = renderer.getRenderer();
  Media gameMedia(rendererPtr);
  std::vector<Texture*> textures = gameMedia.getTextures();

  //Main loop flag
  bool quit = false;

  //Event handler
  SDL_Event e;

  //While application is running
  while( !quit )
  {
    //Handle events on queue
    while( SDL_PollEvent( &e ) != 0 )
    {
      //User requests quit
      if( e.type == SDL_QUIT )
      {
        quit = true;
      }
    }

    //Clear screen
    //SDL_SetRenderDrawColor(rendererPtr, 0xFF, 0xFF, 0xFF, 0xFF );
    SDL_RenderClear(rendererPtr);

    //renderer.render(textures);

    SDL_RenderCopy(rendererPtr, textures[0]->getTexture(), NULL, NULL);

    //Update screen
    SDL_RenderPresent(rendererPtr);
  }

  /*
  Keyboard controller;
  Game game(kGridWidth, kGridHeight);
  game.Run(controller, renderer, kMsPerFrame);
  */
  std::cout << "Game has terminated successfully!\n";
  /*
  std::cout << "Score: " << game.GetScore() << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";
  */
  return 0;
}