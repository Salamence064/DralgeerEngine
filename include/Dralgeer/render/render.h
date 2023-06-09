// todo add renderbatch and render in here

#pragma once

#include "../components/sprite.h"
#include <GLM/glm/gtc/matrix_transform.hpp>

#define MAX_RENDER_BATCH_SIZE 1000
#define MAX_RENDER_VERTICES_LIST_SIZE 40000
#define MAX_TEXTURES 16

#define POS_SIZE 2
#define COLOR_SIZE 4
#define TEX_CORDS_SIZE 2
#define TEX_ID_SIZE 1
#define ENTITY_ID_SIZE 1

#define COLOR_OFFSET (POS_SIZE * sizeof(float))
#define TEX_CORDS_OFFSET (COLOR_OFFSET + (COLOR_SIZE * sizeof(float)))
#define TEX_ID_OFFSET (TEX_CORDS_OFFSET + (TEX_CORDS_SIZE * sizeof(float)))
#define ENTITY_ID_OFFSET (TEX_ID_OFFSET + sizeof(float))

#define VERTEX_SIZE 10
#define VERTEX_SIZE_BYTES (VERTEX_SIZE * sizeof(float))

namespace Dralgeer {
    class RenderBatch {
        private:
            SpriteRenderer sprites[MAX_RENDER_BATCH_SIZE];
            float vertices[MAX_RENDER_VERTICES_LIST_SIZE];
            Texture textures[MAX_TEXTURES];
            int texSlots[MAX_TEXTURES] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
            unsigned int vaoID, vboID;

            // * Helper to just make the code easier to read and debug.
            // * Will probs be moved directly into the code in the end.
            inline void loadVertexProperties(int index) {
                int offset = index * 4 * VERTEX_SIZE;

                // Texture ID
                int texID = 0;
                if (sprites[index].sprite.texture != nullptr) {
                    for (int i = 0; i < numTextures; ++i) {
                        if (textures[i] == *(sprites[index].sprite.texture)) {
                            texID = i + 1;
                            break;
                        }
                    }
                }

                // todo add DMath in a utils thing for compare to ensure no floating point errors

                glm::mat4 transformMat(1);
                Transform t = sprites[index].gameObject.transform;

                if (t.rotation) {
                    transformMat = glm::translate(transformMat, glm::vec3(t.pos.x, t.pos.y, 0.0f));
                    transformMat = glm::rotate(transformMat, (float) glm::radians(t.rotation), glm::vec3(0, 0, 1));
                    transformMat = glm::scale(transformMat, glm::vec3(t.scale.x, t.scale.y, 1.0f));
                }

                // add vertices with the appropriate properties
                
            };

        public:
            int numSprites = 0;
            int numTextures = 0;
            // todo if needed add zIndex for the RenderBatch

            RenderBatch() {};

            void start() {
                // generate and bind a vertex array object
                glGenVertexArrays(1, &vaoID);
                glBindVertexArray(vaoID);

                // allocate space for the vertices
                glGenBuffers(1, &vboID);
                glBindBuffer(GL_ARRAY_BUFFER, vboID);
                glBufferData(GL_ARRAY_BUFFER, MAX_RENDER_VERTICES_LIST_SIZE, vertices, GL_DYNAMIC_DRAW);

                // create the indices buffer
                unsigned int eboID = 0;
                glGenBuffers(1, &eboID);
                
                // * --------- Generate the indices ---------

                int offset = 0;
                const int size = 6 * MAX_RENDER_BATCH_SIZE;
                int indices[size];
                for (int index = 0; index < size; index += 6) {
                    // triangle 1
                    indices[index] = offset + 3;
                    indices[index + 1] = offset + 2;
                    indices[index + 2] = offset;

                    // triangle 2
                    indices[index + 3] = offset;
                    indices[index + 4] = offset + 2;
                    indices[index + 5] = offset + 1;

                    offset += 4;
                }

                // * ----------------------------------------

                // upload the indices buffer
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW); // ! might need to pass the subarray (most likely do)

                // todo if an error arises it's likely due to the pointer casting stuff

                // enable the buffer attribute pointers
                glVertexAttribPointer(0, POS_SIZE, GL_FLOAT, 0, VERTEX_SIZE_BYTES, 0);
                glEnableVertexAttribArray(0);

                glVertexAttribPointer(1, COLOR_SIZE, GL_FLOAT, 0, VERTEX_SIZE_BYTES, (int*) COLOR_OFFSET);
                glEnableVertexAttribArray(1);

                glVertexAttribPointer(2, TEX_CORDS_SIZE, GL_FLOAT, 0, VERTEX_SIZE_BYTES, (int*) TEX_CORDS_OFFSET);
                glEnableVertexAttribArray(2);

                glVertexAttribPointer(3, TEX_ID_SIZE, GL_FLOAT, 0, VERTEX_SIZE_BYTES, (int*) TEX_ID_OFFSET);
                glEnableVertexAttribArray(3);

                glVertexAttribPointer(4, ENTITY_ID_SIZE, GL_FLOAT, 0, VERTEX_SIZE_BYTES, (int*) ENTITY_ID_OFFSET);
                glEnableVertexAttribArray(4);
            };

            void render() {
                bool rebuffer = 0;

                for (int i = 0; i < numSprites; ++i) {
                    if (sprites[i].isDirty) {
                        loadVertexProperties(i);
                        sprites[i].isDirty = 0;
                        rebuffer = 1;
                    }
                }
            }
    };
}
