
#include <SFML/Graphics.hpp>
#include <utility>
#include "button.h"

Button::Button(sf::Vector2f position, sf::Vector2f size, std::string text, sf::Font& font)
            : position(position), size(size) {
        rect.setPosition(position);
        rect.setSize(size);
        rect.setFillColor(sf::Color::Blue);

        // Ustawienie tekstu na przycisku
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
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        if (rect.getGlobalBounds().contains(mousePos)) {
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
