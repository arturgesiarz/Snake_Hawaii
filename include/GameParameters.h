
#ifndef SNAKE_GAMEPARAMETERS_H
#define SNAKE_GAMEPARAMETERS_H

#include "Snake.h"

class GameParameters {
public:
    const static int N = 30, M = 20;
    const static int SIZE = 16;
    const static int W = SIZE * N;
    const static int H = SIZE * M;

    int dir = 0;
    int num = 4;

    Snake s[100];
    Fruct f;

    int getDir() {
        return dir;
    }

    int getNum() {
        return num;
    }

    Snake *getS() {
        return s;
    }

    Fruct &getF() {
        return f;
    }

    void setDir(int dir) {
        this->dir = dir;
    }

    void setNum(int num) {
        this->num = num;
    }


};

#endif //SNAKE_GAMEPARAMETERS_H
