#pragma once
#include <SFML/Graphics.hpp>

// Button.h
class Button {
public:
    Button(const std::string& text, const sf::Font& font, float x, float y);
    virtual ~Button() = default;
    virtual void draw(sf::RenderWindow& window);
    virtual void update(sf::Vector2f mousePosition);
    virtual bool isHovered() const;
    virtual bool isClicked(sf::Vector2f mousePosition) const;
    virtual void animate();

    // Add these accessor methods
    void setCharacterSize(unsigned int size);
    void setString(const std::string& str);
    sf::Text& getText() { return text; }
    const sf::Text& getText() const { return text; }

protected:
    sf::Text text;
    float originalScale = 1.0f;
    float currentScale = 1.0f;
    bool isAnimating = false;
    float animationSpeed = 0.1f;    // Adjust for faster/slower animation
    const float maxScale = 1.2f;    // Adjust for larger/smaller scale
    const float minScale = 1.0f;
};
