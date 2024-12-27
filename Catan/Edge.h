/**
 * @file Edge.h
 * @brief Defines the Edge class, representing the edges between vertices in the game board.
 */

#pragma once
#include <SFML/Graphics.hpp>
#include "Vertex.h"
#include "Road.h"
#include <array>

/**
 * @class Edge
 * @brief Represents an edge between two vertices on the game board.
 * 
 * Edges can contain roads and are used to connect vertices. They are also involved
 * in determining valid placements and gameplay interactions.
 */
class Edge {
public:
    /**
     * @brief Constructs an Edge object.
     * @param window Pointer to the SFML RenderWindow for rendering the edge.
     * @param vertexIndices Indices of the two vertices connected by this edge.
     * @param number The unique identifier for this edge.
     */
    Edge(sf::RenderWindow* window, const std::array<int, 2>& vertexIndices, int number);

    /**
     * @brief Destroys the Edge object.
     */
    ~Edge();

    /**
     * @brief Updates the state of the edge, including highlighting and interaction.
     * @param mousePosition The current mouse position in the window.
     */
    void update(const sf::Vector2f& mousePosition);

    /**
     * @brief Renders the edge to the screen.
     */
    void draw();

    /**
     * @brief Places a road on this edge.
     * @param road Pointer to the Road object to place.
     */
    void placeRoad(Road* road);

    /**
     * @brief Retrieves the indices of the vertices owned by this edge.
     * @return An array containing the indices of the two vertices.
     */
    const std::array<int, 2>& getOwnedVertices() const;

    /**
     * @brief Retrieves the bounding box of the edge for collision detection.
     * @return A FloatRect representing the bounding box of the edge.
     */
    sf::FloatRect getBox() const;

    /**
     * @brief Checks if the edge is available for placing a road.
     * @return True if available, false otherwise.
     */
    bool getAvailability() const;

    /**
     * @brief Checks if the edge is currently highlighted.
     * @return True if highlighted, false otherwise.
     */
    bool isHightlighted() const;

    /**
     * @brief Sets the highlight state of the edge.
     * @param highlight True to highlight the edge, false to remove the highlight.
     */
    void setHighlight(bool highlight);

    /**
     * @brief Sets the availability of the edge for road placement.
     * @param availability True to make the edge available, false otherwise.
     */
    void setAvailability(bool availability);

    /**
     * @brief Checks if the edge is owned by a specific player.
     * @param playerID The ID of the player to check.
     * @return True if the edge is owned by the player, false otherwise.
     */
    bool isOwnedByPlayer(size_t playerID) const;

    /**
     * @brief Checks if the edge contains a specific vertex.
     * @param vertexIndex The index of the vertex to check.
     * @return True if the edge contains the vertex, false otherwise.
     */
    bool containsVertex(int vertexIndex) const;

    /**
     * @brief Retrieves the indices of the vertices connected by this edge.
     * @return An array containing the indices of the vertices.
     */
    const std::array<int, 2>& getVertices() const;

private:
    sf::RenderWindow* window; ///< Pointer to the window used for rendering.
    sf::RectangleShape edge; ///< Visual representation of the edge.
    Road* road = nullptr; ///< Pointer to the road placed on this edge, if any.
    sf::Color color; ///< Color of the edge.
    std::array<int, 2> ownedVertices; ///< Indices of the vertices connected by this edge.
    bool availability; ///< Whether the edge is available for road placement.
    bool highlighted; ///< Whether the edge is currently highlighted.

    static std::array<sf::Vector2f, 72> centerPoints; ///< Precomputed center points for edges.
    static std::array<float, 72> rotations; ///< Precomputed rotation angles for edges.
    static const float center; ///< Center of the board for edge positioning.
    static const float radius; ///< Radius of the board for edge positioning.

    std::array<int, 2> vertices; ///< Indices of the vertices connected by this edge.
};
