#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include "Settlement.h"
#include "City.h"
class Vertex
{
public:

	Vertex(sf::RenderWindow* window, int number);
	~Vertex();

	void update(const sf::Vector2f& mousePosition);
	void draw();

	void placeSettlement(Settlement* settlement);
	sf::FloatRect getBox()const;
	bool getAvailability()const;
	bool isHightlighted()const;
	void setHighlight(bool highlight);
	void setAvailability(bool availability);
	bool isOwnedByPlayer(int playerID)const;
	bool isOwned()const;
	void addResource(ResourceType resourceType);
	Player* getOwner() const;
private:


private:
	sf::RenderWindow* window;
	sf::CircleShape vertex;
	Settlement* settlement = nullptr;
	sf::Color color;
	bool availability;
	bool highlighted;

	static std::array<sf::Vector2f, 54> centerPoints;
	static const float center;
	static const float radius;
	static const float circleRadius;
};

