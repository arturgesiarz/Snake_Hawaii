#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../include/GameParameters.h"
#include "../include/Screen.h"
#include <ctime>
#include <array>

using namespace sf;

int start() {

    bool isGameOver = false;
    bool startGame = false;

    GameParameters gameParameters;
    gameParameters.f.x = 10;
    gameParameters.f.y = 10;

    // game window
    RenderWindow window(VideoMode(GameParameters::W + 200, GameParameters::H + 200), "Snake Game!", Style::Close);
    window.setVisible(false);

    // font loading
    sf::Font font;
    if (!font.loadFromFile("resources/arial.ttf")) {
        return -1;
    }

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Black);
    text.setStyle(sf::Text::Bold);

    // texture
    std::array<sf::Texture, 3> textures;
    textures[0].loadFromFile("resources/white.png");
    textures[1].loadFromFile("resources/red.png");
    textures[2].loadFromFile("resources/green.png");

    std::array<sf::Sprite, 3> sprites;
    for (int i = 0; i < 3; ++i) {
        sprites[i].setTexture(textures[i]);
    }

    // soundtrack
    SoundBuffer gameOverSoundBuffer;
    SoundBuffer eatEffectBuffer;

    if(!gameOverSoundBuffer.loadFromFile(R"(resources/death_song.wav)")) {
        return -1;
    }
    if(!eatEffectBuffer.loadFromFile(R"(resources/eat_effect.wav)")) {
        return -1;
    }

    Sound gameOverSound(gameOverSoundBuffer);
    Sound eatEffectSound(eatEffectBuffer);


    // clock setting
    srand(time(0));
    Clock clock;
    float timer = 0, delay = 0.1;

    // welcome screen
    Screen::welcomeScreen(window,startGame);


    // the game render
    while (window.isOpen() && startGame) {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;

        Event e;

        while (window.pollEvent(e)) {
            if (e.type == Event::Closed) {
                window.close();
            }
        }

        // move
        if (timer > delay) {
            timer = 0;
            Screen::move(isGameOver, eatEffectSound, gameParameters);
        }

        int dir = gameParameters.direction;

        switch (dir) {
            case 0:
            case 3:
                if (Keyboard::isKeyPressed(Keyboard::Left)) gameParameters.direction = 1;
                if (Keyboard::isKeyPressed(Keyboard::Right)) gameParameters.direction = 2;
                break;

            case 1:
            case 2:
                if (Keyboard::isKeyPressed(Keyboard::Up)) gameParameters.direction = 3;
                if (Keyboard::isKeyPressed(Keyboard::Down)) gameParameters.direction = 0;
            default:
                break;
        }

        window.clear();

        sf::Texture mainTexture;
        mainTexture.loadFromFile(R"(resources/main.jpg)");

        sf::Sprite backgroundImage;
        backgroundImage.setTexture(mainTexture);

        window.draw(backgroundImage);

        for (int i = 0; i < GameParameters::N; i++) {
            for (int j = 0; j < GameParameters::M; j++) {
                sprites[0].setPosition(i * GameParameters::SIZE + 100, j * GameParameters::SIZE + 100);
                window.draw(sprites[0]);
            }
        }
        for (int i = 0; i < gameParameters.num; i++) {
            sprites[1].setPosition(gameParameters.s[i].x * GameParameters::SIZE + 100,
                                gameParameters.s[i].y * GameParameters::SIZE + 100);
            window.draw(sprites[1]);
        }

        sprites[2].setPosition(gameParameters.f.x * GameParameters::SIZE + 100,
                            gameParameters.f.y * GameParameters::SIZE + 100);

        window.draw(sprites[2]);

        std::string scoreString = std::to_string(gameParameters.num - 4);

        sf::Text textScore;
        textScore.setFont(font);
        textScore.setCharacterSize(40);
        textScore.setFillColor(sf::Color(133, 133, 224));

        textScore.setString("Your score: " + scoreString);
        textScore.setPosition(300, 5);

        window.draw(textScore);
        window.display();

        if(isGameOver) {
            gameOverSound.play();
            Screen::gameOverScreen(window, isGameOver, gameParameters);
            gameOverSound.stop();
        }
    }
    return 0;
}