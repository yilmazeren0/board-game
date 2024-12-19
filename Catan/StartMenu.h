#pragma once
#include <SFML/Graphics.hpp>

class Catan;

class StartMenu
{
public:

	StartMenu(sf::RenderWindow* window, sf::View* view, Catan* game);

	void draw();
	void update(sf::Vector2f mousePosition);

private:
	sf::RenderWindow* window;
	sf::View* view;
	Catan* game;
	sf::Vector2f mousePosition;
	sf::Text catan;
	sf::Text startGame;
	sf::Text leftSymbol;
	sf::Text rightSymbol;
	sf::Text playerCount;
	sf::Text randomizeBoard;
	sf::Text exit;
	sf::Font font;

	float xPart;
	float yPart;

private:
	void catanText();
	void startGameText();
	void startGameHighlight();
	void leftSymbolText();
	void leftSymbolHighlight();
	void playerCountText();
	void rightSymbolText();
	void rightSymbolHighlight();
	void randomizeBoardText();
	void randomizeBoardHighlight();
	void exitText();
	void exitHighlight();
	void updateText();

	void updateMousePosition();
};

