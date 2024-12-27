/**
 * @file GameMenu.h
 * @brief Defines the GameMenu class for managing the in-game menu system.
 */

#pragma once
#include "Menu.h"
#include "Button.h"
#include <memory>

/**
 * @class GameMenu
 * @brief Manages the in-game menu and its interactions.
 * 
 * The GameMenu class provides functionality to interact with the game through
 * various menu buttons. It supports actions such as rolling dice, building structures,
 * trading, and progressing to the next turn.
 */
class GameMenu : public Menu {
public:
    /**
     * @brief Constructs a GameMenu object.
     * @param window Pointer to the SFML RenderWindow for rendering the menu.
     * @param view Pointer to the SFML View used for the game.
     * @param game Pointer to the main Catan game object.
     */
    GameMenu(sf::RenderWindow* window, sf::View* view, Catan* game);

    /**
     * @brief Draws the current menu state to the screen.
     */
    void draw() override;

    /**
     * @brief Updates the menu based on the mouse position.
     * @param mousePosition The current position of the mouse in the window.
     */
    void update(sf::Vector2f mousePosition) override;

private:
    // Menu state
    bool is_rollDice; ///< Indicates if the roll dice menu is active.
    bool is_buildingMenu; ///< Indicates if the building menu is active.

    // Main menu buttons
    std::unique_ptr<Button> rollDiceBtn; ///< Button for rolling dice.
    std::unique_ptr<Button> buildingBtn; ///< Button for opening the building menu.
    std::unique_ptr<Button> bankBtn; ///< Button for accessing the bank.
    std::unique_ptr<Button> deckBtn; ///< Button for viewing the development card deck.
    std::unique_ptr<Button> tradeBtn; ///< Button for initiating trades.
    std::unique_ptr<Button> nextTurnBtn; ///< Button for ending the turn.

    // Building menu buttons
    std::unique_ptr<Button> backBtn; ///< Button for returning to the main menu.
    std::unique_ptr<Button> buildRoadBtn; ///< Button for building a road.
    std::unique_ptr<Button> buildSettlementBtn; ///< Button for building a settlement.

    /**
     * @brief Initializes all menu buttons.
     */
    void initializeButtons();

    /**
     * @brief Handles interactions specific to the building menu.
     * @param mousePosition The current position of the mouse in the window.
     */
    void handleBuildingMenu(sf::Vector2f mousePosition);

    /**
     * @brief Handles interactions specific to the main menu.
     * @param mousePosition The current position of the mouse in the window.
     */
    void handleMainMenu(sf::Vector2f mousePosition);

    /**
     * @brief Updates the state of all buttons based on the mouse position.
     * @param mousePosition The current position of the mouse in the window.
     */
    void updateButtonStates(sf::Vector2f mousePosition);

    /**
     * @brief Updates the mouse position relative to the view.
     */
    void updateMousePosition();
};
