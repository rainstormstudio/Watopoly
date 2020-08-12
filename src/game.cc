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

void Game::showPlayerAssets(unsigned int playerIndex) const {
    if (playerIndex < 0 || playerIndex >= players.size()) {
        std::cerr << "Invalid player index." << std::endl;
        return;
    }
    std::cout << "== Assets ======================================================================" << std::endl;
    std::cout << "| " << players[playerIndex]->getName() << "(" << players[playerIndex]->getSymbol() << ") : " << std::endl;
    std::cout << "| Balance: " << players[playerIndex]->getBalance() << std::endl;
    std::cout << "| # of TimsCups: " << players[playerIndex]->getTimsCups() << std::endl;
    std::cout << "| # of residences: " << players[playerIndex]->getResiNum() << std::endl;
    std::cout << "| # of gyms: " << players[playerIndex]->getGymNum() << std::endl;
    std::cout << "| Owned properties:" << std::endl;
    int count = 0;
    for (auto& square : squares) {
        std::shared_ptr<Building> building = std::dynamic_pointer_cast<Building>(square);
        if (building && building->getOwner() == players[playerIndex]) {
            std::cout << "|    | " << building->getName() << std::endl;
            ++count;
        }
    }
    if (count == 0) {
        std::cout << "|    | None" << std::endl;
    }
    std::cout << "================================================================================" << std::endl;
}

void Game::buy(std::shared_ptr<Building> building) {}
void Game::auction(std::shared_ptr<Building> building) {}
void Game::trade() {}

void Game::saveGame(std::string filename) {
    std::ofstream outfile {filename};
    if (outfile.is_open()) {
        outfile << players.size() << std::endl;
        for (unsigned int i = 0; i < players.size(); ++i) {
            outfile << players[i]->getName() << " " 
                    << players[i]->getSymbol() << " " 
                    << players[i]->getTimsCups() << " " 
                    << players[i]->getBalance() << " "
                    << players[i]->getPosition();
            if (players[i]->getPosition() == 10) {
                // TODO : DC tims line;
            }
            outfile << std::endl;
        }
        for (unsigned int i = 0; i < squares.size(); ++i) {
            std::shared_ptr<Building> building = std::dynamic_pointer_cast<Building>(squares[i]);
            if (building) {
                outfile << building->getName() << " ";
                if (building->getOwner()) {
                    outfile << building->getOwner()->getName() << " ";
                } else {
                    outfile << "BANK ";
                }
                std::shared_ptr<Academics> academics = std::dynamic_pointer_cast<Academics>(building);
                if (academics) {
                    outfile << academics->getImprovement() << " ";
                } else {
                    outfile << "0 ";
                }
                outfile << std::endl;
            }
        }
        outfile.close();
        std::cout << "Game saved to " << filename << std::endl;
    } else {
        std::cerr << "Error opening file " << filename << std::endl;
    }
}

void Game::loadGame(std::string filename) {
    data = nullptr;
    std::string line;
    std::ifstream infile {filename};
    if (infile.is_open()) {
        data = std::make_shared<SaveData>();
        data->numPlayers = 0;
        data->playerData.resize(0);
        data->buildingData.resize(0);
        if (getline(infile, line)) {
            if (Math::isNat(line)) {
                data->numPlayers = static_cast<unsigned int>(std::stoi(line));
            } else {
                data = nullptr;
                std::cerr << "Number of players is not natural number." << std::endl;
                return;
            }
        } else {
            data = nullptr;
            return;
        }
        for (unsigned int i = 0; i < data->numPlayers; ++i) {
            if (getline(infile, line)) {
                std::vector<std::string> tokens = InputManager::split(line);
                PlayerData playerData; 
                try {
                    if (std::stoi(tokens[4]) == 10) {
                        playerData = {tokens[0], tokens[1][0], 
                                        static_cast<unsigned int>(std::stoi(tokens[2])), 
                                        static_cast<unsigned int>(std::stoi(tokens[3])), 
                                        static_cast<unsigned int>(std::stoi(tokens[4])), 
                                        static_cast<bool>(std::stoi(tokens[5]), 
                                        static_cast<unsigned int>(std::stoi(tokens[6])))};
                    } else {
                        playerData = {tokens[0], tokens[1][0], 
                                        static_cast<unsigned int>(std::stoi(tokens[2])), 
                                        static_cast<unsigned int>(std::stoi(tokens[3])), 
                                        static_cast<unsigned int>(std::stoi(tokens[4])), 0, 0};
                    }
                    data->playerData.emplace_back(playerData);
                } catch (...) {
                    data = nullptr;
                    std::cerr << "Error creating player through the save data." << std::endl;
                    return;
                }
            } else {
                data = nullptr;
                return;
            }
        }
        while (getline(infile, line)) {
            std::vector<std::string> tokens = InputManager::split(line);
            BuildingData buildingData;
            try {
                buildingData = {tokens[0], tokens[1], std::stoi(tokens[2])};
                data->buildingData.emplace_back(buildingData);
            } catch (...) {
                data = nullptr;
                std::cerr << "Error creating building through the save data." << std::endl;
                return;
            }
        }
    } else {
        std::cerr << "Error loading save data." << std::endl;
    }
}

