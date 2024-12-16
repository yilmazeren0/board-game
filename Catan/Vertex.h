#pragma once
#include <SFML/Graphics.hpp>
#include <array>
class Vertex
{
public:

	Vertex(sf::RenderWindow* window, int number);
	~Vertex();

	void update(const sf::Vector2f& mousePosition);
	void draw();

private:


private:
	sf::RenderWindow* window;
	sf::CircleShape vertex;
	bool availability;


	static std::array<sf::Vector2f, 54> centerPoints;
	static const float center;
	static const float radius;
	static const float circleRadius;
};

