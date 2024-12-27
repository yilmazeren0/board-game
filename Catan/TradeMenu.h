// TradeMenu.h
#pragma once
#include "Menu.h"
#include "Button.h"
#include <memory>
#include <array>
#include <map>
#include "ResourceType.h"

class Catan;

class TradeMenu : public Menu {
public:
    TradeMenu(sf::RenderWindow* window, sf::View* view, Catan* game);
    void draw() override;
    void update(sf::Vector2f mousePosition) override;

private:
    // Menu states
    bool selectingPlayer = true;
    bool offeringResources = false;
    bool waitingResponse = false;
    int selectedPlayer = -1;

    // Resource amounts for trading
    std::map<ResourceType, int> offerResources{
        {ResourceType::LUMBER, 0},
        {ResourceType::BRICK, 0},
        {ResourceType::WOOL, 0},
        {ResourceType::GRAIN, 0},
        {ResourceType::ORE, 0}
    };

    std::map<ResourceType, int> requestResources{
        {ResourceType::LUMBER, 0},
        {ResourceType::BRICK, 0},
        {ResourceType::WOOL, 0},
        {ResourceType::GRAIN, 0},
        {ResourceType::ORE, 0}
    };

    std::string getResourceName(ResourceType type) const {
        switch (type) {
        case ResourceType::LUMBER: return "Lumber";
        case ResourceType::BRICK: return "Brick";
        case ResourceType::WOOL: return "Wool";
        case ResourceType::GRAIN: return "Grain";
        case ResourceType::ORE: return "Ore";
        default: return "None";
        }
    }

    std::unique_ptr<Button> offerHeader;
    std::unique_ptr<Button> requestHeader;

    // Add text display for resource names
    std::map<ResourceType, std::unique_ptr<Button>> offerLabels;
    std::map<ResourceType, std::unique_ptr<Button>> requestLabels;



    // UI Elements
    std::unique_ptr<Button> backBtn;
    std::vector<std::unique_ptr<Button>> playerButtons;

    // Offer resource buttons
    std::map<ResourceType, std::unique_ptr<Button>> offerPlusButtons;
    std::map<ResourceType, std::unique_ptr<Button>> offerMinusButtons;
    std::map<ResourceType, std::unique_ptr<Button>> offerCountText;

    // Request resource buttons
    std::map<ResourceType, std::unique_ptr<Button>> requestPlusButtons;
    std::map<ResourceType, std::unique_ptr<Button>> requestMinusButtons;
    std::map<ResourceType, std::unique_ptr<Button>> requestCountText;

    // Action buttons
    std::unique_ptr<Button> proposeTradeBtn;
    std::unique_ptr<Button> acceptTradeBtn;
    std::unique_ptr<Button> declineTradeBtn;

    // Helper methods
    void initializeButtons();
    void drawPlayerSelection();
    void drawTradeInterface();
    void drawTradeProposal();
    void handlePlayerSelection(sf::Vector2f mousePosition);
    void handleResourceSelection(sf::Vector2f mousePosition);
    void handleTradeResponse(sf::Vector2f mousePosition);
    void updateResourceDisplay();
    void resetTrade();
    bool isValidTrade() const;
};
