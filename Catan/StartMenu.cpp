#include "StartMenu.h"
#include "Catan.h"
#include <iostream>
#include <sstream>

StartMenu::StartMenu(sf::RenderWindow* window, sf::View* view, Catan* game)
    : Menu(window, view, game) {
    initializeButtons();
}

void StartMenu::initializeButtons() {
    // Initialize all buttons with their text, position and font
    titleBtn = std::make_unique<Button>("CATAN", font,
        view->getCenter().x + 14 * xPart,
        view->getCenter().y - 10 * yPart);

    // Set title button to larger size
    titleBtn->setCharacterSize(55);

    startGameBtn = std::make_unique<Button>("Start Game", font,
        view->getCenter().x + 14 * xPart,
        view->getCenter().y - 3 * yPart);

    leftArrowBtn = std::make_unique<Button>("<", font,
        view->getCenter().x + 11 * xPart,
        view->getCenter().y + 1 * yPart);

    playerCountBtn = std::make_unique<Button>("4 Players", font,
        view->getCenter().x + 14 * xPart,
        view->getCenter().y + 1.5f * yPart);

    rightArrowBtn = std::make_unique<Button>(">", font,
        view->getCenter().x + 17 * xPart,
        view->getCenter().y + 1 * yPart);

    randomizeBoardBtn = std::make_unique<Button>("Randomize Board", font,
        view->getCenter().x + 14 * xPart,
        view->getCenter().y + 6 * yPart);

    exitBtn = std::make_unique<Button>("Exit Game", font,
        view->getCenter().x + 14 * xPart,
        view->getCenter().y + 10 * yPart);

   
   
}

void StartMenu::draw() {
    titleBtn->draw(*window);
    startGameBtn->draw(*window);
    leftArrowBtn->draw(*window);
    playerCountBtn->draw(*window);
    rightArrowBtn->draw(*window);
    randomizeBoardBtn->draw(*window);
    exitBtn->draw(*window);
}

void StartMenu::update(sf::Vector2f mousePosition) {
    updateMousePosition();
    updatePlayerCount();

    // Update all buttons
    startGameBtn->update(mousePosition);
    leftArrowBtn->update(mousePosition);
    rightArrowBtn->update(mousePosition);
    randomizeBoardBtn->update(mousePosition);
    exitBtn->update(mousePosition);

    // Handle button clicks
    if (startGameBtn->isClicked(mousePosition)) {
        startGameBtn->animate();
        game->setMenu(false);
        game->resetClickPosition();
    }
    else if (leftArrowBtn->isClicked(mousePosition)) {
        leftArrowBtn->animate();
        game->decrementPlayerCount();
        game->resetClickPosition();
    }
    else if (rightArrowBtn->isClicked(mousePosition)) {
        rightArrowBtn->animate();
        game->incrementPlayerCount();
        game->resetClickPosition();
    }
    else if (randomizeBoardBtn->isClicked(mousePosition)) {
        randomizeBoardBtn->animate();
        game->restartBoard();
        game->resetClickPosition();
    }
    else if (exitBtn->isClicked(mousePosition)) {
        exitBtn->animate();
        game->resetClickPosition();
        window->close();
    }
}

void StartMenu::updatePlayerCount() {
    std::stringstream ss;
    ss << game->getPlayerCount() << " Players";
    playerCountBtn->setString(ss.str());
}

void StartMenu::updateMousePosition() {
    if (!window) return;
    sf::Vector2i pixelPos = sf::Mouse::getPosition(*window);
    mousePosition = window->mapPixelToCoords(pixelPos);
}
