// BankMenu.cpp
#include "BankMenu.h"
#include "Catan.h"

BankMenu::BankMenu(sf::RenderWindow* window, sf::View* view, Catan* game)
    : Menu(window, view, game) {
    initializeButtons();
}

std::string BankMenu::getResourceName(ResourceType type) const
{
    switch (type) {
    case ResourceType::LUMBER: return "Lumber";
    case ResourceType::BRICK: return "Brick";
    case ResourceType::WOOL: return "Wool";
    case ResourceType::GRAIN: return "Grain";
    case ResourceType::ORE: return "Ore";
    default: return "None";
    }
}

void BankMenu::initializeButtons() {
    float baseX = view->getCenter().x + 12.0f * xPart;
    float baseY = view->getCenter().y + 8.0f * yPart; 

    // Back button
    backBtn = std::make_unique<Button>("<- Back", font,
        baseX, baseY - 12.0f * yPart);

    // Headers
    offerHeader = std::make_unique<Button>("Give (4:1)", font,
        baseX - 3.0f * xPart, baseY - 8.0f * yPart);
    requestHeader = std::make_unique<Button>("Get (1)", font,
        baseX + 3.0f * xPart, baseY - 8.0f * yPart);

    const std::array<ResourceType, 5> resources = {
        ResourceType::LUMBER, ResourceType::BRICK,
        ResourceType::WOOL, ResourceType::GRAIN, ResourceType::ORE
    };

    float resourceY = baseY - 6.0f * yPart;
    float spacing = 2.0f * yPart;

    for (const auto& resource : resources) {
        // Give buttons
        giveLabels[resource] = std::make_unique<Button>(
            getResourceName(resource), font,
            baseX - 3.0f * xPart, resourceY);
        giveButtons[resource] = std::make_unique<Button>(
            "x4", font,
            baseX - 1.0f * xPart, resourceY);

        // Get buttons
        getLabels[resource] = std::make_unique<Button>(
            getResourceName(resource), font,
            baseX + 3.0f * xPart, resourceY);
        getButtons[resource] = std::make_unique<Button>(
            "x1", font,
            baseX + 5.0f * xPart, resourceY);

        resourceY += spacing;
    }

    // Trade execution button (moved down)
    executeTrade = std::make_unique<Button>("Execute Trade", font,
        baseX, baseY + 6.0f * yPart);  // Adjusted position
}


void BankMenu::draw() {
    backBtn->draw(*window);
    offerHeader->draw(*window);
    requestHeader->draw(*window);

    for (const auto& [resource, button] : giveButtons) {
        giveLabels[resource]->draw(*window);
        button->draw(*window);
        getLabels[resource]->draw(*window);
        getButtons[resource]->draw(*window);
    }

    if (isValidTrade()) {
        executeTrade->draw(*window);
    }
}

void BankMenu::update(sf::Vector2f mousePosition) {
    if (backBtn->isClicked(mousePosition)) {
        backBtn->animate();
        game->setBankTrading(false);
        resetSelection();
        return;
    }

    for (const auto& [resource, button] : giveButtons) {
        if (button->isClicked(mousePosition) &&
            game->getCurrentPlayer()->getResourceCount(resource) >= 4) {
            button->animate();
            selectedGiveResource = resource;
        }
    }

    for (const auto& [resource, button] : getButtons) {
        if (button->isClicked(mousePosition)) {
            button->animate();
            selectedGetResource = resource;
        }
    }

    if (isValidTrade() && executeTrade->isClicked(mousePosition)) {
        if (game->bankTrade(selectedGiveResource, selectedGetResource)) {
            executeTrade->animate();
            resetSelection();
            game->setBankTrading(false);  // Close bank menu after successful trade
        }
    }
}

bool BankMenu::isValidTrade() const {
    return selectedGiveResource != ResourceType::NONE &&
           selectedGetResource != ResourceType::NONE &&
           selectedGiveResource != selectedGetResource;
}

void BankMenu::resetSelection() {
    selectedGiveResource = ResourceType::NONE;
    selectedGetResource = ResourceType::NONE;
}
