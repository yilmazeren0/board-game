#pragma once
#include <SFML/Graphics.hpp>
#include "Vertex.h"
#include <array>
class Edge
{
public:
	Edge(sf::RenderWindow* window, const std::array<int, 2>& vertexIndices, int number);
	~Edge();

	void update(const sf::Vector2f& mousePosition);
	void draw();

	const std::array<int, 2>& getOwnedVertices() const;

private:
	sf::RenderWindow* window;
	sf::RectangleShape edge;
	std::array<int, 2> ownedVertices;
	bool availability;

	static std::array<sf::Vector2f, 72> centerPoints;
	static std::array<float, 72> rotations;
	static const float center;
	static const float radius;
};

