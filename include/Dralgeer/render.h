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

            // * Helper to just make the code easier to read and debug.
            // * Will probs be moved directly into the code in the end.
            inline void loadVertexProperties(int index);
            inline void loadElementIndices(int index);

        public:
            int numSprites = 0;
            int numTextures = 0;

            RenderBatch() {};

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

            // * Returns true if the SpriteRenderer is successfully destroyed and false if it doesn't exist.
            bool destroyIfExists(SpriteRenderer* spr);
            void addSprite(SpriteRenderer* spr);
            bool hasTexture(Texture* tex) const;
    };

    class Renderer {
        private:
            RenderBatch batches[MAX_RENDER_BATCHES]; // todo refactor this to be a dynamic array and just place the batches in terms of zIndices
            int numBatches = 1;

        public:
            inline void start() { batches[0].start(); };

            inline void add(SpriteRenderer* spr) {
                if (!spr) { return; } // todo when I add the custom made logger macros, send out a debug message from here

                int n = numBatches - 1;
                if (batches[n].numSprites < MAX_RENDER_BATCH_SIZE) { batches[n].addSprite(spr); return; }
                if (numBatches == MAX_RENDER_BATCHES) { return; } // todo debug output from here

                batches[numBatches].start();
                batches[numBatches++].addSprite(spr);
            };

            inline void add(GameObject const &go) { if (go.sprite) { add(go.sprite); }};

            // destroy a sprite renderer contained in the renderer
            // returns 1 if it successfully found and destroyed it and 0 otherwise
            inline bool destroy(SpriteRenderer* spr) {
                for (int i = 0; i < numBatches; ++i) { if (batches[i].destroyIfExists(spr)) { return 1; }}
                return 0;
            };

            // render each batch
            inline void render(Shader const &currShader, Camera const &cam) {
                for (int i = 0; i < numBatches; ++i) { batches[i].render(currShader, cam); }
            };
    };
}
