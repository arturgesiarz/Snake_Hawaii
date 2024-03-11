#include <SFML/Graphics.hpp>
#include <ctime>
#include <iostream>
#include "button.h"

using namespace sf;

const int N = 30, M = 20;
const int size = 16;
const int w = size * N;
const int h = size * M;

int dir = 0, num = 4;

struct Snake {
    int x, y;
}
s[100];

struct Fruct {
    int x, y;
} f;

void GameOver(RenderWindow& window) {
    RenderWindow gameOverWindow(VideoMode(300, 200), "GAME OVER!", Style::Close);
    Font font;
    font.loadFromFile("E:\\CLionProjects\\Snake\\resources\\arial.ttf");

    Text text("GAME OVER", font, 30);
    text.setPosition(80, 50);

    Button retryButton(sf::Vector2f(50, 100), sf::Vector2f(100, 40), "RETRY", font);
    Button closeButton(sf::Vector2f(150, 100), sf::Vector2f(100, 40), "CLOSE", font);

    retryButton.setOnClick([&]() {
        gameOverWindow.close();
        dir = 0;
        num = 4;
        f.x = 10;
        f.y = 10;
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
            retryButton.executeOnClick();
        }
        if(closeButton.isClicked(event, gameOverWindow)) {
            closeButton.executeOnClick();
        }
        gameOverWindow.display();
    }
}

void Tick (RenderWindow& window) {
    for (int i = num; i > 0; --i) {
        s[i].x = s[i - 1].x;
        s[i].y = s[i - 1].y;
    }

    switch (dir) {
        case 0:
            s[0].y += 1;
            break;
        case 1:
            s[0].x -= 1;
            break;
        case 2:
            s[0].x += 1;
            break;
        case 3:
            s[0].y -= 1;
            break;
        default:
            break;
    }

    if ((s[0].x == f.x) && (s[0].y == f.y)) {
        num++;
        f.x = rand() % N;
        f.y = rand() % M;
    }

    if (s[0].x > N) s[0].x = 0;
    if (s[0].x < 0) s[0].x = N;
    if (s[0].y > M) s[0].y = 0;
    if (s[0].y < 0) s[0].y = M;

    for (int i = 1; i < num; i++) {
        if(s[0].x == s[i].x && s[0].y == s[i].y) {
            //GAME OVER
            GameOver(window);
        }
    }
}

int main() {
    srand(time(0));

    RenderWindow window(VideoMode(w, h), "Snake Game!");

    Texture t1, t2, t3;
    t1.loadFromFile(R"(E:\CLionProjects\Snake\resources\white.png)");
    t2.loadFromFile(R"(E:\CLionProjects\Snake\resources\red.png)");
    t3.loadFromFile(R"(E:\CLionProjects\Snake\resources\green.png)");

    Sprite sprite1(t1);
    Sprite sprite2(t2);
    Sprite sprite3(t3);

    Clock clock;
    float timer = 0, delay = 0.1;

    f.x = 10;
    f.y = 10;

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
            Tick(window);
        }
        switch (dir) {
            case 0:
            case 3:
                if (Keyboard::isKeyPressed(Keyboard::Left)) dir = 1;
                if (Keyboard::isKeyPressed(Keyboard::Right)) dir = 2;
                break;

            case 1:
            case 2:
                if (Keyboard::isKeyPressed(Keyboard::Up)) dir = 3;
                if (Keyboard::isKeyPressed(Keyboard::Down)) dir = 0;
            default:
                break;
        }

        // draw
        window.clear();

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                sprite1.setPosition(i * size, j * size);
                window.draw(sprite1);
            }
        }
        for (int i = 0; i < num; i++) {
            sprite2.setPosition(s[i].x * size, s[i].y * size);
            window.draw(sprite2);
        }

        sprite3.setPosition(f.x * size, f.y * size);
        window.draw(sprite3);

        window.display();
    }


}