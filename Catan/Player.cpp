#include "Player.h"
#include <iostream>
#include <sstream>
#include <string>

Player::Player(sf::RenderWindow* window, sf::View* view, std::unordered_map<std::string, sf::Texture>* textures, int id, sf::Color color)
    : window{ window }, view{ view }, textures{ textures }, playerID{ id }, color{ color } {
    initResources();

    xPart = window->getSize().x / 30.0f;
    yPart = window->getSize().y / 30.0f;

    font.loadFromFile("font/emmasophia.ttf");

    initTexts();
    initTextures();
    initCardSprites(textures); // Add this line
}

void Player::draw() {
    window->draw(player);
    window->draw(lumber);
    window->draw(brick);
    window->draw(ore);
    window->draw(grain);
    window->draw(wool);
    window->draw(lumberTexture);
    window->draw(brickTexture);
    window->draw(oreTexture);
    window->draw(grainTexture);
    window->draw(woolTexture);

   
}
void Player::update()
{
    updateText();
}

int Player::getVictoryPoints() const {
    // Calculate total victory points:
    // - Settlements (1 point each)
    // - Cities (2 points each)
    // - Victory point cards
    // - Longest road bonus (2 points)
    // - Largest army bonus (2 points)
    int total = victoryPoints;

    // Add points from victory point cards
    total += std::count(cards.begin(), cards.end(), Card::VictoryPoint);

    return total;
}

void Player::setLongestRoad(bool has) {
    if (has && !hasLongestRoad) {
        victoryPoints += 2;  // Add 2 points when gaining longest road
    }
    else if (!has && hasLongestRoad) {
        victoryPoints -= 2;  // Remove 2 points when losing longest road
    }
    hasLongestRoad = has;
}


bool Player::hasResources() const {
    return getTotalResources() > 0;
}

int Player::getTotalResources() const {
    int total = 0;
    for (const auto& [type, count] : resources) {
        total += count;
    }
    return total;
}


ResourceType Player::getRandomResource() const {
    std::vector<ResourceType> available;
    for (const auto& [type, count] : resources) {
        if (count > 0) {
            available.push_back(type);
        }
    }
    if (!available.empty()) {
        return available[rand() % available.size()];
    }
    return ResourceType::NONE;
}

void Player::discardResources(int count) {
    // Implement logic to discard half of resources when count > 7
    while (count > 0 && getTotalResources() > 0) {
        ResourceType resource = getRandomResource();
        if (resource != ResourceType::NONE) {
            removeResource(resource, 1);
            count--;
        }
    }
}

void Player::setMustMoveRobber(bool must) {
    mustPlaceRobber = must;
}

bool Player::mustMoveRobber() const {
    return mustPlaceRobber;
}

void Player::initCardSprites(std::unordered_map<std::string, sf::Texture>* textures) {
    sf::Sprite sprite;

    // Initialize each card sprite
    sprite.setTexture((*textures)["knight"]);
    cardSprites[Card::Knight] = sprite;

    sprite.setTexture((*textures)["year_of_plenty"]);
    cardSprites[Card::YearOfPlenty] = sprite;

    sprite.setTexture((*textures)["road_building"]);
    cardSprites[Card::RoadBuilding] = sprite;

    sprite.setTexture((*textures)["monopoly"]);
    cardSprites[Card::Monopoly] = sprite;

    sprite.setTexture((*textures)["victory_point"]);
    cardSprites[Card::VictoryPoint] = sprite;

    // Set scale for all card sprites
    for (auto& pair : cardSprites) {
        pair.second.setScale(0.60f, 0.60f);  // Adjust scale as needed

        // Set origin to center of sprite
        sf::Vector2u texSize = pair.second.getTexture()->getSize();
        pair.second.setOrigin(texSize.x / 2.0f, texSize.y / 2.0f);
    }
}

void Player::drawCardUI() {
    float startX = view->getCenter().x - (13.0f * xPart);
    float y = view->getCenter().y + (13.0f * yPart);
    float spacing = 6.0f * xPart;

    int i = 0;
    for (const Card& card : cards) {
        sf::Sprite& sprite = cardSprites[card];
        sprite.setPosition(startX + (spacing * i), y);
        window->draw(sprite);

        // Store card position for click detection
        cardPositions[i] = sprite.getGlobalBounds();
        i++;
    }
}
void Player::addResource(ResourceType type, int amount) {
    resources[type] += amount;
}

void Player::removeResource(ResourceType type, int amount) {
    resources[type] = std::max(0, resources[type] - amount);
}

