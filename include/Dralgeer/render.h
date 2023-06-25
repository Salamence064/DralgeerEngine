#ifndef RENDER_H
#define RENDER_H

#include "component.h"

// todo add functions for GameObjects and take the sprite renderers from those.
// todo probably make the Renderer namespace into a class.

namespace Dralgeer {
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
            inline void loadVertexProperties(int index);

        public:
            int zIndex; // zIndex of the RenderBatch
            int numSprites = 0;
            int numTextures = 0;

            RenderBatch() {};

            void start(int zIndex);
            void render();

            // * Returns true if the SpriteRenderer is successfully destroyed and false if it doesn't exist.
            bool destroyIfExists(SpriteRenderer* spr);
            void addSprite(SpriteRenderer const &spr);
            bool hasTexture(Texture* tex) const;
    };

    namespace Renderer { // todo probs make this a class in the end
        extern Shader currentShader;
        extern RenderBatch batches[MAX_RENDER_BATCHES];
        extern int numBatches;

        // todo add the GameObject related functions after fleshing out the GameObject class

        inline void add(SpriteRenderer const &spr) {
            for (int i = 0; i < numBatches; ++i) {
                // todo this last line of the conditional might be wrong
                if (batches[i].numSprites < MAX_RENDER_BATCH_SIZE && batches[i].zIndex == spr.gameObject->transform.zIndex &&
                        spr.sprite.texture && !batches[i].hasTexture(spr.sprite.texture) && batches[i].numTextures < MAX_TEXTURES) { 
                    
                    batches[i].addSprite(spr);
                    return;
                }
            }

            if (numBatches >= MAX_RENDER_BATCHES) { // cannot exceed the max number of render batches
                std::cout << "[INFO] SpriteRenderer could not be added as the max number of RenderBatches has been reached.\n";
                return;
            }

            RenderBatch newBatch;
            newBatch.start(spr.gameObject->transform.zIndex);
            newBatch.addSprite(spr);

            // determine the spot to put the new render batch in so that batches are sorted based on zIndex
            // this uses a modified binary search
            int min = 0, max = numBatches;
            int index = numBatches/2;

            for(;;) {
                if (newBatch.zIndex < batches[index].zIndex) { // shift to look through lower half
                    max = index - 1;

                    if (min == max) { // check if we have determined where to place the RenderBatch
                        int j;                    
                        if (newBatch.zIndex < batches[min].zIndex) { j = min; }
                        else { j = min + 1; }

                        for (int i = numBatches; i > j; --i) { batches[i] = batches[i - 1]; }
                        batches[j] = newBatch;
                        break;
                    }

                    index = (max + min)/2;

                } else if (newBatch.zIndex > batches[index].zIndex) { // shift to look through upper half
                    min = index + 1;

                    if (min == max) { // check if we have determined where to place the RenderBatch
                        int j;                    
                        if (newBatch.zIndex < batches[min].zIndex) { j = min; }
                        else { j = min + 1; }

                        for (int i = numBatches; i > j; --i) { batches[i] = batches[i - 1]; }
                        batches[j] = newBatch;
                        break;
                    }

                    index = (max + min)/2;

                } else { // add it to the index + 1 spot as they are the same zIndex
                    for (int i = numBatches; i > index + 1; --i) { batches[i] = batches[i - 1]; }
                    batches[index + 1] = newBatch;
                    break;
                }
            }

            numBatches++;
        };

        // destroy a sprite renderer contained in the renderer
        // returns 1 if it successfully found and destroyed it and 0 otherwise
        inline bool destroy(SpriteRenderer* spr) {
            for (int i = 0; i < numBatches; ++i) { if (batches[i].destroyIfExists(spr)) { return 1; }}
            return 0;
        };

        // render each batch
        inline void render() {
            currentShader.use();
            for (int i = 0; i < numBatches; ++i) { batches[i].render(); }
        };
    }
}

#endif // !RENDER_H
