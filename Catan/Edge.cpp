#include "Edge.h"

Edge::Edge(sf::RenderWindow* window, const std::array<int, 2>& vertexIndices, int number) {
	this->window = window;
    this->ownedVertices = vertexIndices;
    this->availability = true;

	edge.setSize(sf::Vector2f(radius, 10.0f));
	edge.setOrigin(radius / 2, 10.0f / 2);
	edge.setFillColor(sf::Color::White);

	edge.setPosition(centerPoints[number]);
	edge.setRotation(rotations[number]);
}

Edge::~Edge()
{
}

const std::array<int, 2>& Edge::getOwnedVertices() const
{
    return ownedVertices;
}

void Edge::update(const sf::Vector2f& mousePosition)
{
    if (edge.getGlobalBounds().contains(mousePosition)) {
        edge.setFillColor(sf::Color::Yellow);
    }
    else {
        edge.setFillColor(sf::Color::White);
    }
}

void Edge::draw()
{
	window->draw(edge);
}


std::array<sf::Vector2f, 72> Edge::centerPoints = {
    sf::Vector2f(center - 3.0f * radius, center - 2.0f * std::sqrt(3.0f) * radius),//1  hex1
    sf::Vector2f(center - 2.5f * radius, center - 2.5f * std::sqrt(3.0f) * radius),//2  hex1
    sf::Vector2f(center - 1.5f * radius, center - 2.5f * std::sqrt(3.0f) * radius),//3  hex1
    sf::Vector2f(center - 1.0f * radius, center - 2.0f * std::sqrt(3.0f) * radius),//4  hex1 hex2
    sf::Vector2f(center - 1.5f * radius, center - 1.5f * std::sqrt(3.0f) * radius),//5  hex1 hex5
    sf::Vector2f(center - 2.5f * radius, center - 1.5f * std::sqrt(3.0f) * radius),//6  hex1 hex4
    sf::Vector2f(center - 0.5f * radius, center - 2.5f * std::sqrt(3.0f) * radius),//7  hex2
    sf::Vector2f(center + 0.5f * radius, center - 2.5f * std::sqrt(3.0f) * radius),//8  hex2 
    sf::Vector2f(center + 1.0f * radius, center - 2.0f * std::sqrt(3.0f) * radius),//9  hex2 hex3
    sf::Vector2f(center + 0.5f * radius, center - 1.5f * std::sqrt(3.0f) * radius),//10 hex2 hex6
    sf::Vector2f(center - 0.5f * radius, center - 1.5f * std::sqrt(3.0f) * radius),//11 hex2 hex5
    sf::Vector2f(center + 1.5f * radius, center - 2.5f * std::sqrt(3.0f) * radius),//12 hex3
    sf::Vector2f(center + 2.5f * radius, center - 2.5f * std::sqrt(3.0f) * radius),//13 hex3
    sf::Vector2f(center + 3.0f * radius, center - 2.0f * std::sqrt(3.0f) * radius),//14 hex3
    sf::Vector2f(center + 2.5f * radius, center - 1.5f * std::sqrt(3.0f) * radius),//15 hex3 hex7
    sf::Vector2f(center + 1.5f * radius, center - 1.5f * std::sqrt(3.0f) * radius),//16 hex3 hex6
    sf::Vector2f(center - 4.0f * radius, center - 1.0f * std::sqrt(3.0f) * radius),//17 hex4
    sf::Vector2f(center - 3.5f * radius, center - 1.5f * std::sqrt(3.0f) * radius),//18 hex4
    sf::Vector2f(center - 2.0f * radius, center - 1.0f * std::sqrt(3.0f) * radius),//19 hex4 hex5
    sf::Vector2f(center - 2.5f * radius, center - 0.5f * std::sqrt(3.0f) * radius),//20 hex4 hex9
    sf::Vector2f(center - 3.5f * radius, center - 0.5f * std::sqrt(3.0f) * radius),//21 hex4 hex8
    sf::Vector2f(center, center - 1.0f * std::sqrt(3.0f) * radius),                //22 hex5 hex6
    sf::Vector2f(center - 0.5f * radius, center - 0.5f * std::sqrt(3.0f) * radius),//23 hex5 hex10
    sf::Vector2f(center - 1.5f * radius, center - 0.5f * std::sqrt(3.0f) * radius),//24 hex5 hex9
    sf::Vector2f(center + 2.0f * radius, center - 1.0f * std::sqrt(3.0f) * radius),//25 hex6 hex7
    sf::Vector2f(center + 1.5f * radius, center - 0.5f * std::sqrt(3.0f) * radius),//26 hex6 hex11
    sf::Vector2f(center + 0.5f * radius, center - 0.5f * std::sqrt(3.0f) * radius),//27 hex6 hex10
    sf::Vector2f(center + 3.5f * radius, center - 1.5f * std::sqrt(3.0f) * radius),//28 hex7
    sf::Vector2f(center + 4.0f * radius, center - 1.0f * std::sqrt(3.0f) * radius),//29 hex7
    sf::Vector2f(center + 3.5f * radius, center - 0.5f * std::sqrt(3.0f) * radius),//30 hex7 hex12
    sf::Vector2f(center + 2.5f * radius, center - 0.5f * std::sqrt(3.0f) * radius),//31 hex7 hex11
    sf::Vector2f(center - 5.0f * radius, center),                                  //32 hex8
    sf::Vector2f(center - 4.5f * radius, center - 0.5f * std::sqrt(3.0f) * radius),//33 hex8
    sf::Vector2f(center - 3.0f * radius, center),                                  //34 hex8 hex9
    sf::Vector2f(center - 3.5f * radius, center + 0.5f * std::sqrt(3.0f) * radius),//35 hex8 hex13
    sf::Vector2f(center - 4.5f * radius, center + 0.5f * std::sqrt(3.0f) * radius),//36 hex8
    sf::Vector2f(center - 1.0f * radius, center * std::sqrt(3.0f) * radius),       //37 hex9 hex10
    sf::Vector2f(center - 1.5f * radius, center + 0.5f * std::sqrt(3.0f) * radius),//38 hex9 hex14
    sf::Vector2f(center - 2.5f * radius, center + 0.5f * std::sqrt(3.0f) * radius),//39 hex9 hex13
    sf::Vector2f(center + 1.0f * radius, center * std::sqrt(3.0f) * radius),       //40 hex10 hex11
    sf::Vector2f(center + 0.5f * radius, center + 0.5f * std::sqrt(3.0f) * radius),//41 hex10 hex15
    sf::Vector2f(center - 0.5f * radius, center + 0.5f * std::sqrt(3.0f) * radius),//42 hex10 hex14
    sf::Vector2f(center + 3.0f * radius, center * std::sqrt(3.0f) * radius),       //43 hex11 hex12
    sf::Vector2f(center + 2.5f * radius, center + 0.5f * std::sqrt(3.0f) * radius),//44 hex11 hex16
    sf::Vector2f(center + 1.5f * radius, center + 0.5f * std::sqrt(3.0f) * radius),//45 hex11 hex15
    sf::Vector2f(center + 4.5f * radius, center - 0.5f * std::sqrt(3.0f) * radius),//46 hex12
    sf::Vector2f(center + 5.0f * radius, center * std::sqrt(3.0f) * radius),       //47 hex12
    sf::Vector2f(center + 4.5f * radius, center + 0.5f * std::sqrt(3.0f) * radius),//48 hex12
    sf::Vector2f(center + 3.5f * radius, center + 0.5f * std::sqrt(3.0f) * radius),//49 hex12 hex16
    sf::Vector2f(center - 4.0f * radius, center + 1.0f * std::sqrt(3.0f) * radius),//50 hex13
    sf::Vector2f(center - 2.0f * radius, center + 1.0f * std::sqrt(3.0f) * radius),//51 hex13 hex14
    sf::Vector2f(center - 2.5f * radius, center + 1.5f * std::sqrt(3.0f) * radius),//52 hex13 hex17
    sf::Vector2f(center - 3.5f * radius, center + 1.5f * std::sqrt(3.0f) * radius),//53 hex13
    sf::Vector2f(center, center + 1.0f * std::sqrt(3.0f) * radius),                //54 hex14 hex15
    sf::Vector2f(center - 0.5f * radius, center + 1.5f * std::sqrt(3.0f) * radius),//55 hex14 hex18
    sf::Vector2f(center - 1.5f * radius, center + 1.5f * std::sqrt(3.0f) * radius),//56 hex14 hex17
    sf::Vector2f(center + 2.0f * radius, center + 1.0f * std::sqrt(3.0f) * radius),//57 hex15 hex16
    sf::Vector2f(center + 1.5f * radius, center + 1.5f * std::sqrt(3.0f) * radius),//58 hex15 hex19
    sf::Vector2f(center + 0.5f * radius, center + 1.5f * std::sqrt(3.0f) * radius),//59 hex15 hex18
    sf::Vector2f(center + 4.0f * radius, center + 1.0f * std::sqrt(3.0f) * radius),//60 hex16
    sf::Vector2f(center + 3.5f * radius, center + 1.5f * std::sqrt(3.0f) * radius),//61 hex16
    sf::Vector2f(center + 2.5f * radius, center + 1.5f * std::sqrt(3.0f) * radius),//62 hex16 hex19
    sf::Vector2f(center - 3.0f * radius, center + 2.0f * std::sqrt(3.0f) * radius),//63 hex17
    sf::Vector2f(center - 1.0f * radius, center + 2.0f * std::sqrt(3.0f) * radius),//64 hex17 hex18
    sf::Vector2f(center - 1.5f * radius, center + 2.5f * std::sqrt(3.0f) * radius),//65 hex17 
    sf::Vector2f(center - 2.5f * radius, center + 2.5f * std::sqrt(3.0f) * radius),//66 hex17
    sf::Vector2f(center + 1.0f * radius, center + 2.0f * std::sqrt(3.0f) * radius),//67 hex18 hex19
    sf::Vector2f(center + 0.5f * radius, center + 2.5f * std::sqrt(3.0f) * radius),//68 hex18 
    sf::Vector2f(center - 0.5f * radius, center + 2.5f * std::sqrt(3.0f) * radius),//69 hex18 
    sf::Vector2f(center + 3.0f * radius, center + 2.0f * std::sqrt(3.0f) * radius),//70 hex19
    sf::Vector2f(center + 2.5f * radius, center + 2.5f * std::sqrt(3.0f) * radius),//71 hex19
    sf::Vector2f(center + 1.5f * radius, center + 2.5f * std::sqrt(3.0f) * radius),//72 hex19
};

