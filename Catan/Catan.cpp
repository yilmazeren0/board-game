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

				// Handle card clicks
				Card clickedCard = currentPlayer->handleCardClick(clickPosition);
				if (clickedCard != Card::None) {
					handleCardUse(clickedCard);
				}
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

	if (gameOver) {
		// Optionally handle game over state
		// For example, disable further actions
		return;
	}

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

void Catan::drawVictoryPoints() {
	// Create text for each player's victory points
	for (int i = 0; i < playerNumber; i++) {
		sf::Text pointsText;
		pointsText.setFont(font);

		std::string pointsStr = "Player " + std::to_string(i + 1) +
			": " + std::to_string(players[i].getVictoryPoints()) + " VP";
		
		pointsText.setString(pointsStr);
		pointsText.setCharacterSize(20);
		pointsText.setFillColor(colors[i]);
		pointsText.setPosition(view->getCenter().x + 390.0f,
			view->getCenter().y - 340.0f + (i * 30.0f));
		window->draw(pointsText);

		// Check for winner
		if (players[i].getVictoryPoints() >= 10 && !gameOver) {
			gameOver = true;
			winningPlayer = i;
		}
	}

	// Display winner message if game is over
	if (gameOver) {
		sf::Text winText;
		winText.setFont(font);

		// Create winner message
		std::string winStr = "Player " + std::to_string(winningPlayer + 1) +
			" Wins!\n" + std::to_string(players[winningPlayer].getVictoryPoints()) +
			" Victory Points";
		winText.setString(winStr);
		winText.setCharacterSize(50);
		winText.setFillColor(colors[winningPlayer]);

		// Center the text
		winText.setOrigin(winText.getGlobalBounds().width / 2.0f,
			winText.getGlobalBounds().height / 2.0f);
		winText.setPosition(view->getCenter().x, view->getCenter().y);

		window->draw(winText);
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

	initSetupOrder();
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

	texture.loadFromFile("textures/knight.png");
	textures["knight"] = texture;

	texture.loadFromFile("textures/year_of_plenty.png");
	textures["year_of_plenty"] = texture;

	texture.loadFromFile("textures/road_building.png");
	textures["road_building"] = texture;

	texture.loadFromFile("textures/monopoly.png");
	textures["monopoly"] = texture;

	texture.loadFromFile("textures/victory_point.png");
	textures["victory_point"] = texture;

	texture.loadFromFile("textures/longest_road.png");
	textures["longest_road"] = texture;

	texture.loadFromFile("textures/largest_army.png");
	textures["largest_army"] = texture;
}
void Catan::giveRandomCard() {
	// Random card selection
	int cardType = rand() % 5;
	Card card;

	switch (cardType) {
	case 0: card = Card::Knight; break;
	case 1: card = Card::YearOfPlenty; break;
	case 2: card = Card::RoadBuilding; break;
	case 3: card = Card::Monopoly; break;
	case 4: card = Card::VictoryPoint; break;
	}

	currentPlayer->addCard(card);
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

void Catan::rollDice() {
	int diceNumber = dice->rollDice();

	if (diceNumber == 7) {
		// Enable robber placement mode
		placingRobber = true;
		// Set the current state to handle robber placement
		currentPlayer->setMustMoveRobber(true);

		// Handle resource discarding for players with more than 7 cards
		for (auto& player : players) {
			int totalResources = player.getTotalResources();
			if (totalResources > 7) {
				int discard = totalResources / 2;
				player.discardResources(discard);
			}
		}
	}
	else {
		// Normal resource production
		gameBoard->produceResource(diceNumber);
	}
}

void Catan::handleCardUse(Card card) {
	switch (card) {
	case Card::Knight:
		if (currentPlayer->useKnightCard()) {
			placingRobber = true;
			updateLargestArmy();  // Add this line
		}
		break;

	case Card::YearOfPlenty:
		if (currentPlayer->useYearOfPlentyCard(ResourceType::LUMBER, ResourceType::BRICK)) {
			// Show resource selection UI
			selectingResource = true;
		}
		break;

	case Card::RoadBuilding:
		if (currentPlayer->useRoadBuildingCard()) {
			placingFreeRoad = true;
			freeRoadsRemaining = 1;
			placingRoad = true;
			gameBoard->setplacingRoad(true);
			placementStart = true;
			placementDone = false;
			// Don't deduct resources since these roads are free
		}
		break;

	case Card::Monopoly:
		if (currentPlayer->useMonopolyCard(selectedResource)) {
			// Collect all of one resource type from other players
			for (auto& player : players) {
				if (&player != currentPlayer) {
					int amount = player.getResourceCount(selectedResource);
					player.removeResource(selectedResource, amount);
					currentPlayer->addResource(selectedResource, amount);
				}
			}
		}
		break;

	case Card::VictoryPoint:
		currentPlayer->useVictoryPointCard();
		break;
	}
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
				nextTurnSetupPhase();
				placingRoad = true;
				gameBoard->setplacingRoad(true);
				placingSettlement = false;
				gameBoard->setplacingSettlement(false);
				gameBoard->setSetupPhase(true);
				
			}
		}
	}
}

