#include "Button.h"

Button::Button(const std::string& text, const sf::Font& font, float x, float y) {
    this->text.setFont(font);
    this->text.setString(text);
    this->text.setCharacterSize(25);
    this->text.setOrigin(this->text.getLocalBounds().width / 2.0f, this->text.getLocalBounds().height / 2.0f);
    this->text.setPosition(x, y);
    this->text.setFillColor(sf::Color::White);
}

void Button::draw(sf::RenderWindow& window) {
    window.draw(text);
}
void Button::animate() {
    isAnimating = true;
    currentScale = maxScale;
    text.setScale(currentScale, currentScale);  // Set initial scale
}

void Button::update(sf::Vector2f mousePosition) {
    if (isAnimating) {
        currentScale -= animationSpeed;
        if (currentScale <= minScale) {
            currentScale = minScale;
            isAnimating = false;
        }
        text.setScale(currentScale, currentScale);
    }

    if (text.getGlobalBounds().contains(mousePosition)) {
        text.setFillColor(sf::Color::Black);
    }
    else {
        text.setFillColor(sf::Color::White);
    }
}


bool Button::isHovered() const {
    return text.getFillColor() == sf::Color::Black;
}

bool Button::isClicked(sf::Vector2f mousePosition) const {
    return text.getGlobalBounds().contains(mousePosition);
}