int Player::getResourceCount(ResourceType type) const {
    return resources.at(type);
}
void Player::incrementKnightsPlayed()
{
    knightsPlayed++;
}

int Player::getKnightsPlayed() const
{
    return knightsPlayed;
}

// Add this function to handle card clicks
Card Player::handleCardClick(sf::Vector2f clickPos) {
    int i = 0;
    for (const Card& card : cards) {
        if (cardPositions[i].contains(clickPos)) {
            return card;
        }
        i++;
    }
    return Card::None; // Add None to your Card enum
}

void Player::addCard(Card card) {
    cards.push_back(card);
}
const std::vector<Card>& Player::getCards() const
{
    return cards;
}
bool Player::canBuildRoad() const
{
    return (resources.at(ResourceType::LUMBER) >= 1 && resources.at(ResourceType::BRICK) >= 1);
}

bool Player::hasCard(Card cardType) const {
    return std::find(cards.begin(), cards.end(), cardType) != cards.end();
}

void Player::removeCard(Card cardType) {
    auto it = std::find(cards.begin(), cards.end(), cardType);
    if (it != cards.end()) {
        cards.erase(it);
    }
}

bool Player::useKnightCard() {
    if (!hasCard(Card::Knight)) return false;

    removeCard(Card::Knight);
    knightsPlayed++;
    // The actual moving of robber will be handled by Catan class
    return true;
}

bool Player::useYearOfPlentyCard(ResourceType first, ResourceType second) {
    if (!hasCard(Card::YearOfPlenty)) return false;

    removeCard(Card::YearOfPlenty);
    resources[first]++;
    resources[second]++;
    return true;
}

bool Player::useRoadBuildingCard() {
    if (!hasCard(Card::RoadBuilding)) return false;

    removeCard(Card::RoadBuilding);
    // The actual road placement will be handled by Catan class
    return true;
}

bool Player::useMonopolyCard(ResourceType resource) {
    if (!hasCard(Card::Monopoly)) return false;

    removeCard(Card::Monopoly);
    // The resource collection will be handled by Catan class
    return true;
}

bool Player::useVictoryPointCard() {
    if (!hasCard(Card::VictoryPoint)) return false;

    removeCard(Card::VictoryPoint);
    // Add victory point
    return true;
}

void Player::buildRoad()
{
    resources[ResourceType::LUMBER] -= 1;
    resources[ResourceType::BRICK] -= 1;
}

bool Player::canBuildSettlement() const
{
    return (resources.at(ResourceType::LUMBER) >= 1 && resources.at(ResourceType::BRICK) >= 1 &&
        resources.at(ResourceType::GRAIN) >= 1 && resources.at(ResourceType::WOOL) >= 1);
}

void Player::buildSettlement()
{
    resources[ResourceType::LUMBER] -= 1;
    resources[ResourceType::BRICK] -= 1;
    resources[ResourceType::GRAIN] -= 1;
    resources[ResourceType::WOOL] -= 1;
}

void Player::takeResources(ResourceType resourceType, int amount)
{
    resources[resourceType] += amount;
}

