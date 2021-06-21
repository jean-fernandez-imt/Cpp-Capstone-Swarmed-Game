#include "background.h"

Background::Background(
    Texture background1,
    Texture background2,
    Texture background3,
    Texture background4,
    Texture background5)
    : _background1(std::move(background1)),
      _background2(std::move(background2)),
      _background3(std::move(background3)),
      _background4(std::move(background4)),
      _background5(std::move(background5)) {
          //Store pointers to backgrounds
          _backgrounds.push_back(&_background1);
          _backgrounds.push_back(&_background2);
          _backgrounds.push_back(&_background3);
          _backgrounds.push_back(&_background4);
          _backgrounds.push_back(&_background5);
      }

Texture* Background::getRandomBackgound() {
    //Choose a random Background
    std::uniform_int_distribution<int> distribution(0, 4);
    int randomBackground = distribution(_generator);
    return _backgrounds[randomBackground];
}