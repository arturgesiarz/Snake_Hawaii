
#include "../include/Screen.h"
#include "../include/Button.h"

using namespace sf;

void Screen::gameOver(sf::RenderWindow &window, bool &isGameOver, GameParameters& gameParameters) {
    RenderWindow gameOverWindow(VideoMode(300, 200), "GAME OVER!", Style::Close);
    Font font;
    font.loadFromFile(R"(resources\arial.ttf)");

    Text text("GAME OVER", font, 30);
    text.setPosition(80, 50);

    Button retryButton(sf::Vector2f(50, 100), sf::Vector2f(100, 40), "RETRY", font);
    Button closeButton(sf::Vector2f(150, 100), sf::Vector2f(100, 40), "CLOSE", font);

    retryButton.setOnClick([&]() {
        gameOverWindow.close();
        gameParameters.setDir(0);
        gameParameters.setNum(4);
        gameParameters.getF().x = 10;
        gameParameters.getF().y = 10;
    });

    closeButton.setOnClick([&]() {
        gameOverWindow.close();
        window.close();
    });

    while (gameOverWindow.isOpen()) {
        Event event;
        while (gameOverWindow.pollEvent(event)) {
            if (event.type == Event::Closed) {
                gameOverWindow.close();
                window.close();
            }
        }

        gameOverWindow.clear(Color::White);
        gameOverWindow.draw(text);
        retryButton.draw(gameOverWindow);
        closeButton.draw(gameOverWindow);

        if(retryButton.isClicked(event, gameOverWindow)) {
            isGameOver = false;
            retryButton.executeOnClick();
        }
        if(closeButton.isClicked(event, gameOverWindow)) {
            closeButton.executeOnClick();
        }
        gameOverWindow.display();
    }
}

void Screen::welcomeScreen(sf::RenderWindow &window) {

}
