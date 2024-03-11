
#ifndef SNAKE_GAMEPARAMETERS_H
#define SNAKE_GAMEPARAMETERS_H

#include "Snake.h"

class GameParameters {
public:
    const static int N = 25, M = 25;
    const static int SIZE = 32;
    const static int W = 800;
    const static int H = 800;

    int direction;
    int num;

    Snake s[100]{};
    Fruct f{};

    explicit GameParameters(int direction = 0, int num = 4) : direction(direction), num(num) {}
};

#endif //SNAKE_GAMEPARAMETERS_H
