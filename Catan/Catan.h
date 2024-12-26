/**
 * @file Catan.h
 * @brief Defines the Catan class for managing the overall game logic.
 */

#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <array>
#include <map>
#include <unordered_map>
#include "Board.h"
#include "Player.h"
#include "StartMenu.h"
#include "GameMenu.h"
#include "TradeMenu.h"
#include "Dice.h"
#include "ResourceType.h"
#include "BankMenu.h"

/**
 * @class Catan
 * @brief Manages the core game logic, including state transitions, player actions, and game components.
 */
class Catan {
public:
    /**
     * @brief Constructs the Catan game instance.
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

    // Game state functions

    /**
     * @brief Resets the click position.
     */
    void resetClickPosition();

    /**
     * @brief Sets whether the game is in menu mode.
     * @param menu True if the game is in menu mode, false otherwise.
     */
    void setMenu(bool menu);

    /**
     * @brief Checks if the game is currently in menu mode.
     * @return True if the game is in menu mode, false otherwise.
     */
    bool isMenu() const;

    /**
     * @brief Advances the game to the next player's turn.
     */
    void nextTurn();

    /**
     * @brief Allows the current player to buy a settlement.
     */
    void buySettlement();

    /**
     * @brief Allows the current player to buy a road.
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
     * @brief Gets the total number of players.
     * @return The number of players.
     */
    int getPlayerCount() const;

    /**
     * @brief Increments the total number of players.
     */
    void incrementPlayerCount();

    /**
     * @brief Decrements the total number of players.
     */
    void decrementPlayerCount();

    /**
     * @brief Rolls the dice to produce resources.
     */
    void rollDice();

    // Card functions

    /**
     * @brief Gives a random card to the current player.
     */
    void giveRandomCard();

    /**
     * @brief Handles the use of a development card by the current player.
     * @param card The card being used.
     */
    void handleCardUse(Card card);

    // Trade functions

    /**
     * @brief Initiates a trade with another player.
     * @param target The ID of the target player.
     */
    void initiateTrade(int target);

    /**
     * @brief Proposes a trade to another player.
     * @param targetPlayer The ID of the target player.
     * @param offer The resources being offered.
     * @param request The resources being requested.
     * @return True if the trade proposal is valid, false otherwise.
     */
    bool proposeTrade(int targetPlayer, const std::map<ResourceType, int>& offer,
                      const std::map<ResourceType, int>& request);

    /**
     * @brief Accepts the current trade proposal.
     */
    void acceptTrade();

    /**
     * @brief Declines the current trade proposal.
     */
    void declineTrade();

    /**
     * @brief Gets the current player.
     * @return Pointer to the current player.
     */
    Player* getCurrentPlayer();

    /**
     * @brief Gets a specific player by index.
     * @param playerIndex The index of the player.
     * @return Pointer to the specified player.
     */
    Player* getPlayer(int playerIndex);

    /**
     * @brief Gets the index of the current player.
     * @return The current player's index.
     */
    int getCurrentPlayerIndex() const;

    /**
     * @brief Sets the trading state.
     * @param trading True if trading is active, false otherwise.
     */
    void setTrading(bool trading);

    /**
     * @brief Checks if trading is currently active.
     * @return True if trading is active, false otherwise.
     */
    bool getTrading() const;

    // Bank trade

    /**
     * @brief Executes a bank trade for the current player.
     * @param giveResource The resource to give to the bank.
     * @param getResource The resource to receive from the bank.
     * @param giveAmount The amount of the resource to give (default is 4).
     * @return True if the trade was successful, false otherwise.
     */
    bool bankTrade(ResourceType giveResource, ResourceType getResource, int giveAmount = 4);

    /**
     * @brief Checks if a bank trade is currently in progress.
     * @return True if a bank trade is active, false otherwise.
     */
    bool isBankTrading() const;

    /**
     * @brief Sets the bank trading state.
     * @param trading True if bank trading is active, false otherwise.
     */
    void setBankTrading(bool trading);

    // Board management

    /**
     * @brief Resets the game board to its initial state.
     */
    void restartBoard();

private:
    // Private methods

    /**
     * @brief Polls for and processes events.
     */
    void pollEvent();

    /**
     * @brief Updates the game state based on player actions and game rules.
     */
    void updateGameState();

    /**
     * @brief Draws the game components on the screen.
     */
    void draw();

