#pragma once

#include "constants.h"
#include "texture.h"

namespace Dralgeer {
    struct Sprite {
        float width, height;
        Texture* texture = nullptr;
        glm::vec2 texCoords[4] = {glm::vec2(1, 1), glm::vec2(1, 0), glm::vec2(0, 0), glm::vec2(0, 1)}; // these should not be changed
    };

    class SpriteSheet {
        public:
            Sprite* sprites = nullptr;
            int numSprites = 0; // this value should not be changed

            // ! Only for debugging
            std::string filepath;

            SpriteSheet() {};


            // * ===================
            // * Rule of 5 Stuff
            // * ===================

            SpriteSheet(SpriteSheet const &spr) {
                if (spr.sprites) {
                    numSprites = spr.numSprites;
                    sprites = new Sprite[numSprites];

                    // initialize each sprite
                    for (int i = 0; i < numSprites; ++i) {
                        sprites[i].texture = spr.sprites[i].texture;
                        sprites[i].texCoords[0] = spr.sprites[i].texCoords[0];
                        sprites[i].texCoords[1] = spr.sprites[i].texCoords[1];
                        sprites[i].texCoords[2] = spr.sprites[i].texCoords[2];
                        sprites[i].texCoords[3] = spr.sprites[i].texCoords[3];
                        sprites[i].width = spr.sprites[i].width;
                        sprites[i].height = spr.sprites[i].height;
                    }
                }
            };

            SpriteSheet(SpriteSheet &&spr) {
                numSprites = spr.numSprites;
                sprites = spr.sprites;
                spr.sprites = NULL;
            };

            SpriteSheet& operator = (SpriteSheet const &spr) {
                if (this == &spr) { return *this; }

                // free memory
                if (sprites) {
                    for (int i = 0; i < numSprites; ++i) { delete sprites[i].texture; }
                    delete[] sprites;
                }

                if (!spr.sprites) {
                    sprites = nullptr;
                    numSprites = 0;
                    return *this;
                }

                numSprites = spr.numSprites;
                sprites = new Sprite[numSprites];

                // initialize each sprite
                for (int i = 0; i < numSprites; ++i) {
                    sprites[i].texture = spr.sprites[i].texture;
                    sprites[i].texCoords[0] = spr.sprites[i].texCoords[0];
                    sprites[i].texCoords[1] = spr.sprites[i].texCoords[1];
                    sprites[i].texCoords[2] = spr.sprites[i].texCoords[2];
                    sprites[i].texCoords[3] = spr.sprites[i].texCoords[3];
                    sprites[i].width = spr.sprites[i].width;
                    sprites[i].height = spr.sprites[i].height;
                }

                return *this;
            };

            SpriteSheet& operator = (SpriteSheet &&spr) {
                if (this != &spr) {
                    numSprites = spr.numSprites;
                    sprites = spr.sprites;
                    spr.sprites = NULL;
                }

                return *this;
            };

            ~SpriteSheet() {
                if (sprites) {
                    for (int i = 0; i < numSprites; ++i) { delete sprites[i].texture; }
                    delete[] sprites;
                }
            };

            
            // * ====================
            // * Normal Functions
            // * ====================

            // tex should have init called on it prior to this function call
            void init(Texture* tex, int spriteWidth, int spriteHeight, int numSprites, int spacing) {
                sprites = new Sprite[numSprites];
                this->numSprites = numSprites;
                filepath = tex->filepath;

                int x = 0, y = tex->height - spriteHeight;
                for (int i = 0; i < numSprites; ++i) {
                    float top = (y + spriteHeight)/((float) tex->height);
                    float right = (x + spriteWidth)/((float) tex->width);
                    float left = x/((float) tex->width);
                    float bottom = y/((float) tex->height);

                    // add the sprite to the list
                    Sprite sprite;
                    sprite.texture = tex;
                    sprite.texCoords[0] = glm::vec2(right, top); 
                    sprite.texCoords[1] = glm::vec2(right, bottom);
                    sprite.texCoords[2] = glm::vec2(left, bottom);
                    sprite.texCoords[3] = glm::vec2(left, top);
                    sprite.width = spriteWidth;
                    sprite.height = spriteHeight;
                    sprites[i] = sprite;

                    x += spriteWidth + spacing;
                    if (x >= tex->width) { x = 0; y -= spriteHeight + spacing; }
                }
            };
    };
}
