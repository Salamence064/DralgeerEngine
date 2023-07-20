#include <Dralgeer/render.h>
#include <Zeta2D/zmath2D.h>
#include <Dralgeer/window.h>

// todo change the match batch size to 1000 again and buffer sub data multiple times in smaller chunks

// todo do the z-index based on a z-coordinate passed using the VBO and just make it progressively more positive as the z-index increases

namespace Dralgeer {
    // * ===============================================
    // * RenderBatch Stuff

    RenderBatch::RenderBatch(RenderBatch const &batch) { throw std::runtime_error("[ERROR] Cannot constructor a RenderBatch from another RenderBatch."); };
    RenderBatch::RenderBatch(RenderBatch &&batch) { throw std::runtime_error("[ERROR] Cannot constructor a RenderBatch from another RenderBatch."); };
    RenderBatch& RenderBatch::operator = (RenderBatch const &batch) { throw std::runtime_error("[ERROR] Cannot reassign a RenderBatch object. Do NOT use the '=' operator."); };
    RenderBatch& RenderBatch::operator = (RenderBatch &&batch) { throw std::runtime_error("[ERROR] Cannot reassign a RenderBatch object. Do NOT use the '=' operator."); };
    
    // Do not have to delete the textures as the sprites should take care of that for us.
    RenderBatch::~RenderBatch() {
        for (int i = 0; i < numSprites; ++i) { delete sprites[i]; }
        for (int i = 0; i < numTextures; ++i) { delete textures[i]; }

        // delete the vao. vbo, and ebo
        glDeleteVertexArrays(1, &vaoID);
        glDeleteBuffers(1, &vboID);
        glDeleteBuffers(1, &eboID);

        // unbind everything
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    };

    inline void RenderBatch::loadVertexProperties(int index) {
        int offset = index * 4 * VERTEX_SIZE;

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
        Transform t = sprites[index]->gameObject->transform;

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
            // todo try passing the zIndex for the z position and checking if we can do that instead of a list of renderbatches

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
            vertices[offset + 9] = sprites[index]->gameObject->id;

            offset += VERTEX_SIZE;
        }
    };

    void RenderBatch::start(int zIndex) {
        this->zIndex = zIndex;

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

    void RenderBatch::render(Camera const &cam) {
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
            // todo maybe could use an offset + an equation to determine the size for slightly greater efficiency
            glBindBuffer(GL_ARRAY_BUFFER, vboID);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }

        // bind everything
        glBindVertexArray(vaoID);
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

        // use shader
        Renderer::currentShader.use();
        Renderer::currentShader.uploadMat4("uProjection", cam.proj);
        Renderer::currentShader.uploadMat4("uView", cam.view);

        // bind textures
        for (int i = 0; i < numTextures; ++i) {
            glActiveTexture(GL_TEXTURE0 + i);
            textures[i]->bind();
        }

        Renderer::currentShader.uploadIntArr("uTexture", texSlots, 16);

        glDrawElements(GL_TRIANGLES, 6*numSprites, GL_UNSIGNED_INT, 0);

        Renderer::currentShader.detach();

        // unbind everything
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glBindVertexArray(0);
    };

     bool RenderBatch::destroyIfExists(SpriteRenderer* spr) {
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

    void RenderBatch::addSprite(SpriteRenderer* spr) {
        if (numSprites < MAX_RENDER_BATCH_SIZE) {
            sprites[numSprites] = spr;
            sprites[numSprites]->isDirty = 1;

            // add texture if the sprite has a texture and we don't already have that texture
            // ensure it is within the max number of textures, too (tbh I think the setup I have for the textures is wrong)
            if (spr->sprite.texture && numTextures < MAX_TEXTURES) {
                for (int i = 0; i < numTextures; ++i) { if (textures[i] == spr->sprite.texture) { goto ADDED; }}
                textures[numTextures++] = spr->sprite.texture;

            } else if (numTextures < MAX_TEXTURES) { // todo will remove the logging stuff but this is useful for debugging
                std::cout << "[INFO] Maximum number of textures reached.";
            }

            ADDED:
            numSprites++;
        }
    };

    bool RenderBatch::hasTexture(Texture* tex) const {
        if (!tex) { return 0; }
        for (int i = 0; i < numTextures; ++i) { if (textures[i] == tex) { return 1; }}
        return 0;
    };

    // * ===============================================

    namespace Renderer {
        Shader currentShader;
        RenderBatch batches[MAX_RENDER_BATCHES];
        int numBatches = 0;
    }
}
