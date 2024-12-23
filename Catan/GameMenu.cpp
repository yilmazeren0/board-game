#include "GameMenu.h"
#include "Catan.h"
#include <iostream>
#include <sstream>
#include <string>

GameMenu::GameMenu(sf::RenderWindow* window, sf::View* view, Catan* game) : window{ window }, view{ view }, game{ game }
{
	xPart = window->getSize().x / 30.0f;
	yPart = window->getSize().y / 30.0f;

	is_rollDice = false;

	font.loadFromFile("font/emmasophia.ttf");

	rollDiceText();
	buildingText();
	bankText();
	deckText();
	tradeText();
	nextTurnText();
}

void GameMenu::draw()
{
	window->draw(rollDice);
	window->draw(building);
	window->draw(bank);
	window->draw(deck);
	window->draw(trade);
	window->draw(nextTurn);

}

void GameMenu::update(sf::Vector2f mousePosition)
{
	updateMousePosition();
	
	rollDiceHighlight();
	buildingHighlight();
	bankHighlight();
	deckHighlight();
	tradeHighlight();
	nextTurnHighlight();

	if (rollDice.getGlobalBounds().contains(mousePosition) && !is_rollDice) {

		game->rollDice();
		game->resetClickPosition();
		is_rollDice = true;
		std::cout << "rollDice\n";
	}
	else if (building.getGlobalBounds().contains(mousePosition)) {

		game->resetClickPosition();
		std::cout << "building\n";
	}
	else if (bank.getGlobalBounds().contains(mousePosition)) {
		
		game->resetClickPosition();
		std::cout << "bank\n";
	}
	else if (deck.getGlobalBounds().contains(mousePosition)) {
		
		game->resetClickPosition();
		std::cout << "deck\n";
	}
	else if (trade.getGlobalBounds().contains(mousePosition)) {
	
		game->resetClickPosition();
		std::cout << "trade\n";
	}
	else if (nextTurn.getGlobalBounds().contains(mousePosition)) {

		game->nextTurn();
		game->resetClickPosition();
		is_rollDice = false;
		std::cout << "nextTurn\n";
	}

}

void GameMenu::updateMousePosition()
{
	sf::Vector2i pixelPos = sf::Mouse::getPosition(*window);
	mousePosition = window->mapPixelToCoords(pixelPos);
}

void GameMenu::rollDiceText()
{
	rollDice.setFont(font);
	rollDice.setString("Roll Dice");
	rollDice.setCharacterSize(25);
	rollDice.setOrigin(rollDice.getLocalBounds().width / 2.0f, rollDice.getLocalBounds().height / 2.0f);
	rollDice.setPosition(view->getCenter().x + 11.0f * xPart, view->getCenter().y - 3.4f * yPart);
}

void GameMenu::buildingText()
{
	building.setFont(font);
	building.setString("Building");
	building.setCharacterSize(25);
	building.setOrigin(building.getLocalBounds().width / 2.0f, building.getLocalBounds().height / 2.0f);
	building.setPosition(view->getCenter().x + 10.6f * xPart, view->getCenter().y + 0 * yPart);
}

void GameMenu::bankText()
{
	bank.setFont(font);
	bank.setString("Bank");
	bank.setCharacterSize(25);
	bank.setOrigin(bank.getLocalBounds().width / 2.0f, bank.getLocalBounds().height / 2.0f);
	bank.setPosition(view->getCenter().x + 10.1f * xPart, view->getCenter().y + 3 * yPart);
}

void GameMenu::deckText()
{
	deck.setFont(font);
	deck.setString("Deck");
	deck.setCharacterSize(25);
	deck.setOrigin(deck.getLocalBounds().width / 2.0f, deck.getLocalBounds().height / 2.0f);
	deck.setPosition(view->getCenter().x + 10.2f * xPart, view->getCenter().y + 6 * yPart);
}

void GameMenu::tradeText()
{
	trade.setFont(font);
	trade.setString("Trade");
	trade.setCharacterSize(25);
	trade.setOrigin(trade.getLocalBounds().width / 2.0f, trade.getLocalBounds().height / 2.0f);
	trade.setPosition(view->getCenter().x + 10.4f * xPart, view->getCenter().y + 9 * yPart);
}

void GameMenu::nextTurnText()
{
	nextTurn.setFont(font);
	nextTurn.setString("Next Turn");
	nextTurn.setCharacterSize(25);
	nextTurn.setOrigin(nextTurn.getLocalBounds().width / 2.0f, nextTurn.getLocalBounds().height / 2.0f);
	nextTurn.setPosition(view->getCenter().x + 11.5f * xPart, view->getCenter().y + 12 * yPart);
}

void GameMenu::rollDiceHighlight()
{
	if (rollDice.getGlobalBounds().contains(mousePosition) && !is_rollDice) {
		rollDice.setFillColor(sf::Color::Black);
	}
	else {
		rollDice.setFillColor(sf::Color::White);
	}
}

void GameMenu::buildingHighlight()
{
	if (building.getGlobalBounds().contains(mousePosition)) {
		building.setFillColor(sf::Color::Black);
	}
	else {
		building.setFillColor(sf::Color::White);
	}
}

void GameMenu::bankHighlight()
{
	if (bank.getGlobalBounds().contains(mousePosition)) {
		bank.setFillColor(sf::Color::Black);
	}
	else {
		bank.setFillColor(sf::Color::White);
	}
}

void GameMenu::deckHighlight()
{
	if (deck.getGlobalBounds().contains(mousePosition)) {
		deck.setFillColor(sf::Color::Black);
	}
	else {
		deck.setFillColor(sf::Color::White);
	}
}

void GameMenu::tradeHighlight()
{
	if (trade.getGlobalBounds().contains(mousePosition)) {
		trade.setFillColor(sf::Color::Black);
	}
	else {
		trade.setFillColor(sf::Color::White);
	}
}

void GameMenu::nextTurnHighlight()
{
	if (nextTurn.getGlobalBounds().contains(mousePosition)) {
		nextTurn.setFillColor(sf::Color::Black);
	}
	else {
		nextTurn.setFillColor(sf::Color::White);
	}
}