const std::map<ResourceType, int>& Player::getResources() const
{
    return resources;
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

void Player::initTexts()
{
    //Players turn text
    std::stringstream temp;
    temp << "Player " << playerID + 1 << "'s Turn";
    player.setFont(font);
    player.setString(temp.str());
    player.setCharacterSize(35);
    player.setOrigin(player.getGlobalBounds().width / 2.0f, player.getGlobalBounds().height / 2.0f);
    player.setPosition(view->getCenter().x + 7.0f * xPart, view->getCenter().y - 8.0f * yPart);

    //LUMBER
    temp.str("");
    temp.clear();
    temp << resources[ResourceType::LUMBER] << 'x';
    lumber.setFont(font);
    lumber.setString(temp.str());
    lumber.setCharacterSize(15);
    lumber.setOrigin(lumber.getGlobalBounds().width / 2.0f, lumber.getGlobalBounds().height / 2.0f);
    lumber.setPosition(view->getCenter().x + 13.0f * xPart, view->getCenter().y - 5.6f * yPart);

    //BRICK
    temp.str("");
    temp.clear();
    temp << resources[ResourceType::BRICK] << 'x';
    brick.setFont(font);
    brick.setString(temp.str());
    brick.setCharacterSize(15);
    brick.setOrigin(brick.getGlobalBounds().width / 2.0f, brick.getGlobalBounds().height / 2.0f);
    brick.setPosition(view->getCenter().x + 13.0f * xPart, view->getCenter().y - 2.6f * yPart);

    //ORE
    temp.str("");
    temp.clear();
    temp << resources[ResourceType::ORE] << 'x';
    ore.setFont(font);
    ore.setString(temp.str());
    ore.setCharacterSize(15);
    ore.setOrigin(ore.getGlobalBounds().width / 2.0f, ore.getGlobalBounds().height / 2.0f);
    ore.setPosition(view->getCenter().x + 13.0f * xPart, view->getCenter().y + 0.4f * yPart);
    //GRAIN
    temp.str("");
    temp.clear();
    temp << resources[ResourceType::GRAIN] << 'x';
    grain.setFont(font);
    grain.setString(temp.str());
    grain.setCharacterSize(15);
    grain.setOrigin(grain.getGlobalBounds().width / 2.0f, grain.getGlobalBounds().height / 2.0f);
    grain.setPosition(view->getCenter().x + 13.0f * xPart, view->getCenter().y + 3.4f * yPart);
    //WOOL
    temp.str("");
    temp.clear();
    temp << resources[ResourceType::WOOL] << 'x';
    wool.setFont(font);
    wool.setString(temp.str());
    wool.setCharacterSize(15);
    wool.setOrigin(wool.getGlobalBounds().width / 2.0f, wool.getGlobalBounds().height / 2.0f);
    wool.setPosition(view->getCenter().x + 13.0f * xPart, view->getCenter().y + 6.4f * yPart);
}

void Player::initTextures()
{
    //LUMBER
    lumberTexture.setTexture((*textures)["lumber"]);
    sf::Vector2u texSize1 = lumberTexture.getTexture()->getSize();
    lumberTexture.setOrigin(texSize1.x / 2.0f, texSize1.y / 2.0f);
    lumberTexture.setPosition(view->getCenter().x + 14.3f * xPart, view->getCenter().y - 6.0f * yPart);
    lumberTexture.setScale(0.25f, 0.25f);

    //BRICK
    brickTexture.setTexture((*textures)["brick"]);
    texSize1 = brickTexture.getTexture()->getSize();
    brickTexture.setOrigin(texSize1.x / 2.0f, texSize1.y / 2.0f);
    brickTexture.setPosition(view->getCenter().x + 14.3f * xPart, view->getCenter().y - 3.0f * yPart);
    brickTexture.setScale(0.25f, 0.25f);

    //ORE
    oreTexture.setTexture((*textures)["ore"]);
    texSize1 = oreTexture.getTexture()->getSize();
    oreTexture.setOrigin(texSize1.x / 2.0f, texSize1.y / 2.0f);
    oreTexture.setPosition(view->getCenter().x + 14.3f * xPart, view->getCenter().y - 0.0f * yPart);
    oreTexture.setScale(0.25f, 0.25f);

    //GRAIN
    grainTexture.setTexture((*textures)["grain"]);
    texSize1 = grainTexture.getTexture()->getSize();
    grainTexture.setOrigin(texSize1.x / 2.0f, texSize1.y / 2.0f);
    grainTexture.setPosition(view->getCenter().x + 14.3f * xPart, view->getCenter().y + 3.0f * yPart);
    grainTexture.setScale(0.25f, 0.25f);

    //WOOL
    woolTexture.setTexture((*textures)["wool"]);
    texSize1 = woolTexture.getTexture()->getSize();
    woolTexture.setOrigin(texSize1.x / 2.0f, texSize1.y / 2.0f);
    woolTexture.setPosition(view->getCenter().x + 14.3f * xPart, view->getCenter().y + 6.0f * yPart);
    woolTexture.setScale(0.25f, 0.25f);

}

void Player::updateText()
{
    std::stringstream temp;
    temp << "Player " << playerID + 1 << "'s Turn";
    player.setString(temp.str());

    //LUMBER
    temp.str("");
    temp.clear();
    temp << resources[ResourceType::LUMBER] << 'x';
    lumber.setString(temp.str());

    //BRICK
    temp.str("");
    temp.clear();
    temp << resources[ResourceType::BRICK] << 'x';
    brick.setString(temp.str());


    //ORE
    temp.str("");
    temp.clear();
    temp << resources[ResourceType::ORE] << 'x';
    ore.setString(temp.str());

    //LUMBER
    temp.str("");
    temp.clear();
    temp << resources[ResourceType::GRAIN] << 'x';
    grain.setString(temp.str());

    //LUMBER
    temp.str("");
    temp.clear();
    temp << resources[ResourceType::WOOL] << 'x';
    wool.setString(temp.str());

}


