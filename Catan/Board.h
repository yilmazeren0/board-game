#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <unordered_set>
#include "Hex.h"
#include "Edge.h"
#include "Vertex.h"
#include "Road.h"
#include "Player.h"

class Board
{
public:
	Board(sf::RenderWindow* window);
	~Board();

	void update(int currentPlayerID);
	void draw();
	
	bool placeRoad(Player* player, sf::Vector2f clickPosition);
	bool placeSettlement(Player* player, sf::Vector2f clickPosition);
	void setSetupPhase(bool setupPhase);
	void setplacingRoad(bool placingRoad);
	void setplacingSettlement(bool placingSettlement);
	
	
private:

	void initBoard();
	void updateMousePosition();
	void updateEdgeHighlights(int currentPlayerID);
	void updateVertexHighlights(int currentPlayerID);

private:
	sf::RenderWindow* window;
	std::vector<Hex> hexes;
	std::vector<Edge> edges;
	std::vector<Vertex> vertices;
	std::list<Road> roads;
	std::list<Settlement> settlements;

	std::unordered_set<int> highlightedEdges;
	std::unordered_set<int> highlightedVertices;
	sf::Vector2f mousePosition;
	bool setupPhase;
	bool placingRoad;
	bool placingSettlement;
	int currentPlayerID;

	const static std::array<std::array<int, 6>, 19> hexAndOwnedVertices;
	const static std::array<std::array<int, 2>, 72> edgeAndOwnedVertices;
	const static std::array<std::vector<int>, 54> vertexNeighbours;
	const static std::array<std::vector<int>, 72> edgeNeighbours;
};

