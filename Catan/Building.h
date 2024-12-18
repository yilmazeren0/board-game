#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Player;

class Building {
protected:
    Player* owner;
    sf::Color color;

public:
    Building(Player* owner, sf::Color color);

    Player* getOwner() const;
    sf::Color getColor() const;
};

