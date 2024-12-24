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
	is_buildingMenu = false;

	font.loadFromFile("font/emmasophia.ttf");

	rollDiceText();
	buildingText();
	bankText();
	deckText();
	tradeText();
	nextTurnText();

	backText();

	buildingBuyRoadText();
	buildingBuySettlementText();
}

void GameMenu::draw()
{
	if (is_buildingMenu) {
		window->draw(back);
		window->draw(buildingBuyRoad);
		window->draw(buildingBuySettlement);
	}
	else {
		window->draw(rollDice);
		window->draw(building);
		window->draw(bank);
		window->draw(deck);
		window->draw(trade);
		window->draw(nextTurn);
	}

}

void GameMenu::update(sf::Vector2f mousePosition)
{
	updateMousePosition();
	
	if (!is_rollDice) {
		rollDiceHighlight();
	}
	else {
		buildingHighlight();
		bankHighlight();
		deckHighlight();
		tradeHighlight();
		nextTurnHighlight();

		backHighlight();
		buildingBuyRoadHighlight();
		buildingBuySettlementHighlight();
	}

	if (is_buildingMenu) {

		if (back.getGlobalBounds().contains(mousePosition)) {

			game->resetClickPosition();
			is_buildingMenu = false;
			back.setFillColor(sf::Color::White);
			std::cout << "back\n";
		}

		else if (buildingBuyRoad.getGlobalBounds().contains(mousePosition) && game->canBuildRoad()) {
			
			game->resetClickPosition();
			game->buyRoad();
			buildingBuyRoad.setFillColor(sf::Color::White);
			std::cout << "buildingBuyRoad\n";
		}

		else if (buildingBuySettlement.getGlobalBounds().contains(mousePosition) && game->canBuildSettlement()) {

			game->resetClickPosition();
			game->buySettlement();
			buildingBuySettlement.setFillColor(sf::Color::White);
			std::cout << "buildingBuySettlement\n";
		}
	}
	else {
		if (!is_rollDice) {
			if (rollDice.getGlobalBounds().contains(mousePosition)) {

				game->rollDice();
				game->resetClickPosition();
				is_rollDice = true;
				rollDice.setFillColor(sf::Color::White);
				std::cout << "rollDice\n";
			}
		}
		else {
			if (building.getGlobalBounds().contains(mousePosition)) {

				is_buildingMenu = true;
				game->resetClickPosition();
				building.setFillColor(sf::Color::White);
				std::cout << "building\n";
			}
			else if (bank.getGlobalBounds().contains(mousePosition)) {

				game->resetClickPosition();
				bank.setFillColor(sf::Color::White);
				std::cout << "bank\n";
			}
			else if (deck.getGlobalBounds().contains(mousePosition)) {

				game->resetClickPosition();
				deck.setFillColor(sf::Color::White);
				std::cout << "deck\n";
			}
			else if (trade.getGlobalBounds().contains(mousePosition)) {

				game->resetClickPosition();
				trade.setFillColor(sf::Color::White);

				std::cout << "trade\n";
			}
			else if (nextTurn.getGlobalBounds().contains(mousePosition)) {

				game->nextTurn();
				game->resetClickPosition();
				nextTurn.setFillColor(sf::Color::White);
				is_rollDice = false;
				std::cout << "nextTurn\n";
			}
		}
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

void GameMenu::backText()
{
	back.setFont(font);
	back.setString("Back");
	back.setCharacterSize(25);
	back.setOrigin(back.getLocalBounds().width / 2.0f, back.getLocalBounds().height / 2.0f);
	back.setPosition(view->getCenter().x + 10.2f * xPart, view->getCenter().y + 0 * yPart);
}

void GameMenu::buildingBuyRoadText()
{
	buildingBuyRoad.setFont(font);
	buildingBuyRoad.setString("Buy Road");
	buildingBuyRoad.setCharacterSize(25);
	buildingBuyRoad.setOrigin(buildingBuyRoad.getLocalBounds().width / 2.0f, buildingBuyRoad.getLocalBounds().height / 2.0f);
	buildingBuyRoad.setPosition(view->getCenter().x + 11.3f * xPart, view->getCenter().y + 3 * yPart);
}

void GameMenu::buildingBuySettlementText()
{
	buildingBuySettlement.setFont(font);
	buildingBuySettlement.setString("Buy Settlement");
	buildingBuySettlement.setCharacterSize(25);
	buildingBuySettlement.setOrigin(buildingBuySettlement.getLocalBounds().width / 2.0f, buildingBuySettlement.getLocalBounds().height / 2.0f);
	buildingBuySettlement.setPosition(view->getCenter().x + 12.6f * xPart, view->getCenter().y + 6 * yPart);
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

void GameMenu::backHighlight()
{
	if (back.getGlobalBounds().contains(mousePosition)) {
		back.setFillColor(sf::Color::Black);
	}
	else {
		back.setFillColor(sf::Color::White);
	}
}

void GameMenu::buildingBuyRoadHighlight()
{
	if (buildingBuyRoad.getGlobalBounds().contains(mousePosition) && game->canBuildRoad()) {
		buildingBuyRoad.setFillColor(sf::Color::Black);
	}
	else {
		buildingBuyRoad.setFillColor(sf::Color::White);
	}
}

void GameMenu::buildingBuySettlementHighlight()
{
	if (buildingBuySettlement.getGlobalBounds().contains(mousePosition) && game->canBuildSettlement()) {
		buildingBuySettlement.setFillColor(sf::Color::Black);
	}
	else {
		buildingBuySettlement.setFillColor(sf::Color::White);
	}
}
