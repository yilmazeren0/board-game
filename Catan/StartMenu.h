// StartMenu.h
#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "Menu.h"
#include "Button.h"

class Catan;

/**
 * @file StartMenu.h
 * @brief Defines the StartMenu class for the initial menu screen of the game.
 */

/**
 * @class StartMenu
 * @brief Represents the start menu screen for the game.
 * 
 * The `StartMenu` class is the first screen players interact with when they launch the game.
 * It provides buttons for the player to choose options like starting the game, adjusting player
 * count, randomizing the board, and exiting the game. The class manages the visual display of
 * these options and responds to user input.
 */
class StartMenu : public Menu {
public:
    /**
     * @brief Constructs a StartMenu object.
     * @param window Pointer to the SFML render window for drawing the menu.
     * @param view Pointer to the SFML view for positioning and scaling the menu.
     * @param game Pointer to the Catan game object to manage game states.
     */
    StartMenu(sf::RenderWindow* window, sf::View* view, Catan* game);

    /**
     * @brief Draws the start menu to the window.
     * 
     * This method renders all the menu buttons and other UI elements to the screen.
     * It is called every frame to display the start menu.
     */
    void draw() override;

    /**
     * @brief Updates the state of the start menu based on mouse position.
     * @param mousePosition The current mouse position on the screen.
     * 
     * This method updates button hover effects and checks for clicks on the menu buttons.
     */
    void update(sf::Vector2f mousePosition) override;

private:
    // Buttons for various menu options
    std::unique_ptr<Button> titleBtn; ///< Button to start the game
    std::unique_ptr<Button> startGameBtn; ///< Button to start a new game
    std::unique_ptr<Button> leftArrowBtn; ///< Button to decrease player count
    std::unique_ptr<Button> rightArrowBtn; ///< Button to increase player count
    std::unique_ptr<Button> playerCountBtn; ///< Button to display the current player count
    std::unique_ptr<Button> randomizeBoardBtn; ///< Button to randomize the game board
    std::unique_ptr<Button> exitBtn; ///< Button to exit the game

    /**
     * @brief Initializes the buttons for the start menu.
     * 
     * This helper function creates and sets up the buttons, assigning them positions,
     * labels, and actions.
     */
    void initializeButtons();

    /**
     * @brief Updates the player count displayed on the menu.
     * 
     * This helper function updates the player count based on user interactions with
     * the left and right arrow buttons.
     */
    void updatePlayerCount();

    /**
     * @brief Updates the mouse position for button hover effects and clicks.
     * 
     * This helper function updates the mouse position to check whether the mouse
     * is hovering over or clicking any of the buttons.
     */
    void updateMousePosition();
};
