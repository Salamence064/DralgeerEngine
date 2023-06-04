#pragma once

#include "../camera.h"

namespace Dralgeer {
    class Scene {
        private:
            bool isRunning = 0;
            // ! renderer

        public:
            Camera camera;
            // ! list of game objects
    };
}
