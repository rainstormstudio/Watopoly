#include "game.h"
#include "math.h"
#include "graphics.h"
#include "inputManager.h"
#include "square.h"
#include "building.h"
#include "buildingList.h"
#include "nonProperty.h"
#include "nonPropertiesList.h"

void Game::nextTurn() {
    players[currentPlayer]->setRolled(false);
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

    squares.emplace_back(std::make_shared<CollectOSAP>(0, Vec2(91, 51), "COLLECT OSAP"));
    squares.emplace_back(std::make_shared<Academics>(1, Vec2(82, 51), "AL", 40, "Arts1",    50,  2, 10, 30, 90, 160, 250));
    squares.emplace_back(std::make_shared<Academics>(3, Vec2(64, 51), "ML", 60, "Arts1",    50,  4, 20, 60, 180, 320, 450));
    squares.emplace_back(std::make_shared<Residence>(5, Vec2(46, 51), "MKV", 200));
    squares.emplace_back(std::make_shared<Academics>(6, Vec2(37, 51), "ECH", 100, "Arts2",  50,  6, 30, 90, 270, 400, 550));
    squares.emplace_back(std::make_shared<Academics>(8, Vec2(19, 51), "PAS", 100, "Arts2",  50,  6, 30, 90, 270, 400, 550));
    squares.emplace_back(std::make_shared<Academics>(9, Vec2(10, 51), "HH", 120, "Arts2",   50,  8, 40, 100, 300, 450, 600));
    squares.emplace_back(std::make_shared<Academics>(11, Vec2(1, 46), "RCH", 140, "Eng",    100, 10, 50, 150, 450, 625, 750));
    squares.emplace_back(std::make_shared<Gym>(12, Vec2(1, 41), "PAC", 150));
    squares.emplace_back(std::make_shared<Academics>(13, Vec2(1, 36), "DWE", 140, "Eng",    100, 10, 50, 150, 450, 625, 750));
    squares.emplace_back(std::make_shared<Academics>(14, Vec2(1, 31), "CPH", 160, "Eng",    100, 12, 60, 180, 500, 700, 900));
    squares.emplace_back(std::make_shared<Residence>(15, Vec2(1, 26), "UWP", 200));
    squares.emplace_back(std::make_shared<Academics>(16, Vec2(1, 21), "LHI", 180, "Health", 100, 14, 70, 200, 550, 750, 950));
    squares.emplace_back(std::make_shared<Academics>(18, Vec2(1, 11), "BMH", 180, "Health", 100, 14, 70, 200, 550, 750, 950));
    squares.emplace_back(std::make_shared<Academics>(19, Vec2(1, 6), "OPT", 200, "Health", 100, 16, 80, 220, 600, 800, 1000));
    squares.emplace_back(std::make_shared<Academics>(21, Vec2(10, 1), "EV1", 220, "Env",    150, 18, 90, 250, 700, 875, 1050));
    squares.emplace_back(std::make_shared<Academics>(23, Vec2(28, 1), "EV2", 220, "Env",    150, 18, 90, 250, 700, 875, 1050));
    squares.emplace_back(std::make_shared<Academics>(24, Vec2(37, 1), "EV3", 240, "Env",    150, 20, 100, 300, 750, 925, 1100));
    squares.emplace_back(std::make_shared<Residence>(25, Vec2(46, 1), "V1", 200));
    squares.emplace_back(std::make_shared<Academics>(26, Vec2(55, 1), "PHYS", 260, "Sci1",  150, 22, 110, 330, 800, 975, 1150));
    squares.emplace_back(std::make_shared<Academics>(27, Vec2(64, 1), "B1", 260, "Sci1",    150, 22, 110, 330, 800, 975, 1150));
    squares.emplace_back(std::make_shared<Gym>(28, Vec2(73, 1), "CIF", 150));
    squares.emplace_back(std::make_shared<Academics>(29, Vec2(82, 1), "B2", 280, "Sci1",    150, 24, 120, 360, 850, 1025, 1200));
    squares.emplace_back(std::make_shared<Academics>(31, Vec2(91, 6), "EIT", 300, "Sci2",   200, 26, 130, 390, 900, 1100, 1275));
    squares.emplace_back(std::make_shared<Academics>(32, Vec2(91, 11), "ESC", 300, "Sci2",   200, 26, 130, 390, 900, 1100, 1275));
    squares.emplace_back(std::make_shared<Academics>(34, Vec2(91, 21), "C2", 320, "Sci2",    200, 28, 150, 450, 1000, 1200, 1400));
    squares.emplace_back(std::make_shared<Residence>(35, Vec2(91, 26), "REV", 200));
    squares.emplace_back(std::make_shared<Academics>(37, Vec2(91, 36), "MC", 350, "Math",    200, 35, 175, 500, 1100, 1300, 1500));
    squares.emplace_back(std::make_shared<Academics>(39, Vec2(91, 46), "DC", 400, "Math",    200, 50, 200, 600, 1400, 1700, 2000));
    
    state = PRE_GAME;
}

