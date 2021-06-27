#ifndef HIGHSCORES_H
#define HIGHSCORES_H

#include <cstring>
#include <deque>

#include "parameters.h"
#include "font.h"

typedef struct {
    char player[HIGHSCORES_NAME_MAX_LENGTH];
    int score;
} Highscore;

class Highscores {
    public:
        Highscores(Font font);

        void render(int x, int y);

    private:
        Font _font;
        std::deque<Highscore> _highscores[HIGHSCORES_TOTAL];

        void readFile();
        void constructHighscores();
};

#endif