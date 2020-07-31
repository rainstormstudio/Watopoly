#ifndef GAME_H
#define GAME_H

#include "types.h"

class Graphics;
class InputManager;
class Player;

class Game {
    GameState state;
    Graphics gfx;
    InputManager events;
    std::vector<std::shared_ptr<Player>> players;
    unsigned int currentPlayer;
public:
    Game();

    bool loop() const;
    void init();

    void processInput();
    void update();
    void render();
};

#endif
