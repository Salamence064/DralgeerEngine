#pragma once

#include <iostream>

namespace Dralgeer {
    // * ===================
    // * Error Listener
    // * ===================

    namespace ErrorListener {
        static void errorCallback(int error_code, const char* description) {
            std::cout << "Error " << error_code << ": " << description << "\n";
        };
    }

    // * ====================
    // * Mouse Listener
    // * ====================

    namespace MouseListener { // todo add ImGui stuff
        static float mScrollX = 0, mScrollY = 0;
        static float mX = 0, mY = 0, mLastX = 0, mLastY = 0;
        static float mWorldX = 0, mWorldY = 0, mLastWorldX = 0, mLastWorldY = 0;

        static uint8_t mButtonsDown = 0;
        static bool mIsDragging = 0;
        static bool mButtonPressed[9] = {0};

        static float mGameViewPortX = 0.0f, mGameViewPortY = 0.0f;
        static float mGameViewPortWidth = 0.0f, mGameViewPortHeight = 0.0f;

        extern float calcOrthoX();
        extern float calcOrthoY();

        static void CursoPositionCallback(GLFWwindow* window, double xpos, double ypos) {
            if (mButtonsDown) { mIsDragging = 1; }

            mLastX = mX;
            mLastY = mY;

            mLastWorldX = mWorldX;
            mLastWorldY = mWorldY;
            mWorldX = calcOrthoX();
            mWorldY = calcOrthoY();

            mX = xpos;
            mY = ypos;
        };

        static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
            if (button < 9) {
                if (action == GLFW_PRESS) {
                    mButtonsDown++;
                    mButtonPressed[button] = 1;

                } else if (action == GLFW_RELEASE) {
                    mButtonsDown--;
                    mButtonPressed[button] = 0;
                    mIsDragging = 0;
                }
            }
        };

        static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
            mScrollX = xoffset;
            mScrollY = yoffset;
        };

        inline static void endFrame() {
            mScrollX = 0; mScrollY = 0;
            mLastX = mX; mLastY = mY;
            mLastWorldX = mWorldX; mLastWorldY = mWorldY;
        };

        inline static float getScreenX() { return ((mX - mGameViewPortX)/mGameViewPortWidth) * 1920.0f; };
        inline static float getScreenY() { return 1080.0f - (((mY - mGameViewPortY)/mGameViewPortHeight) * 1080.0f); };
    }

    // * ==================
    // * Key Listener
    // * ==================

    namespace KeyListener {
        static bool keyPressed[350] = {0};

        static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
            if (key < 350) {
                if (action == GLFW_PRESS) { keyPressed[key] = 1; }
                else if (action == GLFW_RELEASE) { keyPressed[key] = 0; }
            }
        };
    }

    // * =====================
    // * Joystick Listener
    // * =====================

    namespace JoystickListener {
        static int jId = GLFW_JOYSTICK_1;
        static bool jConnected = glfwJoystickPresent(jId);
        static bool jGamepad = glfwJoystickIsGamepad(jId);

        static void joystickCallback(int jid, int event) {
            if (jid != jId) { return; }

            // check for connections and disconnections
            if (event == GLFW_CONNECTED) {
                jConnected = 1;
                jGamepad = glfwJoystickIsGamepad(jId);

            } else if (event == GLFW_DISCONNECTED) {
                jConnected = 0;
                jGamepad = 0;
            }
        };
    }
}