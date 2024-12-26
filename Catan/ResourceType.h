#pragma once

/**
 * @file ResourceType.h
 * @brief Defines the ResourceType enum class representing the types of resources in the game.
 */

/**
 * @enum ResourceType
 * @brief Enum representing the types of resources in the game.
 * 
 * The `ResourceType` enum defines the various resource types available in the game, which
 * players can collect, trade, and use for building and purchasing development cards.
 */
enum class ResourceType {
    LUMBER, ///< Represents the Lumber resource.
    BRICK, ///< Represents the Brick resource.
    ORE, ///< Represents the Ore resource.
    GRAIN, ///< Represents the Grain resource.
    WOOL, ///< Represents the Wool resource.
    NONE, ///< Represents no resource or the absence of a resource.
};
