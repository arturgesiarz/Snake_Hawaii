
#include <SFML/Graphics.hpp>
#include <utility>
#include "../include/Button.h"

Button::Button(sf::Vector2f position, sf::Vector2f size, std::string text, sf::Font& font) {
        rect.setPosition(position);
        rect.setSize(size);
        rect.setFillColor(sf::Color::Blue);

        buttonText.setFont(font);
        buttonText.setString(text);
        buttonText.setCharacterSize(20);
        buttonText.setFillColor(sf::Color::White);
        buttonText.setPosition(position.x + 10, position.y + 10);
}

void Button::draw(sf::RenderWindow& window) {
    window.draw(rect);
    window.draw(buttonText);
}

bool Button::isClicked(sf::Event event, sf::RenderWindow& window) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        if (isHovered(window)) {
            return true;
        }
    }
    return false;
}

void Button::setOnClick(std::function<void()> onClickFunction) {
    onClick = std::move(onClickFunction);
}

void Button::executeOnClick() {
    if (onClick) {
        onClick();
    }
}
bool Button::isHovered(sf::RenderWindow& window) {
    sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(window));
    return rect.getGlobalBounds().contains(mousePosition);
}

void Button::setFillColor(const sf::Color& color) {
    rect.setFillColor(color);
}

void Button::setHoverColor(const sf::Color& color) {
    hoverColor = color;
}

void Button::setTextColor(const sf::Color& color) {
    buttonText.setFillColor(color);
}

void Button::setOutlineColor(const sf::Color& color) {
    rect.setOutlineColor(color);
}

void Button::setOutlineThickness(float thickness) {
    rect.setOutlineThickness(thickness);
}



