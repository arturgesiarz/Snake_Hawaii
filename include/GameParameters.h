
#ifndef SNAKE_GAMEPARAMETERS_H
#define SNAKE_GAMEPARAMETERS_H

#include "Snake.h"

class GameParameters {
public:
    const static int N = 20, M = 20;
    const static int SIZE = 40;
    const static int W = 800;
    const static int H = 800;

    int direction;
    int num;

    Snake s[400]{};
    Fruct f{};

    explicit GameParameters(int direction = 0, int num = 4) : direction(direction), num(num) {}
};

#endif //SNAKE_GAMEPARAMETERS_H
