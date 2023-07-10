#include <Dralgeer/render.h>
#include <Zeta2D/zmath2D.h>
#include <Dralgeer/window.h>

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
            if (!ZMath::compare(t.rotation, 0.0f)) { currPos = transformMat * glm::vec4(xAdd, yAdd, 0.0f, 1.0f); } // ! this line looks wrong (will not affect what I'm currently debugging though)

            // load position
            // std::cout << "CurrPos: " << currPos.x << ", " << currPos.y << ", " << 0.0f << "\n";

            vertices[offset] = currPos.x;
            vertices[offset + 1] = currPos.y;
            vertices[offset + 2] = 0.0f;

            // std::cout << "Color: " << sprites[index]->color.x << ", " << sprites[index]->color.y << ", " << sprites[index]->color.z << ", " << sprites[index]->color.w << "\n";

            // load color
            vertices[offset + 3] = sprites[index]->color.x;
            vertices[offset + 4] = sprites[index]->color.y;
            vertices[offset + 5] = sprites[index]->color.z;
            vertices[offset + 6] = sprites[index]->color.w;

            // std::cout << "TexCoords: " << sprites[index]->sprite.texCords[i].x << ", " << sprites[index]->sprite.texCords[i].y << "\n";

            // load texture coords
            vertices[offset + 7] = sprites[index]->sprite.texCords[i].x;
            vertices[offset + 8] = sprites[index]->sprite.texCords[i].y;

            // std::cout << "TexID: " << texID << "\n";

            // load texture IDs
            vertices[offset + 9] = texID;

            // load entity IDs
            // vertices[offset + 9] = sprites[index]->gameObject->id + 1;

            offset += VERTEX_SIZE;
        }
    };

    // inline void RenderBatch::loadElementIndices(int index) {
    //     int iOffset = 6 * index;
    //     int offset = 4 * index;

    //     // triangle 1
    //     indices[iOffset] = offset;
    //     indices[iOffset + 1] = offset + 1;
    //     indices[iOffset + 2] = offset + 2;
        
    //     // triangle 2
    //     indices[iOffset + 3] = offset + 2;
    //     indices[iOffset + 4] = offset + 3;
    //     indices[iOffset + 5] = offset;

    //     // std::cout << "\nIndices:\n" << indices[0] << ", " << indices[1] << ", " << indices[2] << "\n";
    //     // std::cout << indices[3] << ", " << indices[4] << ", " << indices[5] << "\n\n";
    // };

    void RenderBatch::start(int zIndex) {
        this->zIndex = zIndex;

        // generate and bind a vertex array object
        glGenVertexArrays(1, &vaoID);
        glBindVertexArray(vaoID);

        // todo test to see if I can get it to work in the helloworld textures program with 0 initial elements

        // allocate space for the vertices
        glGenBuffers(1, &vboID);
        glBindBuffer(GL_ARRAY_BUFFER, vboID);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

        // todo issue has to be from the vbo.
        // todo try having an empty vbo with set values and then adding them in with the add function

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

        // todo add in glVertexAttribPointer for the gameObjectID after the rest of this stuff works

        glVertexAttribPointer(0, 3, GL_FLOAT, 0, VERTEX_SIZE_BYTES, (void*) 0);
        glVertexAttribPointer(1, 4, GL_FLOAT, 0, VERTEX_SIZE_BYTES, (void*) COLOR_OFFSET);
        glVertexAttribPointer(2, 2, GL_FLOAT, 0, VERTEX_SIZE_BYTES, (void*) TEX_COORDS_OFFSET);
        glVertexAttribPointer(3, 1, GL_FLOAT, 0, VERTEX_SIZE_BYTES, (void*) TEX_ID_OFFSET);
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
        glEnableVertexAttribArray(3);

        // textures[0] = new Texture();
        // textures[0]->init("../../assets/images/wall.jpg");

        // numSprites = 1;
        // sprites[0] = new SpriteRenderer();
        // sprites[0]->isDirty = 1;
    };

    void RenderBatch::render(Camera const &cam) {
        bool rebuffer = 0;
        int offset;

        for (int i = 0; i < numSprites; ++i) {
            if (sprites[i]->isDirty) {
                loadVertexProperties(i);
                sprites[i]->isDirty = 0;
                rebuffer = 1;
                offset = VERTEX_SIZE_BYTES*i;
            }
        }

        // rebuffer data if any of the sprites are dirty
        if (rebuffer) {
            glBindBuffer(GL_ARRAY_BUFFER, vboID);

            // std::cout << sizeof(vertices) << "\n";
            // std::cout << "\nTexture: " << textures[0]->filepath << "\n";
            // std::cout << "\nVertices:\nTop Right: Pos: " << vertices[0] << ", " << vertices[1] << ", " << vertices[2] << " Color: ";
            // std::cout << vertices[3] << ", " << vertices[4] << ", " << vertices[5] << ", " << vertices[6] << " TexCoords: ";
            // std::cout << vertices[7] << ", " << vertices[8] << " TexID: " << vertices[9] << "\nBottom Right: Pos: " << vertices[10] << ", ";
            // std::cout << vertices[11] << ", " << vertices[12] << " Color: " << vertices[13] << ", " << vertices[14] << ", " << vertices[15] << ", " << vertices[16] << " TexCoords: " << vertices[17] << ", " << vertices[18] << " TexID: " << vertices[19] << "\n";
            // std::cout << "Bottom Left: Pos: " << vertices[20] << ", " << vertices[21] << ", " << vertices[22] << " Color: " << vertices[23] << ", " << vertices[24] << ", " << vertices[25] << ", " << vertices[26] << " TexCoords: " << vertices[27] << ", " << vertices[28] << " TexID: " << vertices[29] << "\n";
            // std::cout << "Top Left: Pos: " << vertices[30] << ", " << vertices[31] << ", " << vertices[32] << " Color: " << vertices[33] << ", " << vertices[34] << ", " << vertices[35] << ", " << vertices[36] << " TexCoords: " << vertices[37] << ", " << vertices[38] << " TexID: " << vertices[39] << "\n\n";
            
            // first texture
            // positions            colors                                tex coords       texID
            // 500.0f, 500.0f, 0.0f,   0.8824f, 0.0039f, 0.0039f, 1.0f,      1.0f, 1.0f,      0, // top right
            // 500.0f, 200.0f, 0.0f,   0.8824f, 0.0039f, 0.0039f, 1.0f,      1.0f, 0.0f,      0, // bottom right
            // 200.0f, 200.0f, 0.0f,   0.8824f, 0.0039f, 0.0039f, 1.0f,      0.0f, 0.0f,      0, // bottom left
            // 200.0f, 500.0f, 0.0f,   0.8824f, 0.0039f, 0.0039f, 1.0f,      0.0f, 1.0f,      0  // top left

            // test[0] = 500.0f;
            // test[1] = 500.0f;
            // test[2] = 0.0f;
            // test[3] = 0.8824f;
            // test[4] = 0.0039f;
            // test[5] = 0.0039f;
            // test[6] = 1.0f;
            // test[7] = 1.0f;
            // test[8] = 1.0f;
            // test[9] = 0;

            // test[10] = 500.0f;
            // test[11] = 200.0f;
            // test[12] = 0.0f;
            // test[13] = 0.8824f;
            // test[14] = 0.0039f;
            // test[15] = 0.0039f;
            // test[16] = 1.0f;
            // test[17] = 1.0f;
            // test[18] = 0.0f;
            // test[19] = 0;

            // test[20] = 200.0f;
            // test[21] = 200.0f;
            // test[22] = 0.0f;
            // test[23] = 0.8824f;
            // test[24] = 0.0039f;
            // test[25] = 0.0039f;
            // test[26] = 1.0f;
            // test[27] = 0.0f;
            // test[28] = 0.0f;
            // test[29] = 0;

            // test[30] = 200.0f;
            // test[31] = 500.0f;
            // test[32] = 0.0f;
            // test[33] = 0.8824f;
            // test[34] = 0.0039f;
            // test[35] = 0.0039f;
            // test[36] = 1.0f;
            // test[37] = 0.0f;
            // test[38] = 1.0f;
            // test[39] = 0;

            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // todo causes an invalid value error (error 0x0501)

            GLenum err;
            while((err = glGetError()) != GL_NO_ERROR) {
                std::cout << "[Error] " << err << "\n";
            }

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

        // if (firstTime) {
        //     std::cout << "\nCam.proj:\n";
        //     std::cout << cam.proj[0].x << ", " << cam.proj[0].y << ", " <<cam.proj[0].z << ", " << cam.proj[0].w << "\n";
        //     std::cout << cam.proj[1].x << ", " << cam.proj[1].y << ", " <<cam.proj[1].z << ", " << cam.proj[1].w << "\n";
        //     std::cout << cam.proj[2].x << ", " << cam.proj[2].y << ", " <<cam.proj[2].z << ", " << cam.proj[2].w << "\n";
        //     std::cout << cam.proj[3].x << ", " << cam.proj[3].y << ", " <<cam.proj[3].z << ", " << cam.proj[3].w << "\n";
        //     firstTime = 0;
        // }

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

            // add properties to local vertices array
            // loadVertexProperties(numSprites);
            // loadElementIndices(numSprites++);

            // std::cout << "\nNumSprites: " << numSprites << "\n\n";
            // std::cout << "Vertices:\nTop Right: Pos: " << vertices[0] << ", " << vertices[1] << ", " << vertices[2] << " Color: ";
            // std::cout << vertices[3] << ", " << vertices[4] << ", " << vertices[5] << ", " << vertices[6] << " TexCoords: ";
            // std::cout << vertices[7] << ", " << vertices[8] << " TexID: " << vertices[9] << "\nBottom Right: Pos: " << vertices[10] << ", ";
            // std::cout << vertices[11] << ", " << vertices[12] << " Color: " << vertices[13] << ", " << vertices[14] << ", " << vertices[15] << ", " << vertices[16] << " TexCoords: " << vertices[17] << ", " << vertices[18] << " TexID: " << vertices[19] << "\n";
            // std::cout << "Bottom Left: Pos: " << vertices[20] << ", " << vertices[21] << ", " << vertices[22] << " Color: " << vertices[23] << ", " << vertices[24] << ", " << vertices[25] << ", " << vertices[26] << " TexCoords: " << vertices[27] << ", " << vertices[28] << " TexID: " << vertices[29] << "\n";
            // std::cout << "Top Left: Pos: " << vertices[30] << ", " << vertices[31] << ", " << vertices[32] << " Color: " << vertices[33] << ", " << vertices[34] << ", " << vertices[35] << ", " << vertices[36] << " TexCoords: " << vertices[37] << ", " << vertices[38] << " TexID: " << vertices[39] << "\n\n";
            // std::cout << "Indices:\n" << indices[0] << ", " << indices[1] << ", " << indices[2] << "\n" << indices[3] << ", " << indices[4] << ", " << indices[5] << "\n";
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
