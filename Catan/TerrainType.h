#pragma once

/**
 * @file TerrainType.h
 * @brief Defines the TerrainType enum class used for representing different terrain types.
 */

/**
 * @enum TerrainType
 * @brief Represents the types of terrain available on the game board.
 * 
 * The `TerrainType` enum defines the different types of terrain that can be found on the game board.
 * Each terrain type is associated with a specific resource or gameplay effect:
 * - `FOREST`: Produces wood (lumber).
 * - `HILLS`: Produces brick.
 * - `MOUNTAINS`: Produces ore.
 * - `FIELDS`: Produces grain.
 * - `PASTURE`: Produces wool.
 * - `DESERT`: Does not produce resources and is typically associated with the robber.
 */
enum class TerrainType {
    FOREST, ///< Forest terrain that produces lumber.
    HILLS, ///< Hills terrain that produces brick.
    MOUNTAINS, ///< Mountains terrain that produces ore.
    FIELDS, ///< Fields terrain that produces grain.
    PASTURE, ///< Pasture terrain that produces wool.
    DESERT ///< Desert terrain that produces no resources.
};
