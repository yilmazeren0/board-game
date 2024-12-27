// BankMenu.h
#pragma once
#include "Menu.h"
#include "Button.h"
#include <memory>
#include <map>
#include "ResourceType.h"

class BankMenu : public Menu {
public:
    BankMenu(sf::RenderWindow* window, sf::View* view, Catan* game);
    void draw() override;
    void update(sf::Vector2f mousePosition) override;

private:
    std::unique_ptr<Button> backBtn;
    std::unique_ptr<Button> offerHeader;
    std::unique_ptr<Button> requestHeader;
    std::unique_ptr<Button> executeTrade;

    // Give (4:1) controls
    std::map<ResourceType, std::unique_ptr<Button>> giveLabels;
    std::map<ResourceType, std::unique_ptr<Button>> giveButtons;
    
    // Get (1) controls
    std::map<ResourceType, std::unique_ptr<Button>> getLabels;
    std::map<ResourceType, std::unique_ptr<Button>> getButtons;

    ResourceType selectedGiveResource = ResourceType::NONE;
    ResourceType selectedGetResource = ResourceType::NONE;

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

    void initializeButtons();
    void resetSelection();
    bool isValidTrade() const;
   
};
