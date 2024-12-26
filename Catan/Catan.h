#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <array>
#include <map>
#include "Board.h"
#include "Player.h"
#include "StartMenu.h"
#include "GameMenu.h"
#include "TradeMenu.h"
#include "Dice.h"
#include "ResourceType.h"

class Catan {
public:
    Catan();
    ~Catan();
    void run();

    // Game state functions
    void resetClickPosition();
    void setMenu(bool menu);
    bool isMenu() const;
    void nextTurn();
    void buySettlement();
    void buyRoad();
    bool canBuildRoad() const;
    bool canBuildSettlement() const;
    int getPlayerCount() const;
    void incrementPlayerCount();
    void decrementPlayerCount();
    void rollDice();

    // Card functions
    void giveRandomCard();
    void handleCardUse(Card card);

    // Trade functions
    void initiateTrade(int target);
    bool proposeTrade(int target, const std::map<ResourceType, int>& offer,
        const std::map<ResourceType, int>& request);
    void acceptTrade();
    void declineTrade();
    Player* getCurrentPlayer();
	int getCurrentPlayerIndex() const;

    void setTrading(bool trading) { isTrading = trading; }
    bool getTrading() const { return isTrading; }

    // Board management
    void restartBoard();

private:
    // Window and view
    sf::RenderWindow* window;
    sf::View* view;
    sf::Event event;
    sf::Font font;
    sf::Color backgroundColor;
    const float view_height = 720.0f;

    // Game components
    Board* gameBoard;
    StartMenu* startMenu;
    GameMenu* gameMenu;
    TradeMenu* tradeMenu;
    Dice* dice;

    // Resource management
    std::unordered_map<std::string, sf::Texture> textures;
    std::vector<Card> developmentCards;

    // Player management
    std::vector<Player> players;
    Player* currentPlayer;
    int playerNumber = 4;
    int currentPlayerIndex;
    static const std::array<sf::Color, 4> colors;

    // Game state
    bool is_menu = true;
    bool setupPhase = true;
    bool gameOver = false;
    int winningPlayer = -1;
    sf::Vector2f clickPosition;

    // Setup phase management
    std::vector<int> setupOrder;
    int setupIndex = 0;
    std::vector<int> checkingSetupPhase;

    // Building state
    bool placingRoad = false;
    bool placingSettlement = false;
    bool placementStart = false;
    bool placementDone = false;
    bool placingFreeRoad = false;
    int freeRoadsRemaining = 0;

    // Special conditions
    bool placingRobber = false;
    bool selectingResource = false;
    ResourceType selectedResource;

    // Trade state
    bool tradeInProgress = false;

    bool isTrading = false;

    int tradingPlayer = -1;
    int targetPlayer = -1;
    std::map<ResourceType, int> tradeOffer;
    std::map<ResourceType, int> tradeRequest;

   

    // Special achievements
    Player* longestRoadHolder = nullptr;
    Player* largestArmyHolder = nullptr;

    // Private methods
    void pollEvent();
    void updateGameState();
    void draw();
    void drawVictoryPoints();
    void resizeView();
    void initPlayers();
    void initTextures();
    void initDevelopmentCards();
    void initSetupOrder();
    void handleSetupPhase();
    void handleGamePhase();
    void nextTurnSetupPhase();
    bool placeRoad(sf::Vector2f position);
    bool placeSettlement(sf::Vector2f position);
    void updateLongestRoad();
    void updateLargestArmy();
};
