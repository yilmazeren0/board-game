/**
 * @file Board.h
 * @brief Defines the Board class and its functionality for the Catan game.
 */

#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <array>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include "Hex.h"
#include "Edge.h"
#include "Vertex.h"
#include "Road.h"
#include "Player.h"

/**
 * @class Board
 * @brief Represents the game board for the Catan game, handling terrain, structures, and gameplay mechanics.
 */
class Board {
public:
    /**
     * @brief Constructor for the Board class.
     * @param window Pointer to the SFML render window.
     * @param textures Pointer to a map of textures used in the game.
     */
    Board(sf::RenderWindow* window, std::unordered_map<std::string, sf::Texture>* textures);

    /**
     * @brief Destructor for the Board class.
     */
    ~Board();

    /**
     * @brief Updates the game board state based on the current player.
     * @param currentPlayerID The ID of the current player.
     */
    void update(int currentPlayerID);

    /**
     * @brief Draws the game board and its elements to the screen.
     */
    void draw();

    /**
     * @brief Places a road on the board.
     * @param player Pointer to the player attempting to place the road.
     * @param clickPosition The position where the road is to be placed.
     * @return True if the road is successfully placed, false otherwise.
     */
    bool placeRoad(Player* player, sf::Vector2f clickPosition);

    /**
     * @brief Places a settlement on the board.
     * @param player Pointer to the player attempting to place the settlement.
     * @param clickPosition The position where the settlement is to be placed.
     * @return True if the settlement is successfully placed, false otherwise.
     */
    bool placeSettlement(Player* player, sf::Vector2f clickPosition);

    /**
     * @brief Sets whether the game is in the setup phase.
     * @param setupPhase True to enable the setup phase, false otherwise.
     */
    void setSetupPhase(bool setupPhase);

    /**
     * @brief Sets whether a road is being placed.
     * @param placingRoad True to indicate a road is being placed, false otherwise.
     */
    void setplacingRoad(bool placingRoad);

    /**
     * @brief Sets whether a settlement is being placed.
     * @param placingSettlement True to indicate a settlement is being placed, false otherwise.
     */
    void setplacingSettlement(bool placingSettlement);

    /**
     * @brief Produces resources for players based on the rolled dice number.
     * @param diceNumber The number rolled on the dice.
     */
    void produceResource(int diceNumber);

    /**
     * @brief Places the robber on the specified hex position.
     * @param position The position to place the robber.
     * @return True if the robber is successfully placed, false otherwise.
     */
    bool placeRobber(sf::Vector2f position);

    /**
     * @brief Gets the players present at a specified hex.
     * @param hex Pointer to the hex to check.
     * @return A vector of players at the specified hex.
     */
    std::vector<Player*> getPlayersAtHex(Hex* hex);

    /**
     * @brief Moves the robber to a new position.
     * @param position The new position for the robber.
     */
    void moveRobber(sf::Vector2f position);

    /**
     * @brief Gets the hex where the robber is currently located.
     * @return Pointer to the hex with the robber.
     */
    Hex* getRobberHex() const;

    /**
     * @brief Calculates the longest road length for a specified player.
     * @param playerID The ID of the player.
     * @return The length of the longest road.
     */
    int getLongestRoadLength(int playerID) const;

private:
    /**
     * @brief Initializes the game board.
     */
    void initBoard();

    /**
     * @brief Initializes the terrain hexes on the board.
     */
    void initTerrains();

    /**
     * @brief Updates the current mouse position in the game window.
     */
    void updateMousePosition();

    /**
     * @brief Highlights edges based on the current player's actions.
     * @param currentPlayerID The ID of the current player.
     */
    void updateEdgeHighlights(int currentPlayerID);

    /**
     * @brief Highlights vertices based on the current player's actions.
     * @param currentPlayerID The ID of the current player.
     */
    void updateVertexHighlights(int currentPlayerID);

    /**
     * @brief Shuffles the terrain types for the hexes.
     * @param terrains Array of terrain types to shuffle.
     */
    void shuffleTerrains(std::array<TerrainType, 18>& terrains);

    /**
     * @brief Recursively calculates the connected road length.
     * @param edgeIndex The index of the current edge.
     * @param playerID The ID of the player.
     * @param visited Set of visited edges to avoid loops.
     * @return The length of the connected road.
     */
    int getConnectedRoadLength(int edgeIndex, int playerID, std::set<int>& visited) const;

    /**
     * @brief Gets the edges connected to a specified edge.
     * @param edgeIndex The index of the edge.
     * @return A vector of indices for connected edges.
     */
    std::vector<int> getConnectedEdges(int edgeIndex) const;

private:
    sf::RenderWindow* window;                              ///< Pointer to the SFML render window.
    std::vector<Hex> hexes;                                ///< List of hexes on the board.
    std::vector<Edge> edges;                               ///< List of edges on the board.
    std::vector<Vertex> vertices;                          ///< List of vertices on the board.
    std::list<Road> roads;                                 ///< List of roads placed on the board.
    std::list<Settlement> settlements;                     ///< List of settlements placed on the board.
    std::unordered_map<std::string, sf::Texture>* textures; ///< Pointer to the texture map.

    std::unordered_set<int> highlightedEdges;              ///< Set of highlighted edges.
    std::unordered_set<int> highlightedVertices;           ///< Set of highlighted vertices.
    sf::Vector2f mousePosition;                            ///< Current mouse position.
    bool setupPhase;                                       ///< Indicates if the game is in the setup phase.
    bool placingRoad;                                      ///< Indicates if a road is being placed.
    bool placingSettlement;                                ///< Indicates if a settlement is being placed.
    int currentPlayerID;                                   ///< ID of the current player.
    std::array<TerrainType, 18> terrains;                  ///< Array of terrain types on the board.

    Hex* currentRobberHex = nullptr;                       ///< Pointer to the hex with the robber.

    /// Static arrays defining game mechanics.
    const static std::array<std::array<int, 6>, 19> hexAndOwnedVertices;
    const static std::array<std::array<int, 2>, 72> edgeAndOwnedVertices;
    const static std::array<std::vector<int>, 54> vertexNeighbours;
    const static std::array<std::vector<int>, 72> edgeNeighbours;
    const static std::array<int, 19> diceNumbers;
};
