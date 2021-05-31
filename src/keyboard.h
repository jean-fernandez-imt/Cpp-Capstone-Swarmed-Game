#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "snake.h"

class Keyboard {
 public:
  void HandleInput(bool &running, Snake &snake) const;

 private:
  void ChangeDirection(Snake &snake, Snake::Direction input,
                       Snake::Direction opposite) const;
};

#endif