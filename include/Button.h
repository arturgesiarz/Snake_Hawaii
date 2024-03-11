
#ifndef SNAKE_BUTTON_H
#define SNAKE_BUTTON_H

#include <functional>
#include <SFML/Graphics.hpp>

using namespace sf;

class Button {
public:
    Button(sf::Vector2f position, sf::Vector2f size, std::string text, sf::Font& font);
    void draw(sf::RenderWindow& window);
    bool isHovered(sf::RenderWindow& window);
    bool isClicked(sf::Event event, sf::RenderWindow& window);
    void setFillColor(const sf::Color& color);
    void setHoverColor(const sf::Color& color);
    void setTextColor(const sf::Color& color);
    void setOutlineColor(const sf::Color& color);
    void setOutlineThickness(float thickness);
    void setOnClick(std::function<void()> onClickFunction);
    void executeOnClick();

private:
    sf::RectangleShape rect;
    sf::Text buttonText;
    std::function<void()> onClick;
    sf::Color normalColor;
    sf::Color hoverColor;
    sf::Color textColor;
    sf::Color outlineColor;
    float outlineThickness;
};

#endif //SNAKE_BUTTON_H