#ifndef GAME_HPP
#define GAME_HPP

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <vector>
// #include "../Game.cpp"
/*
    This class is kind of a Game Engine
*/

class Game {
    private:
        // Variables

        // Window
        sf::RenderWindow* window;
        sf::Event event;
        sf::VideoMode vm;

        /// Mouse positions
        sf::Vector2i mousePosWindow;
        sf::Vector2f mousePosView;
        
        // Game logic
        int points;
        float enemySpawnTimer;
        float enemySpawnTimerMax;
        int maxEnemies;

        // Game objects
        std::vector <sf::RectangleShape> enemies;
        sf::RectangleShape enemy;

        // Private functions
        void initVariables();
        void initWindow();
        void initEnemies();

    public:
        // constructor and destructor
        Game();
        virtual ~Game();

        // Accessors
        const bool running() const;

        // Functions

        ////////////////////////////////////////////////////////////
        /// \brief Adds enemy to the queue
        ///
        /// 
        ///
        /// \return void
        ///
        ////////////////////////////////////////////////////////////

        void spawnEnemy();
        void pollEvents();
        void updateMousePositions();
        void updateEnemy();
        void update();
        void renderEnemy();
        void render();
        bool contains(sf::Vector2f pos, sf::Vector2f size);
};

#endif // GAME_HPP
