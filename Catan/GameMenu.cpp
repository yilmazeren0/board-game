#include "GameMenu.h"
#include "Catan.h"
#include <iostream>

GameMenu::GameMenu(sf::RenderWindow* window, sf::View* view, Catan* game)
    : Menu(window, view, game) {
    initializeButtons();
}

void GameMenu::initializeButtons() {
    // Calculate base position for menu alignment
    float baseX = view->getCenter().x + 12.0f * xPart;  // Align to right side
    float baseY = view->getCenter().y + 3.0f *yPart;
    float buttonSpacing = 4.0f * yPart;  // Vertical spacing between buttons

    // Main menu buttons
    rollDiceBtn = std::make_unique<Button>("Roll Dice", font,
        baseX, baseY - 6.0f * yPart);

    buildingBtn = std::make_unique<Button>("Building", font,
        baseX, baseY - 4.0f * yPart);

    bankBtn = std::make_unique<Button>("Bank", font,
        baseX, baseY - 2.0f * yPart);

    deckBtn = std::make_unique<Button>("Development Cards", font,
        baseX, baseY);

    tradeBtn = std::make_unique<Button>("Trade", font,
        baseX, baseY + 2.0f * yPart);

    nextTurnBtn = std::make_unique<Button>("Next Turn", font,
        baseX, baseY + 4.0f * yPart);

    // Building menu buttons
    backBtn = std::make_unique<Button>("Back", font,
        baseX, baseY - 6.0f * yPart);

    buildRoadBtn = std::make_unique<Button>("Build Road", font,
        baseX, baseY - 2.0f * yPart);

    buildSettlementBtn = std::make_unique<Button>("Build Settlement", font,
        baseX, baseY + 2.0f * yPart);

    // Set button styles
    nextTurnBtn->setCharacterSize(30);
    rollDiceBtn->setCharacterSize(30);

    // Set special colors for important buttons
    nextTurnBtn->getText().setFillColor(sf::Color(255, 100, 100));  // Light red
    rollDiceBtn->getText().setFillColor(sf::Color(100, 255, 100));  // Light green
}

void GameMenu::draw() {
    if (is_buildingMenu) {
        // Draw building menu
        backBtn->draw(*window);
        if (game->canBuildRoad()) {
            buildRoadBtn->draw(*window);
        }
        if (game->canBuildSettlement()) {
            buildSettlementBtn->draw(*window);
        }
    }
    else {
        // Draw main menu
        if (!is_rollDice) {
            rollDiceBtn->draw(*window);
        }
        else {
            buildingBtn->draw(*window);
            bankBtn->draw(*window);
            deckBtn->draw(*window);
            tradeBtn->draw(*window);
            nextTurnBtn->draw(*window);
        }
    }
}

void GameMenu::update(sf::Vector2f mousePosition) {
    if (is_buildingMenu) {
        handleBuildingMenu(mousePosition);
    }
    else {
        handleMainMenu(mousePosition);
    }
    updateButtonStates(mousePosition);
}

void GameMenu::handleBuildingMenu(sf::Vector2f mousePosition) {
    if (backBtn->isClicked(mousePosition)) {
        backBtn->animate();
        is_buildingMenu = false;
        game->resetClickPosition();
    }
    else if (buildRoadBtn->isClicked(mousePosition) && game->canBuildRoad()) {
        buildRoadBtn->animate();
        game->buyRoad();
        game->resetClickPosition();
    }
    else if (buildSettlementBtn->isClicked(mousePosition) && game->canBuildSettlement()) {
        buildSettlementBtn->animate();
        game->buySettlement();
        game->resetClickPosition();
    }
}

void GameMenu::handleMainMenu(sf::Vector2f mousePosition) {
    if (!is_rollDice) {
        if (rollDiceBtn->isClicked(mousePosition)) {
            rollDiceBtn->animate();
            game->rollDice();
            game->resetClickPosition();
            is_rollDice = true;
        }
    }
    else {
        if (buildingBtn->isClicked(mousePosition)) {
            buildingBtn->animate();
            is_buildingMenu = true;
            game->resetClickPosition();
        }
        else if (bankBtn->isClicked(mousePosition)) {
            bankBtn->animate();
            game->resetClickPosition();
        }
        else if (deckBtn->isClicked(mousePosition)) {
            deckBtn->animate();
            game->giveRandomCard();
            game->resetClickPosition();
        }
        else if (tradeBtn->isClicked(mousePosition)) {
            tradeBtn->animate();
            game->resetClickPosition();
        }
        else if (nextTurnBtn->isClicked(mousePosition)) {
            nextTurnBtn->animate();
            game->nextTurn();
            game->resetClickPosition();
            is_rollDice = false;
        }
    }
}

void GameMenu::updateButtonStates(sf::Vector2f mousePosition) {
    if (is_buildingMenu) {
        backBtn->update(mousePosition);
        if (game->canBuildRoad()) {
            buildRoadBtn->update(mousePosition);
        }
        if (game->canBuildSettlement()) {
            buildSettlementBtn->update(mousePosition);
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