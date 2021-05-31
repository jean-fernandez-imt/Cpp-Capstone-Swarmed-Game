#include <iostream>

#include "texture.h"

Texture::Texture(SDL_Renderer* renderer) {
	//Initialize
    _renderer = renderer;
	_texture = nullptr;
	_width = 0;
	_height = 0;
}

Texture::~Texture() {
	//Deallocate
	release();
}

bool Texture::loadFromFile(std::string path) {

	//Get rid of preexisting texture
	release();

	//The final texture
	SDL_Texture* newTexture = nullptr;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == nullptr) {
        std::cerr 
            << "Unable to load image from: " 
            << path.c_str() 
            << std::endl;
        std::cerr 
            << " SDL2_IMG_Error:  " 
            << IMG_GetError()
            << std::endl;
        return false;
	} else {
		//Color key image
		SDL_SetColorKey(
            loadedSurface, 
            SDL_TRUE, 
            SDL_MapRGB(
                loadedSurface->format, 
                0, 
                0xFF, 
                0xFF));
    }

    //Create texture from surface pixels
    newTexture = SDL_CreateTextureFromSurface(_renderer, loadedSurface);
    if (newTexture == nullptr) {
        std::cerr 
            << "Unable to create texture from: " 
            << path.c_str() 
            << std::endl;
        std::cerr 
            << " SDL2_Error:  " 
            << SDL_GetError()
            << std::endl;
        return false;
    } else {
        //Get image dimensions
        _width = loadedSurface->w;
        _height = loadedSurface->h;
    }

    //Get rid of old loaded surface
    SDL_FreeSurface(loadedSurface);

	//Return success
	_texture = newTexture;
	return _texture != nullptr;
}

void Texture::release() {
	//Free texture if it exists
	if (_texture != nullptr) {
		SDL_DestroyTexture(_texture);
		_texture = nullptr;
        _renderer = nullptr;
		_width = 0;
		_height = 0;
	}
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
	if (crop != nullptr) {
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