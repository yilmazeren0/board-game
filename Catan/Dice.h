/**
 * @file Dice.h
 * @brief Defines the Dice class, used for rolling dice in the game and displaying the results.
 */

#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>

class Catan;

/**
 * @class Dice
 * @brief Represents a pair of dice for the game, handling rolling, updating, and rendering dice visuals.
 */
class Dice {
public:
    /**
     * @brief Constructs a Dice object.
     * @param window Pointer to the SFML RenderWindow for rendering dice visuals.
     * @param view Pointer to the SFML View for adjusting rendering context.
     * @param textures Pointer to a map of textures used for dice visuals.
     * @param game Pointer to the Catan game object to interact with game state.
     */
    Dice(sf::RenderWindow* window, sf::View* view, std::unordered_map<std::string, sf::Texture>* textures, Catan* game);

    /**
     * @brief Rolls the dice and generates random values for two dice.
     * @return The sum of the two dice values.
     */
    int rollDice();

    /**
     * @brief Updates the state of the dice, including any animations or transitions.
     */
    void update();

    /**
     * @brief Draws the dice visuals to the screen.
     */
    void draw();

private:
    sf::RenderWindow* window; ///< Pointer to the window used for rendering.
    sf::View* view; ///< Pointer to the view for rendering context adjustments.
    Catan* game; ///< Pointer to the Catan game object.
    std::unordered_map<std::string, sf::Texture>* textures; ///< Map of textures for dice visuals.
    sf::Sprite dice1Texture; ///< Sprite for the first die.
    sf::Sprite dice2Texture; ///< Sprite for the second die.
    int dice1; ///< Value of the first die.
    int dice2; ///< Value of the second die.

    float xPart; ///< Horizontal scaling factor for positioning.
    float yPart; ///< Vertical scaling factor for positioning.
};
