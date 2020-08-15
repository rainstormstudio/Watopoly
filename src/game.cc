#include "game.h"
#include "math.h"
#include "graphics.h"
#include "inputManager.h"
#include "square.h"
#include "building.h"
#include "buildingList.h"
#include "nonProperty.h"
#include "nonPropertiesList.h"

bool Game::monopolyHasImprovement(std::shared_ptr<Building> building) {
    std::shared_ptr<Academics> monopoly = std::dynamic_pointer_cast<Academics>(building);
    if (!monopoly) {
        return false;
    }
    std::string block = monopoly->getBlock();
    bool result = false;
    for (auto& square : squares) {
        std::shared_ptr<Academics> academics = std::dynamic_pointer_cast<Academics>(square);
        if (academics && academics->getBlock() == block && academics->getImprovement() > 0) {
            result = true;
            break;
        }
    }
    return result;
}

void Game::nextTurn() {
    rollNum = 0;
    players[currentPlayer]->setRolled(false);
    if (players[currentPlayer]->getBankruptcy()) {
        players.erase(players.begin() + currentPlayer);
        players.shrink_to_fit();
        if (currentPlayer == players.size()) {
            currentPlayer = 0;
        }
    } else {
        currentPlayer = (currentPlayer + 1) % players.size();
    }
    if (players.size() == 1) {
        state = WON_GAME;
    }
}

