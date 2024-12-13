#include "Hex.h"

Hex::Hex(sf::RenderWindow* window, int number)
{
	this->window = window;

    hex.setPointCount(6);

    for (int i = 0; i < 6; ++i)
    {
        float angle_deg = 60.0f * i - 30.0f;
        float angle_rad = angle_deg * 3.14159265f / 180.0f;

        float x = radius * std::cos(angle_rad);
        float y = radius * std::sin(angle_rad);

        hex.setPoint(i, sf::Vector2f(x, y));
    }

    hex.setPosition(centerPoints[number]);
}

Hex::~Hex()
{
}

void Hex::update()
{
}

void Hex::draw()
{
    window->draw(hex);
}

std::array<sf::Vector2f, 19> Hex::centerPoints = {
    sf::Vector2f(center - 2 * radius, center - 2 * std::sqrt(3.0f) * radius),
    sf::Vector2f(center, center - 2 * std::sqrt(3.0f) * radius),
    sf::Vector2f(center + 2 * radius, center - 2 * std::sqrt(3.0f) * radius),
    sf::Vector2f(center - 3.0f * radius, center - std::sqrt(3.0f) * radius),
    sf::Vector2f(center - 1.0f * radius, center - std::sqrt(3.0f) * radius),
    sf::Vector2f(center + 1.0f * radius, center - std::sqrt(3.0f) * radius),
    sf::Vector2f(center + 3.0f * radius, center - std::sqrt(3.0f) * radius),
    sf::Vector2f(center - 4 * radius, center),
    sf::Vector2f(center - 2 * radius, center),
    sf::Vector2f(center, center),//center
    sf::Vector2f(center + 2 * radius, center),
    sf::Vector2f(center + 4 * radius, center),
    sf::Vector2f(center - 3.0f * radius, center + std::sqrt(3.0f) * radius),
    sf::Vector2f(center - 1.0f * radius, center + std::sqrt(3.0f) * radius),
    sf::Vector2f(center + 1.0f * radius, center + std::sqrt(3.0f) * radius),
    sf::Vector2f(center + 3.0f * radius, center + std::sqrt(3.0f) * radius),
    sf::Vector2f(center - 2 * radius, center + 2 * std::sqrt(3.0f) * radius),
    sf::Vector2f(center, center + 2 * std::sqrt(3.0f) * radius),
    sf::Vector2f(center + 2 * radius, center + 2 * std::sqrt(3.0f) * radius)
};

const float Hex::center = 0.0f;
const float Hex::radius = 60.0f;