void Game::processInput() {
    switch (state) {
        case NO_GAME: {
            break;
        }
        case PRE_GAME: {
            std::cout << "How many players? (1-8)" << std::endl;
            bool successInput = false;
            int numPlayers = 0;
            while (!successInput) {
                if (!events->readLine()) {
                    state = NO_GAME;
                    break;
                }
                if (Math::isNat(events->getCommand())) {
                    numPlayers = std::stoi(events->getCommand());
                    if (numPlayers >= 1 && numPlayers <= 8) {
                        successInput = true;
                    } else {
                        std::cout << "Your number is not between 1 and 8." << std::endl;
                    }
                } else {
                    std::cout << "Your input is not a valid number." << std::endl;
                }
            }
            std::cout << "===================================================================================" << std::endl;
            for (int i = 0; i < numPlayers; ++i) {
                std::string name = "";
                std::cout << i + 1 << "-th player: What is your name?" << std::endl;
                if (!events->readLine()) {
                    state = NO_GAME;
                    break;
                } else {
                    name = events->getLine();
                }
                std::cout << "please choose your piece." << std::endl;
                std::cout << "Please choose the corresponding symbol from the following pieces." << std::endl;
                std::cout << "    Goose:                G" << std::endl;
                std::cout << "    GRT Bus:              B" << std::endl;
                std::cout << "    Tim Hortons Doughnut: D" << std::endl;
                std::cout << "    Professor:            P" << std::endl;
                std::cout << "    Student:              S" << std::endl;
                std::cout << "    Money:                $" << std::endl;
                std::cout << "    Laptop:               L" << std::endl;
                std::cout << "    Pink tie:             T" << std::endl;
                std::cout << "Your piece is: ";
                successInput = false;
                while (!successInput) {
                    if (!events->readLine()) {
                        state = NO_GAME;
                        break;
                    }
                    std::string input = events->getCommand();
                    if (input.length() == 1) {
                        bool used = false;
                        for (auto& player : players) {
                            if (player->getSymbol() == input[0]) {
                                used = true;
                                break;
                            }
                        }
                        if (used) {
                            std::cout << "That piece has been taken. Please choose another one." << std::endl;
                        } else {
                            if (input[0] == 'G' || input[0] == 'B' || input[0] == 'D' || input[0] == 'P' 
                                || input[0] == 'S' || input[0] == '$' || input[0] == 'L' || input[0] == 'T') {
                                players.emplace_back(std::make_shared<Player>(name, input[0]));
                                successInput = true;
                            } else {
                                std::cout << "Please choose a character from G, B, D, P, S, $, L, T." << std::endl;
                            }
                        }
                    } else {
                        std::cout << "Please enter a single character." << std::endl;
                    }
                }
                if (!successInput) {
                    break;
                }

                std::cout << "-----------------------------------------------------------------------------------" << std::endl;
            }
            currentPlayer = 0;
            break;
        }
        case IN_GAME: {
            std::cout << "Now is " << players[currentPlayer]->getName() << "'s turn:" << std::endl;
            std::cout << "Please input a command" << std::endl;
            std::cout << "    roll : the player rolls two dice, moves the sum of the two dice and takes action " << std::endl;
            std::cout << "           on the square they landed on." << std::endl;
            std::cout << "    next : give control to the next player." << std::endl;
            std::cout << "    trade <name> <give> <receive> : offers a trade to <name> with the current player " << std::endl;
            std::cout << "                                    offering <give> and requesting <receive>." << std::endl;
            std::cout << "    improve <property> buy/sell : attempts to buy or sell an improvement for property." << std::endl;
            std::cout << "    mortgage <property> : attempts to mortgage property." << std::endl;
            std::cout << "    unmortgage <property> : attempts to unmortgage property." << std::endl;
            std::cout << "    bankrupt : blayer declares bankruptcy." << std::endl;
            std::cout << "    assets : displays the assets of the current player." << std::endl;
            std::cout << "    all : displays the assets of every player." << std::endl;
            std::cout << "    save <filename> : saves the current state of the game to the given file." << std::endl;
            bool successInput = false;
            while (!successInput) {
                if (!events->readLine()) {
                    state = NO_GAME;
                    break;
                } else {
                    if (events->getCommand() == "roll") {
                        if (!players[currentPlayer]->rolled()) {
                            players[currentPlayer]->setPosition((players[currentPlayer]->getPosition() + Math::rollTwoDice()) % 40);
                            players[currentPlayer]->setRolled(true);
                            successInput = true;
                        } else {
                            std::cout << "You have rolled already." << std::endl;
                        }
                        
                    } else if (events->getCommand() == "next") {
                        // TODO : add checks
                        nextTurn();
                        successInput = true;
                    } else if (events->getCommand() == "trade") {

                    } else if (events->getCommand() == "improve") {

                    } else if (events->getCommand() == "mortage") {

                    } else if (events->getCommand() == "unmortgage") {

                    } else if (events->getCommand() == "bankrupt") {

                    } else if (events->getCommand() == "assets") {

                    } else if (events->getCommand() == "all") {

                    } else if (events->getCommand() == "save") {

                    } else {
                        std::cout << "Please enter a valid command." << std::endl;
                    }
                }
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
            for (auto& square : squares) {
                square->update(players);
            }
            state = IN_GAME;
            break;
        }
        case IN_GAME: {
            for (auto& square : squares) {
                square->update(players);
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
