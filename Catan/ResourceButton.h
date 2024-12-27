#pragma once
#include <SFML/Graphics.hpp>

/**
 * @file ResourceButton.h
 * @brief Defines the ResourceButton class, which represents a clickable button for resources.
 */


/**
 * @class ResourceButton
 * @brief Represents a clickable button for resource selection in the game.
 * 
 * The `ResourceButton` class provides the functionality needed to display a resource
 * button on the screen, handle user interactions, and trigger actions when clicked.
 * It uses an SFML sprite for visual representation and allows the button's position
 * and appearance to be customized.
 */
class ResourceButton {
public:
    /**
     * @brief Default constructor for the ResourceButton class.
     * 
     * Initializes the resource button with default values.
     */
    ResourceButton();

    /**
     * @brief Sets the position of the button on the screen.
     * @param x The x-coordinate of the button's position.
     * @param y The y-coordinate of the button's position.
     */
    void setPosition(float x, float y);

    /**
     * @brief Draws the button to the given window.
     * @param window The SFML window where the button will be drawn.
     */
    void draw(sf::RenderWindow& window);

    /**
     * @brief Checks if the button has been clicked by the player.
     * @param mousePos The position of the mouse click.
     * @return True if the button was clicked, false otherwise.
     */
    bool isClicked(const sf::Vector2f& mousePos);

private:
    sf::Sprite sprite; ///< The SFML sprite representing the resource button.
    sf::Vector2f position; ///< The position of the button on the screen.
    
    // Add other necessary members such as textures or other visual elements.
};
