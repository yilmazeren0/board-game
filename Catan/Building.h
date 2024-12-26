/**
 * @file Building.h
 * @brief Defines the Building class, representing a generic building in the game.
 */

#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class Player;

/**
 * @class Building
 * @brief Represents a generic building owned by a player in the game.
 */
class Building {
protected:
    Player* owner;    ///< Pointer to the owner of the building.
    sf::Color color;  ///< Color representing the building's owner.

public:
    /**
     * @brief Constructs a Building object.
     * @param owner Pointer to the Player who owns the building.
     * @param color Color representing the owner of the building.
     */
    Building(Player* owner, sf::Color color);

    /**
     * @brief Gets the owner of the building.
     * @return Pointer to the Player who owns the building.
     */
    Player* getOwner() const;

    /**
     * @brief Gets the color of the building.
     * @return The color representing the building's owner.
     */
    sf::Color getColor() const;
};
