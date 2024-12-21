#include "Dice.h"
#include "Catan.h"
#include <cstdlib>
#include <ctime> 

Dice::Dice(sf::RenderWindow* window, std::unordered_map<std::string, sf::Texture>* textures, Catan* game) : window{ window },
    textures { textures }, game{game}
{
    std::srand(static_cast<unsigned int>(std::time(0)));
    dice1 = 6;
    dice2 = 6;

    dice1Texture.setTexture((*textures)["dice6"]);
    dice2Texture.setTexture((*textures)["dice6"]);;

    sf::Vector2u texSize1 = dice1Texture.getTexture()->getSize();
    sf::Vector2u texSize2 = dice2Texture.getTexture()->getSize();

    dice1Texture.setOrigin(texSize1.x / 2.0f, texSize1.y / 2.0f);
    dice2Texture.setOrigin(texSize2.x / 2.0f, texSize2.y / 2.0f);
    dice1Texture.setPosition(760.0f, -70.0f);
    dice2Texture.setPosition(760.0f, -20.0f);
    dice1Texture.setScale(0.5f, 0.5f);
    dice2Texture.setScale(0.5f, 0.5f);
}
#include <iostream>
int Dice::rollDice()
{
    dice1 = (std::rand() % 6) + 1;
    
    dice2 = (std::rand() % 6) + 1;
    std::cout << dice1 << ' ' << dice2;
    return dice1 + dice2;
}

void Dice::update()
{
    switch (dice1) {
    case 1:
        dice1Texture.setTexture((*textures)["dice1"]); break;
    case 2:
        dice1Texture.setTexture((*textures)["dice2"]); break;
    case 3:
        dice1Texture.setTexture((*textures)["dice3"]); break;
    case 4:
        dice1Texture.setTexture((*textures)["dice4"]); break;
    case 5:
        dice1Texture.setTexture((*textures)["dice5"]); break;
    case 6:
        dice1Texture.setTexture((*textures)["dice6"]); break;
    }

    switch (dice2) {
    case 1:
        dice2Texture.setTexture((*textures)["dice1"]); break;
    case 2:
        dice2Texture.setTexture((*textures)["dice2"]); break;
    case 3:
        dice2Texture.setTexture((*textures)["dice3"]); break;
    case 4:
        dice2Texture.setTexture((*textures)["dice4"]); break;
    case 5:
        dice2Texture.setTexture((*textures)["dice5"]); break;
    case 6:
        dice2Texture.setTexture((*textures)["dice6"]); break;
    }


}

void Dice::draw()
{
    if (!(game->isMenu())) {
        window->draw(dice1Texture);
        window->draw(dice2Texture);
    }
}
