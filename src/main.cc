#include "game.h"
#include "types.h"

int main(int argc, char *argv[]) {
    GameMode mode = NORMAL_GAMEMODE;
    for (int i = 1; i < argc; ++i) {
        if (std::string(argv[i]) == "-testing") {
            mode = TESTING_GAMEMODE;
        }
    }
    Game game = Game(mode);
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
