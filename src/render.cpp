#include <Dralgeer/render.h>
#include <Zeta2D/zmath2D.h>
#include <Dralgeer/window.h>
#include <Dralgeer/assetpool.h>

namespace Dralgeer {
    // * ===============================================
    // * StaticBatch Stuff

    StaticBatch::StaticBatch(StaticBatch const &batch) { throw std::runtime_error("[ERROR] Cannot constructor a StaticBatch from another StaticBatch."); };
    StaticBatch::StaticBatch(StaticBatch &&batch) { throw std::runtime_error("[ERROR] Cannot constructor a StaticBatch from another StaticBatch."); };
    StaticBatch& StaticBatch::operator = (StaticBatch const &batch) { throw std::runtime_error("[ERROR] Cannot reassign a StaticBatch object. Do NOT use the '=' operator."); };
    StaticBatch& StaticBatch::operator = (StaticBatch &&batch) { throw std::runtime_error("[ERROR] Cannot reassign a StaticBatch object. Do NOT use the '=' operator."); };

    // Note we do not need to delete the textures as the AssetPool will take care of that for us.

    StaticBatch::~StaticBatch() {
        // free the GPU
        glDeleteVertexArrays(1, &vaoID);
        glDeleteBuffers(1, &vboID);
        glDeleteBuffers(1, &eboID);

        // unbind everything
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    };

    void StaticBatch::init(SpriteRenderer** spr, int size) {
        float* vertices = new float[size*SPRITE_SIZE];
        unsigned int* indices = new unsigned int[size*6];
        numSprites = size;

        // generate and bind a vertex array object
        glGenVertexArrays(1, &vaoID);
        glBindVertexArray(vaoID);

        // populate the vertices and indices lists
        int offset = 0, iOffset = 0, iIndex = 0;

        for (int i = 0; i < size; ++i) {
            // Texture ID (add new one if not found)
            int texID = -1;
            if (spr[i]->sprite.texture) {
                for (int j = 0; j < numTextures; ++j) {
                    if (textures[j] == spr[i]->sprite.texture) {
                        texID = j;
                        goto ADDED_TEX;
                    }
                }

                if (numTextures < MAX_TEXTURES) {
                    texID = numTextures;
                    textures[numTextures++] = spr[i]->sprite.texture;

                } else { // todo later just add an info message when I set up the system messages
                    throw std::runtime_error("Max number of textures for the StaticBatch reached.");
                }
            }

            ADDED_TEX:

            glm::mat4 transformMat(1);
            Transform t = spr[i]->transform; // for readabiility (will probably remove later)

            if (!ZMath::compare(t.rotation, 0.0f)) {
                transformMat = glm::translate(transformMat, glm::vec3(t.pos.x, t.pos.y, 0.0f));
                transformMat = glm::rotate(transformMat, (float) glm::radians(t.rotation), glm::vec3(0, 0, 1));
                transformMat = glm::scale(transformMat, glm::vec3(t.scale.x, t.scale.y, 1.0f));
            }

            // add vertices with the appropriate properties
            // this loop is slightly inefficient compared to just writing out all 4 cases by hand, but I really don't wanna do that
            float xAdd = 1.0f, yAdd = 1.0f;

            // populate vertices
            for (int j = 0; j < 4; ++j) {
                // account for each vertex
                if (j == 1) { yAdd = 0.0f; }
                else if (j == 2) { xAdd = 0.0f; }
                else if (j == 3) { yAdd = 1.0f; }

                glm::vec4 currPos(t.pos.x + (xAdd * t.scale.x), t.pos.y + (yAdd * t.scale.y), 0.0f, 1.0f);
                if (!ZMath::compare(t.rotation, 0.0f)) { currPos = transformMat * glm::vec4(xAdd, yAdd, 0.0f, 1.0f); }

                // load position
                vertices[offset] = currPos.x;
                vertices[offset + 1] = currPos.y;

                // load color
                vertices[offset + 2] = spr[i]->color.x;
                vertices[offset + 3] = spr[i]->color.y;
                vertices[offset + 4] = spr[i]->color.z;
                vertices[offset + 5] = spr[i]->color.w;

                // load texture coords
                vertices[offset + 6] = spr[i]->sprite.texCoords[i].x;
                vertices[offset + 7] = spr[i]->sprite.texCoords[i].y;
                
                // load texture IDs
                vertices[offset + 8] = texID;

                // load entity IDs
                vertices[offset + 9] = spr[i]->entityID;

                offset += VERTEX_SIZE;
            }
        
            // populate indices
            indices[iIndex] = iOffset;
            indices[iIndex + 1] = iOffset + 1;
            indices[iIndex + 2] = iOffset + 2;
            
            indices[iIndex + 3] = iOffset + 2;
            indices[iIndex + 4] = iOffset + 3;
            indices[iIndex + 5] = iOffset;

            iOffset += 4;
            iIndex += 6;
        }

        // allocate space for the vertices
        glGenBuffers(1, &vboID);
        glBindBuffer(GL_ARRAY_BUFFER, vboID);
        glBufferData(GL_ARRAY_BUFFER, size*SPRITE_SIZE, vertices, GL_STATIC_DRAW);

        // generate the ebo
        glGenBuffers(1, &eboID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size*6, indices, GL_STATIC_DRAW);

        // set the parameters
        glVertexAttribPointer(0, 2, GL_FLOAT, 0, VERTEX_SIZE_BYTES, (void*) 0);
        glVertexAttribPointer(1, 4, GL_FLOAT, 0, VERTEX_SIZE_BYTES, (void*) COLOR_OFFSET);
        glVertexAttribPointer(2, 2, GL_FLOAT, 0, VERTEX_SIZE_BYTES, (void*) TEX_COORDS_OFFSET);
        glVertexAttribPointer(3, 1, GL_FLOAT, 0, VERTEX_SIZE_BYTES, (void*) TEX_ID_OFFSET);
        glVertexAttribPointer(4, 1, GL_FLOAT, 0, VERTEX_SIZE_BYTES, (void*) ENTITY_ID_OFFSET);
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
        glEnableVertexAttribArray(3);
        glEnableVertexAttribArray(4);

        // free the memory
        delete[] vertices;
        delete[] indices;
    };

