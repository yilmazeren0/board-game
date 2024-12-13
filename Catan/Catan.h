#pragma once
#include <SFML/Graphics.hpp>
#include "Board.h"
class Catan
{
public:

	Catan();
	~Catan();

	void run();

private:
	

	void initBoard();
	void pollEvent();
	void resizeView();
	void renderGame();
	void renderMenu();
	void draw();
	


private:
	sf::RenderWindow* window;
	sf::View* view;
	sf::Event event;
	Board* gameBoard;

	const float view_height = 720.0f;
	bool is_game = true;
	bool is_menu = true;
};

