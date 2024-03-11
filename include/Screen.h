
#ifndef SNAKE_SCREEN_H
#define SNAKE_SCREEN_H

#include <SFML/Graphics.hpp>
#include "GameParameters.h"

class Screen {
public:
    void static gameOverScreen(sf::RenderWindow& window, bool& isGameOver, GameParameters& gameParameters);
    void static welcomeScreen(sf::RenderWindow& window, bool& startGame);
};

#endif //SNAKE_SCREEN_H
