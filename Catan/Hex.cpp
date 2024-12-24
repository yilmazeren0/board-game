#include "Hex.h"
#include <iostream>
Hex::Hex(sf::RenderWindow* window, std::unordered_map<std::string, sf::Texture>* textures,
    TerrainType terrainType, const std::array<int, 6>& vertexIndices,
    int number, int diceNumber)
    : window(window),
    textures(textures),
    terrainType(terrainType),
    ownedVertices(vertexIndices),
    diceNumber(diceNumber)  // Initialize the dice number here
{
    font.loadFromFile("font/emmasophia.ttf");
    resourceType = initResourceType(terrainType);

    hex.setPointCount(6);
    for (int i = 0; i < 6; ++i) {
        float angle_deg = 60.0f * i - 30.0f;
        float angle_rad = angle_deg * 3.14159265f / 180.0f;
        float x = radius * std::cos(angle_rad);
        float y = radius * std::sin(angle_rad);
        hex.setPoint(i, sf::Vector2f(x, y));
    }
    hex.setPosition(centerPoints[number]);
    
    robberSprite.setTexture((*textures)["robber"]);
    switch (terrainType) {
        case TerrainType::HILLS:
            sprite.setTexture((*textures)["hills"]); break;
        case TerrainType::FOREST:
            sprite.setTexture((*textures)["forest"]); break;
        case TerrainType::MOUNTAINS:
            sprite.setTexture((*textures)["mountains"]); break;
        case TerrainType::FIELDS:
            sprite.setTexture((*textures)["fields"]); break;
        case TerrainType::PASTURE:
            sprite.setTexture((*textures)["pasture"]); break;
        case TerrainType::DESERT:
            sprite.setTexture((*textures)["desert"]); hasRobber=true; break;
    }

    sf::Vector2u texSize = sprite.getTexture()->getSize();

    sprite.setOrigin(texSize.x / 2.0f, texSize.y / 2.0f);
    sprite.setPosition(centerPoints[number]);
    float desiredWidth = 2.0f * radius;
    float scaleX = desiredWidth / static_cast<float>(texSize.x);
    float scaleY = desiredWidth / static_cast<float>(texSize.y);
    float scale = std::min(scaleX, scaleY);
    sprite.setScale(scale, scale);
    sprite.setRotation(270.0f);
   
    sf::Vector2u robberSize = robberSprite.getTexture()->getSize();
    robberSprite.setOrigin(robberSize.x / 2.0f, robberSize.y / 2.0f);
    robberSprite.setPosition(centerPoints[number]);
    scaleX = desiredWidth / static_cast<float>(robberSize.x);
    scaleY = desiredWidth / static_cast<float>(robberSize.y);
    scale = std::min(scaleX, scaleY);
    robberSprite.setScale(scale, scale);
    
    if (hasRobber) {
        robberSprite.setColor(sf::Color(0, 0, 0, 210));
    }
    else {
        robberSprite.setColor(sf::Color(0, 0, 0, 0));
    }

    circle.setRadius(radius / 3.5f);
    circle.setFillColor(sf::Color(255, 253, 208));
    circle.setOrigin(circle.getRadius(), circle.getRadius());
    circle.setPosition(centerPoints[number]);

    text.setFont(font);
    text.setString(std::to_string(diceNumber));
    text.setCharacterSize(10);

    
    text.setFillColor(sf::Color::Black);

    sf::FloatRect textBounds = text.getLocalBounds();
    text.setOrigin(textBounds.left + textBounds.width / 2.0f,
        textBounds.top + textBounds.height / 2.0f);
    text.setPosition(centerPoints[number].x, centerPoints[number].y);
}
Hex::~Hex()
{
}


const std::array<int, 6>& Hex::getOwnedVertices() const
{
    return ownedVertices;
}




ResourceType Hex::getResourceType() const
{
    return resourceType;
}

ResourceType Hex::initResourceType(TerrainType terrainType) {
    switch (terrainType) {
    case TerrainType::HILLS:
        return ResourceType::BRICK; break;
    case TerrainType::FOREST:
        return ResourceType::LUMBER; break;
    case TerrainType::MOUNTAINS:
        return ResourceType::ORE; break;
    case TerrainType::FIELDS:
        return ResourceType::GRAIN; break;
    case TerrainType::PASTURE:
        return ResourceType::WOOL; break;
    case TerrainType::DESERT:
        return ResourceType::NONE; break;
    default:
        return ResourceType::NONE;
    }
}
void Hex::setRobber()
{
    hasRobber = true;
    robberSprite.setColor(sf::Color(0, 0, 0, 210));
}
void Hex::removeRobber()
{
    hasRobber = false;
    robberSprite.setColor(sf::Color(0, 0, 0, 0));
}
void Hex::update()
{
}

void Hex::draw()
{
    window->draw(hex);

    window->draw(sprite);

    window->draw(circle);

    window->draw(text);

    window->draw(robberSprite);
}

std::array<sf::Vector2f, 19> Hex::centerPoints = {
    sf::Vector2f(center - 2 * radius, center - 2 * std::sqrt(3.0f) * radius),
    sf::Vector2f(center, center - 2 * std::sqrt(3.0f) * radius),
    sf::Vector2f(center + 2 * radius, center - 2 * std::sqrt(3.0f) * radius),
    sf::Vector2f(center - 3.0f * radius, center - std::sqrt(3.0f) * radius),
    sf::Vector2f(center - 1.0f * radius, center - std::sqrt(3.0f) * radius),
    sf::Vector2f(center + 1.0f * radius, center - std::sqrt(3.0f) * radius),
    sf::Vector2f(center + 3.0f * radius, center - std::sqrt(3.0f) * radius),
    sf::Vector2f(center - 4 * radius, center),
    sf::Vector2f(center - 2 * radius, center),
    sf::Vector2f(center, center),//center
    sf::Vector2f(center + 2 * radius, center),
    sf::Vector2f(center + 4 * radius, center),
    sf::Vector2f(center - 3.0f * radius, center + std::sqrt(3.0f) * radius),
    sf::Vector2f(center - 1.0f * radius, center + std::sqrt(3.0f) * radius),
    sf::Vector2f(center + 1.0f * radius, center + std::sqrt(3.0f) * radius),
    sf::Vector2f(center + 3.0f * radius, center + std::sqrt(3.0f) * radius),
    sf::Vector2f(center - 2 * radius, center + 2 * std::sqrt(3.0f) * radius),
    sf::Vector2f(center, center + 2 * std::sqrt(3.0f) * radius),
    sf::Vector2f(center + 2 * radius, center + 2 * std::sqrt(3.0f) * radius)
};

const float Hex::center = 0.0f;
const float Hex::radius = 60.0f;