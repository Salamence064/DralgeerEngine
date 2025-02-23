#pragma once

#include "component.h"

namespace Dralgeer {
    // todo fine tune the constants for StaticBatch and for DynamicBatch (one for level editor's is fine)

    namespace TexSlots { static int texSlots[MAX_TEXTURES] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15}; }

    // A render batch of completely static elements. Once this is initialized, it cannot be changed.
    class StaticBatch {
        private:
            Texture* textures[MAX_TEXTURES];
            int numTextures = 0;
            int numSprites;
            unsigned int vaoID, vboID, eboID;

        public:
            inline StaticBatch() {};

            // * ===================
            // * Rule of 5 Stuff
            // * ===================

            // ? These are all designed to throw errors with the exception of the destructor.
            // ? StaticBatches should NOT be reassigned or constructed from another.

            StaticBatch(StaticBatch const &sb);
            StaticBatch(StaticBatch &&sb);
            StaticBatch& operator = (StaticBatch const &sb);
            StaticBatch& operator = (StaticBatch &&sb);
            ~StaticBatch();

            // * ===================
            // * Normal Functions
            // * ===================

            void init(SpriteRenderer** spr, int size);
            void render(Shader const &currShader, Camera const &cam);
    };

    // A batch of purely dynamic sprites. These sprites will be updated (freqently).
    class DynamicBatch { // todo add add sprites method here, too
        private:
            SpriteRenderer* sprites[MAX_DYNAMIC_BATCH_SIZE];
            float vertices[MAX_DYNAMIC_VERTICES_SIZE] = {0};
            Texture* textures[MAX_TEXTURES];
            unsigned int vaoID, vboID, eboID;

            // * Helper to just make the code easier to read and debug.
            // * Will probs be moved directly into the code in the end.
            void loadVertexProperties(int index);
        
        public:
            int numSprites = 0;
            int numTextures = 0;

            inline DynamicBatch() {};

            // * ===================
            // * Rule of 5 Stuff
            // * ===================

            // ? These are all designed to throw errors with the exception of the destructor.
            // ? DynamicBatches should NOT be reassigned or constructed from another.

            DynamicBatch(DynamicBatch const &batch);
            DynamicBatch(DynamicBatch &&batch);
            DynamicBatch& operator = (DynamicBatch const &batch);
            DynamicBatch& operator = (DynamicBatch &&batch);
            ~DynamicBatch();

            // * ===================
            // * Normal Functions
            // * ===================

            void start();
            void render(Shader const &currShader, Camera const &cam);

            // * Returns true if the SpriteRenderer is successfully removed and false if it doesn't exist.
            bool destroyIfExists(SpriteRenderer* spr);
            void addSprite(SpriteRenderer* spr);
            // void addSprites(SpriteRenderer** spr, int size);
            bool hasTexture(Texture* tex) const;
    };

    class EditorBatch { // todo add an addSprites method
        private:
            SpriteRenderer* sprites[MAX_RENDER_BATCH_SIZE];
            float vertices[MAX_RENDER_VERTICES_LIST_SIZE] = {0};
            Texture* textures[MAX_TEXTURES];
            unsigned int vaoID, vboID, eboID;

            // * Helper to just make the code easier to read and debug.
            // * Will probs be moved directly into the code in the end.
            void loadVertexProperties(int index);
            
        public:
            int numSprites = 0;
            int numTextures = 0;

            inline EditorBatch() {};

            // * ===================
            // * Rule of 5 Stuff
            // * ===================

            // ? These are all designed to throw errors with the exception of the destructor.
            // ? EditorBatches should NOT be reassigned or constructed from another.

            EditorBatch(EditorBatch const &batch);
            EditorBatch(EditorBatch &&batch);
            EditorBatch& operator = (EditorBatch const &batch);
            EditorBatch& operator = (EditorBatch &&batch);
            ~EditorBatch();

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

    // todo update the constant for the max number of batches
    // todo  probs make it 1000 and limit z-index accordingly
    // todo  otherwise it will eat up too much RAM
    // todo  might have to find a better method either way since this takes up a lot of storage
    // todo  might have to reduce it to less than 1000 as well

    // todo make a shader specific for static sprites

    // General use Renderer.
    class Renderer {
        private:
            StaticBatch staticBatch; // static batch for each of the static objects in a subscene
            DynamicBatch batches[MAX_RENDER_BATCHES]; // Note: zIndices from -499 to 500 are permitted
            int indices[MAX_RENDER_BATCHES]; // batches that contain sprites
            int numIndices = 0; // the number of dynamic batches that cointain sprites

            void addBatch(int n);

        public:
            inline Renderer() {};

            // ? Do not allow for reassignment or construction of an Renderer from another Renderer

            inline Renderer(Renderer const &renderer) { throw std::runtime_error("[ERROR] Cannot constructor a Renderer from another Renderer."); };
            inline Renderer(Renderer &&renderer) { throw std::runtime_error("[ERROR] Cannot constructor a Renderer from another Renderer."); };
            inline Renderer& operator = (Renderer const &batch) { throw std::runtime_error("[ERROR] Cannot reassign a Renderer object. Do NOT use the '=' operator."); };
            inline Renderer& operator = (Renderer &&batch) { throw std::runtime_error("[ERROR] Cannot reassign a Renderer object. Do NOT use the '=' operator."); };


            // * ====================
            // * Normal Functions
            // * ====================

            inline void init(SpriteRenderer** spr, int size) { staticBatch.init(spr, size); };
            void add(SpriteRenderer* spr);
            bool destroy(SpriteRenderer* spr);
            
            // todo could also rely on making a separate shader for the static sprites which displays them at like z = -1 instead of z = 0
            inline void render(Shader const &currShader, Camera const &cam) { // todo make sure they're renderered in the right order
                staticBatch.render(currShader, cam);
                for (int i = 0; i < numIndices; ++i) { batches[indices[i]].render(currShader, cam); }
            };

            // update the list of zIndices when called
            // spr = the SpriteRenderer whose zIndex was changed
            void updateZIndex(SpriteRenderer* spr);
    };

    // Renderer specific to the level editor.
    class EditorRenderer {
        private:
            EditorBatch batches[MAX_RENDER_BATCHES]; // Note: zIndices from -499 to 500 are permitted
            int indices[MAX_RENDER_BATCHES]; // batches that contain sprites
            int numIndices = 0; // the number of batches that cointain sprites

            // Helper function to add a dynamic batch.
            void addBatch(int n);

        public:
            inline EditorRenderer() {};

            // ? Do not allow for reassignment or construction of an EditorRenderer from another EditorRenderer

            inline EditorRenderer(EditorRenderer const &renderer) { throw std::runtime_error("[ERROR] Cannot constructor a EditorRenderer from another EditorRenderer."); };
            inline EditorRenderer(EditorRenderer &&renderer) { throw std::runtime_error("[ERROR] Cannot constructor a EditorRenderer from another EditorRenderer."); };
            inline EditorRenderer& operator = (EditorRenderer const &batch) { throw std::runtime_error("[ERROR] Cannot reassign a EditorRenderer object. Do NOT use the '=' operator."); };
            inline EditorRenderer& operator = (EditorRenderer &&batch) { throw std::runtime_error("[ERROR] Cannot reassign a EditorRenderer object. Do NOT use the '=' operator."); };

            inline void add(SpriteRenderer* spr) {
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
                // gizmoBatch.render(cam);
            };

            // update the list of zIndices when called
            // spr = the SpriteRenderer whose zIndex was changed
            inline void updateZIndex(SpriteRenderer* spr) {
                if (!destroy(spr)) { return; }

                // add the sprite to the new batch it belongs to
                int n = spr->transform.zIndex + 499;
                if (batches[n].numSprites == 0) { addBatch(n); }
                batches[n].addSprite(spr);
            };
    };
}