Game::Game(GameMode mode, std::string loadFile) : mode{mode} {
    loadGame(loadFile);
    state = NO_GAME;
    currentPlayer = 0;
}

bool Game::loop() const { return state != NO_GAME; }

void Game::init() {
    if (mode == TESTING_GAMEMODE) {
        std::cout << "Game initialized as Testing Mode." << std::endl;
    }
    gfx = std::make_shared<Graphics>(101, 56);
    events = std::make_shared<InputManager>();

    squares.resize(0);
    squares.emplace_back(std::make_shared<CollectOSAP>(0, Vec2(91, 51), "COLLECT OSAP"));
    squares.emplace_back(std::make_shared<Academics>(1, Vec2(82, 51), "AL", 40, "Arts1",    50,  2, 10, 30, 90, 160, 250));
    squares.emplace_back(std::make_shared<SLC>(2, Vec2(73, 51), "SLC"));
    squares.emplace_back(std::make_shared<Academics>(3, Vec2(64, 51), "ML", 60, "Arts1",    50,  4, 20, 60, 180, 320, 450));
    squares.emplace_back(std::make_shared<Tuition>(4, Vec2(55, 51), "TUITION"));
    squares.emplace_back(std::make_shared<Residence>(5, Vec2(46, 51), "MKV", 200));
    squares.emplace_back(std::make_shared<Academics>(6, Vec2(37, 51), "ECH", 100, "Arts2",  50,  6, 30, 90, 270, 400, 550));
    squares.emplace_back(std::make_shared<NeedlesHall>(7, Vec2(28, 51), "NEEDLES HALL"));
    squares.emplace_back(std::make_shared<Academics>(8, Vec2(19, 51), "PAS", 100, "Arts2",  50,  6, 30, 90, 270, 400, 550));
    squares.emplace_back(std::make_shared<Academics>(9, Vec2(10, 51), "HH", 120, "Arts2",   50,  8, 40, 100, 300, 450, 600));
    squares.emplace_back(std::make_shared<DCtims>(10, Vec2(1, 51), "DC Tims Line"));
    squares.emplace_back(std::make_shared<Academics>(11, Vec2(1, 46), "RCH", 140, "Eng",    100, 10, 50, 150, 450, 625, 750));
    squares.emplace_back(std::make_shared<Gym>(12, Vec2(1, 41), "PAC", 150));
    squares.emplace_back(std::make_shared<Academics>(13, Vec2(1, 36), "DWE", 140, "Eng",    100, 10, 50, 150, 450, 625, 750));
    squares.emplace_back(std::make_shared<Academics>(14, Vec2(1, 31), "CPH", 160, "Eng",    100, 12, 60, 180, 500, 700, 900));
    squares.emplace_back(std::make_shared<Residence>(15, Vec2(1, 26), "UWP", 200));
    squares.emplace_back(std::make_shared<Academics>(16, Vec2(1, 21), "LHI", 180, "Health", 100, 14, 70, 200, 550, 750, 950));
    squares.emplace_back(std::make_shared<SLC>(17, Vec2(1, 16), "SLC"));
    squares.emplace_back(std::make_shared<Academics>(18, Vec2(1, 11), "BMH", 180, "Health", 100, 14, 70, 200, 550, 750, 950));
    squares.emplace_back(std::make_shared<Academics>(19, Vec2(1, 6), "OPT", 200, "Health", 100, 16, 80, 220, 600, 800, 1000));
    squares.emplace_back(std::make_shared<GooseNesting>(20, Vec2(1, 1), "Goose  Nesting"));
    squares.emplace_back(std::make_shared<Academics>(21, Vec2(10, 1), "EV1", 220, "Env",    150, 18, 90, 250, 700, 875, 1050));
    squares.emplace_back(std::make_shared<SLC>(22, Vec2(19, 1), "SLC"));
    squares.emplace_back(std::make_shared<Academics>(23, Vec2(28, 1), "EV2", 220, "Env",    150, 18, 90, 250, 700, 875, 1050));
    squares.emplace_back(std::make_shared<Academics>(24, Vec2(37, 1), "EV3", 240, "Env",    150, 20, 100, 300, 750, 925, 1100));
    squares.emplace_back(std::make_shared<Residence>(25, Vec2(46, 1), "V1", 200));
    squares.emplace_back(std::make_shared<Academics>(26, Vec2(55, 1), "PHYS", 260, "Sci1",  150, 22, 110, 330, 800, 975, 1150));
    squares.emplace_back(std::make_shared<Academics>(27, Vec2(64, 1), "B1", 260, "Sci1",    150, 22, 110, 330, 800, 975, 1150));
    squares.emplace_back(std::make_shared<Gym>(28, Vec2(73, 1), "CIF", 150));
    squares.emplace_back(std::make_shared<Academics>(29, Vec2(82, 1), "B2", 280, "Sci1",    150, 24, 120, 360, 850, 1025, 1200));
    squares.emplace_back(std::make_shared<GoToTims>(30, Vec2(91, 1), "GO TO TIMS"));
    squares.emplace_back(std::make_shared<Academics>(31, Vec2(91, 6), "EIT", 300, "Sci2",   200, 26, 130, 390, 900, 1100, 1275));
    squares.emplace_back(std::make_shared<Academics>(32, Vec2(91, 11), "ESC", 300, "Sci2",   200, 26, 130, 390, 900, 1100, 1275));
    squares.emplace_back(std::make_shared<SLC>(33, Vec2(91, 16), "SLC"));
    squares.emplace_back(std::make_shared<Academics>(34, Vec2(91, 21), "C2", 320, "Sci2",    200, 28, 150, 450, 1000, 1200, 1400));
    squares.emplace_back(std::make_shared<Residence>(35, Vec2(91, 26), "REV", 200));
    squares.emplace_back(std::make_shared<NeedlesHall>(36, Vec2(91, 31), "NEEDLES HALL"));
    squares.emplace_back(std::make_shared<Academics>(37, Vec2(91, 36), "MC", 350, "Math",    200, 35, 175, 500, 1100, 1300, 1500));
    squares.emplace_back(std::make_shared<CoopFee>(38, Vec2(91, 41), "COOP FEE"));
    squares.emplace_back(std::make_shared<Academics>(39, Vec2(91, 46), "DC", 400, "Math",    200, 50, 200, 600, 1400, 1700, 2000));
    
    state = PRE_GAME;
}

