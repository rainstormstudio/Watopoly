#include "game.h"
#include "graphics.h"
#include "inputManager.h"
#include "square.h"
#include "building.h"
#include "buildingList.h"
#include "nonProperty.h"
#include "nonPropertiesList.h"

void Game::nextTurn() {
    currentPlayer = (currentPlayer + 1) % players.size();
}

Game::Game() {
    state = NO_GAME;
    currentPlayer = 0;
}

bool Game::loop() const { return state != NO_GAME; }

void Game::init() {
    gfx = std::make_shared<Graphics>(101, 56);
    events = std::make_shared<InputManager>();

    squares.emplace_back(std::make_shared<Academics>(Vec2(82, 51), "AL", 40, "Arts1",    50,  2, 10, 30, 90, 160, 250));
    squares.emplace_back(std::make_shared<Academics>(Vec2(64, 51), "ML", 60, "Arts1",    50,  4, 20, 60, 180, 320, 450));
    squares.emplace_back(std::make_shared<Residence>(Vec2(46, 51), "MKV", 200));
    squares.emplace_back(std::make_shared<Academics>(Vec2(37, 51), "ECH", 100, "Arts2",  50,  6, 30, 90, 270, 400, 550));
    squares.emplace_back(std::make_shared<Academics>(Vec2(19, 51), "PAS", 100, "Arts2",  50,  6, 30, 90, 270, 400, 550));
    squares.emplace_back(std::make_shared<Academics>(Vec2(10, 51), "HH", 120, "Arts2",   50,  8, 40, 100, 300, 450, 600));
    squares.emplace_back(std::make_shared<Academics>(Vec2(1, 46), "RCH", 140, "Eng",    100, 10, 50, 150, 450, 625, 750));
    squares.emplace_back(std::make_shared<Gym>(Vec2(1, 41), "PAC", 150));
    squares.emplace_back(std::make_shared<Academics>(Vec2(1, 36), "DWE", 140, "Eng",    100, 10, 50, 150, 450, 625, 750));
    squares.emplace_back(std::make_shared<Academics>(Vec2(1, 31), "CPH", 160, "Eng",    100, 12, 60, 180, 500, 700, 900));
    squares.emplace_back(std::make_shared<Residence>(Vec2(1, 26), "UWP", 200));
    squares.emplace_back(std::make_shared<Academics>(Vec2(1, 21), "LHI", 180, "Health", 100, 14, 70, 200, 550, 750, 950));
    squares.emplace_back(std::make_shared<Academics>(Vec2(1, 11), "BMH", 180, "Health", 100, 14, 70, 200, 550, 750, 950));
    squares.emplace_back(std::make_shared<Academics>(Vec2(1, 6), "OPT", 200, "Health", 100, 16, 80, 220, 600, 800, 1000));
    squares.emplace_back(std::make_shared<Academics>(Vec2(10, 1), "EV1", 220, "Env",    150, 18, 90, 250, 700, 875, 1050));
    squares.emplace_back(std::make_shared<Academics>(Vec2(28, 1), "EV2", 220, "Env",    150, 18, 90, 250, 700, 875, 1050));
    squares.emplace_back(std::make_shared<Academics>(Vec2(37, 1), "EV3", 240, "Env",    150, 20, 100, 300, 750, 925, 1100));
    squares.emplace_back(std::make_shared<Residence>(Vec2(46, 1), "V1", 200));
    squares.emplace_back(std::make_shared<Academics>(Vec2(55, 1), "PHYS", 260, "Sci1",  150, 22, 110, 330, 800, 975, 1150));
    squares.emplace_back(std::make_shared<Academics>(Vec2(64, 1), "B1", 260, "Sci1",    150, 22, 110, 330, 800, 975, 1150));
    squares.emplace_back(std::make_shared<Gym>(Vec2(73, 1), "CIF", 150));
    squares.emplace_back(std::make_shared<Academics>(Vec2(82, 1), "B2", 280, "Sci1",    150, 24, 120, 360, 850, 1025, 1200));
    squares.emplace_back(std::make_shared<Academics>(Vec2(91, 6), "EIT", 300, "Sci2",   200, 26, 130, 390, 900, 1100, 1275));
    squares.emplace_back(std::make_shared<Academics>(Vec2(91, 11), "ESC", 300, "Sci2",   200, 26, 130, 390, 900, 1100, 1275));
    squares.emplace_back(std::make_shared<Academics>(Vec2(91, 21), "C2", 320, "Sci2",    200, 28, 150, 450, 1000, 1200, 1400));
    squares.emplace_back(std::make_shared<Residence>(Vec2(91, 26), "REV", 200));
    squares.emplace_back(std::make_shared<Academics>(Vec2(91, 36), "MC", 350, "Math",    200, 35, 175, 500, 1100, 1300, 1500));
    squares.emplace_back(std::make_shared<Academics>(Vec2(91, 46), "DC", 400, "Math",    200, 50, 200, 600, 1400, 1700, 2000));
    
    state = PRE_GAME;
}

void Game::processInput() {
    switch (state) {
        case NO_GAME: {
            break;
        }
        case PRE_GAME: {
            std::cout << "How many players? (0-8)" << std::endl;
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
        case PRE_GAME: {
            state = IN_GAME;
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
        case PRE_GAME: {
            gfx->clear();
            gfx->drawImage("./assets/welcome.txt");
            gfx->render(25);

            break;
        }
        case IN_GAME: {
            gfx->clear();
            gfx->drawImage("./assets/gameboard.txt");
            
            for (auto &square : squares) {
                square->render(gfx);
            }
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
