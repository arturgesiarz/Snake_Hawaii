
#ifndef SNAKE_GAMEPARAMETERS_H
#define SNAKE_GAMEPARAMETERS_H

#include "Snake.h"

class GameParameters {
public:
    const static int N = 50, M = 50;
    const static int SIZE = 16;
    const static int W = SIZE * N;
    const static int H = SIZE * M;

    int direction;
    int num;

    Snake s[100]{};
    Fruct f{};

    explicit GameParameters(int direction = 0, int num = 4) : direction(direction), num(num) {}
};

#endif //SNAKE_GAMEPARAMETERS_H
