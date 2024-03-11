
#include "../include/Screen.h"
#include "../include/Button.h"

using namespace sf;

void Screen::gameOverScreen(sf::RenderWindow &window, bool &isGameOver, GameParameters& gameParameters) {
    window.setVisible(false);
    RenderWindow gameOverWindow(VideoMode(GameParameters::W, GameParameters::H), "GAME OVER!", Style::Close);

    Font font;
    font.loadFromFile(R"(resources\arial.ttf)");

    sf::Texture texture;
    texture.loadFromFile(R"(resources\end.png)");

    sf::Sprite backgroundImage;
    backgroundImage.setTexture(texture);

    Text text("GAME OVER", font, 30);
    text.setPosition(80, 50);

    sf::Vector2f buttonRetryPosition(GameParameters::W / 2 - 100 - 10, GameParameters::H / 2);
    sf::Vector2f buttonClosePosition(GameParameters::W / 2 + 10, GameParameters::H / 2);

    Button retryButton(buttonRetryPosition, sf::Vector2f(100, 40), "RETRY", font);
    Button closeButton( buttonClosePosition, sf::Vector2f(100, 40), "CLOSE", font);

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
        gameOverWindow.draw(backgroundImage);
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

void Screen::welcomeScreen(sf::RenderWindow& window, bool& startGame) {
    RenderWindow gameStartWindow(VideoMode(GameParameters::W, GameParameters::H), "Snake Game! - Start", Style::Close);

    sf::Texture texture;
    texture.loadFromFile(R"(resources\start.png)");

    sf::Sprite backgroundImage;
    backgroundImage.setTexture(texture);

    Font font;
    font.loadFromFile(R"(resources\arial.ttf)");

    sf::Vector2f buttonSize(100, 40);
    sf::Vector2f buttonPosition(GameParameters::W / 2 - buttonSize.x / 2, GameParameters::H / 2 - buttonSize.y / 2);

    Button startButton(buttonPosition, buttonSize, "START", font);

    sf::Color normalColor = sf::Color(255, 77, 255);
    sf::Color textColor = sf::Color::White;
    sf::Color outlineColor = sf::Color(255, 77, 255);
    float outlineThickness = 2.0f;

    startButton.setFillColor(normalColor);
    startButton.setTextColor(textColor);
    startButton.setOutlineColor(outlineColor);
    startButton.setOutlineThickness(outlineThickness);

    startButton.setOnClick([&]() {
        startGame = true;
        gameStartWindow.close();
        window.setVisible(true);
    });

    while (gameStartWindow.isOpen()) {
        Event event;
        while (gameStartWindow.pollEvent(event)) {
            if (event.type == Event::Closed) {
                gameStartWindow.close();
            }
        }

        gameStartWindow.draw(backgroundImage);
        startButton.draw(gameStartWindow);


        if(startButton.isClicked(event,gameStartWindow)) {
            startButton.executeOnClick();
        }

        gameStartWindow.display();
    }

}
