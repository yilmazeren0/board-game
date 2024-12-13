#include "Catan.h"
#include <iostream>
Catan::Catan()
{
	window = new sf::RenderWindow(sf::VideoMode{ 1280,720 }, "Enes", sf::Style::Resize | sf::Style::Close);
	view = new sf::View(sf::Vector2f{ 0.0f,0.0f }, sf::Vector2{ 1280.0f, 720.0f });
	
	gameBoard = new Board(window);
	window->setFramerateLimit(60);
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

void Catan::initBoard()
{

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
		view->setCenter(0.0f, 0.0f);
		window->setView(*view);
		//update
		gameBoard->update();

		//clear
		window->clear();
		// DRAW
		draw();
	}
}

void Catan::renderMenu()
{
	if (is_menu) {

	}
}

void Catan::draw()
{
	gameBoard->draw();
}
