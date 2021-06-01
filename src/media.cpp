#include <iostream>
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
    mainPlayer.loadFromFile("../textures/testTexture.png");

    // Add Texture pointers to _textures.
    _textures.push_back(&mainPlayer);

    if (!checkMedia()) {
        std::cerr << "Failed to load media." << std::endl;
    }
}

bool Media::checkMedia() {
    for (Texture* texture: _textures) {
        if (texture == nullptr) {
            return false;
        }
    }
    return true;
}

std::vector<Texture*> Media::getTextures() {
    return _textures;
}