    void StaticBatch::render(Shader const &currShader, Camera const &cam) {
        // bind everything
        glBindVertexArray(vaoID);
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

        // use shader
        currShader.use();
        currShader.uploadMat4("uProjection", cam.proj);
        currShader.uploadMat4("uView", cam.view);

        // bind textures
        for (int i = 0; i < numTextures; ++i) {
            glActiveTexture(GL_TEXTURE0 + i);
            textures[i]->bind();
        }

        currShader.uploadIntArr("uTexture", TexSlots::texSlots, 16);

        glDrawElements(GL_TRIANGLES, 6*numSprites, GL_UNSIGNED_INT, 0);

        currShader.detach();

        // unbind everything
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glBindVertexArray(0);
    };

    // * ===============================================
    // * DynamicBatch Stuff

    DynamicBatch::DynamicBatch(DynamicBatch const &batch) { throw std::runtime_error("[ERROR] Cannot constructor a DynamicBatch from another DynamicBatch."); };
    DynamicBatch::DynamicBatch(DynamicBatch &&batch) { throw std::runtime_error("[ERROR] Cannot constructor a DynamicBatch from another DynamicBatch."); };
    DynamicBatch& DynamicBatch::operator = (DynamicBatch const &batch) { throw std::runtime_error("[ERROR] Cannot reassign a DynamicBatch object. Do NOT use the '=' operator."); };
    DynamicBatch& DynamicBatch::operator = (DynamicBatch &&batch) { throw std::runtime_error("[ERROR] Cannot reassign a DynamicBatch object. Do NOT use the '=' operator."); };
    
    // Note we do not need to free the textures as the AssetPool will handle that for us.
    DynamicBatch::~DynamicBatch() {
        for (int i = 0; i < numSprites; ++i) { delete sprites[i]; }

        // delete the vao, vbo, and ebo
        glDeleteVertexArrays(1, &vaoID);
        glDeleteBuffers(1, &vboID);
        glDeleteBuffers(1, &eboID);

        // unbind everything
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    };

