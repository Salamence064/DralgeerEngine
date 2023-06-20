#pragma once

#include "components/component.h"

namespace Dralgeer {
    class GridLines : public Component {
        public:
            inline void update(float dt) override; // todo make once we have access to the camera from the current scene in the window
    };
}
