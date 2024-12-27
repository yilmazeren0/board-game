/**
 * @file Button.h
 * @brief Defines the Button class for interactive UI elements.
 */

#pragma once

#include <SFML/Graphics.hpp>
#include <string>

/**
 * @class Button
 * @brief Represents an interactive button for the game's user interface.
 */
class Button {
public:
    /**
     * @brief Constructs a Button object.
     * @param text The text displayed on the button.
     * @param font The font used for the button text.
     * @param x The x-coordinate of the button's position.
     * @param y The y-coordinate of the button's position.
     */
    Button(const std::string& text, const sf::Font& font, float x, float y);

    /**
     * @brief Virtual destructor for the Button class.
     */
    virtual ~Button() = default;

    /**
     * @brief Draws the button on the provided window.
     * @param window Reference to the SFML RenderWindow.
     */
    virtual void draw(sf::RenderWindow& window);

    /**
     * @brief Updates the button's state based on mouse position.
     * @param mousePosition The current mouse position.
     */
    virtual void update(sf::Vector2f mousePosition);

    /**
     * @brief Checks if the button is being hovered over by the mouse.
     * @return True if the mouse is hovering over the button, false otherwise.
     */
    virtual bool isHovered() const;

    /**
     * @brief Checks if the button is clicked based on mouse position.
     * @param mousePosition The position of the mouse click.
     * @return True if the button is clicked, false otherwise.
     */
    virtual bool isClicked(sf::Vector2f mousePosition) const;

    /**
     * @brief Animates the button for hover effects.
     */
    virtual void animate();

    /**
     * @brief Sets the character size of the button text.
     * @param size The new character size.
     */
    void setCharacterSize(unsigned int size);

    /**
     * @brief Sets the string displayed on the button.
     * @param str The new string for the button.
     */
    void setString(const std::string& str);

    /**
     * @brief Gets a mutable reference to the button's text.
     * @return Reference to the SFML Text object.
     */
    sf::Text& getText();

    /**
     * @brief Gets a constant reference to the button's text.
     * @return Constant reference to the SFML Text object.
     */
    const sf::Text& getText() const;

protected:
    sf::Text text;                 ///< The text displayed on the button.
    float originalScale = 1.0f;    ///< The original scale of the button.
    float currentScale = 1.0f;     ///< The current scale of the button during animation.
    bool isAnimating = false;      ///< Flag indicating if the button is animating.
    float animationSpeed = 0.1f;   ///< Speed of the button animation.
    const float maxScale = 1.2f;   ///< Maximum scale during animation.
    const float minScale = 1.0f;   ///< Minimum scale during animation.
};
