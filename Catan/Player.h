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
enum class Card {
    None,
    Knight,
    YearOfPlenty,
    RoadBuilding,
    Monopoly,
    VictoryPoint
};

class Player {
private:
    std::vector<Card> cards;
    std::map<Card, sf::Sprite> cardSprites;
    void initCardSprites(std::unordered_map<std::string, sf::Texture>* textures);
    void drawCards();
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

    std::map<int, sf::FloatRect> cardPositions;
    float xPart;
    float yPart;
    int knightsPlayed = 0;


public:
    Player(sf::RenderWindow* window, sf::View* view, std::unordered_map<std::string, sf::Texture>* textures, int id, sf::Color color);

    void draw();
    void update();
    void addCard(Card card);
    const std::vector<Card>& getCards() const { return cards; }
    void drawCardUI();
    bool canBuildRoad() const;
    void buildRoad();
    bool canBuildSettlement() const;
    void buildSettlement();
    void takeResources(ResourceType resourceType, int amount);
    int getID() const;
    sf::Color getColor()const;
    bool useKnightCard();
    bool useYearOfPlentyCard(ResourceType first, ResourceType second);
    bool useRoadBuildingCard();
    bool useMonopolyCard(ResourceType resource);
    bool useVictoryPointCard();
    bool hasCard(Card cardType) const;
    void removeCard(Card cardType);
    Card handleCardClick(sf::Vector2f clickPosition);
    void addResource(ResourceType type, int amount = 1);
    void removeResource(ResourceType type, int amount = 1);
    int getResourceCount(ResourceType type) const;
private:

    void initResources();
    void initTexts();
    void initTextures();

    void updateText();
};
