#include "Vertex.h"
#include "Player.h"

Vertex::Vertex(sf::RenderWindow *window, int number)
{
    this->window = window;
    this->availability = true;
    this->highlighted = false;
    this->color = sf::Color::Transparent;
    vertex.setRadius(circleRadius);
    vertex.setOrigin(circleRadius, circleRadius);
    vertex.setFillColor(color);

    vertex.setPosition(centerPoints[number]);
}

Vertex::~Vertex()
{
}

void Vertex::update(const sf::Vector2f &mousePosition)
{
    if (vertex.getGlobalBounds().contains(mousePosition) && highlighted)
    {
        vertex.setFillColor(sf::Color::Yellow);
    }
    else
    {
        vertex.setFillColor(color);
    }
}

void Vertex::draw()
{
    window->draw(vertex);
}

void Vertex::placeSettlement(Settlement *settlement)
{
    this->settlement = settlement;
    availability = false;
    highlighted = false;
    color = settlement->getColor();
}

sf::FloatRect Vertex::getBox() const
{
    return vertex.getGlobalBounds();
}

bool Vertex::getAvailability() const
{
    return availability;
}

bool Vertex::isHightlighted() const
{
    return highlighted;
}

void Vertex::setHighlight(bool highlight)
{
    this->highlighted = highlight;
}

void Vertex::setAvailability(bool availability)
{
    this->availability = availability;
}

