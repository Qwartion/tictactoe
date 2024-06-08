/**
 *  This is example of game, that you can use for debugging.
 */
#include <cstdlib>
#include <ctime>
#include <iostream>

#include "Random.h"
#include "my_player.h"
#include "silly_player.hpp"
#include "game_engine.h"


int main() {
    srand(time(NULL));

    /// Creates observer to log every event to std::cout
    BasicObserver obs(std::cout);

    /// Create setting for game
    GameSettings settings = {
        .field_size = {
            .min = {.x = -7, .y = -7},
            .max = {.x = 7, .y = 7},
        },
        .max_moves = 0,
        .win_length = 5,
        .move_timelimit_ms = 0,
    };
    
    for (int i = 0; i < 100; i++)
    {


        /// Creates game engine with given settings
        GameEngine game(settings);

        /// Adds observer to the view of this game engine
        game.get_view().add_observer(obs);
        /// Creates first player

        RandomPlayer player1("Vasya");
        SimplePlayer pl1("Alfa");
        MyPlayer MyBot("BOOOT");
        MyPlayer Bot("bot2");

        /// Create second player
        RandomPlayer player2("Kolya");
        SimplePlayer pl2("Beta");
        /// Adds it to play Xs
        game.set_player(pl1);
        /// Adds it to play Os
        game.set_player(MyBot);
        /// Starts game until someone wins.
        game.play_game();
    }
    std::cout << "Win X : " << winX << "\nWin O : " << winO << "\nDraw : " << draw <<"\n";
    return 0;
}
