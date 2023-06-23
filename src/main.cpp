#define STB_IMAGE_IMPLEMENTATION
#include <Dralgeer/window.h>

int main() {
    Dralgeer::Window::init(1920, 1080, "Dungeon of Dralgeer");
    Dralgeer::Window::run();
    Dralgeer::Window::destroy();
    return 0;
};
