#include <string>

#include "media.h"

Media::Media(SDL_Renderer* renderer): _renderer(renderer) {
    loadMedia();
}

Media::~Media() {
    for (Texture* texture: _textures) {
        texture->release();
    }
}

void Media::loadMedia() {
    // Create empty Textures
    Texture mainPlayer(_renderer);

    // Load Textures from files
    mainPlayer.loadFromFile("texture.png");

    // Add Texture pointers to _textures.
    _textures.push(&mainPlayer);
}