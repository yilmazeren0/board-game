#include "Board.h"

Board::Board(sf::RenderWindow* window)
{
	this->window = window;
	initBoard();
}

Board::~Board()
{
}

void Board::update()
{
	updateMousePosition();

	for (auto hexIterator = hexes.begin(); hexIterator != hexes.end();) {

		(*hexIterator).update();
		++hexIterator;
	}
	for (auto edgeIterator = edges.begin(); edgeIterator != edges.end();) {

		(*edgeIterator).update(mousePosition);
		++edgeIterator;
	}

}

void Board::draw()
{
	for (auto hexIterator = hexes.begin(); hexIterator != hexes.end();) {

		(*hexIterator).draw();
		++hexIterator;
	}
	for (auto edgeIterator = edges.begin(); edgeIterator != edges.end();) {

		(*edgeIterator).draw();
		++edgeIterator;
	}
}

void Board::initBoard()
{
	for (int i = 0; i < 19; i++) {
		hexes.emplace_back(window, i);
	}
	for (int i = 0; i < 72; i++) {
		edges.emplace_back(window, i);
	}
	
}

void Board::updateMousePosition() {
	sf::Vector2i pixelPos = sf::Mouse::getPosition(*window);
	mousePosition = window->mapPixelToCoords(pixelPos);
}