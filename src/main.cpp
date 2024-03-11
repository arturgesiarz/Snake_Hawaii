#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../include/GameParameters.h"
#include "../include/Screen.h"
#include <ctime>

using namespace sf;

void Tick (bool& isGameOver, Sound& eatEffectSound, GameParameters& gameParameters) {
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

        Time duration = seconds(0.5);
        eatEffectSound.play();
        sleep(duration);

        gameParameters.num++;
        gameParameters.f.x = rand() % GameParameters::N;
        gameParameters.f.y = rand() % GameParameters::M;
    }

    if (gameParameters.s[0].x > GameParameters::N) gameParameters.s[0].x = 0;
    if (gameParameters.s[0].x < 0) gameParameters.s[0].x = GameParameters::N;
    if (gameParameters.s[0].y > GameParameters::M) gameParameters.s[0].y = 0;
    if (gameParameters.s[0].y < 0) gameParameters.s[0].y = GameParameters::M;

    for (int i = 1; i < gameParameters.num; i++) {
        if(gameParameters.s[0].x == gameParameters.s[i].x && gameParameters.s[0].y == gameParameters.s[i].y) {
            isGameOver = true;
        }
    }
}

int main() {
    srand(time(0));

    bool isGameOver = false;
    bool startGame = false;

    GameParameters gameParameters;

    RenderWindow window(VideoMode(GameParameters::W, GameParameters::H), "Snake Game!");
    window.setVisible(false);

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

    gameParameters.f.x = 10;
    gameParameters.f.y = 10;

    Screen::welcomeScreen(window,startGame);

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

        if (timer > delay) {
            timer = 0;
            Tick(isGameOver, eatEffectSound, gameParameters);
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

        for (int i = 0; i < GameParameters::N; i++) {
            for (int j = 0; j < GameParameters::M; j++) {
                sprite1.setPosition(i * GameParameters::SIZE, j * GameParameters::SIZE);
                window.draw(sprite1);
            }
        }
        for (int i = 0; i < gameParameters.num; i++) {
            sprite2.setPosition(gameParameters.s[i].x * GameParameters::SIZE,
                                gameParameters.s[i].y * GameParameters::SIZE);
            window.draw(sprite2);
        }

        sprite3.setPosition(gameParameters.f.x * GameParameters::SIZE,
                            gameParameters.f.y * GameParameters::SIZE);
        window.draw(sprite3);

        window.display();

        if(isGameOver) {
            gameOverSound.play();
            Screen::gameOverScreen(window, isGameOver, gameParameters);
            gameOverSound.stop();
        }
    }


}