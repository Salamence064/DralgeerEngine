#pragma once

#include <string>
#include <stdexcept>
#include <GLFW/glfw3.h>

namespace Dralgeer {
    class Window {
        private:
            uint16_t width, height;
            std::string title;
            GLFWwindow* window;

        public:
            Window(uint16_t width, uint16_t height, std::string title) : width(width), height(height), title(title) {};

            // * =========================================
            // * Rule of 3 to ensure no reassignment.
            // * =========================================

            Window(Window const &w) { throw std::runtime_error("Dralgeer::Window objects CANNOT be created from another Dralgeer::Window object."); };
            Window& operator = (Window const &w) { throw std::runtime_error("Dralgeer::Window objects CANNOT be assigned or reassigned."); };

            void init() {
                if (!glfwInit()) { throw std::runtime_error("GLFW failed to initialize."); } // initialize glfw

                // create the window
                window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
                if (!window) { throw std::runtime_error("The window failed to be created."); }

                glfwMakeContextCurrent(window); // make the window's context current
                glfwSwapInterval(1); // enable v-sync

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
                glfwTerminate();
            };

            ~Window() { delete window; };
    };
}
