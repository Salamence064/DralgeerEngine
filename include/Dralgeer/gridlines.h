#pragma once

#include "components/component.h"

namespace Dralgeer {
    class GridLines : public Component {
        public:
            inline void update(float dt) override; // todo make once we have scenes and a way to access the window data
    };
}