void Game::showPlayerAssets(unsigned int playerIndex) const {
    if (playerIndex < 0 || playerIndex >= players.size()) {
        std::cerr << "Invalid player index." << std::endl;
        return;
    }
    std::cout << "== Assets ======================================================================" << std::endl;
    std::cout << "| " << players[playerIndex]->getName() << "(" << players[playerIndex]->getSymbol() << ") : " << std::endl;
    std::cout << "| Balance: $" << players[playerIndex]->getBalance() << std::endl;
    std::cout << "| Asset Amount: $" << players[playerIndex]->getAsset() << std::endl;
    std::cout << "| Total Worth: $" << players[playerIndex]->getBalance()+players[playerIndex]->getAsset() << std::endl;
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

void Game::auction(std::shared_ptr<Building> building) {
    std::cout << "--------------------------------------------------------------------------------" << std::endl;
    std::cout << "Start auction for " << building->getName() << "!" << std::endl;
    unsigned int maxBid = 0;
    unsigned int maxBidPlayer = currentPlayer;
    std::vector<bool> auctionPlayers = std::vector<bool>(players.size());
    unsigned int numAuctionPlayers = players.size();
    unsigned int currentAuctionPlayer = currentPlayer;
    for (unsigned int i = 0; i < players.size(); ++i) {
        if (players[i]->getBankruptcy()) {
            auctionPlayers[i] = false;
        } else {
            auctionPlayers[i] = true;
        }
    }
    while (numAuctionPlayers != 1) {
        do {
            currentAuctionPlayer = (currentAuctionPlayer + 1) % players.size();
        } while (!auctionPlayers[currentAuctionPlayer]);
        std::cout << "--------------------------------------------------------------------------------" << std::endl;
        std::cout << "Now is " << players[currentAuctionPlayer]->getName() << "'s turn to bid." << std::endl;
        std::cout << "The current bid is $" << maxBid << "." << std::endl;
        std::cout << "Your options are:" << std::endl;
        std::cout << "    bid <money>" << std::endl;
        std::cout << "    withdraw" << std::endl;
        std::cout << "    assets" << std::endl;
        bool successInput = false;
        while (!successInput) {
            if (!events->readLine()) {
                state = NO_GAME;
                return;
            }
            if (events->getCommand() == "bid") {
                if (Math::isNat(events->getArg(0))) {
                    unsigned int newBid = static_cast<unsigned int>(std::stoi(events->getArg(0)));
                    if (players[currentAuctionPlayer]->getBalance() < newBid) {
                        std::cout << "Sorry you don't have that much money to bid." << std::endl;
                    } else {
                        if (newBid <= maxBid) {
                            std::cout << "Sorry the max bid is higher than your bid." << std::endl;
                        } else {
                            successInput = true;
                            maxBid = newBid;
                            maxBidPlayer = currentAuctionPlayer;
                            std::cout << "The new max bid is now $" << maxBid << "." << std::endl;
                        }
                    }
                } else {
                    std::cout << "Please enter a valid natural number for <money>." << std::endl;
                }
            } else if (events->getCommand() == "withdraw") {
                successInput = true;
                std::cout << players[currentAuctionPlayer]->getName() << " withdraws the current auction." << std::endl;
                auctionPlayers[currentAuctionPlayer] = false;
                --numAuctionPlayers;
            } else if (events->getCommand() == "assets") {
                showPlayerAssets(currentAuctionPlayer);
            } else {
                std::cout << "Please enter a valid command." << std::endl;
            }
        }
    }
    building->setOwner(players[maxBidPlayer]);
    players[maxBidPlayer]->decBalance(maxBid, nullptr);
    render();
    std::cout << "Summary of auction:" << std::endl;
    std::cout << building->getName() << " was bought by " << players[maxBidPlayer]->getName() << " with $" << maxBid << "." << std::endl;
}

void Game::trade() {
    if (Math::isNat(events->getArg(0))) {
        std::cout << "You should input a player's name for the first argument." << std::endl;
    } else {
        unsigned int target = 0;
        for (unsigned int target = 0; target < players.size(); ++target) {
            if (players[target]->getName() == events->getArg(0)) {
                break;
            }
        }
        if (target == currentPlayer) {
            std::cout << "Sorry you cannot trade with yourself." << std::endl;
        } else if (target == players.size()) {
            std::cout << "Sorry the player with that name does not exist." << std::endl;
        } else {
            if (Math::isNat(events->getArg(1)) && Math::isNat(events->getArg(2))) {
                std::cout << "Sorry you cannot trade money with money" << std::endl;
            } else if (Math::isNat(events->getArg(1))) {
                if (players[currentPlayer]->getBalance() < static_cast<unsigned int>(std::stoi(events->getArg(1)))) {
                    std::cout << "Sorry you do not have that much money" << std::endl;
                    return;
                }
                std::shared_ptr<Building> receive = nullptr;
                for (auto& square : squares) {
                    std::shared_ptr<Building> building = std::dynamic_pointer_cast<Building>(square);
                    if (building && building->getName() == events->getArg(2)) {
                        receive = building;
                        break;
                    }
                }
                if (!receive) {
                    std::cout << "Sorry that is not a valid building name." << std::endl;
                } else if (receive->getOwner() != players[target]) {
                    std::cout << "Sorry " << players[target]->getName() << " does not own that building." << std::endl;
                } else if (monopolyHasImprovement(receive)) {
                    std::cout << "Sorry certain building in that monopoly has improvements." << std::endl;
                } else {
                    std::cout << players[target]->getName() << ", " << players[currentPlayer]->getName() 
                        << " wants to give you $" << events->getArg(1) << " in exchange for your " << receive->getName() << "." << std::endl;
                    std::cout << "Do you accept that? (Yes/No): " << std::endl;
                    bool successInput = false;
                    while (!successInput) {
                        if (!events->readLine()) {
                            state = NO_GAME;
                            return;
                        } else {
                            if (events->getCommand() == "Yes" || events->getCommand() == "yes") {
                                successInput = true;
                                receive->setOwner(players[currentPlayer]);
                                players[currentPlayer]->decBalance(std::stoi(events->getArg(1)), nullptr);
                                players[currentPlayer]->changeAsset(players[currentPlayer]->getAsset() + receive->getCost());
                                players[target]->changeAsset(players[target]->getAsset() - receive->getCost());
                            } else if (events->getCommand() == "No" || events->getCommand() == "no") {
                                successInput = true;
                            } else {
                                std::cout << "Please enter yes or no." << std::endl;
                            }
                        }
                    }
                }
            } else if (Math::isNat(events->getArg(2))) {
                if (players[target]->getBalance() < static_cast<unsigned int>(std::stoi(events->getArg(2)))) {
                    std::cout << "Sorry " << players[target]->getName() << " does not have that much money." << std::endl;
                    return;
                }
                std::shared_ptr<Building> give = nullptr;
                for (auto& square : squares) {
                    std::shared_ptr<Building> building = std::dynamic_pointer_cast<Building>(square);
                    if (building && building->getName() == events->getArg(1)) {
                        give = building;
                        break;
                    }
                }
                if (!give) {
                    std::cout << "Sorry that is not a valid building name." << std::endl;
                } else if (give->getOwner() != players[currentPlayer]) {
                    std::cout << "Sorry you not own that building." << std::endl;
                } else if (monopolyHasImprovement(give)) {
                    std::cout << "Sorry certain building in that monopoly has improvements." << std::endl;
                } else {
                    std::cout << players[target]->getName() << ", " << players[currentPlayer]->getName()
                        << "wants to give you " << give->getName() << " in exchange for your $" << events->getArg(2);
                    std::cout << "Do you accept that? (Yes/No): " << std::endl;
                    bool successInput = false;
                    while (!successInput) {
                        if (!events->readLine()) {
                            state = NO_GAME;
                            return;
                        } else {
                            if (events->getCommand() == "Yes" || events->getCommand() == "yes") {
                                successInput = true;
                                give->setOwner(players[target]);
                                players[target]->decBalance(std::stoi(events->getArg(2)), nullptr);
                                players[target]->changeAsset(players[target]->getAsset() + give->getCost());
                                players[currentPlayer]->changeAsset(players[currentPlayer]->getAsset() - give->getCost());
                            } else if (events->getCommand() == "No" || events->getCommand() == "no") {
                                successInput = true;
                            } else {
                                std::cout << "Please enter yes or no." << std::endl;
                            }
                        }
                    }
                }
            } else {
                std::shared_ptr<Building> give = nullptr;
                for (auto& square : squares) {
                    std::shared_ptr<Building> building = std::dynamic_pointer_cast<Building>(square);
                    if (building && building->getName() == events->getArg(1)) {
                        give = building;
                        break;
                    }
                }
                if (!give) {
                    std::cout << "Sorry " << events->getArg(1) << " is not a valid building name." << std::endl;
                    return;
                } else if (monopolyHasImprovement(give)) {
                    std::cout << "Sorry " << give->getName() << "'s monopoly has improvements." << std::endl;
                    return;
                } else if (give->getOwner() != players[currentPlayer]) {
                    std::cout << "Sorry you do not own that building." << std::endl;
                    return;
                }
                std::shared_ptr<Building> receive = nullptr;
                for (auto& square : squares) {
                    std::shared_ptr<Building> building = std::dynamic_pointer_cast<Building>(square);
                    if (building && building->getName() == events->getArg(2)) {
                        receive = building;
                        break;
                    }
                }
                if (!receive) {
                    std::cout << "Sorry " << events->getArg(2) << " is not a valid building name." << std::endl;
                    return;
                } else if (monopolyHasImprovement(receive)) {
                    std::cout << "Sorry " << receive->getName() << "'s monopoly has improvements." << std::endl;
                    return;
                } else if (receive->getOwner() != players[target]) {
                    std::cout << "Sorry " << players[target]->getName() << " does not own that building." << std::endl;
                    return;
                }
                std::cout << players[target]->getName() << ", " << players[currentPlayer]->getName() 
                        << " wants to give you " << events->getArg(1) << " in exchange for your " << receive->getName() << "." << std::endl;
                std::cout << "Do you accept that? (Yes/No): " << std::endl;
                bool successInput = false;
                while (!successInput) {
                        if (!events->readLine()) {
                            state = NO_GAME;
                            return;
                        } else {
                            if (events->getCommand() == "Yes" || events->getCommand() == "yes") {
                                successInput = true;
                                receive->setOwner(players[currentPlayer]);
                                give->setOwner(players[target]);
                                players[currentPlayer]->changeAsset(players[currentPlayer]->getAsset() + receive->getCost());
                                players[target]->changeAsset(players[target]->getAsset() - receive->getCost());
                                players[target]->changeAsset(players[target]->getAsset() + give->getCost());
                                players[currentPlayer]->changeAsset(players[currentPlayer]->getAsset() - give->getCost());
                            } else if (events->getCommand() == "No" || events->getCommand() == "no") {
                                successInput = true;
                            } else {
                                std::cout << "Please enter yes or no." << std::endl;
                            }
                        }
                }
            }
        }
    }
}

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
                if (players[i]->getTimsTurn() == 0) {
                    outfile << "0";
                } else {
                    outfile << "1 " << players[i]->getTimsTurn();
                }
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
    if (loadFile != "") {
        loadGame(loadFile);
    }
    state = NO_GAME;
    currentPlayer = 0;
}