    void DynamicBatch::loadVertexProperties(int index) {
        int offset = index * SPRITE_SIZE;

        // Texture ID
        int texID = -1;
        if (sprites[index]->sprite.texture) {
            for (int i = 0; i < numTextures; ++i) {
                if (textures[i] == sprites[index]->sprite.texture) {
                    texID = i;
                    break;
                }
            }
        }

        glm::mat4 transformMat(1);
        Transform t = sprites[index]->transform;

        if (!ZMath::compare(t.rotation, 0.0f)) {
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
            else if (i == 3) { yAdd = 1.0f; }

            glm::vec4 currPos(t.pos.x + (xAdd * t.scale.x), t.pos.y + (yAdd * t.scale.y), 0.0f, 1.0f);
            if (!ZMath::compare(t.rotation, 0.0f)) { currPos = transformMat * glm::vec4(xAdd, yAdd, 0.0f, 1.0f); }

            // load position
            vertices[offset] = currPos.x;
            vertices[offset + 1] = currPos.y;

            // load color
            vertices[offset + 2] = sprites[index]->color.x;
            vertices[offset + 3] = sprites[index]->color.y;
            vertices[offset + 4] = sprites[index]->color.z;
            vertices[offset + 5] = sprites[index]->color.w;

            // load texture coords
            vertices[offset + 6] = sprites[index]->sprite.texCoords[i].x;
            vertices[offset + 7] = sprites[index]->sprite.texCoords[i].y;
            
            // load texture IDs
            vertices[offset + 8] = texID;

            // load entity IDs
            vertices[offset + 9] = sprites[index]->entityID;

            offset += VERTEX_SIZE;
        }
    };

    void DynamicBatch::start() {
        // generate and bind a vertex array object
        glGenVertexArrays(1, &vaoID);
        glBindVertexArray(vaoID);

        // allocate space for the vertices
        glGenBuffers(1, &vboID);
        glBindBuffer(GL_ARRAY_BUFFER, vboID);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

        // * ------ Generate the Indices ------

        unsigned int indices[MAX_RENDER_INDICES_LIST_SIZE];
        int offset = 0;
        for (int i = 0; i < MAX_RENDER_INDICES_LIST_SIZE; i += 6) {
            indices[i] = offset;
            indices[i + 1] = offset + 1;
            indices[i + 2] = offset + 2;
            
            indices[i + 3] = offset + 2;
            indices[i + 4] = offset + 3;
            indices[i + 5] = offset;

            offset += 4;
        }

        // * ----------------------------------

        glGenBuffers(1, &eboID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 2, GL_FLOAT, 0, VERTEX_SIZE_BYTES, (void*) 0);
        glVertexAttribPointer(1, 4, GL_FLOAT, 0, VERTEX_SIZE_BYTES, (void*) COLOR_OFFSET);
        glVertexAttribPointer(2, 2, GL_FLOAT, 0, VERTEX_SIZE_BYTES, (void*) TEX_COORDS_OFFSET);
        glVertexAttribPointer(3, 1, GL_FLOAT, 0, VERTEX_SIZE_BYTES, (void*) TEX_ID_OFFSET);
        glVertexAttribPointer(4, 1, GL_FLOAT, 0, VERTEX_SIZE_BYTES, (void*) ENTITY_ID_OFFSET);
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
        glEnableVertexAttribArray(3);
        glEnableVertexAttribArray(4);
    };

    void DynamicBatch::render(Shader const &currShader, Camera const &cam) {
        bool rebuffer = 0;

        for (int i = 0; i < numSprites; ++i) {
            if (sprites[i]->isDirty) {
                loadVertexProperties(i);
                sprites[i]->isDirty = 0;
                rebuffer = 1;
            }
        }

        // rebuffer data if any of the sprites are dirty
        if (rebuffer) {
            glBindBuffer(GL_ARRAY_BUFFER, vboID);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }

        // bind everything
        glBindVertexArray(vaoID);
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

        // use shader
        currShader.use();
        currShader.uploadMat4("uProjection", cam.proj);
        currShader.uploadMat4("uView", cam.view);

        // bind textures
        for (int i = 0; i < numTextures; ++i) {
            glActiveTexture(GL_TEXTURE0 + i);
            textures[i]->bind();
        }

        currShader.uploadIntArr("uTexture", TexSlots::texSlots, 16);

        glDrawElements(GL_TRIANGLES, 6*numSprites, GL_UNSIGNED_INT, 0);

        currShader.detach();

        // unbind everything
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glBindVertexArray(0);
    };

