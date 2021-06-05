#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "keyboard.h"
#include "game.h"
#include "renderer.h"
#include "texture.h"
#include "timer.h"
#include "aim.h"
#include "player.h"

int main(int argc, char* args[]) {
  constexpr std::size_t kScreenWidth{700};
  constexpr std::size_t kScreenHeight{700};

  Renderer renderer(kScreenWidth, kScreenHeight);
  SDL_Renderer* rendererPtr = renderer.getRenderer();

  // Prepare Texture objects
  Texture markTexture(rendererPtr);
  Texture mainPlayerTexture(rendererPtr);

  //Load SDL_Texture from files
  markTexture.loadFromFile("../textures/testTexture.png");
  mainPlayerTexture.loadFromFile("../textures/testTexture.png");

  Aim mark(std::move(markTexture));

  //Create Game elements: Pass pointers to Game object.
  Player mainPlayer(
    kScreenWidth, 
    kScreenHeight,
    std::move(mainPlayerTexture)); 

  //Create Timer instance for frame independent movement control
  //This is better to create also in the Game object...
  Timer stepTimer;

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
      //Handle input for the player
      mainPlayer.handleEvent(e);
      mark.handleEvent(e);
    }

    //Calculate time step
    float timeStep = stepTimer.getTicks() / static_cast<float>(1000);

    //Move the player
		mainPlayer.move(timeStep);

    //Restart step timer
		stepTimer.start();

    //Clear screen
    SDL_RenderClear(rendererPtr);

    //Render objects
	  mainPlayer.render();
    mark.render();

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