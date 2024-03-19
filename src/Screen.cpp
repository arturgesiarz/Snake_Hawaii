
#include "../include/Screen.h"
#include "../include/Button.h"

using namespace sf;

void Screen::gameOverScreen(sf::RenderWindow &window, bool &isGameOver, GameParameters& gameParameters) {
    window.setVisible(false);
    RenderWindow gameOverWindow(VideoMode(GameParameters::W + 200, GameParameters::H + 200), "GAME OVER!", Style::Close);

    Font font;
    font.loadFromFile(R"(resources\arial.ttf)");

    sf::Texture texture;
    texture.loadFromFile(R"(resources\end.png)");

    sf::Sprite backgroundImage;
    backgroundImage.setTexture(texture);

    sf::Vector2f buttonRetryPosition(GameParameters::W / 2 - 50, GameParameters::H);
    sf::Vector2f buttonClosePosition(GameParameters::W / 2 + 100 + 10 , GameParameters::H);

    Button retryButton(buttonRetryPosition, sf::Vector2f(100, 40), "RETRY", font);
    Button closeButton( buttonClosePosition, sf::Vector2f(100, 40), "CLOSE", font);

    sf::Color normalColor = sf::Color(255, 255, 77);
    sf::Color textColor = sf::Color(77, 77, 0);
    sf::Color outlineColor = sf::Color(255, 255, 77);
    float outlineThickness = 2.0f;

    retryButton.setFillColor(normalColor);
    retryButton.setTextColor(textColor);
    retryButton.setOutlineColor(outlineColor);
    retryButton.setOutlineThickness(outlineThickness);

    closeButton.setFillColor(normalColor);
    closeButton.setTextColor(textColor);
    closeButton.setOutlineColor(outlineColor);
    closeButton.setOutlineThickness(outlineThickness);

    sf::Text textScore;
    textScore.setFont(font);
    textScore.setCharacterSize(50);
    textScore.setFillColor(sf::Color(77, 0, 0));

    sf::Text textGameOver;
    textGameOver.setString("GAME OVER");
    textGameOver.setFont(font);
    textGameOver.setCharacterSize(80);
    textGameOver.setFillColor(sf::Color(255, 26, 26));
    textGameOver.setStyle(sf::Text::Bold);

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
        gameOverWindow.draw(backgroundImage);
        retryButton.draw(gameOverWindow);
        closeButton.draw(gameOverWindow);

        std::string scoreString = std::to_string(gameParameters.num - 4);

        sf::RectangleShape gameOverRectangle(sf::Vector2f(GameParameters::W - 200, 200));
        gameOverRectangle.setPosition(200, 500);
        gameOverRectangle.setFillColor(sf::Color(255, 255, 255, 200));


        textScore.setString("Your score: " + scoreString);
        textScore.setPosition(350, 600);
        textGameOver.setPosition(250, 500);

        gameOverWindow.draw(gameOverRectangle);
        gameOverWindow.draw(textGameOver);
        gameOverWindow.draw(textScore);


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
    RenderWindow gameStartWindow(VideoMode(GameParameters::W + 200, GameParameters::H + 200), "Snake Game! - Start", Style::Close);

    sf::Texture texture;
    texture.loadFromFile(R"(resources\start_vol2.png)");

    sf::Sprite backgroundImage;
    backgroundImage.setTexture(texture);

    Font font;
    font.loadFromFile(R"(resources\arial.ttf)");

    sf::Vector2f buttonSize(100, 50);
    sf::Vector2f buttonPosition(450, 800);

    Button startButton(buttonPosition, buttonSize, "START", font);

    sf::Color normalColor = sf::Color(0, 179, 0);
    sf::Color textColor = sf::Color::White;
    sf::Color outlineColor = sf::Color(0, 179, 0);
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

void Screen::move(bool &isGameOver, sf::Sound &eatEffectSound, GameParameters &gameParameters) {
    for (int i = gameParameters.num; i > 0; --i) {
        gameParameters.s[i].x = gameParameters.s[i - 1].x;
        gameParameters.s[i].y = gameParameters.s[i - 1].y;
    }

    switch (gameParameters.direction) {
        case 0:
            gameParameters.s[0].y += 1;
            break;
        case 1:
            gameParameters.s[0].x -= 1;
            break;
        case 2:
            gameParameters.s[0].x += 1;
            break;
        case 3:
            gameParameters.s[0].y -= 1;
            break;
        default:
            break;
    }

    if ((gameParameters.s[0].x == gameParameters.f.x) && (gameParameters.s[0].y == gameParameters.f.y)) {
        eatEffectSound.play();
        gameParameters.num++;
        gameParameters.f.x = rand() % GameParameters::N;
        gameParameters.f.y = rand() % GameParameters::M;
    }

    if (gameParameters.s[0].x >= GameParameters::N) gameParameters.s[0].x = 0;
    if (gameParameters.s[0].x < 0) gameParameters.s[0].x = GameParameters::N - 1;
    if (gameParameters.s[0].y >= GameParameters::M) gameParameters.s[0].y = 0;
    if (gameParameters.s[0].y < 0) gameParameters.s[0].y = GameParameters::M - 1;

    for (int i = 1; i < gameParameters.num; i++) {
        if(gameParameters.s[0].x == gameParameters.s[i].x && gameParameters.s[0].y == gameParameters.s[i].y) {
            isGameOver = true;
        }
    }
}
