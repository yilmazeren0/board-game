#include "Player.h"

Player::Player(int id, sf::Color color) : playerID{ id }, color{ color } {
    initResources();

}

int Player::getID() const
{
    return playerID;
}

sf::Color Player::getColor() const
{
    return color;
}

void Player::initResources()
{
    resources[ResourceType::LUMBER] = 0;
    resources[ResourceType::BRICK] = 0;
    resources[ResourceType::ORE] = 0;
    resources[ResourceType::GRAIN] = 0;
    resources[ResourceType::WOOL] = 0;
}