bool Vertex::isOwned() const
{
    if (settlement == nullptr)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool Vertex::isOwnedByPlayer(int playerID) const
{
    if (settlement == nullptr)
    {
        return false;
    }

    return settlement->getOwner()->getID() == playerID;
}

void Vertex::addResource(ResourceType resourceType)
{
    if (settlement)
    {
        if (dynamic_cast<City *>(settlement))
        {
            settlement->getOwner()->takeResources(resourceType, 2);
        }
        else if (dynamic_cast<Settlement *>(settlement))
        {
            settlement->getOwner()->takeResources(resourceType, 1);
        }
    }
}

Player* Vertex::getOwner() const
{
    return (settlement) ? settlement->getOwner() : nullptr;
}

std::array<sf::Vector2f, 54> Vertex::centerPoints = {
    sf::Vector2f(center - 3.0f * radius, center - 2.35f * std::sqrt(3.0f) * radius), // 1  hex1
    sf::Vector2f(center - 2.0f * radius, center - 2.65f * std::sqrt(3.0f) * radius), // 2  hex1
    sf::Vector2f(center - 1.0f * radius, center - 2.35f * std::sqrt(3.0f) * radius), // 3  hex1 hex2
    sf::Vector2f(center, center - 2.65f * std::sqrt(3.0f) * radius),                 // 4  hex2
    sf::Vector2f(center + 1.0f * radius, center - 2.35f * std::sqrt(3.0f) * radius), // 5  hex2 hex3
    sf::Vector2f(center + 2.0f * radius, center - 2.65f * std::sqrt(3.0f) * radius), // 6  hex3
    sf::Vector2f(center + 3.0f * radius, center - 2.35f * std::sqrt(3.0f) * radius), // 7  hex3

    sf::Vector2f(center - 4.0f * radius, center - 1.35f * std::sqrt(3.0f) * radius), // 8  hex4
    sf::Vector2f(center - 3.0f * radius, center - 1.65f * std::sqrt(3.0f) * radius), // 9  hex1 hex4
    sf::Vector2f(center - 2.0f * radius, center - 1.35f * std::sqrt(3.0f) * radius), // 10 hex1 hex4 hex5
    sf::Vector2f(center - 1.0f * radius, center - 1.65f * std::sqrt(3.0f) * radius), // 11 hex1 hex2 hex5
    sf::Vector2f(center, center - 1.35f * std::sqrt(3.0f) * radius),                 // 12 hex2 hex5 hex6
    sf::Vector2f(center + 1.0f * radius, center - 1.65f * std::sqrt(3.0f) * radius), // 13 hex2 hex3 hex6
    sf::Vector2f(center + 2.0f * radius, center - 1.35f * std::sqrt(3.0f) * radius), // 14 hex3 hex6 hex7
    sf::Vector2f(center + 3.0f * radius, center - 1.65f * std::sqrt(3.0f) * radius), // 15 hex3 hex7
    sf::Vector2f(center + 4.0f * radius, center - 1.35f * std::sqrt(3.0f) * radius), // 16 hex7

    sf::Vector2f(center - 5.0f * radius, center - 0.35f * std::sqrt(3.0f) * radius), // 17 hex8
    sf::Vector2f(center - 4.0f * radius, center - 0.65f * std::sqrt(3.0f) * radius), // 18 hex4 hex8
    sf::Vector2f(center - 3.0f * radius, center - 0.35f * std::sqrt(3.0f) * radius), // 19 hex4 hex8 hex9
    sf::Vector2f(center - 2.0f * radius, center - 0.65f * std::sqrt(3.0f) * radius), // 20 hex4 hex5 hex9
    sf::Vector2f(center - 1.0f * radius, center - 0.35f * std::sqrt(3.0f) * radius), // 21 hex5 hex9 hex10
    sf::Vector2f(center, center - 0.65f * std::sqrt(3.0f) * radius),                 // 22 hex5 hex6 hex10
    sf::Vector2f(center + 1.0f * radius, center - 0.35f * std::sqrt(3.0f) * radius), // 23 hex6 hex10 hex11
    sf::Vector2f(center + 2.0f * radius, center - 0.65f * std::sqrt(3.0f) * radius), // 24 hex6 hex7 hex11
    sf::Vector2f(center + 3.0f * radius, center - 0.35f * std::sqrt(3.0f) * radius), // 25 hex7 hex11 hex12
    sf::Vector2f(center + 4.0f * radius, center - 0.65f * std::sqrt(3.0f) * radius), // 26 hex7 hex12
    sf::Vector2f(center + 5.0f * radius, center - 0.35f * std::sqrt(3.0f) * radius), // 27 hex12

    sf::Vector2f(center - 5.0f * radius, center + 0.35f * std::sqrt(3.0f) * radius), // 28 hex8
    sf::Vector2f(center - 4.0f * radius, center + 0.65f * std::sqrt(3.0f) * radius), // 29 hex8 hex13
    sf::Vector2f(center - 3.0f * radius, center + 0.35f * std::sqrt(3.0f) * radius), // 30 hex8 hex9 hex13
    sf::Vector2f(center - 2.0f * radius, center + 0.65f * std::sqrt(3.0f) * radius), // 31 hex9 hex13 hex14
    sf::Vector2f(center - 1.0f * radius, center + 0.35f * std::sqrt(3.0f) * radius), // 32 hex9 hex10 hex14
    sf::Vector2f(center, center + 0.65f * std::sqrt(3.0f) * radius),                 // 33 hex10 hex14 hex15
    sf::Vector2f(center + 1.0f * radius, center + 0.35f * std::sqrt(3.0f) * radius), // 34 hex10 hex11 hex15
    sf::Vector2f(center + 2.0f * radius, center + 0.65f * std::sqrt(3.0f) * radius), // 35 hex11 hex15 hex16
    sf::Vector2f(center + 3.0f * radius, center + 0.35f * std::sqrt(3.0f) * radius), // 36 hex11 hex12 hex16
    sf::Vector2f(center + 4.0f * radius, center + 0.65f * std::sqrt(3.0f) * radius), // 37 hex12 hex16
    sf::Vector2f(center + 5.0f * radius, center + 0.35f * std::sqrt(3.0f) * radius), // 38 hex12

    sf::Vector2f(center - 4.0f * radius, center + 1.35f * std::sqrt(3.0f) * radius), // 39 hex13
    sf::Vector2f(center - 3.0f * radius, center + 1.65f * std::sqrt(3.0f) * radius), // 40 hex13 hex17
    sf::Vector2f(center - 2.0f * radius, center + 1.35f * std::sqrt(3.0f) * radius), // 41 hex13 hex14 hex17
    sf::Vector2f(center - 1.0f * radius, center + 1.65f * std::sqrt(3.0f) * radius), // 42 hex14 hex17 hex18
    sf::Vector2f(center, center + 1.35f * std::sqrt(3.0f) * radius),                 // 43 hex14 hex15 hex18
    sf::Vector2f(center + 1.0f * radius, center + 1.65f * std::sqrt(3.0f) * radius), // 44 hex15 hex18 hex19
    sf::Vector2f(center + 2.0f * radius, center + 1.35f * std::sqrt(3.0f) * radius), // 45 hex15 hex16 hex19
    sf::Vector2f(center + 3.0f * radius, center + 1.65f * std::sqrt(3.0f) * radius), // 46 hex16 hex19
    sf::Vector2f(center + 4.0f * radius, center + 1.35f * std::sqrt(3.0f) * radius), // 47 hex16

    sf::Vector2f(center - 3.0f * radius, center + 2.35f * std::sqrt(3.0f) * radius), // 48 hex17
    sf::Vector2f(center - 2.0f * radius, center + 2.65f * std::sqrt(3.0f) * radius), // 49 hex17
    sf::Vector2f(center - 1.0f * radius, center + 2.35f * std::sqrt(3.0f) * radius), // 50 hex17 hex18
    sf::Vector2f(center, center + 2.65f * std::sqrt(3.0f) * radius),                 // 51 hex18
    sf::Vector2f(center + 1.0f * radius, center + 2.35f * std::sqrt(3.0f) * radius), // 52 hex18 hex19
    sf::Vector2f(center + 2.0f * radius, center + 2.65f * std::sqrt(3.0f) * radius), // 53 hex19
    sf::Vector2f(center + 3.0f * radius, center + 2.35f * std::sqrt(3.0f) * radius), // 54 hex19

};

const float Vertex::center = 0.0f;
const float Vertex::radius = 60.0f;
const float Vertex::circleRadius = 20.0f;