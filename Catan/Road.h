#pragma once
#include "Building.h"

class Player;

/**
 * @file Road.h
 * @brief Defines the Road class, which represents a road in the game.
 */

/**
 * @class Road
 * @brief Represents a road built by a player in the game.
 * 
 * The `Road` class inherits from the `Building` class and represents a road 
 * that a player can construct. Each road is associated with a player and has
 * a color representing the player's identity. Roads play a crucial role in the 
 * game, connecting settlements and cities, and contributing to the player's 
 * potential for achieving the Longest Road victory condition.
 */
class Road : public Building {

public:
    /**
     * @brief Constructs a Road object for a player.
     * @param owner The player who owns this road.
     * @param color The color associated with the player who owns the road.
     */
    Road(Player* owner, sf::Color color);
};
