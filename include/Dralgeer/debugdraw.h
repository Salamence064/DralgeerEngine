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


        extern Line2D* lines;
        extern int numLines;
        extern int capacity;

        // 6 floats per vertex, 2 vertices per line
        extern float vertexArray[DEBUG_VERTEX_ARR_SIZE];
        extern Shader shader;

        extern unsigned int vaoID, vboID;
        extern bool started;

        // ! fuck it, we are using a temporary camera for now -- replace when I finish scene.h
        extern Camera camera; // ! could be the cause of some issues

        inline void start() {
            // initialize the shader
            shader = AssetPool::getShader("C:/VS/DralgeerEngine/assets/shaders/debugLine2D.glsl");

            // generate the VAO
            glGenVertexArrays(1, &vaoID);
            glBindVertexArray(vaoID);

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
            for (int i = numLines - 1; i >= 0; i--) {
                if (lines[i].beginFrame() < 0) { for (int j = i; j < numLines - 1; ++j) { lines[j] = lines[j + 1]; }}
            }
        };

        inline void draw() {
            if (!numLines) { return; }

            int index = 0;
            for (int i = 0; i < numLines; ++i) { // todo the lines are not being drawn to the specifications
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

            int s = 12*numLines;
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

        inline void destroy() { delete lines; };

        inline void addLine2D(glm::vec2 const &start, glm::vec2 const &end, glm::vec3 const &color = glm::vec3(0.882f, 0.004f, 0.004f), int lifetime = 1) {
            if (numLines >= MAX_DEBUG_LINES) { return; }

            if (numLines == capacity) {
                capacity *= 2;
                Line2D* temp = new Line2D[capacity];

                for (int i = 0; i < numLines; ++i) { temp[i] = lines[i]; }

                delete lines;
                lines = temp;
            }

            lines[numLines++] = {start, end, color, lifetime};
        };

        // TODO: add addBox2D funcs
        // TODO: add addCircle funcs
        // TODO: add constants for common colors
    }
}

#endif // !DEBUG_DRAW_H
