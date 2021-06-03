#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "keyboard.h"
#include "game.h"
#include "renderer.h"
#include "media.h"
#include "texture.h"

int main(int argc, char* args[]) {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  //constexpr std::size_t kScreenWidth{640};
  //constexpr std::size_t kScreenHeight{480};
  const int kScreenWidth = 640;
  const int kScreenHeight = 480;

  Renderer renderer(kScreenWidth, kScreenHeight);
  SDL_Renderer* rendererPtr = renderer.getRenderer();
  //Media gameMedia(rendererPtr);
  //std::vector<Texture*> textures = gameMedia.getTextures();

  //Main loop flag
  bool quit = false;

  //Event handler
  SDL_Event e;

  SDL_Texture* texture = NULL;
  std::string path = "../textures/testTexture.png";
  SDL_Surface* surface = IMG_Load(path.c_str());
  texture = SDL_CreateTextureFromSurface(rendererPtr, surface);
  SDL_FreeSurface(surface);


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

    SDL_RenderCopy(rendererPtr, texture, NULL, NULL);

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