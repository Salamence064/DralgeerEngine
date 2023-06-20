#ifndef SPRITE_H
#define SPRITE_H

#include "constants.h"
#include "texture.h"

namespace Dralgeer {
    // todo having this sprite struct almost seems unnecessary.
    // ! consider removing it and moving all the fields into the SpriteRenderer directly
    struct Sprite {
        float width, height;
        Texture* texture = nullptr;
        glm::vec2 texCords[4] = {glm::vec2(1, 1), glm::vec2(1, 0), glm::vec2(0, 0), glm::vec2(0, 1)};
    };

    // todo add rule of 5 operators
    class SpriteSheet {
        public:
            Sprite* sprites = nullptr;
            int numSprites = 0;

            SpriteSheet() {};
            SpriteSheet(SpriteSheet const &spr) {
                if (spr.sprites) {
                    numSprites = spr.numSprites;
                    sprites = new Sprite[numSprites];

                    // initialize each sprite
                    for (int i = 0; i < numSprites; ++i) {
                        sprites[i].texture = new Texture();
                        sprites[i].texture->init(spr.sprites[i].texture->filepath);
                        sprites[i].texCords[0] = spr.sprites[i].texCords[0];
                        sprites[i].texCords[1] = spr.sprites[i].texCords[1];
                        sprites[i].texCords[2] = spr.sprites[i].texCords[2];
                        sprites[i].texCords[3] = spr.sprites[i].texCords[3];
                        sprites[i].width = spr.sprites[i].width;
                        sprites[i].height = spr.sprites[i].height;
                    }
                }
            };

            SpriteSheet& operator = (SpriteSheet const &spr) {
                // free memory
                if (sprites) {
                    for (int i = 0; i < numSprites; ++i) { delete sprites[i].texture; }
                    delete[] sprites;
                }

                if (!spr.sprites) {
                    sprites = nullptr;
                    numSprites = 0;
                    return (*this);
                }

                numSprites = spr.numSprites;
                sprites = new Sprite[numSprites];

                // initialize each sprite
                for (int i = 0; i < numSprites; ++i) {
                    sprites[i].texture = new Texture();
                    sprites[i].texture->init(spr.sprites[i].texture->filepath);
                    sprites[i].texCords[0] = spr.sprites[i].texCords[0];
                    sprites[i].texCords[1] = spr.sprites[i].texCords[1];
                    sprites[i].texCords[2] = spr.sprites[i].texCords[2];
                    sprites[i].texCords[3] = spr.sprites[i].texCords[3];
                    sprites[i].width = spr.sprites[i].width;
                    sprites[i].height = spr.sprites[i].height;
                }

                return (*this);
            };

            void init(Texture const &tex, int spriteWidth, int spriteHeight, int numSprites, int spacing) {
                sprites = new Sprite[numSprites];
                this->numSprites = numSprites;

                int x = 0, y = tex.height - spriteHeight;
                for (int i = 0; i < numSprites; ++i) {
                    float top = (y + spriteHeight)/((float) tex.height);
                    float right = (x + spriteWidth)/((float) tex.width);
                    float left = x/((float) tex.width);
                    float bottom = y/((float) tex.height);

                    // add the sprite to the list
                    Sprite sprite;
                    sprite.texture = new Texture();
                    sprite.texture->init(tex.filepath);
                    sprite.texCords[0] = glm::vec2(right, top); 
                    sprite.texCords[1] = glm::vec2(right, bottom);
                    sprite.texCords[2] = glm::vec2(left, bottom);
                    sprite.texCords[3] = glm::vec2(left, top);
                    sprite.width = spriteWidth;
                    sprite.height = spriteHeight;
                    sprites[i] = sprite;

                    x += spriteWidth + spacing;
                    if (x >= tex.width) { x = 0; y -= spriteHeight + spacing; }
                }
            };

            ~SpriteSheet() {
                if (sprites) {
                    for (int i = 0; i < numSprites; ++i) { delete sprites[i].texture; }
                    delete[] sprites;
                }
            };
    };
}

#endif // !SPRITE_H