std::array<float, 72> Edge::rotations = {
    90.0f,  //1
    150.0f, //2
    30.0f,  //3
    90.0f,  //4
    150.0f, //5
    30.0f,  //6
    150.0f, //7
    30.0f,  //8
    90.0f,  //9
    150.0f, //10
    30.0f,  //11
    150.0f, //12
    30.0f,  //13
    90.0f,  //14
    150.0f, //15
    30.0f,  //16
    90.0f,  //17
    150.0f, //18
    90.0f,  //19
    150.0f, //20
    30.0f,  //21
    90.0f,  //22
    150.0f, //23
    30.0f,  //24
    90.0f,  //25
    150.0f, //26
    30.0f,  //27
    30.0f,  //28
    90.0f,  //29
    150.0f, //30
    30.0f,  //31
    90.0f,  //32
    150.0f, //33
    90.0f,  //34
    150.0f, //35
    30.0f,  //36
    90.0f,  //37
    150.0f, //38
    30.0f,  //39
    90.0f,  //40
    150.0f, //41
    30.0f,  //42
    90.0f,  //43
    150.0f, //44
    30.0f,  //45
    30.0f,  //46
    90.0f,  //47
    150.0f, //48
    30.0f,  //49
    90.0f,  //50
    90.0f,  //51
    150.0f, //52
    30.0f,  //53
    90.0f,  //54
    150.0f, //55
    30.0f,  //56
    90.0f,  //57
    150.0f, //58
    30.0f,  //59
    90.0f,  //60
    150.0f, //61
    30.0f,  //62
    90.0f,  //63
    90.0f,  //64
    150.0f, //65
    30.0f,  //66
    90.0f,  //67
    150.0f, //68
    30.0f,  //69
    90.0f,  //70
    150.0f, //71
    30.0f,  //72
};

const float Edge::center = 0.0f;
const float Edge::radius = 60.0f;
