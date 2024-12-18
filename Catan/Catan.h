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
	void initTextures();
	void handleSetupPhase();
	void handleGamePhase();
	bool placeRoad(sf::Vector2f clickPosition);
	bool placeSettlement(sf::Vector2f clickPosition);
	void nextTurn();
	void nextTurnSetupPhase();
	void draw();
	void save();
	


private:
	sf::RenderWindow* window;
	sf::View* view;
	sf::Event event;
	sf::Font font;
	Board* gameBoard;
	std::unordered_map<std::string, sf::Texture> textures;
	std::vector<Player> players;
	Player* currentPlayer;
	sf::Vector2f clickPosition;
	sf::Color backgroundColor;
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

