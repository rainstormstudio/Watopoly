#include <iostream>
#include <string>
#include "game.h"
#include "types.h"

int main(int argc, char *argv[]) {
    GameMode mode = NORMAL_GAMEMODE;
    std::string loadfile = "";
    for (int i = 1; i < argc; ++i) {
        if (std::string(argv[i]) == "-testing") {
            mode = TESTING_GAMEMODE;
        } else if (std::string(argv[i]) == "-load") {
            if (i + 1 < argc && argv[i + 1][0] != '-') {
                loadfile = std::string(argv[i + 1]);
            } else {
                std::cerr << "No filename specified." << std::endl;
            }
        }
    }

    Game game = Game(mode, loadfile);
    game.init();

    game.render();
    game.processInput();
    while (game.loop()) {
        game.update();
        game.render();
        game.processInput();
    }

    return 0;
}
