#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include "ResourceType.h"
#include "Road.h"
#include "Settlement.h"
#include "City.h"

/**
 * @file Player.h
 * @brief Defines the Player class, which represents a player in the game.
 */

/**
 * @class Player
 * @brief Represents a player in the game, managing resources, cards, and actions.
 * 
 * The `Player` class stores and manages the player's resources, development cards,
 * victory points, and other attributes such as the player's color and ID. It provides
 * methods for performing actions such as building roads and settlements, using development
 * cards, and checking the player's victory status.
 */
class Player {
private:
    std::vector<Card> cards; ///< A list of the player's development cards.
    std::vector<Card> newlyPurchasedCards; ///< A list of cards newly purchased by the player.

    std::map<Card, sf::Sprite> cardSprites; ///< A map of development card types to their corresponding sprites.
    
    sf::RenderWindow* window; ///< Pointer to the SFML RenderWindow for rendering.
    sf::View* view; ///< Pointer to the SFML View for positioning the camera.
    std::unordered_map<std::string, sf::Texture>* textures; ///< Map of textures used in the game.
    int playerID; ///< The player's unique ID.
    std::map<ResourceType, int> resources; ///< Map of resources the player owns, indexed by resource type.
    sf::Color color; ///< The player's color for UI display.
    sf::Text player; ///< Text element for displaying the player's name.
    sf::Text lumber; ///< Text element for displaying the player's lumber resources.
    sf::Text brick; ///< Text element for displaying the player's brick resources.
    sf::Text ore; ///< Text element for displaying the player's ore resources.
    sf::Text grain; ///< Text element for displaying the player's grain resources.
    sf::Text wool; ///< Text element for displaying the player's wool resources.
    sf::Font font; ///< Font used for rendering player-related text.
    sf::Sprite lumberTexture; ///< Sprite representing the lumber resource.
    sf::Sprite brickTexture; ///< Sprite representing the brick resource.
    sf::Sprite oreTexture; ///< Sprite representing the ore resource.
    sf::Sprite grainTexture; ///< Sprite representing the grain resource.
    sf::Sprite woolTexture; ///< Sprite representing the wool resource.

    std::map<int, sf::FloatRect> cardPositions; ///< Positions of the player's cards in the UI.
    float xPart; ///< Horizontal partition for positioning elements.
    float yPart; ///< Vertical partition for positioning elements.
    int knightsPlayed = 0; ///< Counter for the number of knights played by the player.

    bool mustPlaceRobber = false; ///< Flag indicating whether the player must place the robber.

    int victoryPoints = 0; ///< Number of victory points the player has.

    bool hasLongestRoad = false; ///< Flag indicating if the player has the Longest Road card.
    bool hasLargestArmy = false; ///< Flag indicating if the player has the Largest Army card.
    int roadCount = 0; ///< The number of roads the player has built.

public:
    /**
     * @brief Constructs a Player object.
     * @param window Pointer to the SFML RenderWindow for rendering.
     * @param view Pointer to the SFML View for positioning the camera.
     * @param textures Pointer to the map of textures used in the game.
     * @param id The unique ID of the player.
     * @param color The color representing the player in the game.
     */
    Player(sf::RenderWindow* window, sf::View* view, std::unordered_map<std::string, sf::Texture>* textures, int id, sf::Color color);

    /**
     * @brief Draws the player's UI elements.
     */
    void draw();

    /**
     * @brief Updates the player's state, including the UI and resources.
     */
    void update();

    /**
     * @brief Adds a card to the player's hand.
     * @param card The card to be added.
     */
    void addCard(Card card);

    /**
     * @brief Gets the list of cards the player has.
     * @return A constant reference to the vector of the player's cards.
     */
    const std::vector<Card>& getCards() const;

    /**
     * @brief Draws the player's card UI.
     */
    void drawCardUI();

    /**
     * @brief Checks if the player can build a road.
     * @return True if the player can build a road, false otherwise.
     */
    bool canBuildRoad() const;

    /**
     * @brief Builds a road for the player.
     */
    void buildRoad();

    /**
     * @brief Checks if the player can build a settlement.
     * @return True if the player can build a settlement, false otherwise.
     */
    bool canBuildSettlement() const;

    /**
     * @brief Builds a settlement for the player.
     */
    void buildSettlement();

    /**
     * @brief Takes resources from the player.
     * @param resourceType The type of resource to take.
     * @param amount The amount of the resource to take.
     */
    void takeResources(ResourceType resourceType, int amount);

    /**
     * @brief Gets the resources the player has.
     * @return A constant reference to the map of resources the player has.
     */
    const std::map<ResourceType, int>& getResources() const;

    /**
     * @brief Gets the number of victory points the player has.
     * @return The number of victory points.
     */
    int getVictoryPoints() const;

    /**
     * @brief Checks if the player has won the game.
     * @return True if the player has won, false otherwise.
     */
    bool hasWon() const;

    /**
     * @brief Sets whether the player has the Largest Army card.
     * @param has True if the player has the Largest Army card, false otherwise.
     */
    void setLargestArmy(bool has);

    /**
     * @brief Checks if the player has the Largest Army card.
     * @return True if the player has the Largest Army card, false otherwise.
     */
    bool hasLargestArmyCard() const { return hasLargestArmy; }

