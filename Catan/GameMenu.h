#pragma once
#include <SFML/Graphics.hpp>

class Catan;

class GameMenu
{
public:

	GameMenu(sf::RenderWindow* window, sf::View* view, Catan* game);

	void draw();
	void update(sf::Vector2f mousePosition);

private:
	sf::RenderWindow* window;
	sf::View* view;
	Catan* game;
	sf::Vector2f mousePosition;
	sf::Text rollDice;
	sf::Text building;
	sf::Text bank;
	sf::Text deck;
	sf::Text trade;
	sf::Text nextTurn;
	sf::Text back;
	sf::Text buildingBuyRoad;
	sf::Text buildingBuySettlement;
	sf::Font font;

	float xPart;
	float yPart;

	bool is_rollDice;
	bool is_buildingMenu;

private:
	void updateMousePosition();

	void rollDiceText();
	void buildingText();
	void bankText();
	void deckText();
	void tradeText();
	void nextTurnText();
	void backText();

	void buildingBuyRoadText();
	void buildingBuySettlementText();
	

	void rollDiceHighlight();
	void buildingHighlight();
	void bankHighlight();
	void deckHighlight();
	void tradeHighlight();
	void nextTurnHighlight();
	void backHighlight();

	void buildingBuyRoadHighlight();
	void buildingBuySettlementHighlight();


};

