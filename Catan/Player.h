#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include "ResourceType.h"
#include "Road.h"
#include "Settlement.h"
#include "City.h"


class Player {
private:
    sf::RenderWindow* window;
    sf::View* view;
    std::unordered_map<std::string, sf::Texture>* textures;
    int playerID;
    std::map<ResourceType, int> resources;
    sf::Color color;
    sf::Text player;
    sf::Text lumber;
    sf::Text brick;
    sf::Text ore;
    sf::Text grain;
    sf::Text wool;
    sf::Font font;
    sf::Sprite lumberTexture;
    sf::Sprite brickTexture;
    sf::Sprite oreTexture;
    sf::Sprite grainTexture;
    sf::Sprite woolTexture;

    float xPart;
    float yPart;


public:
    Player(sf::RenderWindow* window, sf::View* view, std::unordered_map<std::string, sf::Texture>* textures, int id, sf::Color color);

    void draw();
    void update();
    
    int getID() const;
    sf::Color getColor()const;

private:
    void initResources();
    void initTexts();
    void initTextures();
};
