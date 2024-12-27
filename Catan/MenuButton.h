#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"

class MenuButton : public Button {
public:
    MenuButton(const std::string& text, const sf::Font& font, float x, float y);
};