    bool DynamicBatch::destroyIfExists(SpriteRenderer* spr) {
        for (int i = 0; i < numSprites; ++i) {
            if (sprites[i] == spr) {
                for (int j = i; j < numSprites - 1; ++j) {
                    sprites[j] = sprites[j + 1];
                    sprites[j]->isDirty = 1;
                }

                numSprites--;
                return 1;
            }
        }

        return 0;
    };

    void DynamicBatch::addSprite(SpriteRenderer* spr) {
        if (numSprites < MAX_RENDER_BATCH_SIZE) {
            sprites[numSprites] = spr;
            sprites[numSprites]->isDirty = 1;

            // add texture if the sprite has a texture and we don't already have that texture
            // ensure it is within the max number of textures, too (tbh I think the setup I have for the textures is wrong)
            if (spr->sprite.texture && numTextures < MAX_TEXTURES) {
                for (int i = 0; i < numTextures; ++i) { if (textures[i] == spr->sprite.texture) { goto ADDED; }}
                textures[numTextures++] = spr->sprite.texture;

            } else if (numTextures >= MAX_TEXTURES) { // todo will remove the logging stuff but this is useful for debugging
                std::cout << "[INFO] Maximum number of textures reached.\n";
            }

            ADDED:
            numSprites++;
        }
    };

    // void DynamicBatch::addSprites(SpriteRenderer** spr, int size) {};

    bool DynamicBatch::hasTexture(Texture* tex) const {
        if (!tex) { return 0; }
        for (int i = 0; i < numTextures; ++i) { if (textures[i] == tex) { return 1; }}
        return 0;
    };

    // * ===============================================
    // * EditorBatch Stuff

    EditorBatch::EditorBatch(EditorBatch const &batch) { throw std::runtime_error("[ERROR] Cannot constructor a EditorBatch from another EditorBatch."); };
    EditorBatch::EditorBatch(EditorBatch &&batch) { throw std::runtime_error("[ERROR] Cannot constructor a EditorBatch from another EditorBatch."); };
    EditorBatch& EditorBatch::operator = (EditorBatch const &batch) { throw std::runtime_error("[ERROR] Cannot reassign a EditorBatch object. Do NOT use the '=' operator."); };
    EditorBatch& EditorBatch::operator = (EditorBatch &&batch) { throw std::runtime_error("[ERROR] Cannot reassign a EditorBatch object. Do NOT use the '=' operator."); };
    
    // Do not have to delete the textures as the AssetPool should take care of that for us.
    EditorBatch::~EditorBatch() {
        for (int i = 0; i < numSprites; ++i) { delete sprites[i]; }

        // delete the vao, vbo, and ebo
        glDeleteVertexArrays(1, &vaoID);
        glDeleteBuffers(1, &vboID);
        glDeleteBuffers(1, &eboID);

        // unbind everything
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    };

    void EditorBatch::loadVertexProperties(int index) {
        int offset = index * SPRITE_SIZE;

        // Texture ID
        int texID = -1;
        if (sprites[index]->sprite.texture) {
            for (int i = 0; i < numTextures; ++i) {
                if (textures[i] == sprites[index]->sprite.texture) {
                    texID = i;
                    break;
                }
            }
        }

        glm::mat4 transformMat(1);
        Transform t = sprites[index]->transform;

        if (!ZMath::compare(t.rotation, 0.0f)) {
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
            else if (i == 3) { yAdd = 1.0f; }

            glm::vec4 currPos(t.pos.x + (xAdd * t.scale.x), t.pos.y + (yAdd * t.scale.y), 0.0f, 1.0f);
            if (!ZMath::compare(t.rotation, 0.0f)) { currPos = transformMat * glm::vec4(xAdd, yAdd, 0.0f, 1.0f); }

            // load position
            vertices[offset] = currPos.x;
            vertices[offset + 1] = currPos.y;

            // load color
            vertices[offset + 2] = sprites[index]->color.x;
            vertices[offset + 3] = sprites[index]->color.y;
            vertices[offset + 4] = sprites[index]->color.z;
            vertices[offset + 5] = sprites[index]->color.w;

            // load texture coords
            vertices[offset + 6] = sprites[index]->sprite.texCoords[i].x;
            vertices[offset + 7] = sprites[index]->sprite.texCoords[i].y;
            
            // load texture IDs
            vertices[offset + 8] = texID;

            // load entity IDs
            vertices[offset + 9] = sprites[index]->entityID;

            offset += VERTEX_SIZE;
        }
    };

