#pragma once
#include "Menu.h"
#include "Button.h"
#include <memory>

class Catan;

class GameMenu : public Menu {
public:
    GameMenu(sf::RenderWindow* window, sf::View* view, Catan* game);
    void draw() override;
    void update(sf::Vector2f mousePosition) override;

private:
    // Menu state
    bool is_rollDice;
    bool is_buildingMenu;

    // Main menu buttons
    std::unique_ptr<Button> rollDiceBtn;
    std::unique_ptr<Button> buildingBtn;
    std::unique_ptr<Button> bankBtn;
    std::unique_ptr<Button> deckBtn;
    std::unique_ptr<Button> tradeBtn;
    std::unique_ptr<Button> nextTurnBtn;

    // Building menu buttons
    std::unique_ptr<Button> backBtn;
    std::unique_ptr<Button> buildRoadBtn;
    std::unique_ptr<Button> buildSettlementBtn;

    // Helper methods
    void initializeButtons();
    void handleBuildingMenu(sf::Vector2f mousePosition);
    void handleMainMenu(sf::Vector2f mousePosition);
    void updateButtonStates(sf::Vector2f mousePosition);
    void updateMousePosition();
};
