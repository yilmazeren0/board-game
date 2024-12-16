#pragma once
#include <SFML/Graphics.hpp>
#include "Hex.h"
#include "Edge.h"
#include "Vertex.h"
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
	std::vector<Vertex> vertices;
	sf::Vector2f mousePosition;

	const static std::array<std::array<int, 6>, 19> hexAndOwnedVertices;
	const static std::array<std::array<int, 2>, 72> edgeAndOwnedVertices;
	const static std::array<std::vector<int>, 54> vertexNeighbours;
	const static std::array<std::vector<int>, 72> edgeNeighbours;
};

