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
      SDL_RENDERER_ACCELERATED);

  if (sdl_renderer == NULL) {
    std::cerr << "Renderer could not be created." << std::endl;
    std::cerr << "SDL2_Error: " << SDL_GetError() << std::endl;
  }

  //Initialize renderer color
	SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);

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

/*
void Renderer::Render(Snake const snake, SDL_Point const &food) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  // Render food
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
  block.x = food.x * block.w;
  block.y = food.y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);

  // Render snake's body
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  for (SDL_Point const &point : snake.body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Render snake's head
  block.x = static_cast<int>(snake.head_x) * block.w;
  block.y = static_cast<int>(snake.head_y) * block.h;
  if (snake.alive) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
  } else {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  }
  SDL_RenderFillRect(sdl_renderer, &block);

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}
*/

void Renderer::render(std::vector<Texture*> textures) {
  textures[0]->render();
}

void Renderer::UpdateWindowTitle(int score, int fps) {
  std::string title{"Snake Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}
