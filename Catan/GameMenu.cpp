#include "GameMenu.h"
#include "Catan.h"
#include <iostream>

// GameMenu implementation
GameMenu::GameMenu(sf::RenderWindow* window, sf::View* view, Catan* game)
    : window(window)
    , view(view)
    , game(game)
    , is_rollDice(false)
    , is_buildingMenu(false) {

    xPart = window->getSize().x / 30.0f;
    yPart = window->getSize().y / 30.0f;

    if (!font.loadFromFile("font/emmasophia.ttf")) {
        throw std::runtime_error("Failed to load font");
    }

    initializeButtons();
}

void GameMenu::initializeButtons() {
    // Initialize main menu buttons
    rollDiceBtn = std::make_unique<MenuButton>("Roll Dice", font,
        view->getCenter().x + 11.0f * xPart, view->getCenter().y - 3.4f * yPart);

    buildingBtn = std::make_unique<MenuButton>("Building", font,
        view->getCenter().x + 10.6f * xPart, view->getCenter().y);

    bankBtn = std::make_unique<MenuButton>("Bank", font,
        view->getCenter().x + 10.1f * xPart, view->getCenter().y + 3 * yPart);

    deckBtn = std::make_unique<MenuButton>("Deck", font,
        view->getCenter().x + 10.2f * xPart, view->getCenter().y + 6 * yPart);

    tradeBtn = std::make_unique<MenuButton>("Trade", font,
        view->getCenter().x + 10.4f * xPart, view->getCenter().y + 9 * yPart);

    nextTurnBtn = std::make_unique<MenuButton>("Next Turn", font,
        view->getCenter().x + 11.5f * xPart, view->getCenter().y + 12 * yPart);

    // Initialize building menu buttons
    backBtn = std::make_unique<MenuButton>("Back", font,
        view->getCenter().x + 10.2f * xPart, view->getCenter().y);

    buildingBuyRoadBtn = std::make_unique<MenuButton>("Buy Road", font,
        view->getCenter().x + 11.3f * xPart, view->getCenter().y + 3 * yPart);

    buildingBuySettlementBtn = std::make_unique<MenuButton>("Buy Settlement", font,
        view->getCenter().x + 12.6f * xPart, view->getCenter().y + 6 * yPart);
}


void GameMenu::draw() {
    if (is_buildingMenu) {
        backBtn->draw(*window);
        buildingBuyRoadBtn->draw(*window);
        buildingBuySettlementBtn->draw(*window);
    }
    else {
        rollDiceBtn->draw(*window);
        buildingBtn->draw(*window);
        bankBtn->draw(*window);
        deckBtn->draw(*window);
        tradeBtn->draw(*window);
        nextTurnBtn->draw(*window);
    }
}

void GameMenu::update(sf::Vector2f mousePosition) {
    try {
        updateMousePosition();

        if (is_buildingMenu) {
            handleBuildingMenu(mousePosition);
        }
        else {
            handleMainMenu(mousePosition);
        }

        // Update button visuals
        updateButtonStates(mousePosition);
    }
    catch (const std::exception& e) {
        std::cerr << "Error in GameMenu::update: " << e.what() << std::endl;
    }
}


void GameMenu::handleBuildingMenu(sf::Vector2f mousePosition) {
    if (backBtn->isClicked(mousePosition)) {
        game->resetClickPosition();
        is_buildingMenu = false;
        std::cout << "back\n";
    }
    else if (buildingBuyRoadBtn->isClicked(mousePosition) && game->canBuildRoad()) {
        game->resetClickPosition();
        game->buyRoad();
        std::cout << "buildingBuyRoad\n";
    }
    else if (buildingBuySettlementBtn->isClicked(mousePosition) && game->canBuildSettlement()) {
        game->resetClickPosition();
        game->buySettlement();
        std::cout << "buildingBuySettlement\n";
    }
}

void GameMenu::updateButtonStates(sf::Vector2f mousePosition) {
    if (is_buildingMenu) {
        backBtn->update(mousePosition);
        if (game->canBuildRoad()) {
            buildingBuyRoadBtn->update(mousePosition);
        }
        if (game->canBuildSettlement()) {
            buildingBuySettlementBtn->update(mousePosition);
        }
    }
    else {
        if (!is_rollDice) {
            rollDiceBtn->update(mousePosition);
        }
        else {
            buildingBtn->update(mousePosition);
            bankBtn->update(mousePosition);
            deckBtn->update(mousePosition);
            tradeBtn->update(mousePosition);
            nextTurnBtn->update(mousePosition);
        }
    }
}

void GameMenu::handleMainMenu(sf::Vector2f mousePosition) {
    if (!is_rollDice) {
        if (rollDiceBtn->isClicked(mousePosition)) {
            rollDiceBtn->animate();  // Add animation
            game->rollDice();
            game->resetClickPosition();
            is_rollDice = true;
            std::cout << "rollDice\n";
        }
    }
    else {
        if (buildingBtn->isClicked(mousePosition)) {
            buildingBtn->animate();
            is_buildingMenu = true;
            game->resetClickPosition();
            std::cout << "building\n";
        }
        else if (bankBtn->isClicked(mousePosition)) {
            bankBtn->animate();
            game->resetClickPosition();
            std::cout << "bank\n";
        }
        else if (deckBtn->isClicked(mousePosition)) {
            deckBtn->animate();
            game->giveRandomCard();
            game->resetClickPosition();
        }
        else if (tradeBtn->isClicked(mousePosition)) {
            tradeBtn->animate();
            game->resetClickPosition();
            std::cout << "trade\n";
        }
        else if (nextTurnBtn->isClicked(mousePosition)) {
            nextTurnBtn->animate();  // Add animation
            game->nextTurn();
            game->resetClickPosition();
            is_rollDice = false;
            std::cout << "nextTurn\n";
        }
    }
}



void GameMenu::updateMousePosition() {
    if (!window) {
        return;
    }
    sf::Vector2i pixelPos = sf::Mouse::getPosition(*window);
    mousePosition = window->mapPixelToCoords(pixelPos);
}
