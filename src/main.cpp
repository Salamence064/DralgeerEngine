#include "../include/window.h"

int main() {
    Dralgeer::Window window(1920, 1080, "Dungeon of Dralgeer");

    window.init();
    window.run();
    window.destroy();

    return 0;
};