    void EditorBatch::start() {
        // generate and bind a vertex array object
        glGenVertexArrays(1, &vaoID);
        glBindVertexArray(vaoID);

        // allocate space for the vertices
        glGenBuffers(1, &vboID);
        glBindBuffer(GL_ARRAY_BUFFER, vboID);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

        // * ------ Generate the Indices ------

        unsigned int indices[MAX_RENDER_INDICES_LIST_SIZE];
        int offset = 0;
        for (int i = 0; i < MAX_RENDER_INDICES_LIST_SIZE; i += 6) {
            indices[i] = offset;
            indices[i + 1] = offset + 1;
            indices[i + 2] = offset + 2;
            
            indices[i + 3] = offset + 2;
            indices[i + 4] = offset + 3;
            indices[i + 5] = offset;

            offset += 4;
        }

        // * ----------------------------------

        glGenBuffers(1, &eboID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 2, GL_FLOAT, 0, VERTEX_SIZE_BYTES, (void*) 0);
        glVertexAttribPointer(1, 4, GL_FLOAT, 0, VERTEX_SIZE_BYTES, (void*) COLOR_OFFSET);
        glVertexAttribPointer(2, 2, GL_FLOAT, 0, VERTEX_SIZE_BYTES, (void*) TEX_COORDS_OFFSET);
        glVertexAttribPointer(3, 1, GL_FLOAT, 0, VERTEX_SIZE_BYTES, (void*) TEX_ID_OFFSET);
        glVertexAttribPointer(4, 1, GL_FLOAT, 0, VERTEX_SIZE_BYTES, (void*) ENTITY_ID_OFFSET);
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
        glEnableVertexAttribArray(3);
        glEnableVertexAttribArray(4);
    };

    void EditorBatch::render(Shader const &currShader, Camera const &cam) {
        bool rebuffer = 0;

        for (int i = 0; i < numSprites; ++i) {
            if (sprites[i]->isDirty) {
                loadVertexProperties(i);
                sprites[i]->isDirty = 0;
                rebuffer = 1;
            }
        }

        // rebuffer data if any of the sprites are dirty
        if (rebuffer) {
            glBindBuffer(GL_ARRAY_BUFFER, vboID);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }

        // bind everything
        glBindVertexArray(vaoID);
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

        // use shader
        currShader.use();
        currShader.uploadMat4("uProjection", cam.proj);
        currShader.uploadMat4("uView", cam.view);

        // bind textures
        for (int i = 0; i < numTextures; ++i) {
            glActiveTexture(GL_TEXTURE0 + i);
            textures[i]->bind();
        }

        currShader.uploadIntArr("uTexture", TexSlots::texSlots, 16);

        glDrawElements(GL_TRIANGLES, 6*numSprites, GL_UNSIGNED_INT, 0);

        currShader.detach();

        // unbind everything
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glBindVertexArray(0);
    };

     bool EditorBatch::destroyIfExists(SpriteRenderer* spr) {
        for (int i = 0; i < numSprites; ++i) {
            if (sprites[i] == spr) {
                for (int j = i; j < numSprites - 1; ++j) {
                    sprites[j] = sprites[j + 1];
                    sprites[j]->isDirty = 1;
                }

                numSprites--;
                return 1;
            }
        }

        return 0;
    };

