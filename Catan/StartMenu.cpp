#include "StartMenu.h"
#include "Catan.h"
#include <iostream>
#include <sstream>
#include <string>
StartMenu::StartMenu(sf::RenderWindow* window, sf::View* view, Catan* game) : window{window}, view{view}, game{game}
{
	xPart = window->getSize().x / 30.0f;
	yPart = window->getSize().y / 30.0f;
	
	font.loadFromFile("font/emmasophia.ttf");

	catanText();
	startGameText();
	leftSymbolText();
	playerCountText();
	rightSymbolText();
	randomizeBoardText();
	exitText();
}

void StartMenu::draw()
{
	window->draw(catan);
	window->draw(startGame);
	window->draw(leftSymbol);
	window->draw(playerCount);
	window->draw(rightSymbol);
	window->draw(randomizeBoard);
	window->draw(exit);

}

void StartMenu::update(sf::Vector2f mousePosition)
{
	updateMousePosition();
	startGameHighlight();
	leftSymbolHighlight();
	rightSymbolHighlight();
	randomizeBoardHighlight();
	exitHighlight();
	updateText();
	
	if (startGame.getGlobalBounds().contains(mousePosition)) {
		game->setMenu(false);
		game->resetClickPosition();
		std::cout << "start game\n";
	}
	else if (leftSymbol.getGlobalBounds().contains(mousePosition)) {
		game->decrementPlayerCount();
		game->resetClickPosition();
		std::cout << "left symbol\n";
	}
	else if (rightSymbol.getGlobalBounds().contains(mousePosition)) {
		game->incrementPlayerCount();
		game->resetClickPosition();
		std::cout << "right symbol\n";
	}
	else if (randomizeBoard.getGlobalBounds().contains(mousePosition)) {
		game->restartBoard();
		game->resetClickPosition();
		std::cout << "randomize board\n";
	}
	else if (exit.getGlobalBounds().contains(mousePosition)) {
		game->resetClickPosition();			
		window->close();
	}
	
}

void StartMenu::catanText()
{
	catan.setFont(font);
	catan.setString("CATAN");
	catan.setCharacterSize(55);
	catan.setOrigin(catan.getGlobalBounds().width / 2.0f, catan.getGlobalBounds().height / 2.0f);
	catan.setPosition(view->getCenter().x + 14 * xPart, view->getCenter().y - 10 * yPart);
}

void StartMenu::startGameText()
{
	startGame.setFont(font);
	startGame.setString("Start Game");
	startGame.setCharacterSize(25);
	startGame.setOrigin(startGame.getLocalBounds().width / 2.0f, startGame.getLocalBounds().height / 2.0f);
	startGame.setPosition(view->getCenter().x + 14 * xPart, view->getCenter().y - 3 * yPart);

	//startGameContainer.setSize(sf::Vector2f(startGame.getGlobalBounds().width + 20.0f, startGame.getGlobalBounds().height + 20.0f));
	//startGameContainer.setOrigin(startGameContainer.getSize().x / 2.0f, startGameContainer.getSize().y / 2.0f);
	//startGameContainer.setPosition(view->getCenter().x + 14 * xPart, view->getCenter().y - 3 * yPart);
	
	//startGame.setPosition(startGameContainer.getPosition());
}

void StartMenu::leftSymbolText()
{
	leftSymbol.setFont(font);
	leftSymbol.setString("<");
	leftSymbol.setCharacterSize(25);
	leftSymbol.setOrigin(leftSymbol.getLocalBounds().width / 2.0f, leftSymbol.getLocalBounds().height / 2.0f);
	leftSymbol.setPosition(view->getCenter().x + 11 * xPart, view->getCenter().y + 1 * yPart);
}

void StartMenu::playerCountText()
{
	playerCount.setFont(font);
	playerCount.setString("4 Players");
	playerCount.setCharacterSize(25);
	playerCount.setOrigin(playerCount.getGlobalBounds().width / 2.0f, playerCount.getGlobalBounds().height / 2.0f);
	playerCount.setPosition(view->getCenter().x + 14 * xPart, view->getCenter().y + 1.5f * yPart);
}

void StartMenu::rightSymbolText()
{
	rightSymbol.setFont(font);
	rightSymbol.setString(">");
	rightSymbol.setCharacterSize(25);
	rightSymbol.setOrigin(rightSymbol.getLocalBounds().width / 2.0f, rightSymbol.getLocalBounds().height / 2.0f);
	rightSymbol.setPosition(view->getCenter().x + 17 * xPart, view->getCenter().y + 1 * yPart);
}

void StartMenu::randomizeBoardText()
{
	randomizeBoard.setFont(font);
	randomizeBoard.setString("Randomize Board");
	randomizeBoard.setCharacterSize(25);
	randomizeBoard.setOrigin(randomizeBoard.getLocalBounds().width / 2.0f, randomizeBoard.getLocalBounds().height / 2.0f);
	randomizeBoard.setPosition(view->getCenter().x + 14 * xPart, view->getCenter().y + 6 * yPart);
}

void StartMenu::exitText()
{
	exit.setFont(font);
	exit.setString("Exit Game");
	exit.setCharacterSize(25);
	exit.setOrigin(exit.getLocalBounds().width / 2.0f, exit.getLocalBounds().height / 2.0f);
	exit.setPosition(view->getCenter().x + 14 * xPart, view->getCenter().y + 10 * yPart);
}

void StartMenu::startGameHighlight()
{
	if (startGame.getGlobalBounds().contains(mousePosition)) {
		startGame.setFillColor(sf::Color::Black);
	}
	else {
		startGame.setFillColor(sf::Color::White);
	}
}

void StartMenu::leftSymbolHighlight()
{
	if (leftSymbol.getGlobalBounds().contains(mousePosition)) {
		leftSymbol.setFillColor(sf::Color::Black);
	}
	else {
		leftSymbol.setFillColor(sf::Color::White);
	}
}

void StartMenu::rightSymbolHighlight()
{
	if (rightSymbol.getGlobalBounds().contains(mousePosition)) {
		rightSymbol.setFillColor(sf::Color::Black);
	}
	else {
		rightSymbol.setFillColor(sf::Color::White);
	}
}

void StartMenu::randomizeBoardHighlight()
{
	if (randomizeBoard.getGlobalBounds().contains(mousePosition)) {
		randomizeBoard.setFillColor(sf::Color::Black);
	}
	else {
		randomizeBoard.setFillColor(sf::Color::White);
	}
}

void StartMenu::exitHighlight()
{
	if (exit.getGlobalBounds().contains(mousePosition)) {
		exit.setFillColor(sf::Color::Black);
	}
	else {
		exit.setFillColor(sf::Color::White);
	}
}

void StartMenu::updateText()
{
	std::stringstream temp;
	temp << game->getPlayerCount() << " Players";
	playerCount.setString(temp.str());
}


void StartMenu::updateMousePosition()
{
	sf::Vector2i pixelPos = sf::Mouse::getPosition(*window);
	mousePosition = window->mapPixelToCoords(pixelPos);
}
