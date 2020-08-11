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

    // changes currentPlayer to the next
    void nextTurn();

    void showPlayerAssets(unsigned int playerIndex) const;
    
    void buy(std::shared_ptr<Building> building);
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