void Game::processInput() {
    switch (state) {
        case NO_GAME: {
            break;
        }
        case PRE_GAME: {
            if (data) {
                std::cout << "loading save data ..." << std::endl;
                for (unsigned int i = 0; i < data->numPlayers; ++i) {
                    players.emplace_back(std::make_shared<Player>(data->playerData[i].name, data->playerData[i].symbol));
                    players[players.size() - 1]->setPosition(data->playerData[i].position);
                    players[players.size() - 1]->setBalance(data->playerData[i].money);
                    players[players.size() - 1]->setTimsCups(data->playerData[i].timsCups);
                    // TODO: more about player ...
                }
                for (unsigned int i = 0; i < data->buildingData.size(); ++i) {
                    for (unsigned int j = 0; j < squares.size(); ++j) {
                        std::shared_ptr<Building> building = std::dynamic_pointer_cast<Building>(squares[j]);
                        if (building && building->getName() == data->buildingData[i].name) {
                            for (unsigned int k = 0; k < players.size(); ++k) {
                                if (players[k]->getName() == data->buildingData[i].owner) {
                                    building->setOwner(players[k]);
                                    break;
                                }
                            }
                            std::shared_ptr<Academics> academics = std::dynamic_pointer_cast<Academics>(building);
                            if (academics) {
                                academics->setImprovement(data->buildingData[i].improvements);
                            }
                        }
                    }
                }
            } else {
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
                std::cout << "================================================================================" << std::endl;
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
                                    std::static_pointer_cast<CollectOSAP>(squares[0])->addPlayer(players[players.size() - 1]);
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

                    std::cout << "--------------------------------------------------------------------------------" << std::endl;
                }
            }
            currentPlayer = 0;
            break;
        }
        case IN_GAME: {
            if (players[currentPlayer]->getCanBuy()) {
                bool successInput = false;
                while (!successInput) {
                    if (!events->readLine()) {
                        state = NO_GAME;
                        return;
                    } else {
                        if (events->getCommand() == "Yes" || events->getCommand() == "yes") {
                            std::shared_ptr<Building> building = std::dynamic_pointer_cast<Building>(squares[players[currentPlayer]->getPosition()]);
                            if (building) {
                                unsigned int cost = building->getCost();
                                building->setOwner(players[currentPlayer]);
                                players[currentPlayer]->decBalance(cost);
                                if (std::dynamic_pointer_cast<Gym>(building)) {
                                    players[currentPlayer]->setGymNum(players[currentPlayer]->getGymNum() + 1);
                                }
                                if (std::dynamic_pointer_cast<Residence>(building)) {
                                    players[currentPlayer]->setResiNum(players[currentPlayer]->getResiNum() + 1);
                                }
                                successInput = true;
                                std::cout << players[currentPlayer]->getName() << " bought " << building->getName() << ". " << std::endl;
                            } else {
                                std::cout << "Error: current property is not a Building type." << std::endl; // only for debugging
                            }
                        } else if (events->getCommand() == "No" || events->getCommand() == "no") {
                            successInput = true;
                        } else {
                            std::cout << "Please enter yes or no." << std::endl;
                        }
                    }
                }
                players[currentPlayer]->setCanBuy(false);
            }
            std::cout << "================================================================================" << std::endl;
            std::cout << "Now is " << players[currentPlayer]->getName() << "'s turn:" << std::endl;
            std::cout << "Please input a command" << std::endl;
           
            bool successInput = false;
            while (!successInput) {
                if (!events->readLine()) {
                    state = NO_GAME;
                    break;
                } else {
                    if (events->getCommand() == "roll") {
                        if (mode == NORMAL_GAMEMODE) {
                            if (!players[currentPlayer]->rolled()) {
                                players[currentPlayer]->setPosition((players[currentPlayer]->getPosition() + Math::rollTwoDice()) % 40);
                                players[currentPlayer]->setRolled(true);
                                successInput = true;
                            } else {
                                std::cout << "You have rolled already." << std::endl;
                            }
                        } else if (mode == TESTING_GAMEMODE) {
                            if (!players[currentPlayer]->rolled()) {
                                if (Math::isNat(events->getArg(0)) && Math::isNat(events->getArg(1))) {
                                    players[currentPlayer]->setPosition(players[currentPlayer]->getPosition() + std::stoi(events->getArg(0)) + std::stoi(events->getArg(1)));
                                    players[currentPlayer]->setRolled(true);
                                    successInput = true;
                                } else {
                                    std::cout << "Please input two natural numbers." << std::endl;
                                }
                            } else {
                                std::cout << "You have rolled already." << std::endl;
                            }
                        }
                    } else if (events->getCommand() == "next") {
                        // TODO : add checks
                        nextTurn();
                        successInput = true;
                    } else if (events->getCommand() == "trade") {
                        
                    } else if (events->getCommand() == "improve") {
                        if (events->getArgs().size() == 2) {
                            bool existing = false;
                            for (unsigned int i = 0; i < squares.size(); ++i) {
                                if (events->getArg(0) == squares[i]->getName()) {
                                    existing = true;
                                    std::shared_ptr<Academics> academics = std::dynamic_pointer_cast<Academics>(squares[i]);
                                    if (academics) {
                                        unsigned int monopolyTotal = 0;
                                        unsigned int monopolyOwned = 0;
                                        for (unsigned int j = 0; j < squares.size(); ++j) {
                                            std::shared_ptr<Academics> monopoly = std::dynamic_pointer_cast<Academics>(squares[j]);
                                            if (monopoly) {
                                                if (monopoly->getBlock() == academics->getBlock()) {
                                                    ++monopolyTotal;
                                                    if (monopoly->getOwner() == players[currentPlayer]) {
                                                        ++monopolyOwned;
                                                    }
                                                }
                                            }
                                        }
                                        if (monopolyTotal != monopolyOwned) {
                                            std::cout << "Sorry you don't own this monopoly block: " << academics->getBlock() << "." << std::endl;
                                            break;
                                        }
                                        if (academics->getOwner() == players[currentPlayer]) {
                                            if (events->getArg(1) == "buy") {
                                                if (academics->getImprovement() < 5) {
                                                    if (players[currentPlayer]->getBalance() >= academics->getImprovementCost()) {
                                                        players[currentPlayer]->decBalance(academics->getImprovementCost());
                                                        academics->addImprovement();
                                                        successInput = true;
                                                    } else {
                                                        std::cout << "Sorry, you don't have enough money." << std::endl;
                                                    }
                                                } else {
                                                    std::cout << "This property already has all the improvements." << std::endl;
                                                }
                                            } else if (events->getArg(1) == "sell") {
                                                if (academics->getImprovement() > 0) {
                                                    players[currentPlayer]->addBalance(academics->getImprovementCost() / 2);
                                                    academics->removeImprovement();
                                                    successInput = true;
                                                } else {
                                                    std::cout << "This property has no improvements to be sold." << std::endl;
                                                }
                                            } else {
                                                std::cout << "Please input buy/sell." << std::endl;
                                            }
                                        } else {
                                            std::cout << "Sorry, this property is not owned by you." << std::endl;
                                        }
                                    } else {
                                        std::cout << "Cannot improve non-academics building!" << std::endl;
                                    }
                                }
                            }
                            if (!existing) {
                                std::cout << "Not a valid square name." << std::endl;
                            }
                        } else {
                            std::cout << "Please specify a property name and whether buy or sell" << std::endl;
                        }
                    } else if (events->getCommand() == "mortgage") {
                        bool existing = false;
                        for (unsigned int i = 0; i < squares.size(); i++) {
                            if (events->getArg(0) == squares[i]->getName()) {
                                existing = true;
                                // debugging use
                                std::shared_ptr<Building> building = std::dynamic_pointer_cast<Building>(squares[i]);
                                if (building) {
                                    players[currentPlayer]->mortgage(building);
                                    break;
                                } else {
                                    std::cout << "Cannot mortgage NonProperty or Academic Buildings!" << std::endl;
                                    break;
                                }
                            }
                        }
                        if (!existing) {
                            std::cout << "Please enter the correct property!" << std::endl;
                        }
                    } else if (events->getCommand() == "unmortgage") {
                        bool existing = false;
                        for (unsigned int i = 0; i < squares.size(); i++) {
                            if (events->getArg(0) == squares[i]->getName()) {
                                existing = true;
                                std::shared_ptr<Building> building = std::dynamic_pointer_cast<Building>(squares[i]);
                                if (building) {
                                    players[currentPlayer]->unmortgage(building);
                                    break;
                                } else {
                                    std::cout << "Cannot unmortgage NonProperty or Academic Buildings!" << std::endl;
                                    break;
                                }
                            }
                        }
                        if (!existing) {
                            std::cout << "Please enter a valid property name!" << std::endl;
                        }
                    } else if (events->getCommand() == "bankrupt") {

                    } else if (events->getCommand() == "assets") {
                        showPlayerAssets(currentPlayer);
                    } else if (events->getCommand() == "all") {
                        for ( unsigned int i = 0; i < players.size(); ++i) {
                            showPlayerAssets(i);
                        }
                    } else if (events->getCommand() == "save") {
                        if (events->getArgs().size() > 0) {
                            saveGame(events->getArg(0));
                        } else {
                            std::cout << "Please specify a filename." << std::endl;
                        }
                    } else {
                        std::cout << "Please enter a valid command:" << std::endl;
                        if (mode == NORMAL_GAMEMODE) {
                            std::cout << "    roll : the player rolls two dice, moves the sum of the two dice and takes action " << std::endl;
                            std::cout << "           on the square they landed on." << std::endl;
                        } else if (mode == TESTING_GAMEMODE) {
                            std::cout << "    roll <die1> <die2>" << std::endl;
                        }
                        std::cout << "    next : give control to the next player." << std::endl;
                        std::cout << "    trade <name> <give> <receive> : offers a trade to <name> with the current player " << std::endl;
                        std::cout << "                                    offering <give> and requesting <receive>." << std::endl;
                        std::cout << "    improve <property> buy/sell : attempts to buy or sell an improvement for property." << std::endl;
                        std::cout << "    mortgage <property> : attempts to mortgage property." << std::endl;
                        std::cout << "    unmortgage <property> : attempts to unmortgage property." << std::endl;
                        std::cout << "    bankrupt : player declares bankruptcy." << std::endl;
                        std::cout << "    assets : displays the assets of the current player." << std::endl;
                        std::cout << "    all : displays the assets of every player." << std::endl;
                        std::cout << "    save <filename> : saves the current state of the game to the given file." << std::endl;
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
