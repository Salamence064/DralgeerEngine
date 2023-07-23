#pragma once

#include <iostream>
#include <Dralgeer/camera.h>
#include <GLFW/glfw3.h>

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

    namespace MouseListener {
        static float mScrollX = 0, mScrollY = 0;
        static float mX = 0, mY = 0, mLastX = 0, mLastY = 0;
        extern float mWorldX, mWorldY, mLastWorldX, mLastWorldY;

        static uint8_t mButtonsDown = 0;
        static bool mIsDragging = 0;
        extern bool mButtonPressed[9];

        extern float mGameViewPortX, mGameViewPortY;
        extern float mGameViewPortWidth, mGameViewPortHeight;

        static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
            if (mButtonsDown) { mIsDragging = 1; }

            mLastX = mX;
            mLastY = mY;
            mX = xpos;
            mY = ypos;
        };

        static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
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

        static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
            mScrollX = xoffset;
            mScrollY = yoffset;
        };

        inline static void endFrame() { // todo not so sure if the lastX updates are necessary here
            mScrollX = 0; mScrollY = 0;
            mLastX = mX; mLastY = mY;
            mLastWorldX = mWorldX; mLastWorldY = mWorldY;
        };

        inline static float getScreenX() { return ((mX - mGameViewPortX)/mGameViewPortWidth) * 1920.0f; };
        inline static float getScreenY() { return 1080.0f - (((mY - mGameViewPortY)/mGameViewPortHeight) * 1080.0f); };

        inline void updateWorldCoords(Camera const &cam) {
            mLastWorldX = mWorldX;
            mLastWorldY = mWorldY;

            glm::mat4 prod = cam.invView * cam.invProj;
            mWorldX = (prod * glm::vec4(((mX - mGameViewPortX)/mGameViewPortWidth) * 2.0f - 1.0f, 0.0f, 0.0f, 1.0f)).x;
            mWorldY = (prod * glm::vec4(0.0f, -(((mY - mGameViewPortY)/mGameViewPortHeight) * 2.0f - 1.0f), 0.0f, 1.0f)).y;
        };
    }

    // * ==================
    // * Key Listener
    // * ==================

    namespace KeyListener {
        static bool keyPressed[350] = {0};

        static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
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

        static void joystick_callback(int jid, int event) {
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