#pragma once
#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Player.h"

class Catan
{
public:

	Catan();
	~Catan();

	void run();

private:
	
	void pollEvent();
	void resizeView();
	void renderGame();
	void renderMenu();
	void initPlayers();
	void handleSetupPhase();
	void handleGamePhase();
	bool placeRoad();
	bool placeSettlement();
	void nextTurn();
	void draw();
	void save();
	


private:
	sf::RenderWindow* window;
	sf::View* view;
	sf::Event event;
	Board* gameBoard;
	std::vector<Player> players;
	Player* currentPlayer;
	int playerNumber = 4;
	int currentPlayerIndex;

	const float view_height = 720.0f;
	bool is_game = true;
	bool is_menu = true;

	bool setupPhase = true;
	bool placingRoad = false;
	bool placingSettlement = false;
	std::vector<int> checkingSetupPhase;
	
	bool placementStart = false;
	bool placementDone = false;

	const static std::array<sf::Color, 4> colors;
};

