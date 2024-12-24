#include "Catan.h"
#include <iostream>
Catan::Catan()
{
	window = new sf::RenderWindow(sf::VideoMode{ 1280,720 }, "Enes", sf::Style::Resize | sf::Style::Close);
	view = new sf::View(sf::Vector2f{ 0.0f,0.0f }, sf::Vector2{ 1280.0f, 720.0f });
	initPlayers();
	initTextures();
	gameBoard = new Board(window, &textures);
	startMenu = new StartMenu(window, view, this);
	gameMenu = new GameMenu(window, view, this);
	dice = new Dice(window, view, &textures, this);
	window->setFramerateLimit(60);
	
	backgroundColor = sf::Color(169, 169, 169);

	font.loadFromFile("font/emmasophia.ttf");

	setupPhase = false;
	gameBoard->setSetupPhase(false);
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
	delete startMenu;
	delete dice;
}

void Catan::run() {
	while (window->isOpen()) {
		
		pollEvent();

		updateGameState();

		window->clear(backgroundColor);

		draw();

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
				buySettlement();
			}
			if (!setupPhase && event.key.code == sf::Keyboard::P) {
				// road
				buyRoad();
			}
			if (!setupPhase && event.key.code == sf::Keyboard::N) {
				// road
				nextTurn();
			}
			if (event.key.code == sf::Keyboard::D) {
				// road
				dice->rollDice();
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

void Catan::updateGameState()
{

	view->setCenter(250.0f, 0.0f);
	window->setView(*view);

	gameBoard->update(currentPlayer->getID());
	

	currentPlayer->update();
	if (setupPhase) {
		handleSetupPhase();
	}
	else {
		handleGamePhase();
		
	}		
	
	if (is_menu) {
		startMenu->update(clickPosition);
	}
	else {
		gameMenu->update(clickPosition);
		dice->update();
	}
	
	

}


void Catan::initPlayers()
{
	players.clear();

	for (int i = 0; i < playerNumber; i++) {
		players.emplace_back(window, view, &textures, i, colors[i]);
	}

	checkingSetupPhase.resize(playerNumber, 0);

	currentPlayer = &players[0];
	currentPlayerIndex = 0;
}

void Catan::initTextures() {
	textures.clear();

	sf::Texture texture;
	texture.loadFromFile("textures/hills.png");
	textures["hills"] = texture;

	texture.loadFromFile("textures/forest.png");
	textures["forest"] = texture;

	texture.loadFromFile("textures/mountains.png");
	textures["mountains"] = texture;

	texture.loadFromFile("textures/fields.png");
	textures["fields"] = texture;

	texture.loadFromFile("textures/pasture.png");
	textures["pasture"] = texture;

	texture.loadFromFile("textures/desert.png");
	textures["desert"] = texture;

	texture.loadFromFile("textures/robber.png");
	textures["robber"] = texture;

	texture.loadFromFile("textures/dice1.png");
	textures["dice1"] = texture;

	texture.loadFromFile("textures/dice2.png");
	textures["dice2"] = texture;

	texture.loadFromFile("textures/dice3.png");
	textures["dice3"] = texture;

	texture.loadFromFile("textures/dice4.png");
	textures["dice4"] = texture;

	texture.loadFromFile("textures/dice5.png");
	textures["dice5"] = texture;

	texture.loadFromFile("textures/dice6.png");
	textures["dice6"] = texture;

	texture.loadFromFile("textures/lumber.png");
	textures["lumber"] = texture;

	texture.loadFromFile("textures/brick.png");
	textures["brick"] = texture;

	texture.loadFromFile("textures/ore.png");
	textures["ore"] = texture;

	texture.loadFromFile("textures/grain.png");
	textures["grain"] = texture;

	texture.loadFromFile("textures/wool.png");
	textures["wool"] = texture;
}

void Catan::restartBoard()
{
	initPlayers();
	delete gameBoard;
	gameBoard = new Board(window, &textures);

	checkingSetupPhase.clear();
	checkingSetupPhase.resize(playerNumber, 0);
	setupPhase = false;
	gameBoard->setSetupPhase(false);
	placingSettlement = false;
	gameBoard->setplacingSettlement(false);
	placingRoad = true;
	gameBoard->setplacingRoad(true);
	placementStart = false;
	placementDone = false;
}

void Catan::incrementPlayerCount()
{
	if (playerNumber < 4) {
		playerNumber++;
		initPlayers();
	}
}

void Catan::decrementPlayerCount()
{
	if (playerNumber > 2) {
		playerNumber--;
		initPlayers();
	}
}

int Catan::getPlayerCount() const
{
	return playerNumber;
}

bool Catan::isMenu() const
{
	return is_menu;
}

void Catan::rollDice()
{
	int diceNumber = dice->rollDice();
	gameBoard->produceResource(diceNumber);
}



void Catan::handleSetupPhase()
{
	if (placingRoad) {
		if (placeRoad(clickPosition)) {
			placingRoad = false;
			gameBoard->setplacingRoad(false);
			placingSettlement = true;
			gameBoard->setplacingSettlement(true);
			resetClickPosition();
			//gameBoard->setSetupPhase(false);
		}
	}
	else if (placingSettlement) {
		if (placeSettlement(clickPosition)) {
			resetClickPosition();
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

void Catan::resetClickPosition()
{
	clickPosition = { 0.0f, 0.0f };
}

void Catan::setMenu(bool menu)
{
	initPlayers();
	is_menu = menu;
	setupPhase = !menu;
	gameBoard->setSetupPhase(!menu);

}

void Catan::nextTurn()
{
	currentPlayerIndex = (currentPlayerIndex + 1) % playerNumber;
	currentPlayer = &players[currentPlayerIndex];
	std::cout << "Switched to player " << currentPlayerIndex << "." << std::endl;
}

void Catan::buySettlement()
{
	placementStart = true;
	placingSettlement = true;
	gameBoard->setplacingSettlement(true);
	placingRoad = false;
	gameBoard->setplacingRoad(false);
	placementDone = false;
	currentPlayer->buildSettlement();
}

void Catan::buyRoad()
{
	placementStart = true;
	placingSettlement = false;
	gameBoard->setplacingSettlement(false);
	placingRoad = true;
	gameBoard->setplacingRoad(true);
	placementDone = false;
	currentPlayer->buildRoad();
}

bool Catan::canBuildRoad() const
{
	return currentPlayer->canBuildRoad();
}

bool Catan::canBuildSettlement() const
{
	return currentPlayer->canBuildRoad();
}


void Catan::draw()
{
	gameBoard->draw();

	if (is_menu) {
		startMenu->draw();
	}
	else {

		currentPlayer->draw();
		if (!setupPhase) {
			gameMenu->draw();
			dice->draw();
		}
		
		
	}
	
}

void Catan::save()
{

}

const std::array<sf::Color, 4> Catan::colors = { 
	sf::Color::Red,
	sf::Color::Blue,
	sf::Color::Green,
	sf::Color(106, 13, 173),//purple
};