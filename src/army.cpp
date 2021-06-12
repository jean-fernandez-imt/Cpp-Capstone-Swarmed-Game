#include <cmath>

#include "army.h"

Army::Army(
    const std::size_t screenWidth, 
    const std::size_t screenHeight,
    Player* target,
    Texture texture)
    : _screenWidth(screenWidth),
      _screenHeight(screenHeight),
      _target(target),
      _texture(std::move(texture)) {}

void Army::spawn() {
    // Create enemies here
}

void Army::updateEnemies() {
    //Check for remaining enemies here
}

void Army::render() {
    //Render the remaining enemies
} 