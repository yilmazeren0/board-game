#include "City.h"
#include "Player.h"

City::City(Player* owner, sf::Color color) : Settlement{ owner, color } {

}

void City::addResource(ResourceType type) {
    //owner->addResource(type, 1);
}

