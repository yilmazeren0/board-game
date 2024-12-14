#pragma once
#include <SFML/Graphics.hpp>
#include "Hex.h"
#include "Edge.h"
#include <vector>
class Board
{
public:
	Board(sf::RenderWindow* window);
	~Board();

	void update();
	void draw();


private:

	void initBoard();
	void updateMousePosition();

private:
	sf::RenderWindow* window;
	std::vector<Hex> hexes;
	std::vector<Edge> edges;
	sf::Vector2f mousePosition;
};

