#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include "Settlement.h"
#include "City.h"

/**
 * @file Vertex.h
 * @brief Defines the Vertex class, which represents a vertex (settlement location) on the game board.
 */

/**
 * @class Vertex
 * @brief Represents a vertex (or settlement location) on the game board.
 * 
 * The `Vertex` class is responsible for managing the state and appearance of a vertex on the board, 
 * where players can place settlements or cities. It tracks availability, ownership, and whether the vertex is highlighted.
 */
class Vertex
{
public:
    /**
     * @brief Constructs a Vertex object at the given location.
     * @param window Pointer to the SFML RenderWindow for rendering.
     * @param number The vertex number (or ID).
     */
    Vertex(sf::RenderWindow* window, int number);

    /**
     * @brief Destroys the Vertex object, releasing any allocated resources.
     */
    ~Vertex();

    /**
     * @brief Updates the state of the vertex, including handling interactions with the mouse.
     * @param mousePosition The current mouse position used for interaction detection.
     */
    void update(const sf::Vector2f& mousePosition);

    /**
     * @brief Draws the vertex to the screen.
     */
    void draw();

    /**
     * @brief Places a settlement at this vertex.
     * @param settlement Pointer to the Settlement object to place.
     */
    void placeSettlement(Settlement* settlement);

    /**
     * @brief Gets the bounding box of the vertex for collision detection.
     * @return The bounding box of the vertex.
     */
    sf::FloatRect getBox() const;

    /**
     * @brief Checks if the vertex is available for placing a building.
     * @return True if the vertex is available; otherwise, false.
     */
    bool getAvailability() const;

    /**
     * @brief Checks if the vertex is highlighted.
     * @return True if the vertex is highlighted; otherwise, false.
     */
    bool isHightlighted() const;

    /**
     * @brief Sets whether the vertex should be highlighted.
     * @param highlight Whether to highlight the vertex.
     */
    void setHighlight(bool highlight);

    /**
     * @brief Sets the availability of the vertex.
     * @param availability Whether the vertex is available for placing a building.
     */
    void setAvailability(bool availability);

    /**
     * @brief Checks if the vertex is owned by a specific player.
     * @param playerID The ID of the player to check.
     * @return True if the vertex is owned by the specified player; otherwise, false.
     */
    bool isOwnedByPlayer(int playerID) const;

    /**
     * @brief Checks if the vertex is owned.
     * @return True if the vertex is owned; otherwise, false.
     */
    bool isOwned() const;

    /**
     * @brief Adds a resource to this vertex.
     * @param resourceType The type of resource to add.
     */
    void addResource(ResourceType resourceType);

    /**
     * @brief Gets the owner of this vertex, if it has one.
     * @return Pointer to the player who owns this vertex; nullptr if no owner.
     */
    Player* getOwner() const;

private:
    sf::RenderWindow* window; ///< Pointer to the SFML RenderWindow for rendering.
    sf::CircleShape vertex; ///< The graphical representation of the vertex.
    Settlement* settlement = nullptr; ///< Pointer to the settlement on this vertex, if any.
    sf::Color color; ///< Color of the vertex (used for highlighting and ownership indication).
    bool availability; ///< Whether the vertex is available for placing a building.
    bool highlighted; ///< Whether the vertex is highlighted.

    static std::array<sf::Vector2f, 54> centerPoints; ///< Static array of center points for the vertices on the game board.
    static const float center; ///< The center of the board (used for position calculations).
    static const float radius; ///< The radius for calculating positions.
    static const float circleRadius; ///< The radius of the vertex circle.
};
