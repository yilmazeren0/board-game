#include "Settlement.h"
#include "Player.h"

Settlement::Settlement(Player* owner, sf::Color color) : Building{ owner, color } {

}

void Settlement::addResource(ResourceType type) {
    //owner->addResource(type, 1);
}
