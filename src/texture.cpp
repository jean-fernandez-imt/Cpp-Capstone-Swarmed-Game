#include <iostream>

#include "texture.h"

Texture::Texture(SDL_Renderer* renderer) {
	//Initialize
    _renderer = renderer;
	_texture = NULL;
	_width = 0;
	_height = 0;
}

Texture::~Texture() {
	//Deallocate
	release();
}

void Texture::loadFromFile(std::string path) {

	//Get rid of preexisting texture
	//release();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());

	if (loadedSurface == NULL) {
        std::cerr << "Unable to load image from: " << path.c_str() << std::endl;
        std::cerr << "SDL2_IMG_Error: " << IMG_GetError() << std::endl;
	} 

    //Create texture from surface pixels
    newTexture = SDL_CreateTextureFromSurface(_renderer, loadedSurface);
    
    if (newTexture == NULL) {
        std::cerr << "Unable to create texture from: " << path.c_str() << std::endl;
        std::cerr << "SDL2_Error: " << SDL_GetError() << std::endl;
    } 

    //Get rid of old loaded surface
    SDL_FreeSurface(loadedSurface);

	//Store as Texture
	_texture = newTexture;
}

void Texture::release() {
	//Free texture if it exists
	if (_texture != NULL) {
		SDL_DestroyTexture(_texture);
		_texture = NULL;
        _renderer = NULL;
		_width = 0;
		_height = 0;
	}
}

SDL_Texture* Texture::getTexture() {
	return _texture;
}

void Texture::render(
    int x, 
    int y, 
    SDL_Rect* crop, 
    double angle, 
    SDL_Point* center, 
    SDL_RendererFlip flip) {

	//Set rendering space and render to screen
	SDL_Rect renderQuad = {x, y, _width, _height};

	//Set clip rendering dimensions
	if (crop != NULL) {
		renderQuad.w = crop->w;
		renderQuad.h = crop->h;
	}

	//Render to screen
	SDL_RenderCopyEx(_renderer, _texture, crop, &renderQuad, angle, center, flip );

}

int Texture::getWidth() {
	return _width;
}

int Texture::getHeight() {
	return _height;
}