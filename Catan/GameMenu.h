#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "Button.h"
#include "MenuButton.h"

class Catan;

class GameMenu {
public:
    GameMenu(sf::RenderWindow* window, sf::View* view, Catan* game);
    void draw();
    void update(sf::Vector2f mousePosition);

private:
    

    // Menu Methods
    void initializeButtons();
    void handleMainMenu(sf::Vector2f mousePosition);
    void handleBuildingMenu(sf::Vector2f mousePosition);
    void updateMousePosition();
    void updateButtonStates(sf::Vector2f mousePosition);

    // Core pointers
    sf::RenderWindow* window;
    sf::View* view;
    Catan* game;

    // Resources
    sf::Vector2f mousePosition;
    sf::Font font;
    float xPart;
    float yPart;

    // State flags
    bool is_rollDice;
    bool is_buildingMenu;

    // Main menu buttons
    std::unique_ptr<MenuButton> rollDiceBtn;
    std::unique_ptr<MenuButton> buildingBtn;
    std::unique_ptr<MenuButton> bankBtn;
    std::unique_ptr<MenuButton> deckBtn;
    std::unique_ptr<MenuButton> tradeBtn;
    std::unique_ptr<MenuButton> nextTurnBtn;

    // Building menu buttons
    std::unique_ptr<MenuButton> backBtn;
    std::unique_ptr<MenuButton> buildingBuyRoadBtn;
    std::unique_ptr<MenuButton> buildingBuySettlementBtn;
};
