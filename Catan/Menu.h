#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

class Catan;

class Menu {
public:
    Menu(sf::RenderWindow* window, sf::View* view, Catan* game)
        : window(window), view(view), game(game) {
        xPart = window->getSize().x / 30.0f;
        yPart = window->getSize().y / 30.0f;

        if (!font.loadFromFile("font/emmasophia.ttf")) {
            throw std::runtime_error("Failed to load font");
        }
    }

    virtual ~Menu() = default;
    virtual void draw() = 0;
    virtual void update(sf::Vector2f mousePosition) = 0;

protected:
    sf::RenderWindow* window;
    sf::View* view;
    Catan* game;
    sf::Font font;
    float xPart;
    float yPart;
    sf::Vector2f mousePosition;
    void updateMousePosition();
};