bool Game::loop() const { return state != NO_GAME; }

void Game::init() {
    Math::initRandom();
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
                    if (data->playerData[i].position == 0) {
                        std::shared_ptr<CollectOSAP> collectOsap = std::dynamic_pointer_cast<CollectOSAP>(squares[0]);
                        if (collectOsap) {
                            collectOsap->addPlayer(players[players.size() - 1]);
                        } else {
                            std::cerr << "Error loading data for CollectOSAP." << std::endl;
                        }
                    }
                    players[players.size() - 1]->setBalance(data->playerData[i].money);
                    players[players.size() - 1]->setTimsCups(data->playerData[i].timsCups);
                    if (data->playerData[i].isInDCTims) {
                        players[players.size() - 1]->setTimsTurn(data->playerData[i].DCturns);
                    }
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
                            std::shared_ptr<Gym> gym = std::dynamic_pointer_cast<Gym>(building);
                            if (gym && gym->getOwner()) {
                                gym->getOwner()->setGymNum(gym->getOwner()->getGymNum() + 1);
                            }
                            std::shared_ptr<Residence> residence = std::dynamic_pointer_cast<Residence>(building);
                            if (residence && residence->getOwner()) {
                                residence->getOwner()->setResiNum(residence->getOwner()->getResiNum() + 1);
                            }
                        }
                    }
                }
            } else {
                std::cout << "How many players? (2-8)" << std::endl;
                bool successInput = false;
                int numPlayers = 0;
                while (!successInput) {
                    if (!events->readLine()) {
                        state = NO_GAME;
                        break;
                    } 
                    if (Math::isNat(events->getCommand())) {
                        numPlayers = std::stoi(events->getCommand());
                        if (numPlayers >= 2 && numPlayers <= 8) {
                            successInput = true;
                        } else {
                            std::cout << "Your number is not between 2 and 8." << std::endl;
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
            if (players[currentPlayer]->getTimsTurn() > 0) {
                bool successInput = false;
                int firstRoll = 0;
                int secondRoll = 0;
                while (!successInput) {
                    if (!events->readLine()) {
                        state = NO_GAME;
                        return;
                    } else {
                        if (events->getCommand() == "1") {
                            if (players[currentPlayer]->getTimsTurn() < 3) {
                                successInput = true;
                                firstRoll = Math::rollDice();
                                secondRoll = Math::rollDice();
                                std::cout << "Your first roll is " << firstRoll << std::endl;
                                std::cout << "Your second roll is " << secondRoll << std::endl;
                                if (firstRoll == secondRoll) {
                                    std::cout << "Congratulations! You got doubles!" << std::endl;
                                    std::cout << "You left DC Tims line." << std::endl;
                                    players[currentPlayer]->resetTimsTurn();
                                } else {
                                    std::cout << "Sorry you have to stay at DC Tims line." << std::endl;
                                }
                            } else if (players[currentPlayer]->getTimsTurn() == 3) {
                                firstRoll = Math::rollDice();
                                secondRoll = Math::rollDice();
                                std::cout << "Your first roll is " << firstRoll << std::endl;
                                std::cout << "Your second roll is " << secondRoll << std::endl;
                                if (firstRoll == secondRoll) {
                                    successInput = true;
                                    std::cout << "Congratulations! You got doubles!" << std::endl;
                                    std::cout << "You left DC Tims line." << std::endl;
                                    players[currentPlayer]->resetTimsTurn();
                                    players[currentPlayer]->setPosition(players[currentPlayer]->getPosition() + firstRoll + secondRoll);
                                    players[currentPlayer]->setRolled(true);
                                } else {
                                    std::cout << "Sorry you must choose other options to leave the line." << std::endl;
                                    players[currentPlayer]->setTimsTurn(4);
                                }
                            } else {
                                std::cout << "You must choose other options to leave the line." << std::endl;
                            }
                        } else if (events->getCommand() == "2") {
                                successInput = true;
                                players[currentPlayer]->decBalance(50, nullptr);
                                bool needUpdate = false;
                                if (players[currentPlayer]->getTimsTurn() == 4) {
                                    needUpdate = true;
                                    players[currentPlayer]->setPosition(players[currentPlayer]->getPosition() + firstRoll + secondRoll);
                                }
                                players[currentPlayer]->resetTimsTurn();
                                std::cout << "You paid $50 and you left DC Tims line." << std::endl;
                                if (needUpdate) {
                                    return;
                                }
                        } else if (events->getCommand() == "3") {
                            if (players[currentPlayer]->getTimsCups() > 0) {
                                successInput = true;
                                players[currentPlayer]->setTimsCups(players[currentPlayer]->getTimsCups() - 1);
                                bool needUpdate = false;
                                if (players[currentPlayer]->getTimsTurn() == 4) {
                                    needUpdate = true;
                                    players[currentPlayer]->setPosition(players[currentPlayer]->getPosition() + firstRoll + secondRoll);
                                }
                                players[currentPlayer]->resetTimsTurn();
                                std::cout << "You used one Roll Up the Rim cup and you left DC Tims line." << std::endl;
                                if (needUpdate) {
                                    return;
                                }
                            } else {
                                std::cout << "Sorry you don't have enough Roll Up the Rim cup." << std::endl;
                            }
                        } else {
                            std::cout << "Please enter 1/2/3." << std::endl;
                        }
                    }
                }
                
            }
            if (players[currentPlayer]->getTimsTurn() > 0) {
                players[currentPlayer]->setTimsTurn(players[currentPlayer]->getTimsTurn() + 1);
            }
            if (players[currentPlayer]->getPassOSAP()) {
                std::cout << "Passed by OSAP! Received $200!" << std::endl;
            }
            if (players[currentPlayer]->getCollectGooseBonus()) {
                players[currentPlayer]->addBalance(bank);
                bank = 0;
                players[currentPlayer]->setCollectGooseBonus(false);
            }
            if (players[currentPlayer]->getCanBuy()) {
                bool successInput = false;
                while (!successInput) {
                    if (!events->readLine()) {
                        state = NO_GAME;
                        return;
                    } else {
                        if (events->getCommand() == "Yes" || events->getCommand() == "yes") {
                            std::shared_ptr<Building> building = std::dynamic_pointer_cast<Building>(squares[players[currentPlayer]->getPosition()]);
                            if (players[currentPlayer]->getBalance() >= building->getCost()) {
                                if (building) {
                                    players[currentPlayer]->buy(building);
                                    building->setOwner(players[currentPlayer]);
                                    gfx->addMsg(players[currentPlayer]->getName() + " bought " + building->getName() + ". ");
                                    render();
                                } else {
                                    std::cout << "Error: current property is not a Building type." << std::endl; // only for debugging
                                }
                            } else {
                                std::cout << "Cannot buy " << building->getName() << "! Do not have enough balance!" << std::endl;
                            }
                            successInput = true;
                        } else if (events->getCommand() == "No" || events->getCommand() == "no") {
                            std::shared_ptr<Building> building = std::dynamic_pointer_cast<Building>(squares[players[currentPlayer]->getPosition()]);
                            auction(building);
                            successInput = true;
                        } else if (events->getCommand() == "assets") {
                            showPlayerAssets(currentPlayer);
                        } else {
                            std::cout << "Please enter yes or no." << std::endl;
                        }
                    }
                }
                players[currentPlayer]->setCanBuy(false);
            }
            if (players[currentPlayer]->getNeedToPayTuition()) {
                bool successInput = false;
                while (!successInput) {
                    if (!events->readLine()) {
                        state = NO_GAME;
                        return;
                    } else {
                        if (events->getCommand() == "1" || events->getCommand() == "2") {
                            int tuition = players[currentPlayer]->payTuition(events->getCommand());
                            bank += tuition;
                            successInput = true;
                        } else {
                            std::cout << "Please enter 1 or 2!" << std::endl;
                        }
                    }
                }
                players[currentPlayer]->setNeedToPayTuition(false);
                /*if (successInput) {
                    return;
                }*/
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
                        if (players[currentPlayer]->getTimsTurn() > 0) {
                            std::cout << "Sorry you are in DC Tims line and you cannot leave yet." << std::endl;
                            continue;
                        }
                        if (mode == NORMAL_GAMEMODE) {
                            if (!players[currentPlayer]->rolled()) {
                                unsigned int firstRoll = Math::rollDice();
                                unsigned int secondRoll = Math::rollDice();
                                if (firstRoll == secondRoll && rollNum == 2) {
                                    players[currentPlayer]->setRolled(true);
                                    players[currentPlayer]->gotoTims();
                                    successInput = true;
                                    rollNum = 0;
                                } else {
                                    unsigned int moveForward = firstRoll + secondRoll;
                                    unsigned int newPosition = players[currentPlayer]->getPosition() + moveForward;
                                    players[currentPlayer]->setPosition(newPosition);
                                    // osap update;
                                    if (40-players[currentPlayer]->getPosition() < moveForward) {
                                        players[currentPlayer]->addBalance(200);
                                        players[currentPlayer]->setPassOSAP(true);
                                    }
                                    if (firstRoll != secondRoll) {
                                        players[currentPlayer]->setRolled(true);
                                    } else {
                                        ++rollNum;
                                    }
                                    successInput = true;
                                }
                            } else {
                                std::cout << "You have rolled already." << std::endl;
                            }
                        } else if (mode == TESTING_GAMEMODE) {
                            if (!players[currentPlayer]->rolled()) {
                                if (Math::isNat(events->getArg(0)) && Math::isNat(events->getArg(1))) {
                                    unsigned int moveForward = std::stoi(events->getArg(0)) + std::stoi(events->getArg(1));
                                    unsigned int newPosition = players[currentPlayer]->getPosition() + std::stoi(events->getArg(0)) + std::stoi(events->getArg(1));
                                    players[currentPlayer]->setPosition(newPosition);
                                    if (40-players[currentPlayer]->getPosition() < moveForward) {
                                        players[currentPlayer]->setPassOSAP(true);
                                        players[currentPlayer]->addBalance(200);
                                    }
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
                        if (players[currentPlayer]->getWillBankrupt() && !players[currentPlayer]->getBankruptcy()) {
                            std::cout << "You cannot go to next turn yet." << std::endl;
                            std::cout << "You must try to raise your balance and pay for what you owe or claim bankruptcy." << std::endl;
                        } else {
                            nextTurn();
                            successInput = true;
                        }
                    } else if (events->getCommand() == "trade") {
                        trade();
                        successInput = true;
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
                                                        players[currentPlayer]->changeAsset(players[currentPlayer]->getAsset()+academics->getImprovementCost());
                                                        players[currentPlayer]->decBalance(academics->getImprovementCost(), nullptr);
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
                                                    players[currentPlayer]->changeAsset(players[currentPlayer]->getAsset()-academics->getImprovementCost());
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
                        if (players[currentPlayer]->getWillBankrupt()) {
                            players[currentPlayer]->setBankruptcy(true);
                            std::cout << players[currentPlayer]->getName() << " claimed bankruptcy!" << std::endl;
                            if (players[currentPlayer]->getOwedPlayer()) {
                                for (auto& square : squares) {
                                    std::shared_ptr<Building> building = std::dynamic_pointer_cast<Building>(square);
                                    if (building && building->getOwner() == players[currentPlayer]) {
                                        building->setOwner(players[currentPlayer]->getOwedPlayer());
                                    }
                                }
                                players[currentPlayer]->getOwedPlayer()->changeAsset(
                                    players[currentPlayer]->getOwedPlayer()->getAsset() + players[currentPlayer]->getAsset());
                                std::cout << players[currentPlayer]->getName() << "'s assets are now owned by '" 
                                    << players[currentPlayer]->getOwedPlayer()->getName() << "'s" << std::endl;
                            } else {
                                for (auto& square : squares) {
                                    std::shared_ptr<Building> building = std::dynamic_pointer_cast<Building>(square);
                                    std::cout << players[currentPlayer]->getName() << "'s assets are now returned to the open market." << std::endl;
                                    if (building && building->getOwner() == players[currentPlayer]) {
                                        building->setMortgage(false);
                                        auction(building);
                                    }
                                }
                            }
                            successInput = true;
                        } else {
                            std::cout << "You do not owe anyone anything! You can continue playing ;)" << std::endl;
                        }
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

                if (players[currentPlayer]->getWillBankrupt()) {
                    if (players[currentPlayer]->getBalance() >= players[currentPlayer]->getOwedMoney()) {
                        std::cout << "You now have $" << players[currentPlayer]->getBalance() << std::endl;
                        players[currentPlayer]->decBalance(players[currentPlayer]->getOwedMoney(), players[currentPlayer]->getOwedPlayer());
                        if (players[currentPlayer]->getOwedPlayer()) {
                            players[currentPlayer]->getOwedPlayer()->addBalance(players[currentPlayer]->getOwedMoney());
                            std::cout << "You paid " << players[currentPlayer]->getOwedPlayer()->getName() 
                                << " $" << players[currentPlayer]->getOwedMoney() << " for what you owe." << std::endl;
                        } else {
                            std::cout << "You paid the bank $" << players[currentPlayer]->getOwedMoney() << " for what you owe." << std::endl;
                        }
                        players[currentPlayer]->setOwedMoney(0);
                        std::cout << "You do not owe anyone anything now." << std::endl;
                        players[currentPlayer]->setWillBankrupt(false);
                    }
                }
            }
            break;
        }
        case WON_GAME: {
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
                square->update(players, gfx);
            }
            state = IN_GAME;
            break;
        }
        case IN_GAME: {
            gfx->resetMsg();
            for (auto& square : squares) {
                std::shared_ptr<Building> building = std::dynamic_pointer_cast<Building>(square);
                if (building) {
                    building->update(players, gfx);
                }
            }
            for (auto& square : squares) {
                std::shared_ptr<DCtims> dctims = std::dynamic_pointer_cast<DCtims>(square);
                if (!dctims) {
                    square->update(players, gfx);
                }
            }
            for (auto& square : squares) {
                std::shared_ptr<DCtims> dctims = std::dynamic_pointer_cast<DCtims>(square);
                if (dctims) {
                    dctims->setCurrentPlayer(currentPlayer);
                    dctims->update(players, gfx);
                }
            }
            std::shared_ptr<SLC> slc1 = std::dynamic_pointer_cast<SLC>(squares[2]);
            std::shared_ptr<SLC> slc2 = std::dynamic_pointer_cast<SLC>(squares[17]);
            std::shared_ptr<SLC> slc3 = std::dynamic_pointer_cast<SLC>(squares[33]);
            SLCmove moves[3];
            moves[0] = slc1->getMove();
            moves[1] = slc2->getMove();
            moves[2] = slc3->getMove();
            for (int i = 0; i < 3; ++i) {
                if (moves[i] != NONE) {
                    for (auto& square : squares) {
                        square->update(players, gfx);
                    }
                    break;
                }
            }
            if (players[currentPlayer]->getWillBankrupt()) {
                if (players[currentPlayer]->getOwedPlayer()) {
                    gfx->addMsg("Warning! You owe " + players[currentPlayer]->getOwedPlayer()->getName() + 
                        " $" + std::to_string(players[currentPlayer]->getOwedMoney()) + ".\n");
                } else {
                    gfx->addMsg("Warning! You owe bank $" + std::to_string(players[currentPlayer]->getOwedMoney()) + ".\n");
                }
            }
            break;
        }
        case WON_GAME: {
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
            std::cout << "================================================================================" << std::endl;
            std::cout << "Congratulations! " << players[currentPlayer]->getName() << " is the final winner!" << std::endl;
            std::cout << "This is your final assets summary:" << std::endl;
            showPlayerAssets(currentPlayer);
            state = NO_GAME;
            break;
        }
    }
    
}
