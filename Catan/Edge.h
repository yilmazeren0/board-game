#pragma once
#include <SFML/Graphics.hpp>
#include "Vertex.h"
#include "Road.h"
#include <array>

class Edge
{
public:
	Edge(sf::RenderWindow* window, const std::array<int, 2>& vertexIndices, int number);
	~Edge();

	void update(const sf::Vector2f& mousePosition);
	void draw();

	void placeRoad(Road* road);
	const std::array<int, 2>& getOwnedVertices() const;
	sf::FloatRect getBox()const;
	bool getAvailability()const;
	bool isHightlighted()const;
	void setHighlight(bool highlight);
	void setAvailability(bool availability);
	bool isOwnedByPlayer(size_t playerID) const;

	bool containsVertex(int vertexIndex) const {
		return vertices[0] == vertexIndex || vertices[1] == vertexIndex;
	}

	const std::array<int, 2>& getVertices() const {
		return vertices;
	}

private:
	sf::RenderWindow* window;
	sf::RectangleShape edge;
	Road* road = nullptr;
	sf::Color color;
	std::array<int, 2> ownedVertices;
	bool availability;
	bool highlighted;

	static std::array<sf::Vector2f, 72> centerPoints;
	static std::array<float, 72> rotations;
	static const float center;
	static const float radius;

	std::array<int, 2> vertices;
};

