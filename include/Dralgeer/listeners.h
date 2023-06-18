#pragma once

#include <string>

namespace Dralgeer {
    struct WindowData {
        // * =================
        // * Standard Data
        // * =================

        uint16_t width, height;
        std::string title;

        // * =========================
        // * Mouse Listener Stuff
        // * =========================

        double mScrollX = 0, mScrollY = 0;
        double mX = 0, mY = 0, mLastX = 0, mLastY = 0;
        // double mWorldX = 0, mWorldY = 0, mLastWorldX = 0, mLastWorldY = 0; // todo add when adding Dear ImGUI

        uint8_t mButtonsDown = 0;
        bool mIsDragging = 0;
        bool mButtonPressed[9] = {0};

        // * ======================
        // * Key Listener Stuff
        // * ======================

        bool keyPressed[350] = {0};

        // * ===========================
        // * Joystick Listener Stuff
        // * ===========================

        // int jId;
        // bool jConnected, jGamepad;
    };

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
        // todo fill this out more once adding ImGui stuff

        static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
            WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);
            
            if (data.mButtonsDown) { data.mIsDragging = 1; }

            data.mLastX = data.mX;
            data.mLastY = data.mY;
            data.mX = xpos;
            data.mY = ypos;
        };

        static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
            WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);

            if (button < 9) {
                if (action == GLFW_PRESS) {
                    data.mButtonsDown++;
                    data.mButtonPressed[button] = 1;

                } else if (action == GLFW_RELEASE) {
                    data.mButtonsDown--;
                    data.mButtonPressed[button] = 0;
                    data.mIsDragging = 0;
                }
            }
        };

        static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
            WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);

            data.mScrollX = xoffset;
            data.mScrollY = yoffset;
        };
    }

    // * ==================
    // * Key Listener
    // * ==================

    namespace KeyListener {
        static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
            if (key < 350) {
                WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);

                if (action == GLFW_PRESS) { data.keyPressed[key] = 1; }
                else if (action == GLFW_RELEASE) { data.keyPressed[key] = 1; }
            }
        };
    }

    // * =====================
    // * Joystick Listener
    // * =====================

    namespace JoystickListener {
        // todo add when event system is set up (as it doesn't have the window as a parameter)
        // static void joystick_callback(int jid, int event) {
            
        // };
    }
}