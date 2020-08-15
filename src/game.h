#ifndef GAME_H
#define GAME_H

#include "types.h"

class Graphics;
class InputManager;
class Square;
class Building;
class Player;

class Game {
    GameMode mode;
    std::shared_ptr<SaveData> data;
    GameState state;
    std::shared_ptr<Graphics> gfx;
    std::shared_ptr<InputManager> events;
    std::vector<std::shared_ptr<Square>> squares;
    std::vector<std::shared_ptr<Player>> players;
    unsigned int currentPlayer;
    unsigned int bank = 500;

    unsigned int rollNum = 0;

    bool monopolyHasImprovement(std::shared_ptr<Building> building);

    // changes currentPlayer to the next
    void nextTurn();

    void showPlayerAssets(unsigned int playerIndex) const;
    
    void auction(std::shared_ptr<Building> building);
    void trade();

    void saveGame(std::string filename);
    void loadGame(std::string filename);
public:
    Game(GameMode mode, std::string loadFile);

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
