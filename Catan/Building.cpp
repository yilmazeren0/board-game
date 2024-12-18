#include "Building.h"
#include "Player.h"

Building::Building(Player* owner, sf::Color color) : owner(owner), color(color) {}

Player* Building::getOwner() const {
    return owner;
}

sf::Color Building::getColor() const {
    return color;
}