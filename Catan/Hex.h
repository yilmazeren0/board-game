/**
 * @file Hex.h
 * @brief Defines the Hex class representing a single hexagonal tile in the game board.
 */

#pragma once
#include <SFML/Graphics.hpp>
#include "ResourceType.h"
#include "TerrainType.h"
#include "Vertex.h"
#include <array>
#include <unordered_map>

/**
 * @class Hex
 * @brief Represents a hexagonal tile on the game board.
 * 
 * The Hex class contains details about its terrain type, resource production,
 * vertices it owns, and whether it is currently robbed.
 */
class Hex
{
public:
    /**
     * @brief Constructs a Hex object.
     * @param window Pointer to the SFML RenderWindow for rendering.
     * @param textures Pointer to the map of textures used in the game.
     * @param terrainType The type of terrain this hex represents.
     * @param vertexIndices Indices of vertices owned by this hex.
     * @param number The index of this hex.
     * @param diceNumber The dice roll number required to produce resources on this hex.
     */
    Hex(sf::RenderWindow* window, std::unordered_map<std::string, sf::Texture>* textures, 
        TerrainType terrainType, const std::array<int, 6>& vertexIndices, 
        int number, int diceNumber);

    /**
     * @brief Destructor for the Hex class.
     */
    ~Hex();

    /**
     * @brief Updates the hex's state (e.g., animations or visual effects).
     */
    void update();

    /**
     * @brief Draws the hex to the window.
     */
    void draw();

    /**
     * @brief Gets the indices of vertices owned by this hex.
     * @return A constant reference to the array of owned vertex indices.
     */
    const std::array<int, 6>& getOwnedVertices() const;

    /**
     * @brief Gets the dice number associated with this hex.
     * @return The dice number.
     */
    int getDiceNumber() const;

    /**
     * @brief Gets the type of resource produced by this hex.
     * @return The resource type.
     */
    ResourceType getResourceType() const;

    /**
     * @brief Sets the robber on this hex.
     */
    void setRobber();

    /**
     * @brief Removes the robber from this hex.
     */
    void removeRobber();

    /**
     * @brief Checks if this hex is currently robbed.
     * @return True if the hex is robbed, false otherwise.
     */
    bool isRobbed() const;

    /**
     * @brief Gets the bounding box of this hex.
     * @return A FloatRect representing the hex's bounding box.
     */
    sf::FloatRect getBox() const;

private:
    /**
     * @brief Initializes the resource type based on the terrain type.
     * @param terrainType The type of terrain.
     * @return The corresponding resource type.
     */
    ResourceType initResourceType(TerrainType terrainType);

private:
    sf::RenderWindow* window; ///< Pointer to the SFML window for rendering.
    sf::ConvexShape hex; ///< Shape representing the hexagonal tile.
    sf::Sprite sprite; ///< Sprite for terrain texture.
    sf::Text text; ///< Text displaying the dice number.
    sf::Font font; ///< Font for the dice number text.
    sf::CircleShape circle; ///< Circle for visual effects.
    sf::Sprite robberSprite; ///< Sprite representing the robber.
    std::array<int, 6> ownedVertices; ///< Indices of vertices owned by this hex.
    std::unordered_map<std::string, sf::Texture>* textures; ///< Map of game textures.

    ResourceType resourceType; ///< Resource type produced by this hex.
    TerrainType terrainType; ///< Terrain type of this hex.
    bool hasRobber = false; ///< Flag indicating if the robber is on this hex.
    int diceNumber; ///< Dice number required to produce resources.

    // Static attributes for positioning and geometry
    static std::array<sf::Vector2f, 19> centerPoints; ///< Predefined center points of hexes.
    static const float center; ///< Center coordinate offset.
    static const float radius; ///< Radius of the hex.
};
