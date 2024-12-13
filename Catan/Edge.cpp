#include "Edge.h"
#include <array>
Edge::Edge(sf::RenderWindow* window, int number) {
	this->window = window;

	edge.setSize(sf::Vector2f(radius, 10.0f));
	edge.setOrigin(radius / 2, 10.0f / 2);
	edge.setFillColor(sf::Color::Blue);

	edge.setPosition(centerPoints[number]);
	edge.setRotation(rotations[number]);
}

Edge::~Edge()
{
}

void Edge::update()
{

}

void Edge::draw()
{
	window->draw(edge);
}

std::array<sf::Vector2f, 54> Edge::centerPoints = {
    sf::Vector2f(center - 3.0f * radius, center - 2 * std::sqrt(3.0f) * radius),//1     hex1
    sf::Vector2f(center - 2.5f * radius, center - 2.5f * std::sqrt(3.0f) * radius),//2  hex1
    sf::Vector2f(center - 1.5f * radius, center - 2.5f * std::sqrt(3.0f) * radius),//3  hex1
    sf::Vector2f(center - 1.0f * radius, center - 2 * std::sqrt(3.0f) * radius),//4     hex1 hex2
    sf::Vector2f(center - 1.5f * radius, center - 1.5f * std::sqrt(3.0f) * radius),//5  hex1 hex5
    sf::Vector2f(center - 2.5f * radius, center - 1.5f * std::sqrt(3.0f) * radius),//6  hex1 hex4
    sf::Vector2f(center - 0.5f * radius, center - 2.5f * std::sqrt(3.0f) * radius),//7  hex2
    sf::Vector2f(center + 0.5f * radius, center - 2.5f * std::sqrt(3.0f) * radius),//8  hex2 
    sf::Vector2f(center + 1.0f * radius, center - 2 * std::sqrt(3.0f) * radius),//9     hex2 hex3
    sf::Vector2f(center + 0.5f * radius, center - 1.5f * std::sqrt(3.0f) * radius),//10 hex2 hex3 hex6
    sf::Vector2f(center - 0.5f * radius, center - 1.5f * std::sqrt(3.0f) * radius),//11 hex2 hex5
    sf::Vector2f(center + 4 * radius, center),
    sf::Vector2f(center - 3.0f * radius, center + std::sqrt(3.0f) * radius),
    sf::Vector2f(center - 1.0f * radius, center + std::sqrt(3.0f) * radius),
    sf::Vector2f(center + 1.0f * radius, center + std::sqrt(3.0f) * radius),
    sf::Vector2f(center + 3.0f * radius, center + std::sqrt(3.0f) * radius),
    sf::Vector2f(center - 2 * radius, center + 2 * std::sqrt(3.0f) * radius),
    sf::Vector2f(center, center + 2 * std::sqrt(3.0f) * radius),
    sf::Vector2f(center + 2 * radius, center + 2 * std::sqrt(3.0f) * radius)
};

std::array<float, 54> Edge::rotations = {
    90.0f,//1
    150.0f,//2
    30.0f,//3
    90.0f,//4
    150.0f,//5
    30.0f,//6
    150.0f,//7
    30.0f,//8
    90.0f,//9
    150.0f,//10
    30.0f,//11
    90.0f,//12
    90.0f,//13
    90.0f,//14
    90.0f,//15
    90.0f,//16
    90.0f,//17
    90.0f,//18
    90.0f,//19
    90.0f,//20
    90.0f,//21
    90.0f,//22
    90.0f,//23
    90.0f,//24
    90.0f,//25
    90.0f,//26
    90.0f,//27
    90.0f,//28
    90.0f,//29
    90.0f,//30
    90.0f,//31
    90.0f,//32
    90.0f,//33
    90.0f,//34
    90.0f,//35
    90.0f,//36
    90.0f,//37

};

const float Edge::center = 0.0f;
const float Edge::radius = 60.0f;