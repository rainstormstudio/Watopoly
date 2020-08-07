#include "game.h"

int main(int argc, char *argv[]) {
    Game game = Game();
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
