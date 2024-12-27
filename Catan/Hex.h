#pragma once
#include <SFML/Graphics.hpp>
#include "ResourceType.h"
#include "TerrainType.h"
#include "Vertex.h"
#include <array> 
#include <unordered_map>
class Hex
{
public:

	Hex(sf::RenderWindow* window, std::unordered_map<std::string, sf::Texture>* textures, TerrainType terrainType, const std::array<int, 6>& vertexIndices,
		int number, int diceNumber);
	~Hex();

	void update();
	void draw();

	const std::array<int, 6>& getOwnedVertices() const;

	int getDiceNumber() const;
	ResourceType getResourceType() const;

	void setRobber();
	void removeRobber();
	bool isRobbed() const;
	sf::FloatRect getBox() const;

private:
	ResourceType initResourceType(TerrainType terrainType);
	int diceNumber;

private:
	sf::RenderWindow* window;
	sf::ConvexShape hex;
	sf::Sprite sprite;
	sf::Text text;
	sf::Font font;
	sf::CircleShape circle;
	sf::Sprite robberSprite;
	std::array<int, 6> ownedVertices;
	std::unordered_map<std::string, sf::Texture>* textures;

	ResourceType resourceType;
	TerrainType terrainType;
	bool hasRobber = false;


	static std::array<sf::Vector2f, 19> centerPoints;
	static const float center;
	static const float radius;
};