void Catan::handleGamePhase() {
	if (placingRobber) {
		if (gameBoard->placeRobber(clickPosition)) {
			// Get the hex where robber was placed
			Hex* robberHex = gameBoard->getRobberHex();
			if (robberHex) {
				// Get all players who have settlements/cities adjacent to this hex
				std::vector<Player*> victims = gameBoard->getPlayersAtHex(robberHex);

				// Remove current player from potential victims
				victims.erase(std::remove_if(victims.begin(), victims.end(),
					[this](Player* p) { return p->getID() == currentPlayer->getID(); }),
					victims.end());

				// If there are victims, steal from one at random
				if (!victims.empty()) {
					int victimIndex = rand() % victims.size();
					Player* victim = victims[victimIndex];

					// Steal a random resource
					if (victim->hasResources()) {
						ResourceType stolenResource = victim->getRandomResource();
						victim->removeResource(stolenResource, 1);
						currentPlayer->addResource(stolenResource, 1);
					}
				}
			}

			// Reset robber placement state
			placingRobber = false;
			currentPlayer->setMustMoveRobber(false);
		}
	}
	if (placingFreeRoad && freeRoadsRemaining > 0) {
		if (placeRoad(clickPosition)) {
			freeRoadsRemaining--;
			if (freeRoadsRemaining == 0) {
				placingFreeRoad = false;
			}
		}
	}
	else if (placementStart && !placementDone) {
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

void Catan::updateLongestRoad() {
	int maxRoadLength = 4;  // Minimum requirement is 5, so start at 4
	Player* newHolder = nullptr;

	// Check each player's connected road length
	for (auto& player : players) {
		int connectedRoadLength = gameBoard->getLongestRoadLength(player.getID());
		if (connectedRoadLength > maxRoadLength) {
			maxRoadLength = connectedRoadLength;
			newHolder = &player;
		}
	}

	// Update longest road holder if necessary
	if (newHolder != longestRoadHolder) {
		if (longestRoadHolder) {
			longestRoadHolder->setLongestRoad(false);
		}
		if (newHolder && maxRoadLength >= 5) {
			newHolder->setLongestRoad(true);
			longestRoadHolder = newHolder;
		}
	}
}

void Catan::updateLargestArmy() {
	int maxKnights = 2;  // Minimum requirement is 3 knights, so start at 2
	Player* newHolder = nullptr;

	// Check each player's knight count
	for (auto& player : players) {
		int knightCount = player.getKnightsPlayed();
		if (knightCount > maxKnights) {
			maxKnights = knightCount;
			newHolder = &player;
		}
	}

	// Update largest army holder if necessary
	if (newHolder != largestArmyHolder) {
		if (largestArmyHolder) {
			largestArmyHolder->setLargestArmy(false);
		}
		if (newHolder && maxKnights >= 3) {
			newHolder->setLargestArmy(true);
			largestArmyHolder = newHolder;
		}
	}
}

bool Catan::placeRoad(sf::Vector2f clickPosition) {
	if (gameBoard->placeRoad(&(players[currentPlayerIndex]), clickPosition)) {
		currentPlayer->incrementRoadCount();
		updateLongestRoad();  // Check if longest road needs to be updated
		return true;
	}
	return false;
}


bool Catan::placeSettlement(sf::Vector2f clickPosition)
{
	return gameBoard->placeSettlement(&(players[currentPlayerIndex]), clickPosition);
}

void Catan::initSetupOrder()
{
	setupOrder.clear();

	for (int i = 0; i < playerNumber; i++) {
		setupOrder.push_back(i);
	}

	for (int i = playerNumber - 1; i >= 0; i--) {
		setupOrder.push_back(i);
	}

	setupIndex = 0;
}

void Catan::nextTurnSetupPhase()
{
	setupIndex++;

	if (setupIndex >= (int)setupOrder.size()) {
		return;
	}

	currentPlayerIndex = setupOrder[setupIndex];
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

void Catan::buyRoad() {
    if (!placingFreeRoad) {  // Only deduct resources if not placing free roads
        currentPlayer->buildRoad();
    }
    placementStart = true;
    placingSettlement = false;
    gameBoard->setplacingSettlement(false);
    placingRoad = true;
    gameBoard->setplacingRoad(true);
    placementDone = false;
}

bool Catan::canBuildRoad() const
{
	return currentPlayer->canBuildRoad();
}

bool Catan::canBuildSettlement() const
{
	return currentPlayer->canBuildSettlement();
}

void Catan::draw()
{
	gameBoard->draw();

	if (is_menu) {
		startMenu->draw();
	}
	else {
		currentPlayer->draw();
		currentPlayer->drawCardUI();
		drawVictoryPoints(); 
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