    void EditorBatch::addSprite(SpriteRenderer* spr) {
        if (numSprites < MAX_RENDER_BATCH_SIZE) {
            sprites[numSprites] = spr;
            sprites[numSprites]->isDirty = 1;

            // add texture if the sprite has a texture and we don't already have that texture
            // ensure it is within the max number of textures, too (tbh I think the setup I have for the textures is wrong)
            if (spr->sprite.texture && numTextures < MAX_TEXTURES) {
                for (int i = 0; i < numTextures; ++i) { if (textures[i] == spr->sprite.texture) { goto ADDED; }}
                textures[numTextures++] = spr->sprite.texture;

            } else if (numTextures >= MAX_TEXTURES) { // todo will remove the logging stuff but this is useful for debugging
                std::cout << "[INFO] Maximum number of textures reached.\n";
            }

            ADDED:
            ++numSprites;
        }
    };

    bool EditorBatch::hasTexture(Texture* tex) const {
        if (!tex) { return 0; }
        for (int i = 0; i < numTextures; ++i) { if (textures[i] == tex) { return 1; }}
        return 0;
    };

    // * ===============================================
    // * Renderer Stuff

    void Renderer::addBatch(int n) {
        // determine the spot to put the index in using a modified binary search
        int min = 0, max = numIndices;
        int index = numIndices/2;

        for(;;) {
            if (n > indices[index]) { // look through lower half
                max = index;

                if (min >= max) {
                    for (int i = numIndices; i > min; --i) { indices[i] = indices[i - 1]; }
                    indices[min] = n;
                    break;
                }

                index = (max + min)/2;

            } else { // look through upper half
                min = index + 1;

                if (min >= max) {
                    for (int i = numIndices; i > min; --i) { indices[i] = indices[i - 1]; }
                    indices[min] = n;
                    break;
                }

                index = (max + min)/2;

            } // ? We do not have to consider the case that they are equal as this system guarentees that cannot happen
        }
        
        batches[n].start();
        ++numIndices;
    };

    void Renderer::add(SpriteRenderer* spr) {
        if (!spr || spr->transform.zIndex < -499 || spr->transform.zIndex > 500) { return; } // todo use an appropriate logger message when I fix that

        int n = spr->transform.zIndex + 499;
        if (batches[n].numSprites >= MAX_RENDER_BATCH_SIZE) { return; } // todo use an info message here

        if (numIndices == 0) {
            indices[numIndices++] = n;
            batches[n].start();
            batches[n].addSprite(spr);
            return;
        }

        if (batches[n].numSprites == 0) { addBatch(n); }
        batches[n].addSprite(spr);
    };

    bool Renderer::destroy(SpriteRenderer* spr) {
        for (int i = 0; i < numIndices; ++i) {
            if (batches[indices[i]].destroyIfExists(spr)) {
                if (batches[indices[i]].numSprites == 0) {
                    for (int j = i; j < numIndices - 1; ++j) { indices[j] = indices[j + 1]; }
                    --numIndices;
                }

                return 1;
            }
        }

        return 0;
    };

    void Renderer::updateZIndex(SpriteRenderer* spr) {
        if (!destroy(spr)) { return; }

        // add the sprite to the new batch it belongs to
        int n = spr->transform.zIndex + 499;
        if (batches[n].numSprites == 0) { addBatch(n); }
        batches[n].addSprite(spr);
    };

    // * ===============================================
    // * EditorRenderer Stuff

    void EditorRenderer::addBatch(int n) {
        // determine the spot to put the index in using a modified binary search
        int min = 0, max = numIndices;
        int index = numIndices/2;

        for(;;) {
            if (n > indices[index]) { // look through lower half
                max = index;

                if (min >= max) {
                    for (int i = numIndices; i > min; --i) { indices[i] = indices[i - 1]; }
                    indices[min] = n;
                    break;
                }

                index = (max + min)/2;

            } else { // look through upper half
                min = index + 1;

                if (min >= max) {
                    for (int i = numIndices; i > min; --i) { indices[i] = indices[i - 1]; }
                    indices[min] = n;
                    break;
                }

                index = (max + min)/2;

            } // ? We do not have to consider the case that they are equal as this system guarentees that cannot happen
        }
        
        batches[n].start();
        ++numIndices;
    };
}
