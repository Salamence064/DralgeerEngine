#pragma once

#include "assetpool.h"
#include "camera.h"

namespace Dralgeer { // todo set it up to use -1 to indicate infinite lifetime
    namespace DebugDraw {
        struct Line2D {
            glm::vec2 start;
            glm::vec2 end;
            glm::vec3 color;
            int lifetime;
            bool isDirty = 1;
        };


        extern Line2D* lines;
        extern int numLines;
        extern int capacity;

        // 6 floats per vertex, 2 vertices per line
        extern float vertices[DEBUG_VERTEX_ARR_SIZE];
        extern Shader shader;

        extern unsigned int vaoID, vboID;
        extern bool started;

        inline void loadVertexProperties(int index) {
            int offset = index * 2 * DEBUG_VERTEX_SIZE;

            // * Starting vertex
            // load position
            vertices[offset] = lines[index].start.x;
            vertices[offset + 1] = lines[index].start.y;

            // load color
            vertices[offset + 2] = lines[index].color.x;
            vertices[offset + 3] = lines[index].color.y;
            vertices[offset + 4] = lines[index].color.z;

            // * Ending vertex
            // load position
            vertices[offset + 5] = lines[index].end.x;
            vertices[offset + 6] = lines[index].end.y;

            // load color
            vertices[offset + 7] = lines[index].color.x;
            vertices[offset + 8] = lines[index].color.y;
            vertices[offset + 9] = lines[index].color.z;
        };

        inline void start() {
            // initialize the shader
            shader = *(AssetPool::getShader("../../assets/shaders/debugLine2D.glsl"));

            // generate the VAO
            glGenVertexArrays(1, &vaoID);
            glBindVertexArray(vaoID);

            // create the VBO and buffer some memory
            glGenBuffers(1, &vboID);
            glBindBuffer(GL_ARRAY_BUFFER, vboID);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

            // enable the vertex array attributes
            glVertexAttribPointer(0, 2, GL_FLOAT, 0, DEBUG_VERTEX_SIZE_BYTES, (void*) 0);
            glVertexAttribPointer(1, 3, GL_FLOAT, 0, DEBUG_VERTEX_SIZE_BYTES, (void*) DEBUG_COLOR_OFFSET);
            glEnableVertexAttribArray(0);
            glEnableVertexAttribArray(1);

            glLineWidth(2.0f);
            started = 1;
        };

        inline void beginFrame() {
            if (!started) { start(); }

            // remove dead lines
            for (int i = numLines - 1; i >= 0; i--) {
                if (--lines[i].lifetime < 0) {
                    numLines--;
                    for (int j = i; j < numLines; ++j) {
                        lines[j] = lines[j + 1];
                        lines[j].isDirty = 1;
                    }
                }
            }
        };

        inline void draw(Camera const &cam) {
            if (!numLines) { return; }

            bool rebuffer = 0;

            for (int i = 0; i < numLines; ++i) {
                if (lines[i].isDirty) {
                    loadVertexProperties(i);
                    lines[i].isDirty = 0;
                    rebuffer = 1;
                }
            }

            if (rebuffer) {
                glBindBuffer(GL_ARRAY_BUFFER, vboID);
                glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // todo causes invalid value error (error 0x0501)

                // GLenum err;
                // while((err = glGetError()) != GL_NO_ERROR) {
                //     std::cout << "[Error] " << err << "\n";
                // }

                glBindBuffer(GL_ARRAY_BUFFER, 0);
            }

            // bind the VAO
            glBindVertexArray(vaoID);
            glEnableVertexAttribArray(0);
            glEnableVertexAttribArray(1);

            // use our shader
            shader.use();
            shader.uploadMat4("uProjection", cam.proj);
            shader.uploadMat4("uView", cam.view);

            // draw the batch
            glDrawArrays(GL_LINES, 0, 2*numLines);

            // disable the location
            glDisableVertexAttribArray(0);
            glDisableVertexAttribArray(1);
            glBindVertexArray(0);

            // unbind shader
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
