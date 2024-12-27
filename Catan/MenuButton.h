#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"

/**
 * @file MenuButton.h
 * @brief Defines the MenuButton class, which extends the Button class to create specialized buttons for the menu system.
 */

/**
 * @class MenuButton
 * @brief Represents a button in the menu system.
 * 
 * The `MenuButton` class extends the `Button` class to define buttons that are specifically
 * used in the game's menus. It provides constructors to set the button's text, font, and position.
 */
class MenuButton : public Button {
public:
    /**
     * @brief Constructs a MenuButton object.
     * @param text The text displayed on the button.
     * @param font The font used for the button's text.
     * @param x The X position of the button on the screen.
     * @param y The Y position of the button on the screen.
     */
    MenuButton(const std::string& text, const sf::Font& font, float x, float y);
};
