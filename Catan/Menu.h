#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

class Catan;

/**
 * @file Menu.h
 * @brief Defines the Menu class, which serves as an abstract base class for creating various menus in the game.
 */

class Menu {
public:
    /**
     * @brief Constructs a Menu object.
     * @param window Pointer to the SFML RenderWindow used for rendering.
     * @param view Pointer to the SFML View for positioning the camera.
     * @param game Pointer to the Catan game object for accessing game state.
     */
    Menu(sf::RenderWindow* window, sf::View* view, Catan* game)
        : window(window), view(view), game(game)
    {
        initializeBase();
    }

    /**
     * @brief Virtual destructor for the Menu class.
     */
    virtual ~Menu() = default;

    /**
     * @brief Pure virtual function for drawing the menu elements.
     * @details This function must be implemented by derived classes to render
     *          the specific menu contents.
     */
    virtual void draw() = 0;

    /**
     * @brief Pure virtual function for updating the menu state based on mouse position.
     * @param mousePosition The current mouse position in window coordinates.
     * @details This function must be implemented by derived classes to handle
     *          mouse interactions with the menu.
     */
    virtual void update(sf::Vector2f mousePosition) = 0;

protected:
    /** @brief Pointer to the SFML RenderWindow for rendering. */
    sf::RenderWindow* window;
    
    /** @brief Pointer to the SFML View for adjusting the camera view. */
    sf::View* view;
    
    /** @brief Pointer to the Catan game object to access game state. */
    Catan* game;

    /** @brief Font for rendering text on the menu. */
    sf::Font font;

    /** @brief Horizontal screen partition factor used for positioning elements. */
    float xPart;  

    /** @brief Vertical screen partition factor used for positioning elements. */
    float yPart;  

    /** @brief Current mouse position in window coordinates. */
    sf::Vector2f mousePosition;

    /**
     * @brief Updates the mouse position based on the current window.
     * @details This function retrieves the current mouse position in pixel coordinates
     *          and maps it to the coordinate system of the view.
     */
    void updateMousePosition() {
        if (!window) return;
        sf::Vector2i pixelPos = sf::Mouse::getPosition(*window);
        mousePosition = window->mapPixelToCoords(pixelPos);
    }

private:
    /**
     * @brief Initializes base values such as font and screen partition sizes.
     * @details This function calculates partition sizes for consistent element placement
     *          and loads the font used for text rendering on the menu.
     * @throws std::runtime_error If the font loading fails.
     */
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
    const float BUTTON_PADDING = 1.5f;     ///< Spacing between buttons
    const float TITLE_SCALE = 2.0f;        ///< Scale for title text
    const float BUTTON_SCALE = 1.0f;       ///< Scale for regular buttons

    /** @brief Size of the title text. */
    const unsigned int TITLE_SIZE = 55;

    /** @brief Size of regular buttons. */
    const unsigned int REGULAR_BUTTON_SIZE = 30;

    /** @brief Size of smaller buttons. */
    const unsigned int SMALL_BUTTON_SIZE = 25;

    // Standard colors for menu elements
    const sf::Color NORMAL_COLOR = sf::Color::White;    ///< Color for normal button state
    const sf::Color HOVER_COLOR = sf::Color::Yellow;    ///< Color for button hover state
    const sf::Color ACTIVE_COLOR = sf::Color::Green;    ///< Color for active button state
    const sf::Color INACTIVE_COLOR = sf::Color(128, 128, 128); ///< Color for inactive button state

    /**
     * @brief Gets the center position of the current view.
     * @return A vector representing the center position of the view.
     */
    sf::Vector2f getCenterPosition() const {
        return view->getCenter();
    }

    /**
     * @brief Calculates the X position for a menu element.
     * @param multiplier Multiplier for adjusting the X position.
     * @return The calculated X position.
     */
    float getXPos(float multiplier) const {
        return getCenterPosition().x + multiplier * xPart;
    }

    /**
     * @brief Calculates the Y position for a menu element.
     * @param multiplier Multiplier for adjusting the Y position.
     * @return The calculated Y position.
     */
    float getYPos(float multiplier) const {
        return getCenterPosition().y + multiplier * yPart;
    }

    // Default button positions in the menu
    struct ButtonPositions {
        static constexpr float TITLE_X = 14.0f;  ///< X position for the title
        static constexpr float TITLE_Y = -10.0f; ///< Y position for the title
        static constexpr float START_X = 14.0f;  ///< X position for the start button
        static constexpr float START_Y = -3.0f;  ///< Y position for the start button
        static constexpr float EXIT_X = 14.0f;   ///< X position for the exit button
        static constexpr float EXIT_Y = 10.0f;   ///< Y position for the exit button
    };
};
