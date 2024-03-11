#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../include/GameParameters.h"
#include "../include/Screen.h"
#include <ctime>

using namespace sf;

void Tick (bool& isGameOver, Sound& eatEffectSound, GameParameters& gameParameters) {
    for (int i = gameParameters.getNum(); i > 0; --i) {
        gameParameters.getS()[i].x = gameParameters.getS()[i - 1].x;
        gameParameters.getS()[i].y = gameParameters.getS()[i - 1].y;
    }

    switch (gameParameters.getDir()) {
        case 0:
            gameParameters.getS()[0].y += 1;
            break;
        case 1:
            gameParameters.getS()[0].x -= 1;
            break;
        case 2:
            gameParameters.getS()[0].x += 1;
            break;
        case 3:
            gameParameters.getS()[0].y -= 1;
            break;
        default:
            break;
    }

    if ((gameParameters.getS()[0].x == gameParameters.getF().x) && (gameParameters.getS()[0].y == gameParameters.getF().y)) {
        Time duration = seconds(0.5);
        eatEffectSound.play();
        sleep(duration);
        gameParameters.setNum(gameParameters.getNum() + 1);
        gameParameters.getF().x = rand() % GameParameters::N;
        gameParameters.getF().y = rand() % GameParameters::M;
    }

    if (gameParameters.getS()[0].x > GameParameters::N) gameParameters.getS()[0].x = 0;
    if (gameParameters.getS()[0].x < 0) gameParameters.getS()[0].x = GameParameters::N;
    if (gameParameters.getS()[0].y > GameParameters::M) gameParameters.getS()[0].y = 0;
    if (gameParameters.getS()[0].y < 0) gameParameters.getS()[0].y = GameParameters::M;

    for (int i = 1; i < gameParameters.getNum(); i++) {
        if(gameParameters.getS()[0].x == gameParameters.getS()[i].x && gameParameters.getS()[0].y == gameParameters.getS()[i].y) {
            isGameOver = true;
        }
    }
}

int main() {
    srand(time(0));

    bool isGameOver = false;

    GameParameters gameParameters;

    RenderWindow window(VideoMode(GameParameters::W, GameParameters::H), "Snake Game!");

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

    Texture t1, t2, t3;
    t1.loadFromFile(R"(resources\white.png)");
    t2.loadFromFile(R"(resources\red.png)");
    t3.loadFromFile(R"(resources\green.png)");

    Sprite sprite1(t1);
    Sprite sprite2(t2);
    Sprite sprite3(t3);

    Clock clock;
    float timer = 0, delay = 0.1;

    gameParameters.getF().x = 10;
    gameParameters.getF().y = 10;

    while (window.isOpen()) {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;

        Event e;

        while (window.pollEvent(e)) {
            if (e.type == Event::Closed) {
                window.close();
            }
        }

        if (timer > delay) {
            timer = 0;
            Tick(isGameOver, eatEffectSound, gameParameters);
        }

        int dir = gameParameters.getDir();

        switch (dir) {
            case 0:
            case 3:
                if (Keyboard::isKeyPressed(Keyboard::Left)) gameParameters.setDir(1);
                if (Keyboard::isKeyPressed(Keyboard::Right)) gameParameters.setDir(2);
                break;

            case 1:
            case 2:
                if (Keyboard::isKeyPressed(Keyboard::Up)) gameParameters.setDir(3);
                if (Keyboard::isKeyPressed(Keyboard::Down)) gameParameters.setDir(0);
            default:
                break;
        }

        window.clear();

        for (int i = 0; i < GameParameters::N; i++) {
            for (int j = 0; j < GameParameters::M; j++) {
                sprite1.setPosition(i * GameParameters::SIZE, j * GameParameters::SIZE);
                window.draw(sprite1);
            }
        }
        for (int i = 0; i < gameParameters.getNum(); i++) {
            sprite2.setPosition(gameParameters.getS()[i].x * GameParameters::SIZE,
                                gameParameters.getS()[i].y * GameParameters::SIZE);
            window.draw(sprite2);
        }

        sprite3.setPosition(gameParameters.getF().x * GameParameters::SIZE,
                            gameParameters.getF().y * GameParameters::SIZE);
        window.draw(sprite3);

        window.display();

        if(isGameOver) {
            gameOverSound.play();
            Screen::gameOver(window, isGameOver, gameParameters);
            gameOverSound.stop();
        }
    }


}