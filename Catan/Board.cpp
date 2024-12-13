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
	for (auto hexIterator = hexes.begin(); hexIterator != hexes.end();) {

		(*hexIterator).update();
		++hexIterator;
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
	for (int i = 0; i < 11; i++) {
		edges.emplace_back(window, i);
	}
	
}
