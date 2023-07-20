#pragma once

#include "component.h"

// todo add functions for GameObjects and take the sprite renderers from those.
// todo probably make the Renderer namespace into a class.

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
            int zIndex; // zIndex of the RenderBatch
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

            void start(int zIndex);
            void render(Camera const &cam);

            // * Returns true if the SpriteRenderer is successfully destroyed and false if it doesn't exist.
            bool destroyIfExists(SpriteRenderer* spr);
            void addSprite(SpriteRenderer* spr);
            bool hasTexture(Texture* tex) const;
    };

    namespace Renderer { // todo probs make this a class in the end
        extern Shader currentShader;
        extern RenderBatch batches[MAX_RENDER_BATCHES];
        extern int numBatches;

        inline void add(SpriteRenderer* spr) {
            if (!spr) { return; }

            for (int i = 0; i < numBatches; ++i) {
                if (batches[i].numSprites < MAX_RENDER_BATCH_SIZE && batches[i].zIndex == spr->gameObject->transform.zIndex) { 
                    batches[i].addSprite(spr);
                    return;
                }
            }

            if (numBatches >= MAX_RENDER_BATCHES) { // cannot exceed the max number of render batches
                std::cout << "[INFO] SpriteRenderer could not be added as the max number of RenderBatches has been reached.\n";
                return;
            }

            if (!numBatches) {
                batches[numBatches].start(spr->gameObject->transform.zIndex);
                batches[numBatches++].addSprite(spr);
                return;
            }

            // determine the spot to put the new render batch in so that batches are sorted based on zIndex
            // this uses a modified binary search
            int min = 0, max = numBatches;
            int index = numBatches/2;

            // todo OR WE COULD make the equals operator functional and just not delete anything and inform users to not use the
            // todo  assignment operator for RenderBatches (in fact, the users shouldn't be using RenderBatches in their code in the first place)
            for(;;) { // todo solution is either the vbo thing or we could make it using a dynamic array
                if (spr->gameObject->transform.zIndex < batches[index].zIndex) { // shift to look through lower half
                    max = index - 1;

                    if (min == max) { // check if we have determined where to place the RenderBatch
                        int j;                    
                        if (spr->gameObject->transform.zIndex < batches[min].zIndex) { j = min; }
                        else { j = min + 1; }

                        for (int i = numBatches; i > j; --i) { batches[i] = batches[i - 1]; }
                        batches[j].start(spr->gameObject->transform.zIndex);
                        batches[j].addSprite(spr);
                        break;
                    }

                    index = (max + min)/2;

                } else if (spr->gameObject->transform.zIndex > batches[index].zIndex) { // shift to look through upper half
                    min = index + 1;

                    if (min == max) { // check if we have determined where to place the RenderBatch
                        int j;                    
                        if (spr->gameObject->transform.zIndex < batches[min].zIndex) { j = min; }
                        else { j = min + 1; }

                        for (int i = numBatches; i > j; --i) { batches[i] = batches[i - 1]; }
                        batches[j].start(spr->gameObject->transform.zIndex);
                        batches[j].addSprite(spr);
                        break;
                    }

                    index = (max + min)/2;

                } else { // add it to the index + 1 spot as they are the same zIndex
                    for (int i = numBatches; i > index + 1; --i) { batches[i] = batches[i - 1]; }
                    index++;
                    batches[index].start(spr->gameObject->transform.zIndex);
                    batches[index].addSprite(spr);
                    break;
                }
            }

            numBatches++;
        };

        inline void add(GameObject const &go) {
            SpriteRenderer* spr = (SpriteRenderer*) go.getComponent(SPRITE_RENDERER);
            if (spr) { add(spr); }
        };

        // destroy a sprite renderer contained in the renderer
        // returns 1 if it successfully found and destroyed it and 0 otherwise
        inline bool destroy(SpriteRenderer* spr) {
            for (int i = 0; i < numBatches; ++i) { if (batches[i].destroyIfExists(spr)) { return 1; }}
            return 0;
        };

        // render each batch
        inline void render(Camera const &cam) {
            currentShader.use();
            for (int i = 0; i < numBatches; ++i) { batches[i].render(cam); }
        };
    }
}
