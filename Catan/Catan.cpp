#include "Catan.h"
#include <iostream>

Catan::Catan() {
	// Existing initialization
	window = new sf::RenderWindow(sf::VideoMode{ 1280,720 }, "Catan Game",
		sf::Style::Resize | sf::Style::Close);
	view = new sf::View(sf::Vector2f{ 0.0f,0.0f }, sf::Vector2{ 1280.0f, 720.0f });

	initPlayers();
	initTextures();
	initDevelopmentCards();

	gameBoard = new Board(window, &textures);
	startMenu = new StartMenu(window, view, this);
	gameMenu = new GameMenu(window, view, this);
	tradeMenu = new TradeMenu(window, view, this); 
	dice = new Dice(window, view, &textures, this);
	bankMenu = new BankMenu(window, view, this);

	window->setFramerateLimit(60);
	backgroundColor = sf::Color(169, 169, 169);

	if (!font.loadFromFile("font/emmasophia.ttf")) {
		throw std::runtime_error("Failed to load font");
	}

	// Game state initialization
	setupPhase = false;
	gameBoard->setSetupPhase(false);
	placingSettlement = false;
	gameBoard->setplacingSettlement(false);
	placingRoad = true;
	gameBoard->setplacingRoad(true);
	placementStart = false;
	placementDone = false;
}
Catan::~Catan() {
	delete window;
	delete view;
	delete gameBoard;
	delete startMenu;
	delete gameMenu;
	delete tradeMenu; // Clean up trade menu
	delete dice;
	delete bankMenu;
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

void Catan::updateGameState() {
	view->setCenter(250.0f, 0.0f);
	window->setView(*view);

	gameBoard->update(currentPlayer->getID());
	currentPlayer->update();

	if (gameOver) return;

	if (setupPhase) {
		handleSetupPhase();
	}
	else {
		handleGamePhase();
	}

	if (is_menu) {
		startMenu->update(clickPosition);
	}
	else if (isTrading) {
		tradeMenu->update(clickPosition);
		dice->update();
	}
	else if (isBankTrade) {  // Add this condition
		bankMenu->update(clickPosition);
		dice->update();
	}
	else {
		gameMenu->update(clickPosition);
		dice->update();
	}
}

void Catan::setBankTrading(bool trading) {
	isBankTrade = trading;  // Fix the implementation to actually set the value
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

#include <random>
#include <algorithm>

// Inside Catan.cpp:
void Catan::initDevelopmentCards() {
	developmentCards.clear();

	// Add Knight cards (14)
	for (int i = 0; i < 14; i++) {
		developmentCards.push_back(Card::Knight);
	}

	// Add Progress cards (2 each)
	for (int i = 0; i < 2; i++) {
		developmentCards.push_back(Card::RoadBuilding);
		developmentCards.push_back(Card::YearOfPlenty);
		developmentCards.push_back(Card::Monopoly);
	}

	// Add Victory Point cards (5 total)
	for (int i = 0; i < 5; i++) {
		developmentCards.push_back(Card::VictoryPoint);
	}

	// Create random number generator
	std::random_device rd;
	std::mt19937 gen(rd());

	// Shuffle the deck using std::shuffle
	std::shuffle(developmentCards.begin(), developmentCards.end(), gen);
}


void Catan::giveRandomCard() {
	if (developmentCards.empty()) {
		std::cout << "No development cards left in the deck!" << std::endl;
		return;
	}

	if (!currentPlayer->canBuyDevelopmentCard()) {
		std::cout << "Not enough resources to buy a development card!" << std::endl;
		return;
	}

	// Take card from the deck
	Card card = developmentCards.back();
	developmentCards.pop_back();

	// Deduct resources and give card to player
	currentPlayer->buyDevelopmentCard();
	currentPlayer->addCard(card);

	std::cout << "Player " << currentPlayer->getID() + 1 << " bought a development card!" << std::endl;
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

		//warning for place robber
		sf::Text warningText;
		warningText.setFont(font);
		warningText.setString("7 Rolled! Place the Robber");
		warningText.setCharacterSize(30);
		warningText.setFillColor(sf::Color::Red);
		warningText.setPosition(view->getCenter().x, view->getCenter().y - 200);
		window->draw(warningText);
		window->display();
		sf::sleep(sf::seconds(2));

		// Handle resource discarding for players with more than 7 cards
		for (auto& player : players) {
			int totalResources = player.getTotalResources();
			if (totalResources > 7) {
				int discard = totalResources / 2;
				player.discardResources(discard);
			}
		}
		return; // fix automatic robber placement
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
			Hex* robberHex = gameBoard->getRobberHex();
			if (robberHex) {
				std::vector<Player*> victims = gameBoard->getPlayersAtHex(robberHex);

				// Remove current player from victims
				victims.erase(std::remove_if(victims.begin(), victims.end(),
					[this](Player* p) { return p->getID() == currentPlayer->getID(); }),
					victims.end());

				// Handle stealing
				if (!victims.empty()) {
					int victimIndex = rand() % victims.size();
					Player* victim = victims[victimIndex];
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
			// Reset click position after placement
			resetClickPosition();
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
	if (gameBoard->placeSettlement(&(players[currentPlayerIndex]), clickPosition)) {
		currentPlayer->incrementVictoryPoints();
		return true;
	}
	return false;
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
	clickPosition = sf::Vector2f(-1, -1);
}

void Catan::setMenu(bool menu)
{
	initPlayers();
	is_menu = menu;
	setupPhase = !menu;
	gameBoard->setSetupPhase(!menu);

}

void Catan::nextTurn() {
	currentPlayerIndex = (currentPlayerIndex + 1) % playerNumber;
	currentPlayer = &players[currentPlayerIndex];
	// Clear the list of newly purchased cards from previous turn
	players[currentPlayerIndex].clearNewlyPurchasedCards();
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

void Catan::draw() {
	gameBoard->draw();

	if (is_menu) {
		startMenu->draw();
	}
	else {
		currentPlayer->draw();
		currentPlayer->drawCardUI();
		drawVictoryPoints();

		if (!setupPhase) {
			if (isTrading) {
				tradeMenu->draw();
			}
			else if (isBankTrade) {
				bankMenu->draw();
			}
			else {
				gameMenu->draw();
			}
			dice->draw();
		}
	}
}

//Trade functions

void Catan::initiateTrade(int target) {
	if (target != currentPlayerIndex) {
		tradingPlayer = currentPlayerIndex;
		targetPlayer = target;
		isTrading = true;
	}
}
bool Catan::proposeTrade(int target, const std::map<ResourceType, int>& offer,
	const std::map<ResourceType, int>& request) {
	tradingPlayer = getCurrentPlayerIndex();
	targetPlayer = target;
	tradeOffer = offer;
	tradeRequest = request;
	isTrading = true;
	return true;
}

void Catan::acceptTrade() {
	if (!isTrading) return;

	Player* currentTrader = &players[tradingPlayer];
	Player* targetTrader = &players[targetPlayer];

	// Verify resources are available
	for (const auto& [resource, count] : tradeOffer) {
		if (currentTrader->getResourceCount(resource) < count) {
			return; // Trade failed - insufficient resources
		}
	}

	// Execute the trade
	for (const auto& [resource, count] : tradeOffer) {
		currentTrader->removeResource(resource, count);
		targetTrader->addResource(resource, count);
	}

	for (const auto& [resource, count] : tradeRequest) {
		targetTrader->removeResource(resource, count);
		currentTrader->addResource(resource, count);
	}

	isTrading = false;
}

void Catan::declineTrade() {
	isTrading = false;
}

bool Catan::bankTrade(ResourceType giveResource, ResourceType getResource, int giveAmount) {
	// Check if player has enough resources
	if (currentPlayer->getResourceCount(giveResource) >= giveAmount) {
		// Execute the trade
		currentPlayer->removeResource(giveResource, giveAmount);
		currentPlayer->addResource(getResource, 1);
		return true;
	}
	return false;
}

bool Catan::isBankTrading() const
{
	return isBankTrade;
}

Player* Catan::getCurrentPlayer() {
	return currentPlayer;
}

Player* Catan::getPlayer(int playerIndex)
{
	return &players[playerIndex];
}

int Catan::getCurrentPlayerIndex() const {
	return currentPlayerIndex;
}

void Catan::setTrading(bool trading)
{
	isTrading = trading;
}

bool Catan::getTrading() const
{
	return isTrading;
}

const std::array<sf::Color, 4> Catan::colors = { 
	sf::Color::Red,
	sf::Color::Blue,
	sf::Color::Green,
	sf::Color(106, 13, 173),//purple
};