#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <array>
#include <unordered_set>
#include <unordered_map>
#include "Hex.h"
#include "Edge.h"
#include "Vertex.h"
#include "Road.h"
#include "Player.h"


class Board
{
public:
	Board(sf::RenderWindow* window, std::unordered_map<std::string, sf::Texture>* textures);
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
	void initTerrains();
	void updateMousePosition();
	void updateEdgeHighlights(int currentPlayerID);
	void updateVertexHighlights(int currentPlayerID);
	void shuffleTerrains(std::array<TerrainType, 18>& terrains);

private:
	sf::RenderWindow* window;
	std::vector<Hex> hexes;
	std::vector<Edge> edges;
	std::vector<Vertex> vertices;
	std::list<Road> roads;
	std::list<Settlement> settlements;
	std::unordered_map<std::string, sf::Texture>* textures;

	std::unordered_set<int> highlightedEdges;
	std::unordered_set<int> highlightedVertices;
	sf::Vector2f mousePosition;
	bool setupPhase;
	bool placingRoad;
	bool placingSettlement;
	int currentPlayerID;
	std::array<TerrainType, 18> terrains;

	const static std::array<std::array<int, 6>, 19> hexAndOwnedVertices;
	const static std::array<std::array<int, 2>, 72> edgeAndOwnedVertices;
	const static std::array<std::vector<int>, 54> vertexNeighbours;
	const static std::array<std::vector<int>, 72> edgeNeighbours;
	const static std::array<int, 19> diceNumbers;
	
};

