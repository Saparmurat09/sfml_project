#include "ge/Game.hpp"
#include "ge/Game.cpp"

int main()
{
    // sf::RenderWindow window(sf::VideoMode(800,600), "Game", sf::Style::Default);
    // sf::Event event;

    // Init srand
    std::srand(static_cast<unsigned>(time(NULL)));
    //Init game engine
    Game game;

    // Game loop
    while(game.running()) {       
        //Update
        game.update(); 
        // Render
        game.render();
    }
    // end of application
}