    /**
     * @brief Checks if the player can buy a development card.
     * @return True if the player can buy a development card, false otherwise.
     */
    bool canBuyDevelopmentCard() const;

    /**
     * @brief Buys a development card for the player.
     */
    void buyDevelopmentCard();

    /**
     * @brief Gets the player's unique ID.
     * @return The player's unique ID.
     */
    int getID() const;

    /**
     * @brief Gets the color representing the player.
     * @return The color of the player.
     */
    sf::Color getColor() const;

    /**
     * @brief Uses a Knight card.
     * @return True if the Knight card was successfully used, false otherwise.
     */
    bool useKnightCard();

    /**
     * @brief Uses a Year of Plenty card to gain two resources.
     * @param first The first resource to gain.
     * @param second The second resource to gain.
     * @return True if the Year of Plenty card was successfully used, false otherwise.
     */
    bool useYearOfPlentyCard(ResourceType first, ResourceType second);

    /**
     * @brief Uses a Road Building card to build two roads.
     * @return True if the Road Building card was successfully used, false otherwise.
     */
    bool useRoadBuildingCard();

    /**
     * @brief Uses a Monopoly card to steal all of one type of resource from other players.
     * @param resource The resource to steal.
     * @return True if the Monopoly card was successfully used, false otherwise.
     */
    bool useMonopolyCard(ResourceType resource);

    /**
     * @brief Uses a Victory Point card.
     * @return True if the Victory Point card was successfully used, false otherwise.
     */
    bool useVictoryPointCard();

    /**
     * @brief Checks if the player has a specific card.
     * @param cardType The type of card to check.
     * @return True if the player has the card, false otherwise.
     */
    bool hasCard(Card cardType) const;

    /**
     * @brief Removes a specific card from the player's hand.
     * @param cardType The type of card to remove.
     */
    void removeCard(Card cardType);

    /**
     * @brief Handles the card click event and determines which card was clicked.
     * @param clickPosition The position of the mouse click.
     * @return The card that was clicked.
     */
    Card handleCardClick(sf::Vector2f clickPosition);

    /**
     * @brief Adds a certain amount of a resource to the player's resources.
     * @param type The type of resource to add.
     * @param amount The amount of the resource to add (default is 1).
     */
    void addResource(ResourceType type, int amount = 1);

    /**
     * @brief Removes a certain amount of a resource from the player's resources.
     * @param type The type of resource to remove.
     * @param amount The amount of the resource to remove (default is 1).
     */
    void removeResource(ResourceType type, int amount = 1);

    /**
     * @brief Gets the number of a specific resource the player has.
     * @param type The type of resource to check.
     * @return The amount of the resource.
     */
    int getResourceCount(ResourceType type) const;

    /**
     * @brief Increments the number of knights the player has played.
     */
    void incrementKnightsPlayed();

    /**
     * @brief Gets the number of knights the player has played.
     * @return The number of knights played.
     */
    int getKnightsPlayed() const;

    /**
     * @brief Checks if the player has any resources.
     * @return True if the player has resources, false otherwise.
     */
    bool hasResources() const;

    /**
     * @brief Gets the total number of resources the player has.
     * @return The total number of resources.
     */
    int getTotalResources() const;

    /**
     * @brief Gets a random resource the player has.
     * @return A randomly selected resource type.
     */
    ResourceType getRandomResource() const;

    /**
     * @brief Discards a specified number of resources.
     * @param count The number of resources to discard.
     */
    void discardResources(int count);

    /**
     * @brief Sets whether the player must move the robber.
     * @param must True if the player must move the robber, false otherwise.
     */
    void setMustMoveRobber(bool must);

    /**
     * @brief Checks if the player must move the robber.
     * @return True if the player must move the robber, false otherwise.
     */
    bool mustMoveRobber() const;

    /**
     * @brief Sets whether the player has the Longest Road card.
     * @param has True if the player has the Longest Road card, false otherwise.
     */
    void setLongestRoad(bool has);

    /**
     * @brief Checks if the player has the Longest Road card.
     * @return True if the player has the Longest Road card, false otherwise.
     */
    bool hasLongestRoadCard() const { return hasLongestRoad; }

    /**
     * @brief Increments the player's road count.
     */
    void incrementRoadCount();

    /**
     * @brief Gets the number of roads the player has built.
     * @return The number of roads.
     */
    int getRoadCount() const;

    /**
     * @brief Clears the list of newly purchased cards.
     */
    void clearNewlyPurchasedCards();

    /**
     * @brief Checks if a specific card is playable by the player.
     * @param card The card to check.
     * @return True if the card is playable, false otherwise.
     */
    bool isCardPlayable(Card card) const;

private:
    /**
     * @brief Initializes the player's resources.
     */
    void initResources();

    /**
     * @brief Initializes the text elements used by the player.
     */
    void initTexts();

    /**
     * @brief Initializes the textures used by the player.
     */
    void initTextures();

    /**
     * @brief Initializes the card sprites used by the player.
     * @param textures Pointer to the map of textures used in the game.
     */
    void initCardSprites(std::unordered_map<std::string, sf::Texture>* textures);

    /**
     * @brief Draws the player's cards.
     */
    void drawCards();

    /**
     * @brief Updates the player's text elements.
     */
    void updateText();
};
