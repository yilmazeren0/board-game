#pragma once
#include "Menu.h"
#include "Button.h"
#include <memory>
#include <array>
#include <map>
#include "ResourceType.h"

class Catan;

/**
 * @file TradeMenu.h
 * @brief Defines the TradeMenu class that handles the user interface and logic for trading resources in the game.
 */

/**
 * @class TradeMenu
 * @brief Handles the trading interface and logic during a trade between players.
 * 
 * The `TradeMenu` class provides the user interface for players to propose, accept, or decline trades. 
 * Players can offer and request resources, select other players to trade with, and interact with the trade menu.
 */
class TradeMenu : public Menu {
public:
    /**
     * @brief Constructs the TradeMenu object.
     * @param window Pointer to the SFML RenderWindow for rendering.
     * @param view Pointer to the SFML View used for positioning elements.
     * @param game Pointer to the Catan game instance.
     */
    TradeMenu(sf::RenderWindow* window, sf::View* view, Catan* game);

    /**
     * @brief Draws the trade menu and its elements to the screen.
     */
    void draw() override;

    /**
     * @brief Updates the trade menu, handling user interactions and menu state changes.
     * @param mousePosition The current mouse position for detecting interactions.
     */
    void update(sf::Vector2f mousePosition) override;

private:
    /**
     * @brief Menu state for the selection phase (choosing a player).
     */
    bool selectingPlayer = true;

    /**
     * @brief Menu state for offering resources.
     */
    bool offeringResources = false;

    /**
     * @brief Menu state for waiting for a response to a trade.
     */
    bool waitingResponse = false;

    /**
     * @brief Index of the selected player for trade.
     */
    int selectedPlayer = -1;

    /**
     * @brief Resources the player is offering for trade.
     */
    std::map<ResourceType, int> offerResources{
        {ResourceType::LUMBER, 0},
        {ResourceType::BRICK, 0},
        {ResourceType::WOOL, 0},
        {ResourceType::GRAIN, 0},
        {ResourceType::ORE, 0}
    };

    /**
     * @brief Resources the player is requesting in trade.
     */
    std::map<ResourceType, int> requestResources{
        {ResourceType::LUMBER, 0},
        {ResourceType::BRICK, 0},
        {ResourceType::WOOL, 0},
        {ResourceType::GRAIN, 0},
        {ResourceType::ORE, 0}
    };

    /**
     * @brief Converts the resource type to its corresponding name as a string.
     * @param type The resource type to convert.
     * @return The name of the resource type.
     */
    std::string getResourceName(ResourceType type) const;

    // Menu buttons and UI elements
    std::unique_ptr<Button> offerHeader; ///< Button displaying the offer header.
    std::unique_ptr<Button> requestHeader; ///< Button displaying the request header.

    // Labels for resource display
    std::map<ResourceType, std::unique_ptr<Button>> offerLabels; ///< Labels for displaying offered resources.
    std::map<ResourceType, std::unique_ptr<Button>> requestLabels; ///< Labels for displaying requested resources.

    // Back button and player selection buttons
    std::unique_ptr<Button> backBtn; ///< Button for returning to the previous menu.
    std::vector<std::unique_ptr<Button>> playerButtons; ///< Buttons for selecting players to trade with.

    // Resource offering and requesting buttons
    std::map<ResourceType, std::unique_ptr<Button>> offerPlusButtons; ///< Buttons for increasing offered resources.
    std::map<ResourceType, std::unique_ptr<Button>> offerMinusButtons; ///< Buttons for decreasing offered resources.
    std::map<ResourceType, std::unique_ptr<Button>> offerCountText; ///< Text display for offered resource amounts.

    std::map<ResourceType, std::unique_ptr<Button>> requestPlusButtons; ///< Buttons for increasing requested resources.
    std::map<ResourceType, std::unique_ptr<Button>> requestMinusButtons; ///< Buttons for decreasing requested resources.
    std::map<ResourceType, std::unique_ptr<Button>> requestCountText; ///< Text display for requested resource amounts.

    // Action buttons for trade proposals and responses
    std::unique_ptr<Button> proposeTradeBtn; ///< Button to propose a trade.
    std::unique_ptr<Button> acceptTradeBtn; ///< Button to accept a trade.
    std::unique_ptr<Button> declineTradeBtn; ///< Button to decline a trade.

    // Helper methods
    void initializeButtons(); ///< Initializes all buttons in the trade menu.
    void drawPlayerSelection(); ///< Draws the player selection interface.
    void drawTradeInterface(); ///< Draws the resource offering and requesting interface.
    void drawTradeProposal(); ///< Draws the trade proposal interface.
    void handlePlayerSelection(sf::Vector2f mousePosition); ///< Handles player selection for the trade.
    void handleResourceSelection(sf::Vector2f mousePosition); ///< Handles resource offering and requesting.
    void handleTradeResponse(sf::Vector2f mousePosition); ///< Handles responses to the trade proposal.
    void updateResourceDisplay(); ///< Updates the display for resource amounts.
    void resetTrade(); ///< Resets the trade state to prepare for a new trade.
    bool isValidTrade() const; ///< Checks if the current trade is valid.
};
