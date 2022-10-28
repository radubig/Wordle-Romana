#include <iostream>
#include <cstdlib>
#include "WordleGame.h"

const uint32_t cuvSize = 11454; //Nr de cuvinte din dictionar (pentru optimizare la alocare de memorie)

int main() {
    WordleGame game;
    game.hint(cuvSize);
    game.init();
    std::cout << std::endl;
    game.play();

    game.clear();
    return 0;
}
