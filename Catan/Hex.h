#pragma once
#include <SFML/Graphics.hpp>
#include "ResourceType.h"
#include "TerrainType.h"
#include "Vertex.h"
#include <array> 
class Hex
{
public:

	Hex(sf::RenderWindow* window, const std::array<int, 6>& vertexIndices, int number);
	~Hex();

	void update();
	void draw();

	const std::array<int, 6>& getOwnedVertices() const;

private:


private:
	sf::RenderWindow* window;
	sf::ConvexShape hex;
	std::array<int, 6> ownedVertices;

	ResourceType resourceType;
	TerrainType terrainType;
	int diceNumber;
	bool hasRobber;
	

	static std::array<sf::Vector2f, 19> centerPoints;
	static const float center;
	static const float radius;
};

