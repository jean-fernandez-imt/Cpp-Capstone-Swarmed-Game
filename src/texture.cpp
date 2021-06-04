#include <iostream>

#include "texture.h"

Texture::Texture(SDL_Renderer* renderer): _renderer(renderer) {
	//Initialize
	_texture = NULL;
}

Texture::~Texture() {
	//Deallocate
	release();
}

//Copy constructor
Texture::Texture(const Texture &source) {
	std::cout << "Texture: Copy constructor called." << std::endl;
	_texture = source._texture;
	_renderer = source._renderer;
}

//Copy assignment operator
Texture &Texture::operator=(const Texture &source) {
	std::cout << "Texture: Copy assignment operator used." << std::endl;
	if (this == &source) {
		return *this;
	}
	_texture = source._texture;
	_renderer = source._renderer;
}

//Move constructor
Texture::Texture(Texture &&source) {
	std::cout << "Texture: Move constructor called." << std::endl;
	_texture = source._texture;
	_renderer = source._renderer;
	source._texture = NULL;
	source._renderer = NULL;
}

//Move assignment operator
Texture &Texture::operator=(Texture &&source) {
	std::cout << "Texture: Move assignment operator used." << std::endl;
	if (this == &source) {
		return *this;
	}
	_texture = source._texture;
	_renderer = source._renderer;
	source._texture = NULL;
	source._renderer = NULL;
}

void Texture::release() {
	//Free texture if it exists
	if (_texture != NULL) {
		SDL_DestroyTexture(_texture);
		_texture = NULL;
        _renderer = NULL;
	}
}

void Texture::loadFromFile(std::string path) {

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

void Texture::render() {
	SDL_RenderCopy(_renderer, _texture, NULL, NULL);
}

SDL_Texture* Texture::getTexture() {
	return _texture;
}

/*
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
*/
