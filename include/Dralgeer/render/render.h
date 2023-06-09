// todo add renderbatch and render in here

#pragma once

#include "../components/sprite.h"
#include "../camera.h"

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
    namespace Render { Shader currentShader; }

    class RenderBatch {
        private:
            Camera camera = {glm::vec2(0.0f)}; // ! Temporary until I make scenes -- could cause some issues

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
                if (sprites[index].sprite.texture) {
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
                // this loop is slightly inefficient compared to just writing out all 4 cases by hand, but I really don't wanna do that
                float xAdd = 1.0f, yAdd = 1.0f;
                for (int i = 0; i < 4; ++i) {
                    // account for each vertex
                    if (i == 1) { yAdd = 0.0f; }
                    else if (i == 2) { xAdd = 0.0f; }
                    if (i == 3) { yAdd = 1.0f; }

                    glm::vec4 currPos(t.pos.x + (xAdd * t.scale.x), t.pos.y + (yAdd * t.scale.y), 0.0f, 1.0f);
                    if (t.rotation) { currPos = transformMat * glm::vec4(xAdd, yAdd, 0.0f, 1.0f); }

                    // load position
                    vertices[offset] = currPos.x;
                    vertices[offset + 1] = currPos.y;

                    // load color
                    vertices[offset + 2] = sprites[index].color.x;
                    vertices[offset + 3] = sprites[index].color.y;
                    vertices[offset + 4] = sprites[index].color.z;
                    vertices[offset + 5] = sprites[index].color.w;

                    // load texture coords
                    vertices[offset + 6] = sprites[index].sprite.texCords[i].x;
                    vertices[offset + 7] = sprites[index].sprite.texCords[i].y;

                    // load texture IDs
                    vertices[offset + 8] = texID;

                    // load entity IDs
                    vertices[offset + 9] = sprites[index].gameObject.uID + 1;

                    offset += VERTEX_SIZE;
                }
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

                // rebuffer data if any of the sprites are dirty
                if (rebuffer) {
                    glBindBuffer(GL_ARRAY_BUFFER, vboID);
                    glBufferSubData(GL_ARRAY_BUFFER, 0, MAX_RENDER_VERTICES_LIST_SIZE, vertices); // todo make it a subarray of the vertices most likely
                }

                // ! This is temp code, this will not be here once scenes are made
                camera.adjustProjection();
                camera.adjustView();
                // !==============================================================

                // use shader
                Shader shader = Render::currentShader;
                shader.uploadMat4("uProjection", camera.proj);
                shader.uploadMat4("uView", camera.view);

                // bind textures
                for (int i = 0; i < numTextures; ++i) {
                    glActiveTexture(GL_TEXTURE0 + i + 1);
                    textures[i].bind();
                }

                shader.uploadIntArr("uTextures", texSlots, 16);

                glBindVertexArray(vaoID);
                glEnableVertexAttribArray(0);
                glEnableVertexAttribArray(1);

                glDrawElements(GL_TRIANGLES, 6*numSprites, GL_UNSIGNED_INT, 0); // ! not sure if this is right -- probs isn't tbh

                // unbind everything
                glDisableVertexAttribArray(0);
                glDisableVertexAttribArray(1);
                glBindVertexArray(0);

                for (int i = 0; i < numTextures; ++i) { textures[i].unbind(); }
                shader.detach();
            };

            // * Returns true if the GameObject is successfully destroyed and false if it doesn't exist.
            bool destroyIfExists(SpriteRenderer const &spr) {
                for (int i = 0; i < numSprites; ++i) {
                    if (&sprites[i] == &spr) {
                        for (int j = i; j < numSprites - 1; ++j) {
                            sprites[j] = sprites[j + 1];
                            sprites[j].isDirty = 1;
                        }

                        numSprites--;
                        return 1;
                    }
                }

                return 0;
            };

            void addSprite(SpriteRenderer const &spr) {
                if (numSprites < MAX_RENDER_BATCH_SIZE) {
                    sprites[numSprites++] = spr;

                    // add texture if the sprite has a texture and we don't already have that texture
                    // ensure it is within the max number of textures, too (tbh I think the setup I have for the textures is wrong)
                    if (spr.sprite.texture && numTextures < MAX_TEXTURES) {
                        for (int i = 0; i < numTextures; ++i) { if (textures[i] == (*spr.sprite.texture)) { goto ADDED; }}
                        textures[numTextures++] = (*spr.sprite.texture);
                    }

                    ADDED:

                    // add properties to local vertices array
                    loadVertexProperties(numSprites - 1);
                }
            };
    };
}
