#include <iostream>
#include <string>

#include "renderer.h"

Renderer::Renderer(
  const std::size_t screen_width,
  const std::size_t screen_height)
    : screen_width(screen_width),
      screen_height(screen_height) {

  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize." << std::endl;
    std::cerr << "SDL2_Error: " << SDL_GetError() << std::endl;
  }

  //Set texture filtering to linear
  if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
    std::cerr << "Warning! Linear texture filtering not enabled." << std::endl;
  }

  // Create Window
  sdl_window = 
    SDL_CreateWindow(
      "Game", 
      SDL_WINDOWPOS_CENTERED,
      SDL_WINDOWPOS_CENTERED, 
      screen_width,
      screen_height, 
      SDL_WINDOW_SHOWN);

  if (sdl_window == NULL) {
    std::cerr << "Window could not be created." << std::endl;
    std::cerr << "SDL2_Error: " << SDL_GetError() << std::endl;
  }

  // Create renderer
  sdl_renderer = 
    SDL_CreateRenderer(
      sdl_window, 
      -1, 
      SDL_RENDERER_ACCELERATED
      | SDL_RENDERER_PRESENTVSYNC);

  if (sdl_renderer == NULL) {
    std::cerr << "Renderer could not be created." << std::endl;
    std::cerr << "SDL2_Error: " << SDL_GetError() << std::endl;
  }

  //Initialize renderer color
	SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0x1E);

  //Initialize PNG loading
  int imgFlags = IMG_INIT_PNG;
  if(!(IMG_Init( imgFlags ) & imgFlags)) {
    std::cerr << "SDL2_image could not initialize." << std::endl;
    std::cerr << "SDL2_Error: " << IMG_GetError() << std::endl;
  }
}

// Destroy SDL elements with appropriate methods.
Renderer::~Renderer() {
  SDL_DestroyRenderer(sdl_renderer);
  SDL_DestroyWindow(sdl_window);
  IMG_Quit();
  SDL_Quit();
}

SDL_Renderer* Renderer::getRenderer() {
  return sdl_renderer;
}

void Renderer::UpdateWindowTitle(int score, int hp) {
  std::string title{
    "Swarmed Score: " 
    + std::to_string(score) 
    + " HP: " + std::to_string(hp)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}
