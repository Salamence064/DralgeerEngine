#pragma once

// todo go through and ensure no memory leaks, especially in move assignment operators

// todo go through and make sure all memory allocated on the GPU is properly disposed of (with destructors and other stuff)
// todo go through and make certain constructors inline

// todo I never detach Renderer::currentShader

// todo delete vao and buffers for the other things that use them too in the destructor

// todo go through and do not delete textures when they're inside of a container, only do so in the AssetPool afterwards and ensure
// todo  everything adds textures to the AssetPool

// todo go through all the stuff that uses the Windows namespace outside of windows.h and refactor it to be based around parameters passed to a function
// todo this one has been done but only with ideas through todos

// todo there are likely leaks in this engine

// todo at some point determine better values for the starting positions for the ImGui stuff
// todo at some point organize the .h files into some directories

// todo make sure that each texture is added to the assetpool (we could also try to do the same for shaders and sprites, too, but not as useful)

// ===================================================================
// List of what to fix
// // - Framebuffer causes screen tearing
// // - ImGui docking space
// // - Get GridLines to draw in the gameview window (this will be accomplished when the framebuffer works to properly draw to the gameview window)
// // - Pick up the Sprite selected from the ImGui menu
// // - Place down the sprite on the gameview window (and only there)
// - Memory leak(s) and artifacts from placing sprites
// - Add a drag click feature
// ===================================================================

// what the framebuffer does is allow me to draw to the null texture on it
// I can then place this framebuffer texture on the ImGui for the GameviewWindow, displaying the scene in the gameview window instead

#include "imguilayer.h"
#include "listeners.h"
#include "render.h"
#include "debugdraw.h"

namespace Dralgeer {
    struct WindowData {
        int width, height;
        std::string title;
    };

    // Model a window
    namespace Window {
        static WindowData data;
        static GLFWwindow* window;
        static Scene* currScene = nullptr;

        static ImGuiLayer imGuiLayer;
        static FrameBuffer frameBuffer;
        static PickingTexture pickingTexture;

        // static bool initGamepadState = 1;
        // static GLFWgamepadstate gamepadState;

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

        inline static void init(uint16_t width, uint16_t height, std::string const &title) {
            data = {width, height, title};

            // error callback
            glfwSetErrorCallback(ErrorListener::errorCallback);

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
            glfwSetMouseButtonCallback(window, MouseListener::mouse_button_callback);
            glfwSetScrollCallback(window, MouseListener::scroll_callback);

            // keyboard
            glfwSetKeyCallback(window, KeyListener::key_callback);

            // joystick
            glfwSetJoystickCallback(JoystickListener::joystick_callback);

            // enable alpha blending
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            // frame buffer config
            frameBuffer.init(1920, 1080);
            pickingTexture.init(1920, 1080);
            glViewport(0, 0, 1920, 1080);

            // initialize imgui
            imGuiLayer.init(window, pickingTexture);

            // initialize scene
            currScene = new LevelEditorScene();
            currScene->init();
        };

        inline static void run() {
            float startTime = (float) glfwGetTime(), endTime;
            float dt = 0.0f;

            DebugDraw::start();
            currScene->start();

            // DebugDraw::addLine2D(glm::vec2(10, 10), glm::vec2(300, 10), glm::vec3(0, 0, 1), 250);
            // DebugDraw::addLine2D(glm::vec2(10, 100), glm::vec2(300, 100), glm::vec3(0.8824f, 0.0039f, 0.0039f), 250);

            Shader defaultShader = *(AssetPool::getShader("../../assets/shaders/default.glsl"));
            Shader pickingShader = *(AssetPool::getShader("../../assets/shaders/pickingShader.glsl"));

            // * Game Loop
            while(!glfwWindowShouldClose(window)) {
                // Poll for events
                glfwPollEvents();

                // render picking texture
                glDisable(GL_BLEND);
                pickingTexture.enableWriting();

                glViewport(0, 0, 1920, 1080);
                glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                currScene->render(pickingShader);

                pickingTexture.disableWriting();
                glEnable(GL_BLEND);

                // render the actual game
                DebugDraw::beginFrame();
                frameBuffer.bind();

                glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                glEnable(GL_DEPTH_TEST);

                DebugDraw::draw(currScene->camera);
                currScene->update(dt, imGuiLayer.gameViewWindow.getWantCaptureMouse());
                currScene->render(defaultShader);

                glDisable(GL_DEPTH_TEST);
                frameBuffer.unbind();

                // clear the main screen's background
                glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
                glClear(GL_COLOR_BUFFER_BIT);

                MouseListener::updateWorldCoords(currScene->camera);
                imGuiLayer.update(dt, currScene, frameBuffer.getTextureID(), data.width, data.height);

                // initialize the gamepadState // todo set up later
                // if (initGamepadState && JoystickListener::jConnected && JoystickListener::jGamepad) {
                //     gamepadState = 
                // }

                if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
                    GLFWwindow* backupWindow = glfwGetCurrentContext();
                    ImGui::UpdatePlatformWindows();
                    ImGui::RenderPlatformWindowsDefault();
                    glfwMakeContextCurrent(backupWindow);
                }

                glfwSwapBuffers(window); // swaps front and back buffers
                MouseListener::endFrame();
                
                // handle the dt value
                endTime = (float) glfwGetTime();
                dt += endTime - startTime;
                startTime = endTime;

                // * Check for errors to make it easier to debug
                // ! this will be removed in the final build
                // GLenum err;
                // while((err = glGetError()) != GL_NO_ERROR) {
                //     std::cout << "[Error] " << err << "\n";
                // }
            }
        };

        inline static void destroy() {
            DebugDraw::destroy();
            AssetPool::destroy();
            imGuiLayer.dispose();
            glfwDestroyWindow(window);
            glfwSetErrorCallback(NULL);
            glfwTerminate();
            delete currScene;
        };
    }
}
