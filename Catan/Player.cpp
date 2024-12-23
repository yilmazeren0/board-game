#include "Player.h"
#include <iostream>
#include <sstream>
#include <string>

Player::Player(sf::RenderWindow* window, sf::View* view, std::unordered_map<std::string, sf::Texture>* textures, int id, sf::Color color)
    : window{window}, view{view}, textures{textures}, playerID{id}, color{color} {
    initResources();

    xPart = window->getSize().x / 30.0f;
    yPart = window->getSize().y / 30.0f;

    font.loadFromFile("font/emmasophia.ttf");

    initTexts();
    initTextures();

}

void Player::draw()
{
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

void Player::takeResources(ResourceType resourceType, int amount)
{
    resources[resourceType] += amount;
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


