#include "Game.hpp"
#include <iostream>
#include <ctime>
#include <string>

// Private functions
void Game::initVariables() {
	this->window = nullptr;
	int points;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;

	this->points = 0;
	this->enemySpawnTimerMax = 100.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->maxEnemies = 5;
}

void Game::initWindow() {
	this->vm.width = 800;
	this->vm.height = 600;
	
	this->window = new sf::RenderWindow(this->vm, "Game", sf::Style::Default);

	this->window->setFramerateLimit(60);
}

void Game::initEnemies(){
	// this->enemy.setPosition(this->vm.width/2,this->vm.height/2);
	this->enemy.setSize(sf::Vector2f(50.0f,50.0f));
	// this->enemy.setScale(sf::Vector2f(0.);
	this->enemy.setFillColor(sf::Color(255, 126, 41));
	this->enemy.setOutlineColor(sf::Color(255, 126, 41));
	this->enemy.setOutlineThickness(1.0f);
}

// Constructors / Destructors
Game::Game() {
	this->initVariables();
	this->initWindow();
	this->initEnemies();
}

Game::~Game() {
	delete this->window;
}

//Functions

//Accessors
const bool Game::running() const {
	return this->window->isOpen();
}

void Game::pollEvents() {
	//Event polling
	while (this->window->pollEvent(this->event)) {
		switch (this->event.type) {
			case sf::Event::Closed:
				this->window->close();
				break;
			case sf::Event::KeyPressed:
				if(this->event.key.code == sf::Keyboard::Escape)
					this->window->close();
				break;
		}
	}
}

void Game::spawnEnemy() {
	this->enemy.setPosition(
		static_cast<float>(rand()%static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
		-60
	);
	// Color the enemy
	this->enemy.setFillColor(sf::Color(25, 189, 33));
	// Spawn the enemy
	this->enemies.push_back(this->enemy);
}   

// UPDATE:
bool Game::contains(sf::Vector2f pos, sf::Vector2f size) {
	if(mousePosView.x >= pos.x && mousePosView.y >= pos.y && 
		mousePosView.x <= pos.x + size.x && mousePosView.y <= pos.y + size.y) {
		return true;
	}
	return false;
}

void Game::updateMousePositions() {
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::updateEnemy() {
	if (this->enemies.size() < this->maxEnemies)
	{
		if(enemySpawnTimer >= enemySpawnTimerMax) {
			this->spawnEnemy();
			enemySpawnTimer = 0.f;
		}
		else {
			enemySpawnTimer +=1.0f;
		}
	}	

	//Move enemies
	for (int i = 0; i < this->enemies.size(); i++) {
		bool deleted = false;
		this->enemies[i].move(0.f,1.f);
		// Check if clicked upon
		if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			if(contains(enemies[i].getPosition(), enemies[i].getSize())) {
				deleted = true;
			}
		}
	
		if(deleted) {
			this->enemies.erase(enemies.begin() + i);
		}
	}
}

void Game::update() {
	this->pollEvents();
	this->updateMousePositions();
	this->updateEnemy();
}

// RENDER
void Game::renderEnemy() {
	sf::Font font1;
	if (!font1.loadFromFile("arial.ttf"))
	{
		// error...
	}

	sf::Text text;
	sf::Color clr (246, 255, 0);
	text.setFont(font1);
	text.setFillColor(clr);
	text.setStyle(sf::Text::Regular);
	text.setCharacterSize(10);

	for (auto &&e : enemies) {
		sf::Vector2f pos = e.getPosition();
		std::string x = std::to_string((int)pos.x);
		std::string y = std::to_string((int)pos.y);
		text.setString(x + ", " + y);
		text.setPosition(e.getPosition());
		this->window->draw(e);
		this->window->draw(text);
		sf::FloatRect bounds = e.getLocalBounds();
		// if(bounds.)
	}
}

void Game::render() {
	this->window->clear(sf::Color(40, 49, 79));

	// Draw game
	this->renderEnemy();

	this->window->display();
}