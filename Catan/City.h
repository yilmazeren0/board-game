#pragma once
#include "Settlement.h"

class Player;

class City : public Settlement {
public:
    City( Player* owner, sf::Color color);

    void addResource(ResourceType type) override;

};
