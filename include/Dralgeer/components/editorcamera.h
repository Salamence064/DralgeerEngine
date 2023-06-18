#pragma once

#include "component.h"
#include "../camera.h"

// Editor camera constants
#define EDITOR_DRAG_SENSITIVITY 30.0f
#define EDITOR_SCROLL_SENSITIVITY 0.1f

namespace Dralgeer {
    class EditorCamera : public Component {
        private:
            float dragDebounce = 0.032f;
            float lerpTime = 0.0f;
            bool reset = 0;

            Camera camera;
            glm::vec2 clickOrigin;

        public:
            // todo override the update function and add the stuff that would normally be there
            // todo  We will need to figure out a way certain pieces of data can be accessed by this that we will need
    };
}
