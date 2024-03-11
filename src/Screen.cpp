
#include "../include/Screen.h"
#include "../include/Button.h"

using namespace sf;

void Screen::gameOverScreen(sf::RenderWindow &window, bool &isGameOver, GameParameters& gameParameters) {
    window.setVisible(false);
    RenderWindow gameOverWindow(VideoMode(300, 200), "GAME OVER!", Style::Close);
    Font font;
    font.loadFromFile(R"(resources\arial.ttf)");

    Text text("GAME OVER", font, 30);
    text.setPosition(80, 50);

    Button retryButton(sf::Vector2f(50, 100), sf::Vector2f(100, 40), "RETRY", font);
    Button closeButton(sf::Vector2f(150, 100), sf::Vector2f(100, 40), "CLOSE", font);

    retryButton.setOnClick([&]() {
        gameOverWindow.close();
        gameParameters.direction = 0;
        gameParameters.num = 4;
        gameParameters.f.x = 0;
        gameParameters.f.y = 0;
        window.setVisible(true);
    });

    closeButton.setOnClick([&]() {
        window.close();
        gameOverWindow.close();
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
