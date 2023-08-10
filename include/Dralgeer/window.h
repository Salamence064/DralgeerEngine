#pragma once

// todo go through and ensure no memory leaks, especially in move assignment operators

// todo go through and make sure all memory allocated on the GPU is properly disposed of (with destructors and other stuff)
// todo go through and make certain constructors inline

// todo delete vao and buffers for the other things that use them too in the destructor

// todo go through and do not delete textures when they're inside of a container, only do so in the AssetPool afterwards and ensure
// todo  everything adds textures to the AssetPool

// todo go through all the stuff that uses the Windows namespace outside of windows.h and refactor it to be based around parameters passed to a function
// todo this one has been done but only with ideas through todos

// todo there are likely leaks in this engine

// todo at some point determine better values for the starting positions for the ImGui stuff
// todo at some point organize the .h files into some directories

// todo make sure that each texture is added to the assetpool (we could also try to do the same for shaders and sprites, too, but not as useful)

// todo artifacts occur when placing sprites on top of each other (actually placing them on top of each other could be useful)
// todo later will add a feature to filter out specific sprite types from being placed on top but others can be placed on top

// todo Remove the abstract classes in favor of void* + enum values

// todo create a header that stores macros for debug, info, warning, and error messages

// ===================================================================
// List of what to fix
// // - Framebuffer causes screen tearing
// // - ImGui docking space
// // - Get GridLines to draw in the gameview window (this will be accomplished when the framebuffer works to properly draw to the gameview window)
// // - Pick up the Sprite selected from the ImGui menu
// // - Place down the sprite on the gameview window (and only there)
// // - Add a drag click feature
// - PickingTexture stuff for the properties window
// // - port over gizmos
// - setup physics (update Zeta2D, too)
// - setup serialization
// - port over the ImGui stuff to fully furnish the properties window
// // - port over the event system
// // - make the stuff void* with an enum
// - fix the rule of 5 operators for the classes I have them for
// - fix the renderer thing by making it a class and adding the zIndex stuff (test to see if buffering greater than the max buffer size causes an error)
// - make a scene selector in the level editor scene
// - go through the rest of the 2D engine series and see what final things I need to add
// - organize the headers
// ===================================================================

