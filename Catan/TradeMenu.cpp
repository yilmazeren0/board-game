#include "TradeMenu.h"
#include "Catan.h"
#include <sstream>

TradeMenu::TradeMenu(sf::RenderWindow* window, sf::View* view, Catan* game)
    : Menu(window, view, game), selectingPlayer(true), offeringResources(false), waitingResponse(false) {
    initializeButtons();
}

void TradeMenu::initializeButtons() {
    float baseX = view->getCenter().x + 13.0f * xPart;  // Align with game menu
    float baseY = view->getCenter().y + 140.0f;

    // Back button at top
    backBtn = std::make_unique<Button>("<- Back", font,
        baseX, baseY - 12.0f * yPart);
    backBtn->setCharacterSize(20);

    // Initialize player selection buttons only for actual number of players
    int playerCount = game->getPlayerCount();  // Get actual number of players
    for (int i = 0; i < playerCount; i++) {    // Changed from hardcoded 4 to playerCount
        auto btn = std::make_unique<Button>(
            "Trade with Player " + std::to_string(i + 1), font,
            baseX, baseY + (-6.0f + i * 3.0f) * yPart);
        btn->setCharacterSize(20);
        playerButtons.push_back(std::move(btn));
    }

    // Resource trading interface
    const std::array<ResourceType, 5> resources = {
        ResourceType::LUMBER, ResourceType::BRICK,
        ResourceType::WOOL, ResourceType::GRAIN, ResourceType::ORE
    };

    float resourceY = baseY - 6.0f * yPart;
    float resourceSpacing = 2.5f * yPart;

    // Add headers for the two sections
    offerHeader = std::make_unique<Button>("Your Offer", font,
        baseX - 3.0f * xPart, baseY - 8.0f * yPart);
    requestHeader = std::make_unique<Button>("You Request", font,
        baseX + 3.0f * xPart, baseY - 8.0f * yPart);

    offerHeader->setCharacterSize(18);
    requestHeader->setCharacterSize(18);

    for (const auto& resource : resources) {
        // Resource names/labels
        offerLabels[resource] = std::make_unique<Button>(
            getResourceName(resource) + ":", font,
            baseX - 4.0f * xPart, resourceY);
        requestLabels[resource] = std::make_unique<Button>(
            getResourceName(resource) + ":", font,
            baseX + 2.0f * xPart, resourceY);

        // Offer controls
        offerMinusButtons[resource] = std::make_unique<Button>("-", font,
            baseX - 2.5f * xPart, resourceY);
        offerCountText[resource] = std::make_unique<Button>("0", font,
            baseX - 1.5f * xPart, resourceY);
        offerPlusButtons[resource] = std::make_unique<Button>("+", font,
            baseX - 0.5f * xPart, resourceY);

        // Request controls
        requestMinusButtons[resource] = std::make_unique<Button>("-", font,
            baseX + 3.5f * xPart, resourceY);
        requestCountText[resource] = std::make_unique<Button>("0", font,
            baseX + 4.5f * xPart, resourceY);
        requestPlusButtons[resource] = std::make_unique<Button>("+", font,
            baseX + 5.5f * xPart, resourceY);

        // Set text sizes and colors
        sf::Color labelColor = sf::Color(200, 200, 200);  // Light gray for labels
        offerLabels[resource]->setCharacterSize(14);
        requestLabels[resource]->setCharacterSize(14);
        offerLabels[resource]->getText().setFillColor(labelColor);
        requestLabels[resource]->getText().setFillColor(labelColor);

        offerCountText[resource]->setCharacterSize(16);
        requestCountText[resource]->setCharacterSize(16);

        offerPlusButtons[resource]->setCharacterSize(18);
        offerMinusButtons[resource]->setCharacterSize(18);
        requestPlusButtons[resource]->setCharacterSize(18);
        requestMinusButtons[resource]->setCharacterSize(18);

        resourceY += resourceSpacing;
    }

    // Action buttons at bottom
    proposeTradeBtn = std::make_unique<Button>("Propose Trade", font,
        baseX, baseY + 8.0f * yPart);
    acceptTradeBtn = std::make_unique<Button>("Accept", font,
        baseX - 2.0f * xPart, baseY + 8.0f * yPart);
    declineTradeBtn = std::make_unique<Button>("Decline", font,
        baseX + 2.0f * xPart, baseY + 8.0f * yPart);

    proposeTradeBtn->setCharacterSize(24);
    acceptTradeBtn->setCharacterSize(24);
    declineTradeBtn->setCharacterSize(24);

    // Set special colors for action buttons
    proposeTradeBtn->getText().setFillColor(sf::Color(100, 255, 100));  // Light green
    acceptTradeBtn->getText().setFillColor(sf::Color(100, 255, 100));   // Light green
    declineTradeBtn->getText().setFillColor(sf::Color(255, 100, 100));  // Light red
}

void TradeMenu::draw() {
    backBtn->draw(*window);

    if (selectingPlayer) {
        drawPlayerSelection();
    }
    else if (offeringResources) {
        drawTradeInterface();
    }
    else if (waitingResponse) {
        drawTradeProposal();
    }
}

void TradeMenu::drawTradeInterface() {
    // Draw headers
    offerHeader->draw(*window);
    requestHeader->draw(*window);

    // Draw resource interface
    for (const auto& [resource, label] : offerLabels) {
        // Draw labels
        label->draw(*window);
        requestLabels[resource]->draw(*window);

        // Draw controls
        offerMinusButtons[resource]->draw(*window);
        offerCountText[resource]->draw(*window);
        offerPlusButtons[resource]->draw(*window);

        requestMinusButtons[resource]->draw(*window);
        requestCountText[resource]->draw(*window);
        requestPlusButtons[resource]->draw(*window);
    }

    proposeTradeBtn->draw(*window);
}


