#pragma once

/**
 * @file Catan.h
 * @brief Defines the Catan game class and its functionality.
 */

#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Player.h"
#include "StartMenu.h"
#include "GameMenu.h"
#include "Dice.h"
#include <sstream>
#include <string>

 /**
  * @class Catan
  * @brief Manages the game logic and rendering for Catan.
  */
class Catan
{
public:

    /**
     * @brief Constructor for the Catan class.
     */
    Catan();

    /**
     * @brief Destructor for the Catan class.
     */
    ~Catan();

    /**
     * @brief Main game loop.
     */
    void run();

    /**
     * @brief Restarts the game board to its initial state.
     */
    void restartBoard();

    /**
     * @brief Resets the player's click position.
     */
    void resetClickPosition();

    /**
     * @brief Sets whether the game is in menu mode.
     * @param menu True to enable menu mode, false to disable.
     */
    void setMenu(bool menu);

    /**
     * @brief Increments the player count.
     */
    void incrementPlayerCount();

    /**
     * @brief Decrements the player count.
     */
    void decrementPlayerCount();

    /**
     * @brief Gets the current player count.
     * @return The number of players in the game.
     */
    int getPlayerCount() const;

    /**
     * @brief Checks if the game is in menu mode.
     * @return True if in menu mode, false otherwise.
     */
    bool isMenu() const;

    /**
     * @brief Rolls the dice for the current turn.
     */
    void rollDice();

    /**
     * @brief Advances the game to the next turn.
     */
    void nextTurn();

    /**
     * @brief Purchases a settlement for the current player.
     */
    void buySettlement();

    /**
     * @brief Purchases a road for the current player.
     */
    void buyRoad();

    /**
     * @brief Checks if the current player can build a road.
     * @return True if the player can build a road, false otherwise.
     */
    bool canBuildRoad() const;

    /**
     * @brief Checks if the current player can build a settlement.
     * @return True if the player can build a settlement, false otherwise.
     */
    bool canBuildSettlement() const;

    /**
     * @brief Gives a random resource card to the current player.
     */
    void giveRandomCard();

private:

    /**
     * @brief Handles events polled from the SFML window.
     */
    void pollEvent();

    /**
     * @brief Resizes the game view when the window size changes.
     */
    void resizeView();

    /**
     * @brief Updates the game state.
     */
    void updateGameState();

    /**
     * @brief Initializes the players in the game.
     */
    void initPlayers();

    /**
     * @brief Loads and initializes textures used in the game.
     */
    void initTextures();

    /**
     * @brief Handles the setup phase logic.
     */
    void handleSetupPhase();

    /**
     * @brief Handles the main game phase logic.
     */
    void handleGamePhase();

    /**
     * @brief Places a road at the specified position.
     * @param clickPosition The position where the road is to be placed.
     * @return True if the road was successfully placed, false otherwise.
     */
    bool placeRoad(sf::Vector2f clickPosition);

    /**
     * @brief Places a settlement at the specified position.
     * @param clickPosition The position where the settlement is to be placed.
     * @return True if the settlement was successfully placed, false otherwise.
     */
    bool placeSettlement(sf::Vector2f clickPosition);

    /**
     * @brief Handles the use of a card by the current player.
     * @param card The card being used.
     */
    void handleCardUse(Card card);

    /**
     * @brief Advances to the next turn in the setup phase.
     */
    void nextTurnSetupPhase();

    /**
     * @brief Initializes the setup order for the game.
     */
    void initSetupOrder();

    /**
     * @brief Draws all game elements to the window.
     */
    void draw();

    /**
     * @brief Saves the current game state.
     */
    void save();

    void drawVictoryPoints();
    bool gameOver = false;
    int winningPlayer = -1;

private:
    sf::RenderWindow* window;                   ///< Pointer to the SFML window.
    sf::View* view;                             ///< Pointer to the SFML view.
    sf::Event event;                            ///< Stores events from the SFML window.
    sf::Font font;                              ///< Font used in the game.
    Board* gameBoard;                           ///< Pointer to the game board.
    StartMenu* startMenu;                       ///< Pointer to the start menu.
    GameMenu* gameMenu;                         ///< Pointer to the game menu.
    Dice* dice;                                 ///< Pointer to the dice.
    std::unordered_map<std::string, sf::Texture> textures; ///< Map of textures used in the game.
    std::vector<Player> players;               ///< List of players in the game.
    Player* currentPlayer;                     ///< Pointer to the current player.
    sf::Vector2f clickPosition;                ///< Position of the last click.
    sf::Color backgroundColor;                 ///< Background color of the game window.
    int playerNumber = 4;                      ///< Number of players in the game.
    int currentPlayerIndex;                    ///< Index of the current player.
    std::vector<int> setupOrder;               ///< Order of player turns in the setup phase.
    int setupIndex = 0;                        ///< Index for the setup phase.

    bool placingRobber = false;                ///< Flag for placing the robber.
    bool selectingResource = false;            ///< Flag for resource selection.
    bool placingFreeRoad = false;              ///< Flag for placing free roads.
    int freeRoadsRemaining = 0;                ///< Number of free roads remaining.
    ResourceType selectedResource;             ///< The currently selected resource.

    const float view_height = 720.0f;          ///< Height of the game view.
    bool is_menu = true;                       ///< Indicates if the game is in menu mode.
    bool is_diceTurn = true;                   ///< Indicates if it is the dice roll phase.
    bool is_builldingTurn = false;             ///< Indicates if it is the building phase.

    bool setupPhase = true;                    ///< Indicates if the game is in the setup phase.
    bool placingRoad = false;                  ///< Indicates if a road is being placed.
    bool placingSettlement = false;            ///< Indicates if a settlement is being placed.
    std::vector<int> checkingSetupPhase;       ///< Tracks setup phase progress.

    bool placementStart = false;               ///< Indicates if placement has started.
    bool placementDone = false;                ///< Indicates if placement is complete.

    Player* longestRoadHolder = nullptr;
    void updateLongestRoad();

    Player* largestArmyHolder = nullptr;
    void updateLargestArmy();

    const static std::array<sf::Color, 4> colors; ///< Array of player colors.
};