#include "event.h"
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
    namespace Window { // todo because this shit is static it can't be accessed by outside .cpp files -- maybe change the currScene one if I find it to be necessary
        static WindowData data;
        static GLFWwindow* window;
        static Scene currScene;

        static ImGuiLayer imGuiLayer;
        static FrameBuffer frameBuffer;
        static PickingTexture* pickingTexture;

        // static bool initGamepadState = 1;
        // static GLFWgamepadstate gamepadState;

        static bool runtimePlaying = 0; // Is the scene being played?

        inline static void changeScene(SceneType scene) {
            switch(scene) {
                case LEVEL_EDITOR_SCENE: {
                    LevelEditorScene* newScene = new LevelEditorScene();
                    // newScene->load();
                    newScene->init();
                    newScene->start();

                    // free the memory of the old scene
                    switch(currScene.type) {
                        case LEVEL_EDITOR_SCENE: { delete (LevelEditorScene*) currScene.scene; break; }
                    }

                    currScene.scene = newScene;
                    currScene.type = LEVEL_EDITOR_SCENE;

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
            pickingTexture = new PickingTexture();
            pickingTexture->init(1920, 1080);
            glViewport(0, 0, 1920, 1080);

            // initialize imgui
            imGuiLayer.init(window, pickingTexture);

            // initialize scene
            LevelEditorScene* scene = new LevelEditorScene();
            // scene->load();
            scene->init();
            scene->start();
            currScene.scene = scene;
            currScene.type = LEVEL_EDITOR_SCENE;
        };

        inline static void run() {
            float startTime = (float) glfwGetTime(), endTime;
            float dt = 0.0f;

            DebugDraw::start();

            // DebugDraw::addLine2D(glm::vec2(10, 10), glm::vec2(300, 10), glm::vec3(0, 0, 1), 250);
            // DebugDraw::addLine2D(glm::vec2(10, 100), glm::vec2(300, 100), glm::vec3(0.8824f, 0.0039f, 0.0039f), 250);

            // DebugDraw::addLine2D(glm::vec2(0, 0), glm::vec2(0, 32), glm::vec3(0.5, 1, 0));
            // DebugDraw::addLine2D(glm::vec2(0, 0), glm::vec2(32, 0), glm::vec3(0.5, 1, 0));
            // DebugDraw::addLine2D(glm::vec2(32, 0), glm::vec2(32, 32), glm::vec3(0.5, 1, 0));
            // DebugDraw::addLine2D(glm::vec2(0, 32), glm::vec2(32, 32), glm::vec3(0.5, 1, 0));

            // DebugDraw::addLine2D(glm::vec2(32, 32), glm::vec2(32, 64), glm::vec3(0.5, 1, 0));
            // DebugDraw::addLine2D(glm::vec2(32, 32), glm::vec2(64, 32), glm::vec3(0.5, 1, 0));
            // DebugDraw::addLine2D(glm::vec2(64, 32), glm::vec2(64, 64), glm::vec3(0.5, 1, 0));
            // DebugDraw::addLine2D(glm::vec2(32, 64), glm::vec2(64, 64), glm::vec3(0.5, 1, 0));

            DebugDraw::addLine2D(glm::vec2(736, 416), glm::vec2(736, 438), glm::vec3(0.5f, 1, 0.0f));

            Shader defaultShader = *(AssetPool::getShader("../../assets/shaders/default.glsl"));
            Shader pickingShader = *(AssetPool::getShader("../../assets/shaders/pickingShader.glsl"));

            // * Game Loop
            while(!glfwWindowShouldClose(window)) {
                // Poll for events and update
                glfwPollEvents();

                // determine the activeScene's type
                switch(currScene.type) {
                    case LEVEL_EDITOR_SCENE: {
                        LevelEditorScene* activeScene = (LevelEditorScene*) currScene.scene;

                        // update the scene
                        activeScene->update(dt, imGuiLayer.gameViewWindow.getWantCaptureMouse());

                        // render picking texture
                        glDisable(GL_BLEND);
                        pickingTexture->enableWriting();

                        glViewport(0, 0, 1920, 1080); // todo not sure if this is needed. Test after getting it to work (ahhhhhhh)
                        glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // todo this is what the mouse picking gives as the numbers
                        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                        // todo possibly the mouse pos isnt being obtained properly

                        // todo we need to create an imgui offset for the tab bar to calc the pos precisely
                        // todo use imguicursorpos to achieve this

                        // todo regardless of the fbo I attach it to, it just outputs the color of the glClearColor
                        // todo and not clearing the color outputs 0, 0, 0


                        // todo issue seems to be a combo of code structure as the glClearColor call makes it so the rendered scene doesnt work for it
                        // todo and the coordinate system might be fucked since it doesnt work consistently when drag placing


                        // todo part of the issue is when glReadPixels is reading the pixels it reads an entire quad as one of the sprites in it

                        activeScene->render(pickingShader);

                        pickingTexture->disableWriting();
                        glEnable(GL_BLEND);

                        // render the visual for the scene
                        DebugDraw::beginFrame();
                        frameBuffer.bind();

                        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
                        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                        glEnable(GL_DEPTH_TEST);

                        // todo put this segment in the dt loop when I set it up -------------------
                        DebugDraw::draw(activeScene->camera);
                        activeScene->render(defaultShader);
                        // -------------------------------------------------------------------------

                        glDisable(GL_DEPTH_TEST);
                        frameBuffer.unbind();

                        // clear the main screen's background
                        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
                        glClear(GL_COLOR_BUFFER_BIT);

                        // MouseListener and ImGui updates
                        MouseListener::updateWorldCoords(activeScene->camera);
                        imGuiLayer.update(dt, activeScene, currScene.type, frameBuffer.getTextureID(), data.width, data.height);

                        // ! for debugging ------------------
                        if (KeyListener::keyPressed[GLFW_KEY_W]) {
                            // todo same quad issue. Really confused what is causing it

                            pickingTexture->test = 0;
                            pickingTexture->enableWriting();
                            glReadBuffer(GL_COLOR_ATTACHMENT0);

                            float pixels[3];
                            glReadPixels(16, 80, 1, 1, GL_RGB, GL_FLOAT, pixels);

                            std::cout << "Test: ";
                            std::cout << pixels[0] << ", " << pixels[1] << ", " << pixels[2] << "\n";

                            pickingTexture->disableWriting();
                        }
                        // ! --------------------------------

                        break;
                    }
                }

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
            
            // free the memory of the scene
            switch(currScene.type) {
                case LEVEL_EDITOR_SCENE: { delete (LevelEditorScene*) currScene.scene; break; }
            }
        };

        // todo potentially add onNotify functions to PropertiesWindow and scenes that this will call when notified
        inline static void onNotify(EventType event, GameObject* go) {
            switch(event) { // todo add the save stuff when adding serialization
                case START_PLAY: {
                    runtimePlaying = 1;
                    // currScene->save();
                    changeScene(LEVEL_EDITOR_SCENE); // ! I dont think this is necessary
                    break;
                }

                case STOP_PLAY: {
                    runtimePlaying = 0;
                    changeScene(LEVEL_EDITOR_SCENE);
                    break;
                }

                case LOAD_LEVEL: {
                    changeScene(LEVEL_EDITOR_SCENE);
                    break;
                }

                case SAVE_LEVEL: {
                    // currScene->save();
                    break;
                }

                case ADD_GAMEOBJECT_TO_SCENE: {
                    switch (currScene.type) {
                        case LEVEL_EDITOR_SCENE: { ((LevelEditorScene*) currScene.scene)->addGameObject(go); break; }
                    }

                    break;
                }
            }
        };

        inline GameObject* getActiveObject() { return imGuiLayer.propertiesWindow.activeGameObject; };
    }
}
