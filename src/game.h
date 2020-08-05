#ifndef GAME_H
#define GAME_H

#include "types.h"

class Graphics;
class InputManager;
class Square;
class Building;
class Player;

class Game {
    GameState state;
    std::shared_ptr<Graphics> gfx;
    std::shared_ptr<InputManager> events;
    std::vector<std::shared_ptr<Square>> squares;
    std::vector<std::shared_ptr<Player>> players;
    unsigned int currentPlayer;

    // changes currentPlayer to the next
    void nextTurn();
    
    void buy(std::shared_ptr<Building> building);
    void auction(std::shared_ptr<Building> building);
    void trade();

    void saveGame();
    void loadGame();
public:
    Game();

    bool loop() const;

    // initialization
    void init();

    // deal with user inputs
    void processInput();

    // update game logic
    void update();

    // render the board
    void render();
};

#endif
