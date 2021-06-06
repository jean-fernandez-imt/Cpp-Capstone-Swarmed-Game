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
  Texture spaceshipTexture(rendererPtr);

  //Load SDL_Texture from files
  markTexture.loadFromFile("../textures/aim.png");
  spaceshipTexture.loadFromFile("../textures/Spaceship.png");

  Aim mark(std::move(markTexture));

  //Create Game elements: Pass pointers to Game object.
  Player spaceship(
    kScreenWidth, 
    kScreenHeight,
    std::move(spaceshipTexture)); 

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
      spaceship.handleEvent(e);
      mark.handleEvent(e);
    }

    //Calculate time step
    float timeStep = stepTimer.getTicks() / static_cast<float>(1000);

    //Rotate the player
    spaceship.updateAngle(mark.getPosition());

    //Move the player
		spaceship.move(timeStep);

    //Restart step timer
		stepTimer.start();

    //Clear screen
    SDL_RenderClear(rendererPtr);

    //Render objects
	  spaceship.render();
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