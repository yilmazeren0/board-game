#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <map>
#include "ResourceType.h"
#include "Road.h"
#include "Settlement.h"
#include "City.h"


class Player {
private:
    //std::string name;
    int playerID;
    std::map<ResourceType, int> resources;
    sf::Color color;

public:
    Player(int id, sf::Color color);
    
    int getID() const;
    sf::Color getColor()const;

private:
    void initResources();
};
