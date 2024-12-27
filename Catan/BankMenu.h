/**
 * @file BankMenu.h
 * @brief Defines the BankMenu class for managing bank trades in the Catan game.
 */

#pragma once

#include "Menu.h"
#include "Button.h"
#include <memory>
#include <map>
#include "ResourceType.h"

/**
 * @class BankMenu
 * @brief Represents the menu for conducting trades with the bank.
 */
class BankMenu : public Menu {
public:
    /**
     * @brief Constructor for the BankMenu class.
     * @param window Pointer to the SFML render window.
     * @param view Pointer to the SFML view.
     * @param game Pointer to the main Catan game instance.
     */
    BankMenu(sf::RenderWindow* window, sf::View* view, Catan* game);

    /**
     * @brief Draws the BankMenu to the screen.
     */
    void draw() override;

    /**
     * @brief Updates the state of the BankMenu based on mouse position.
     * @param mousePosition The current mouse position in the game window.
     */
    void update(sf::Vector2f mousePosition) override;

private:
    std::unique_ptr<Button> backBtn;        ///< Button to return to the previous menu.
    std::unique_ptr<Button> offerHeader;   ///< Label for the "Offer" section.
    std::unique_ptr<Button> requestHeader; ///< Label for the "Request" section.
    std::unique_ptr<Button> executeTrade;  ///< Button to execute the trade.

    /// Buttons and labels for offering resources (4:1 trade ratio).
    std::map<ResourceType, std::unique_ptr<Button>> giveLabels; ///< Labels for resources to give.
    std::map<ResourceType, std::unique_ptr<Button>> giveButtons; ///< Buttons for selecting resources to give.

    /// Buttons and labels for requesting resources (1:1 ratio).
    std::map<ResourceType, std::unique_ptr<Button>> getLabels; ///< Labels for resources to get.
    std::map<ResourceType, std::unique_ptr<Button>> getButtons; ///< Buttons for selecting resources to get.

    ResourceType selectedGiveResource = ResourceType::NONE; ///< Currently selected resource to give.
    ResourceType selectedGetResource = ResourceType::NONE;  ///< Currently selected resource to get.

    /**
     * @brief Retrieves the name of a resource as a string.
     * @param type The resource type.
     * @return The name of the resource.
     */
    std::string getResourceName(ResourceType type) const;

    /**
     * @brief Initializes the buttons used in the BankMenu.
     */
    void initializeButtons();

    /**
     * @brief Resets the selected resources for trading.
     */
    void resetSelection();

    /**
     * @brief Validates whether the current trade is valid.
     * @return True if the trade is valid, false otherwise.
     */
    bool isValidTrade() const;
};
