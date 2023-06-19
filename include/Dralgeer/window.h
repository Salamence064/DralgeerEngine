#pragma once

// todo go through and make sure all memory allocated on the GPU is properly disposed of (with destructors and other stuff)
// todo go through each class and make sure assignment stuff can't be used for GPU related ones (unless I set it up to call init and stuff)

// todo create the editor library from the existing code-base
// todo go through and make certain constructors inline

#include <IMGUI/imgui.h>
#include "render/debugdraw.h"
#include "listeners.h"

// equivalent of 16:9 aspect ratio
#define TARGET_ASPECT_RATIO 1.77778f

namespace Dralgeer {
    struct WindowData {
        uint16_t width, height;
        std::string title;
    };

    class Window {
        private:
            WindowData data;
            GLFWwindow* window;

        public:
            Window(uint16_t width, uint16_t height, std::string const &title) : data({width, height, title}) {};

            // * =========================================
            // * Rule of 3 to ensure no reassignment.
            // * =========================================

            Window(Window const &w) { throw std::runtime_error("Dralgeer::Window objects CANNOT be created from another Dralgeer::Window object."); };
            Window& operator = (Window const &w) { throw std::runtime_error("Dralgeer::Window objects CANNOT be assigned or reassigned."); };

            void init() {
                // error callback
                glfwSetErrorCallback(ErrorListener::errorCallback);

                // initialize glfw
                if (!glfwInit()) { throw std::runtime_error("GLFW failed to initialize."); }

                // configure glfw
                glfwDefaultWindowHints();
                glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
                glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
                glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
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

                // initialize glew
                if (glewInit() != GLEW_OK) { throw std::runtime_error("GLEW failed to initialize."); }

                // setup callbacks
                // windows
                glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height) {
                    WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);
                    data.width = width;
                    data.height = height;
                });

                // mouse
                glfwSetCursorPosCallback(window, MouseListener::cursor_position_callback);
                glfwSetMouseButtonCallback(window, MouseListener::mouseButtonCallback);
                glfwSetScrollCallback(window, MouseListener::scroll_callback);

                // keyboard
                glfwSetKeyCallback(window, KeyListener::key_callback);

                // joystick
                // todo will add

                // enable alpha blending
                glEnable(GL_BLEND);
                glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

                // frame buffer config
                // todo will add

                // initialize imgui

                // initialize scene
            };

            void run() {
                float startTime = (float) glfwGetTime(), endTime;
                float dt = 0.0f;

                DebugDraw::start();
                DebugDraw::addLine2D(glm::vec2(10, 10), glm::vec2(300, 10), glm::vec3(0, 0, 1), 500);
                DebugDraw::addLine2D(glm::vec2(200, 200), glm::vec2(340, 340), glm::vec3(1, 0, 0), 500);


                // * Game Loop
                while(!glfwWindowShouldClose(window)) {
                    // ! Render here
                    glClear(GL_COLOR_BUFFER_BIT);

                    DebugDraw::beginFrame();
                    DebugDraw::draw();

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