void TradeMenu::drawPlayerSelection() {
    int playerCount = game->getPlayerCount();
    for (size_t i = 0; i < playerCount; i++) {
        if (static_cast<int>(i) != game->getCurrentPlayerIndex()) {
            playerButtons[i]->draw(*window);
        }
    }
}


void TradeMenu::drawTradeProposal() {
    acceptTradeBtn->draw(*window);
    declineTradeBtn->draw(*window);
}

void TradeMenu::update(sf::Vector2f mousePosition) {
    if (backBtn->isClicked(mousePosition)) {
        backBtn->animate();
        resetTrade();
        return;
    }

    if (selectingPlayer) {
        handlePlayerSelection(mousePosition);
    }
    else if (offeringResources) {
        handleResourceSelection(mousePosition);
    }
    else if (waitingResponse) {
        handleTradeResponse(mousePosition);
    }

    updateResourceDisplay();
}

void TradeMenu::handlePlayerSelection(sf::Vector2f mousePosition) {
    for (size_t i = 0; i < playerButtons.size(); i++) {
        if (static_cast<int>(i) != game->getCurrentPlayerIndex() &&
            playerButtons[i]->isClicked(mousePosition)) {
            selectedPlayer = static_cast<int>(i);
            selectingPlayer = false;
            offeringResources = true;
            playerButtons[i]->animate();
            game->resetClickPosition();
        }
    }
}

void TradeMenu::handleResourceSelection(sf::Vector2f mousePosition) {
    bool clicked = false;  // Flag to check if any button was clicked

    for (const auto& [resource, button] : offerPlusButtons) {
        // Handle Offer Plus Button
        if (button->isClicked(mousePosition) &&
            game->getCurrentPlayer()->getResourceCount(resource) > offerResources[resource]) {
            offerResources[resource]++;
            button->animate();
            clicked = true;
        }

        // Handle Offer Minus Button
        if (offerMinusButtons[resource]->isClicked(mousePosition) &&
            offerResources[resource] > 0) {
            offerResources[resource]--;
            offerMinusButtons[resource]->animate();
            clicked = true;
        }

        // Handle Request Plus Button
        if (requestPlusButtons[resource]->isClicked(mousePosition)) {
            requestResources[resource]++;
            requestPlusButtons[resource]->animate();
            clicked = true;
        }

        // Handle Request Minus Button
        if (requestMinusButtons[resource]->isClicked(mousePosition) &&
            requestResources[resource] > 0) {
            requestResources[resource]--;
            requestMinusButtons[resource]->animate();
            clicked = true;
        }
    }

    // Handle Propose Trade Button
    if (proposeTradeBtn->isClicked(mousePosition)) {
        if (isValidTrade()) {
            // Verify player has enough resources
            bool hasEnoughResources = true;
            for (const auto& [resource, count] : offerResources) {
                if (game->getCurrentPlayer()->getResourceCount(resource) < count) {
                    hasEnoughResources = false;
                    break;
                }
            }

            if (hasEnoughResources) {
                proposeTradeBtn->animate();
                offeringResources = false;
                waitingResponse = true;
                if (game->proposeTrade(selectedPlayer, offerResources, requestResources)) {
                    clicked = true;
                }
            }
        }
    }

    // Reset click position if any button was clicked
    if (clicked) {
        game->resetClickPosition();
    }
}



void TradeMenu::handleTradeResponse(sf::Vector2f mousePosition) {
    if (acceptTradeBtn->isClicked(mousePosition)) {
        // Verify target player has enough resources before accepting
        bool canAcceptTrade = true;
        Player* targetPlayer = game->getPlayer(selectedPlayer);

        for (const auto& [resource, count] : requestResources) {
            if (targetPlayer->getResourceCount(resource) < count) {
                canAcceptTrade = false;
                break;
            }
        }

        if (canAcceptTrade) {
            acceptTradeBtn->animate();
            game->acceptTrade();
            resetTrade();
        }
    }
    else if (declineTradeBtn->isClicked(mousePosition)) {
        declineTradeBtn->animate();
        game->declineTrade();
        resetTrade();
    }
}

void TradeMenu::updateResourceDisplay() {
    for (const auto& [resource, count] : offerResources) {
        offerCountText[resource]->setString(std::to_string(count));
    }
    for (const auto& [resource, count] : requestResources) {
        requestCountText[resource]->setString(std::to_string(count));
    }
}

bool TradeMenu::isValidTrade() const {
    bool hasOffer = false;
    bool hasRequest = false;

    for (const auto& [resource, count] : offerResources) {
        if (count > 0) hasOffer = true;
    }
    for (const auto& [resource, count] : requestResources) {
        if (count > 0) hasRequest = true;
    }

    return hasOffer && hasRequest;
}

void TradeMenu::resetTrade() {
    selectingPlayer = true;
    offeringResources = false;
    waitingResponse = false;
    selectedPlayer = -1;

    for (auto& [resource, count] : offerResources) {
        count = 0;
    }
    for (auto& [resource, count] : requestResources) {
        count = 0;
    }

    game->setTrading(false);  // Deactivate trade menu
    game->resetClickPosition();
}
