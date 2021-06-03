#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

#include "texture.h"
#include "snake.h"

class Renderer {
  public:
    Renderer (
      const int screen_width, 
      const int screen_height);
      
    ~Renderer();

    SDL_Renderer* getRenderer();

    //void Render(Snake const snake, SDL_Point const &food);
    //void render(std::vector<Texture*> textures);
    void UpdateWindowTitle(int score, int fps);

  private:
    SDL_Window* sdl_window;
    SDL_Renderer* sdl_renderer;

    const std::size_t screen_width;
    const std::size_t screen_height;
};

#endif