#pragma once

#include "component.h"

namespace Dralgeer {
    class RenderBatch {
        private:
            SpriteRenderer* sprites[MAX_RENDER_BATCH_SIZE];
            float vertices[MAX_RENDER_VERTICES_LIST_SIZE] = {0};
            Texture* textures[MAX_TEXTURES];
            int texSlots[MAX_TEXTURES] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
            unsigned int vaoID, vboID, eboID;

            // todo this should not compile with the inline functions being declared this way and defined in the header
            // * Helper to just make the code easier to read and debug.
            // * Will probs be moved directly into the code in the end.
            inline void loadVertexProperties(int index);
            inline void loadElementIndices(int index);

        public:
            int numSprites = 0;
            int numTextures = 0;

            inline RenderBatch() {};

            // * ===================
            // * Rule of 5 Stuff
            // * ===================

            // ? These are all designed to throw errors with the exception of the destructor.
            // ? RenderBatches should NOT be reassigned or constructed from another.

            RenderBatch(RenderBatch const &batch);
            RenderBatch(RenderBatch &&batch);
            RenderBatch& operator = (RenderBatch const &batch);
            RenderBatch& operator = (RenderBatch &&batch);
            ~RenderBatch();

            // * ===================
            // * Normal Functions
            // * ===================

            void start();
            void render(Shader const &currShader, Camera const &cam);

            // * Returns true if the SpriteRenderer is successfully removed and false if it doesn't exist.
            bool destroyIfExists(SpriteRenderer* spr);
            void addSprite(SpriteRenderer* spr);
            bool hasTexture(Texture* tex) const;
    };

    class GizmoBatch {
        private:
            Shader* gizmoShader; // Note: we do not need to delete this as the AssetPool will handle this for us.
            SpriteRenderer* gizmos[GIZMO_BATCH_SIZE];
            float vertices[GIZMO_BATCH_VERTICES_SIZE] = {0};
            Texture* gizmoTexture; // We will store this texture at slot 16 on the GPU
            unsigned int vaoID, vboID, eboID;
            int numGizmos = 0;

        public:
            GizmoBatch();

            GizmoBatch(GizmoBatch const &gb);
            GizmoBatch(GizmoBatch &&gb);
            GizmoBatch& operator = (GizmoBatch const &gb);
            GizmoBatch& operator = (GizmoBatch &&gb);
            
            // Note: we do not need a destructor as the scene and AssetPool will clean up all the memory allocated here
            // todo in the future maybe add a destructor for this shader and texture as the AssetPool won't clean it up till the very end

            void addGizmo(SpriteRenderer* spr);

            // call before adding any gizmos
            void init(Texture* gizmoTexture); // ? probably do this for the parameter????
            void render();
    };

    class Renderer {
        private:
            RenderBatch batches[MAX_RENDER_BATCHES]; // Note: zIndices from -1000 to 1499 are permitted
            int indices[MAX_RENDER_BATCHES]; // batches that contain sprites
            int numIndices = 0; // the number of batches that cointain sprites

            inline void addBatch(int n) {
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

        public:
            inline Renderer() {};

            inline void add(SpriteRenderer* spr) {
                if (!spr || spr->transform.zIndex < -1000 || spr->transform.zIndex > 1499) { return; } // todo use an appropriate logger message when I fix that

                int n = spr->transform.zIndex + 1000;
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

            // remove a sprite renderer contained in the renderer
            // returns 1 if it successfully found and destroyed it and 0 otherwise
            inline bool destroy(SpriteRenderer* spr) {
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

            // render each batch
            inline void render(Shader const &currShader, Camera const &cam) {
                for (int i = 0; i < numIndices; ++i) { batches[indices[i]].render(currShader, cam); }
            };

            // update the list of zIndices when called
            // spr = the SpriteRenderer whose zIndex was changed
            inline void updateZIndex(SpriteRenderer* spr) {
                if (!destroy(spr)) { return; }

                // add the sprite to the new batch it belongs to
                int n = spr->transform.zIndex + 1000;
                if (batches[n].numSprites == 0) { addBatch(n); }
                batches[n].addSprite(spr);
            };
    };
}
