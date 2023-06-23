#ifndef WINDOW_H
#define WINDOW_H

// todo go through and make sure all memory allocated on the GPU is properly disposed of (with destructors and other stuff)
// todo go through and make certain constructors inline

#include <IMGUI/imgui.h>
#include "scene.h"
#include "debugdraw.h"

namespace Dralgeer {
    struct WindowData {
        uint16_t width, height;
        std::string title;
    };

    // Model a window
    namespace Window {
        static WindowData data;
        static GLFWwindow* window;
        static Scene* currScene = nullptr;

        inline static void changeScene(SceneType scene) {
            switch(scene) {
                case SceneType::LEVEL_EDITOR_SCENE: {
                    delete currScene;
                    currScene = new LevelEditorScene();
                    currScene->init();
                    break;
                }
            }
        };

        static void init(uint16_t width, uint16_t height, std::string const &title) {
            data = {width, height, title};

            // error callback
            glfwSetErrorCallback(ErrorListener::errorCallback);

            // initialize glfw
            if (!glfwInit()) { throw std::runtime_error("GLFW failed to initialize."); }

            // todo could add some sort of check here for various OS's
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
            glfwSetJoystickCallback(JoystickListener::joystick_callback);

            // enable alpha blending
            glEnable(GL_BLEND);
            glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

            // frame buffer config
            // todo will add

            // initialize imgui

            // initialize scene
            currScene = new LevelEditorScene();
            currScene->init();
        };

        static void run() {
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

        static void destroy() {
            glfwDestroyWindow(window);
            glfwSetErrorCallback(NULL);
            glfwTerminate();
            delete currScene;
        };
    }
}

#endif // ! WINDOW_H