    /**
     * @brief Draws the victory points of each player.
     */
    void drawVictoryPoints();

    /**
     * @brief Resizes the game view to fit the window.
     */
    void resizeView();

    /**
     * @brief Initializes the players.
     */
    void initPlayers();

    /**
     * @brief Initializes the textures used in the game.
     */
    void initTextures();

    /**
     * @brief Initializes the development cards.
     */
    void initDevelopmentCards();

    /**
     * @brief Initializes the setup order for players.
     */
    void initSetupOrder();

    /**
     * @brief Handles the setup phase of the game.
     */
    void handleSetupPhase();

    /**
     * @brief Handles the main game phase.
     */
    void handleGamePhase();

    /**
     * @brief Advances to the next turn during the setup phase.
     */
    void nextTurnSetupPhase();

    /**
     * @brief Places a road at the specified position.
     * @param position The position to place the road.
     * @return True if the road was successfully placed, false otherwise.
     */
    bool placeRoad(sf::Vector2f position);

    /**
     * @brief Places a settlement at the specified position.
     * @param position The position to place the settlement.
     * @return True if the settlement was successfully placed, false otherwise.
     */
    bool placeSettlement(sf::Vector2f position);

    /**
     * @brief Updates the longest road achievement.
     */
    void updateLongestRoad();

    /**
     * @brief Updates the largest army achievement.
     */
    void updateLargestArmy();

    // Private members

    sf::RenderWindow* window; ///< Pointer to the main game window.
    sf::View* view; ///< Pointer to the game view.
    sf::Event event; ///< Event object for handling user input.
    sf::Font font; ///< Font used in the game.
    sf::Color backgroundColor; ///< Background color of the game window.
    const float view_height = 720.0f; ///< Default height of the game view.

    Board* gameBoard; ///< Pointer to the game board.
    StartMenu* startMenu; ///< Pointer to the start menu.
    GameMenu* gameMenu; ///< Pointer to the game menu.
    TradeMenu* tradeMenu; ///< Pointer to the trade menu.
    Dice* dice; ///< Pointer to the dice object.
    BankMenu* bankMenu; ///< Pointer to the bank menu.

    std::unordered_map<std::string, sf::Texture> textures; ///< Map of texture resources.
    std::vector<Card> developmentCards; ///< Vector of development cards.

    std::vector<Player> players; ///< Vector of players in the game.
    Player* currentPlayer; ///< Pointer to the current player.
    int playerNumber = 4; ///< Number of players in the game.
    int currentPlayerIndex; ///< Index of the current player.
    static const std::array<sf::Color, 4> colors; ///< Colors for the players.

    bool is_menu = true; ///< Indicates if the game is in menu mode.
    bool setupPhase = true; ///< Indicates if the game is in the setup phase.
    bool gameOver = false; ///< Indicates if the game is over.
    int winningPlayer = -1; ///< ID of the winning player.
    sf::Vector2f clickPosition; ///< Position of the last click.

    std::vector<int> setupOrder; ///< Order of player turns during setup.
    int setupIndex = 0; ///< Current index in the setup order.
    std::vector<int> checkingSetupPhase; ///< Players checking the setup phase.

    bool placingRoad = false; ///< Indicates if a road is being placed.
    bool placingSettlement = false; ///< Indicates if a settlement is being placed.
    bool placementStart = false; ///< Indicates if placement has started.
    bool placementDone = false; ///< Indicates if placement is complete.
    bool placingFreeRoad = false; ///< Indicates if a free road is being placed.
    int freeRoadsRemaining = 0; ///< Number of free roads remaining.

    bool placingRobber = false; ///< Indicates if the robber is being placed.
    bool selectingResource = false; ///< Indicates if a resource is being selected.
    ResourceType selectedResource; ///< The selected resource type.

    bool tradeInProgress = false; ///< Indicates if a trade is in progress.
    bool isTrading = false; ///< Indicates if trading is active.

    int tradingPlayer = -1; ///< ID of the trading player.
    int targetPlayer = -1; ///< ID of the target player.
    std::map<ResourceType, int> tradeOffer; ///< Offered resources in a trade.
    std::map<ResourceType, int> tradeRequest; ///< Requested resources in a trade.

    bool isBankTrade = false; ///< Indicates if a bank trade is in progress.

    Player* longestRoadHolder = nullptr; ///< Player with the longest road.
    Player* largestArmyHolder = nullptr; ///< Player with the largest army.
};
