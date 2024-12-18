#include "Catan.h"
#include <iostream>
Catan::Catan()
{
	window = new sf::RenderWindow(sf::VideoMode{ 1280,720 }, "Enes", sf::Style::Resize | sf::Style::Close);
	view = new sf::View(sf::Vector2f{ 0.0f,0.0f }, sf::Vector2{ 1280.0f, 720.0f });
	
	gameBoard = new Board(window);
	window->setFramerateLimit(60);
	initPlayers();

	setupPhase = true;
	gameBoard->setSetupPhase(true);
	placingSettlement = false;
	gameBoard->setplacingSettlement(false);
	placingRoad = true;
	gameBoard->setplacingRoad(true);
	placementStart = false;
	placementDone = false;
}

Catan::~Catan()
{
	delete window;
	delete view;
	delete gameBoard;
}

void Catan::run() {
	while (window->isOpen()) {
		
		pollEvent();

		renderGame();

		renderMenu();

		window->display();
	}
}

void Catan::pollEvent()
{
	while (window->pollEvent(event)) {
		switch (event.type) {
		case sf::Event::Closed:
			window->close();
			break;
		case sf::Event::Resized:
			resizeView();
			break;
		case sf::Event::KeyPressed:
			if (!setupPhase && event.key.code == sf::Keyboard::O) {
				// settlement
				placementStart = true;
				placingSettlement = true;
				gameBoard->setplacingSettlement(true);
				placingRoad = false;
				gameBoard->setplacingRoad(false);
				placementDone = false;
			}
			if (!setupPhase && event.key.code == sf::Keyboard::P) {
				// road
				placementStart = true;
				placingSettlement = false;
				gameBoard->setplacingSettlement(false);
				placingRoad = true;
				gameBoard->setplacingRoad(true);
				placementDone = false;
			}
			if (!setupPhase && event.key.code == sf::Keyboard::N) {
				// road
				nextTurn();
			}
			break;
		case sf::Event::MouseButtonReleased:
			if (event.mouseButton.button == sf::Mouse::Left) {
				sf::Vector2i position = sf::Mouse::getPosition(*window);
				clickPosition = window->mapPixelToCoords(position);
			}
			break;
		}
	}
}

void Catan::resizeView()
{
	float aspectRatio = static_cast<float>(window->getSize().x) / static_cast<float>(window->getSize().y);
	view->setSize(view_height * aspectRatio, view_height);
}

void Catan::renderGame()
{
	if (is_game) {
		view->setCenter(250.0f, 0.0f);
		window->setView(*view);

		gameBoard->update(currentPlayer->getID());

		if (setupPhase) {
			handleSetupPhase();
		}
		else {
			handleGamePhase();
		}
		
		// Clear window
		window->clear();

		// Draw elements
		draw();
	}
}

void Catan::renderMenu()
{
	if (is_menu) {

	}
}

void Catan::initPlayers()
{
	players.clear();

	for (int i = 0; i < playerNumber; i++) {
		players.emplace_back(i, colors[i]);
	}

	checkingSetupPhase.resize(playerNumber, 0);

	currentPlayer = &players[0];
	currentPlayerIndex = 0;
}

void Catan::handleSetupPhase()
{
	if (placingRoad) {
		if (placeRoad(clickPosition)) {
			placingRoad = false;
			gameBoard->setplacingRoad(false);
			placingSettlement = true;
			gameBoard->setplacingSettlement(true);
			clickPosition = { 0.0f, 0.0f };
			//gameBoard->setSetupPhase(false);
		}
	}
	else if (placingSettlement) {
		if (placeSettlement(clickPosition)) {
			clickPosition = { 0.0f, 0.0f };
			checkingSetupPhase[currentPlayerIndex]++;

			bool done = true;
			for (int i = 0; i < playerNumber; i++) {
				if (checkingSetupPhase[i] < 2) {
					done = false;
					break;
				}
			}

			if (done) {
				setupPhase = false;
				placingRoad = false;
				gameBoard->setplacingRoad(false);
				placingSettlement = false;
				gameBoard->setplacingSettlement(false);
				gameBoard->setSetupPhase(false);
			}
			else {
				if (checkingSetupPhase[currentPlayerIndex] < 2) {
					nextTurn();
					placingRoad = true;
					gameBoard->setplacingRoad(true);
					placingSettlement = false;
					gameBoard->setplacingSettlement(false);
					gameBoard->setSetupPhase(true);
				}
				else {
					nextTurn();
					placingRoad = true;
					gameBoard->setplacingRoad(true);
					placingSettlement = false;
					gameBoard->setplacingSettlement(false);
					gameBoard->setSetupPhase(true);
				}
			}
		}
	}
}

void Catan::handleGamePhase()
{

	if (placementStart && !placementDone) {
		if (placingSettlement) {
			if (placeSettlement(clickPosition)) {
				placingSettlement = false;
				gameBoard->setplacingSettlement(false);
				placementStart = false;
				placementDone = true;
			}
		}
		else if (placingRoad) {
			if (placeRoad(clickPosition)) {
				placingRoad = false;
				gameBoard->setplacingRoad(false);
				placementStart = false;
				placementDone = true;
				
			}
		}
	}
}

bool Catan::placeRoad(sf::Vector2f clickPosition)
{
	return gameBoard->placeRoad(&(players[currentPlayerIndex]), clickPosition);
}

bool Catan::placeSettlement(sf::Vector2f clickPosition)
{
	return gameBoard->placeSettlement(&(players[currentPlayerIndex]), clickPosition);
}


void Catan::nextTurnSetupPhase()
{
	int startIndex = currentPlayerIndex;
	do {
		currentPlayerIndex = (currentPlayerIndex + 1) % playerNumber;
		if (checkingSetupPhase[currentPlayerIndex] < 2) {
			break;
		}
	} while (currentPlayerIndex != startIndex);

	currentPlayer = &players[currentPlayerIndex];
}

void Catan::nextTurn()
{
	currentPlayerIndex = (currentPlayerIndex + 1) % playerNumber;
	currentPlayer = &players[currentPlayerIndex];
	std::cout << "Switched to player " << currentPlayerIndex << "." << std::endl;
}


void Catan::draw()
{
	gameBoard->draw();
}

void Catan::save()
{

}


const std::array<sf::Color, 4> Catan::colors = { 
	sf::Color::Red,
	sf::Color::Blue,
	sf::Color::Green,
	sf::Color::Magenta
};