#ifndef RENDER_H
#define RENDER_H

#include "component.h"

// todo add functions for GameObjects and take the sprite renderers from those.
// todo probably make the Renderer namespace into a class.

namespace Dralgeer {
    namespace Renderer { Shader currentShader; } // todo probs do something a bit different for the actual thing

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

    
    namespace Renderer {
        RenderBatch batches[MAX_RENDER_BATCHES];
        int numBatches = 0;

        // todo add the GameObject related functions after fleshing out the GameObject class

        void add(SpriteRenderer const &spr);

        // destroy a sprite renderer contained in the renderer
        // returns 1 if it successfully found and destroyed it and 0 otherwise
        bool destroy(SpriteRenderer* spr);

        // render each batch
        void render();
    }
}

#endif // !RENDER_H
