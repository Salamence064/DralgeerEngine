#pragma once

#include <string>
#include <stdexcept>
#include <iostream>
#include <GLFW/glfw3.h>

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

    class Window {
        private:
            WindowData data;
            GLFWwindow* window;

            // * =================
            // * Error Callback
            // * =================

            static void errorCallback(int error_code, const char* description) {
                std::cout << "Error " << error_code << ": " << description << "\n";
            };

            // * ==================
            // * Mouse Listener
            // * ==================

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

            // * ===============
            // * Key Listener
            // * ===============

            static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
                if (key < 350) {
                    WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);

                    if (action == GLFW_PRESS) { data.keyPressed[key] = 1; }
                    else if (action == GLFW_RELEASE) { data.keyPressed[key] = 1; }
                }
            };

            // * ====================
            // * Joystick Listener
            // * ====================

            // todo add when event system is set up (as it doesn't have the window as a parameter)
            // static void joystick_callback(int jid, int event) {
                
            // };

        public:
            Window(uint16_t width, uint16_t height, std::string const &title) : data({width, height, title}) {};

            // * =========================================
            // * Rule of 3 to ensure no reassignment.
            // * =========================================

            Window(Window const &w) { throw std::runtime_error("Dralgeer::Window objects CANNOT be created from another Dralgeer::Window object."); };
            Window& operator = (Window const &w) { throw std::runtime_error("Dralgeer::Window objects CANNOT be assigned or reassigned."); };

            void init() {
                // error callback
                glfwSetErrorCallback(errorCallback);

                // initialize glfw
                if (!glfwInit()) { throw std::runtime_error("GLFW failed to initialize."); }

                // configure glfw
                glfwDefaultWindowHints();
                glfwWindowHint(GLFW_VISIBLE, 0);
                glfwWindowHint(GLFW_RESIZABLE, 1);
                glfwWindowHint(GLFW_MAXIMIZED, 1);

                // create the window
                window = glfwCreateWindow(data.width, data.height, data.title.c_str(), NULL, NULL);
                if (!window) { throw std::runtime_error("The window failed to be created."); }

                glfwMakeContextCurrent(window); // make the window's context current
                glfwSetWindowUserPointer(window, &data); // add the data as a pointer to the window
                glfwSwapInterval(1); // enable v-sync
                glfwShowWindow(window); // show the window

                // setup callbacks
                // windows
                glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height) {
                    WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);
                    data.width = width;
                    data.height = height;
                });

                // mouse
                glfwSetCursorPosCallback(window, cursor_position_callback);
                glfwSetMouseButtonCallback(window, mouseButtonCallback);
                glfwSetScrollCallback(window, scroll_callback);

                // keyboard
                glfwSetKeyCallback(window, key_callback);

                // joystick
                // todo will add

                // enable alpha blending
                glEnable(GL_BLEND);
                glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
            };

            void run() {
                float startTime = (float) glfwGetTime(), endTime;
                float dt = 0.0f;

                // * Game Loop
                while(!glfwWindowShouldClose(window)) {
                    // ! Render here
                    glClear(GL_COLOR_BUFFER_BIT);

                    glfwSwapBuffers(window); // swaps front and back buffers

                    // Poll for and process events
                    glfwPollEvents();

                    // handle the dt value
                    endTime = (float) glfwGetTime();
                    dt += endTime - startTime;
                    startTime = endTime;
                }
            };

            void destroy() {
                glfwDestroyWindow(window);
                glfwSetErrorCallback(NULL);
                glfwTerminate();
            };
    };
}
