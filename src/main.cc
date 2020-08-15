#include <iostream>
#include <string>
#include "game.h"
#include "types.h"

int main(int argc, char *argv[]) {
    GameMode mode = NORMAL_GAMEMODE;
    std::string loadfile = "";
    std::string themeName = "";
    for (int i = 1; i < argc; ++i) {
        if (std::string(argv[i]) == "-testing") {
            mode = TESTING_GAMEMODE;
        } else if (std::string(argv[i]) == "-load") {
            if (i + 1 < argc && argv[i + 1][0] != '-') {
                loadfile = std::string(argv[i + 1]);
            } else {
                std::cerr << "No filename specified." << std::endl;
            }
        } else if (std::string(argv[i]) == "-theme") {
            if (i + 1 < argc && argv[i + 1][0] != '-') {
                themeName = std::string(argv[i + 1]);
            } else {
                std::cerr << "No theme name specified." << std::endl;
            }
        } 
    }

    Game game = Game(mode, loadfile, themeName);
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
