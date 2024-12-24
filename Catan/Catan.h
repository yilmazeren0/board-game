#pragma once
#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Player.h"
#include "StartMenu.h"
#include "GameMenu.h"
#include "Dice.h"

class Catan
{
public:

	Catan();
	~Catan();

	void run();
	void restartBoard();
	void resetClickPosition();
	void setMenu(bool menu);
	void incrementPlayerCount();
	void decrementPlayerCount();
	int getPlayerCount() const;
	bool isMenu() const;
	void rollDice();
	void nextTurn();
	void buySettlement();
	void buyRoad();
	bool canBuildRoad() const;
	bool canBuildSettlement() const;
	void giveRandomCard();


private:
	
	void pollEvent();
	void resizeView();
	void updateGameState();
	void initPlayers();
	void initTextures();
	void handleSetupPhase();
	void handleGamePhase();
	bool placeRoad(sf::Vector2f clickPosition);
	bool placeSettlement(sf::Vector2f clickPosition);
	
	void nextTurnSetupPhase();
	
	void draw();
	void save();
	


private:
	sf::RenderWindow* window;
	sf::View* view;
	sf::Event event;
	sf::Font font;
	Board* gameBoard;
	StartMenu* startMenu;
	GameMenu* gameMenu;
	Dice* dice;
	std::unordered_map<std::string, sf::Texture> textures;
	std::vector<Player> players;
	Player* currentPlayer;
	sf::Vector2f clickPosition;
	sf::Color backgroundColor;
	int playerNumber = 4;
	int currentPlayerIndex;


	bool placingRobber = false;
	bool selectingResource = false;
	bool placingFreeRoad = false;
	int freeRoadsRemaining = 0;
	ResourceType selectedResource;
	void handleCardUse(Card card);

	const float view_height = 720.0f;
	bool is_menu = true;
	bool is_diceTurn = true;
	bool is_builldingTurn = false;

	bool setupPhase = true;
	bool placingRoad = false;
	bool placingSettlement = false;
	std::vector<int> checkingSetupPhase;
	
	bool placementStart = false;
	bool placementDone = false;

	const static std::array<sf::Color, 4> colors;
};

