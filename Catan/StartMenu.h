// StartMenu.h
#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "Menu.h"
#include "Button.h"

class Catan;

class StartMenu : public Menu {
public:
    StartMenu(sf::RenderWindow* window, sf::View* view, Catan* game);
    void draw() override;
    void update(sf::Vector2f mousePosition) override;

private:
    std::unique_ptr<Button> titleBtn;
    std::unique_ptr<Button> startGameBtn;
    std::unique_ptr<Button> leftArrowBtn;
    std::unique_ptr<Button> rightArrowBtn;
    std::unique_ptr<Button> playerCountBtn;
    std::unique_ptr<Button> randomizeBoardBtn;
    std::unique_ptr<Button> exitBtn;

    void initializeButtons();
    void updatePlayerCount();
    void updateMousePosition();
};
