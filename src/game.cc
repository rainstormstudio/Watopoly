#include "game.h"
#include "graphics.h"
#include "inputManager.h"

Game::Game() {
    state = NO_GAME;
    currentPlayer = 0;
}

bool Game::loop() const { return state != NO_GAME; }

void Game::init() {
    gfx = std::make_shared<Graphics>(101, 56);
    events = std::make_shared<InputManager>();

    state = IN_GAME;
}

void Game::processInput() {
    switch (state) {
        case NO_GAME: {
            break;
        }
        case IN_GAME: {
            if (!events->readLine()) {
                state = NO_GAME;
            }
            break;
        }
        case WON_GAME: {
            break;
        }
        case LOST_GAME: {
            break;
        }
    }
    
}

void Game::update() {
    switch (state) {
        case NO_GAME: {
            break;
        }
        case IN_GAME: {
            break;
        }
        case WON_GAME: {
            break;
        }
        case LOST_GAME: {
            break;
        }
    }
}

void Game::render() {
    switch (state) {
        case NO_GAME: {
            break;
        }
        case IN_GAME: {
            gfx->clear();
            gfx->drawImage("./assets/gameboard.txt");
            /*
            for (auto &square : squares) {
                square->render(*gfx);
            }
            */
            gfx->render();
            break;
        }
        case WON_GAME: {
            break;
        }
        case LOST_GAME: {
            break;
        }
    }
    
}
