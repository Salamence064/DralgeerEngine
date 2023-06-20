#ifndef DEBUG_DRAW_H
#define DEBUG_DRAW_H

#include "assetpool.h"

namespace Dralgeer {
    namespace DebugDraw {
        struct Line2D {
            glm::vec2 start;
            glm::vec2 end;
            glm::vec3 color;
            int lifetime;

            inline int beginFrame() {
                lifetime--;
                return lifetime;
            };
        };


        namespace {
            static std::vector<Line2D> lines = {}; // not sure if we even want this
            // probs make a dynamic pointer array

            // 6 floats per vertex, 2 vertices per line
            static float vertexArray[DEBUG_VERTEX_ARR_SIZE];
            static Shader shader;
            // todo issue results from the above line -- maybe use some couts and stuff to debug here shortly
            // todo we can also try dumb stuff like commenting out the annonymous namespaces

            static unsigned int vaoID, vboID;
            static bool started = 0;

            // ! fuck it, we are using a temporary camera for now -- replace when I finish scene.h
            Camera camera = {glm::vec2(0.0f)}; // ! could be the cause of some issues
        }

        inline void start() {
            // initialize the shader
            shader = AssetPool::getShader("C:/VS/DralgeerEngine/assets/shaders/debugLine2D.glsl");

            // generate the VAO
            glGenVertexArrays(1, &vaoID);
            glBindVertexArray(vaoID);

            // todo may have to do with this

            // create the VBO and buffer some memory
            glGenBuffers(1, &vboID);
            glBindBuffer(GL_ARRAY_BUFFER, vboID);
            glBufferData(GL_ARRAY_BUFFER, DEBUG_VERTEX_ARR_SIZE * sizeof(float), vertexArray, GL_DYNAMIC_DRAW);

            // enable the vertex array attributes
            const float* ptr = 0;
            glVertexAttribPointer(0, 3, GL_FLOAT, 0, 6*sizeof(float), ptr);
            glEnable(0);

            ptr += 3*sizeof(float); // todo, this may be causing some issues
            glVertexAttribPointer(1, 3, GL_FLOAT, 0, 6*sizeof(float), ptr);
            glEnable(1);

            glLineWidth(2.0f);
            started = 1;
        };

        inline void beginFrame() {
            if (!started) { start(); }

            // remove dead lines
            for (int i = lines.size() - 1; i >= 0; i--) {
                if (lines[i].beginFrame() < 0) { lines.erase(lines.begin() + i); }
            }
        };

        inline void draw() {
            size_t size = lines.size();
            if (!size) { return; }

            int index = 0;
            for (int i = 0; i < size; ++i) { // todo the lines are not being drawn to the specifications
                // * Populate the vertexArray
                // technically more efficient to not use a loop of two here

                // load starting point
                vertexArray[index] = lines[i].start.x;
                vertexArray[index + 1] = lines[i].start.y;
                vertexArray[index + 2] = 10.0f;

                // load color
                vertexArray[index + 3] = lines[i].color.x;
                vertexArray[index + 4] = lines[i].color.y;
                vertexArray[index + 5] = lines[i].color.z;

                index += 6;


                // load ending point
                vertexArray[index] = lines[i].end.x;
                vertexArray[index + 1] = lines[i].end.y;
                vertexArray[index + 2] = 10.0f;

                // load color
                vertexArray[index + 3] = lines[i].color.x;
                vertexArray[index + 4] = lines[i].color.y;
                vertexArray[index + 5] = lines[i].color.z;

                index += 6;
            }

            // todo issue might be because I don't have a subarray and pass in the full vertex array instead

            size_t s = 12*size;
            glBindBuffer(GL_ARRAY_BUFFER, vboID);
            glBufferSubData(GL_ARRAY_BUFFER, 0, s, vertexArray);

            // ! This is temp code, this will not be here once scenes are made
            camera.adjustProjection();
            camera.adjustView();
            // !==============================================================

            // use our shader
            shader.use();
            shader.uploadMat4("uProjection", camera.proj);
            shader.uploadMat4("uView", camera.view);

            // bind the VAO
            glBindVertexArray(vaoID);
            glEnableVertexAttribArray(0);
            glEnableVertexAttribArray(1);

            // draw the batch
            glDrawArrays(GL_LINES, 0, s);

            // disable the location
            glDisableVertexAttribArray(0);
            glDisableVertexAttribArray(1);
            glBindVertexArray(0);

            // unbind shader and free memory
            shader.detach();
        };

        inline void addLine2D (glm::vec2 const &start, glm::vec2 const &end, glm::vec3 const &color = glm::vec3(0.882f, 0.004f, 0.004f), int lifetime = 1) {
            if (lines.size() >= MAX_DEBUG_LINES) { return; }
            lines.push_back({start, end, color, lifetime});
        };

        // TODO: add addBox2D funcs
        // TODO: add addCircle funcs
        // TODO: add constants for common colors
    }
}

#endif // !DEBUG_DRAW_H
