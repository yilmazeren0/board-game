#pragma once
#include "Building.h"

class Player;
enum class ResourceType;

class Settlement : public Building {
public:
    Settlement(Player* owner, sf::Color color);

    virtual void addResource(ResourceType type);
};

