/**
 * @file City.h
 * @brief Defines the City class, representing an upgraded settlement in the game.
 */

#pragma once
#include "Settlement.h"

/**
 * @class City
 * @brief Represents a city, which is an upgraded version of a settlement.
 * Cities produce more resources than settlements.
 */
class City : public Settlement {
public:
    /**
     * @brief Constructs a City object.
     * @param owner Pointer to the player who owns the city.
     * @param color The color of the city, representing the owning player.
     */
    City(Player* owner, sf::Color color);

    /**
     * @brief Adds resources to the city during production.
     *        Overrides the Settlement's behavior to produce additional resources.
     * @param type The type of resource being added.
     */
    void addResource(ResourceType type) override;
};
