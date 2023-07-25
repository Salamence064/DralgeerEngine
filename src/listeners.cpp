#include <Dralgeer/listeners.h>

namespace Dralgeer {
    namespace MouseListener {
        float mScrollX = 0, mScrollY = 0;
        float mX = 0, mY = 0, mLastX = 0, mLastY = 0;
        float mWorldX = 0, mWorldY = 0, mLastWorldX = 0, mLastWorldY = 0;

        int mButtonsDown = 0;
        bool mIsDragging = 0;
        bool mButtonPressed[9] = {0};

        float mGameViewPortX = 0.0f, mGameViewPortY = 0.0f;
        float mGameViewPortWidth = 0.0f, mGameViewPortHeight = 0.0f;
    }

    namespace KeyListener {
        bool keyPressed[350] = {0};
    }

    namespace JoystickListener {
        int jId = GLFW_JOYSTICK_1;
        bool jConnected = glfwJoystickPresent(jId);
        bool jGamepad = glfwJoystickIsGamepad(jId);
    }
}
