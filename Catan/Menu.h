#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

class Catan;

class Menu {
public:
    Menu(sf::RenderWindow* window, sf::View* view, Catan* game)
        : window(window), view(view), game(game)
    {
        initializeBase();
    }

    virtual ~Menu() = default;

    // Pure virtual functions that must be implemented by derived classes
    virtual void draw() = 0;
    virtual void update(sf::Vector2f mousePosition) = 0;

protected:
    // Window and view pointers
    sf::RenderWindow* window;
    sf::View* view;
    Catan* game;

    // Resources
    sf::Font font;

    // Screen partitions for consistent positioning
    float xPart;  // Window width / 30
    float yPart;  // Window height / 30

    // Mouse position
    sf::Vector2f mousePosition;

    // Helper functions
    void updateMousePosition() {
        if (!window) return;
        sf::Vector2i pixelPos = sf::Mouse::getPosition(*window);
        mousePosition = window->mapPixelToCoords(pixelPos);
    }

private:
    void initializeBase() {
        // Calculate screen partitions
        xPart = window->getSize().x / 30.0f;
        yPart = window->getSize().y / 30.0f;

        // Load font
        if (!font.loadFromFile("font/emmasophia.ttf")) {
            throw std::runtime_error("Failed to load font in Menu");
        }
    }

protected:
    // Constants for menu positioning and sizing
    const float BUTTON_PADDING = 1.5f;     // Spacing between buttons
    const float TITLE_SCALE = 2.0f;        // Scale for title text
    const float BUTTON_SCALE = 1.0f;       // Scale for regular buttons

    // Standard button sizes
    const unsigned int TITLE_SIZE = 55;
    const unsigned int REGULAR_BUTTON_SIZE = 30;
    const unsigned int SMALL_BUTTON_SIZE = 25;

    // Standard colors
    const sf::Color NORMAL_COLOR = sf::Color::White;
    const sf::Color HOVER_COLOR = sf::Color::Yellow;
    const sf::Color ACTIVE_COLOR = sf::Color::Green;
    const sf::Color INACTIVE_COLOR = sf::Color(128, 128, 128); // Gray

    // Helper methods for derived classes
    sf::Vector2f getCenterPosition() const {
        return view->getCenter();
    }

    float getXPos(float multiplier) const {
        return getCenterPosition().x + multiplier * xPart;
    }

    float getYPos(float multiplier) const {
        return getCenterPosition().y + multiplier * yPart;
    }

    // Default button positions
    struct ButtonPositions {
        static constexpr float TITLE_X = 14.0f;
        static constexpr float TITLE_Y = -10.0f;
        static constexpr float START_X = 14.0f;
        static constexpr float START_Y = -3.0f;
        static constexpr float EXIT_X = 14.0f;
        static constexpr float EXIT_Y = 10.0f;
    };
};
