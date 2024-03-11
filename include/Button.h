
#ifndef SNAKE_BUTTON_H
#define SNAKE_BUTTON_H

#include <functional>
#include <SFML/Graphics.hpp>

using namespace sf;

class Button {
public:
    Button(sf::Vector2f position, sf::Vector2f size, std::string text, sf::Font& font);
    void draw(sf::RenderWindow& window);
    bool isClicked(sf::Event event, sf::RenderWindow& window);
    void setOnClick(std::function<void()> onClickFunction);
    void executeOnClick();

private:
    sf::RectangleShape rect;
    sf::Text buttonText;
    sf::Vector2f position;
    sf::Vector2f size;
    std::function<void()> onClick;
};

#endif //SNAKE_BUTTON_H