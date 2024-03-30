#pragma once

#include "component.h"
#include "assetpool.h"
#include <cstring>

namespace Dralgeer {
    // * ===================
    // * Serializer Stuff
    // * ===================

    namespace Serializer {
        // * ========================================================================================
        // * Primitive Serializer

        // Serialize an arbitrary primitive of type T.
        // Do NOT use this function on non-trivial datatypes.
        // It is not recommended to use on pointers as only the memory address will be serialized.
        template <typename T>
        static constexpr void serializePrimitive(char* buffer, size_t &bufferSize, T n) {
            std::memcpy(&buffer[bufferSize], &n, sizeof(T));
            bufferSize += sizeof(T);
        };

        // * ========================================================================================
        // * String Serializer

        static constexpr void serializeString(char* buffer, size_t &bufferSize, const char* str) {
            size_t n = 0;
            while (str[n]) { buffer[bufferSize++] = str[n++];} // null character = 0x00000000
            buffer[bufferSize++] = str[n]; // add the null character to the buffer to ensure we know when our string ends for deserializing
        };

        // * ========================================================================================
        // * Sprite Serializer

        static inline void serializeSprite(char* buffer, size_t &bufferSize, Sprite const &sprite) {
            // store the width and height
            serializePrimitive<uint16_t>(buffer, bufferSize, (uint16_t) sprite.width);
            serializePrimitive<uint16_t>(buffer, bufferSize, (uint16_t) sprite.height);

            // store the texCoords
            serializePrimitive<float>(buffer, bufferSize, sprite.texCoords[0].x);
            serializePrimitive<float>(buffer, bufferSize, sprite.texCoords[0].y);
            serializePrimitive<float>(buffer, bufferSize, sprite.texCoords[1].x);
            serializePrimitive<float>(buffer, bufferSize, sprite.texCoords[1].y);
            serializePrimitive<float>(buffer, bufferSize, sprite.texCoords[2].x);
            serializePrimitive<float>(buffer, bufferSize, sprite.texCoords[2].y);
            serializePrimitive<float>(buffer, bufferSize, sprite.texCoords[3].x);
            serializePrimitive<float>(buffer, bufferSize, sprite.texCoords[3].y);

            // store the texture's filepath
            size_t n = sprite.texture->filepath.find_last_of('/') + 1;
            std::string filepath = sprite.texture->filepath.substr(n, sprite.texture->filepath.find_last_of('.') - n);
            serializeString(buffer, bufferSize, filepath.c_str());
        };

        // * ========================================================================================
        // * Transform Serializer

        static constexpr void serializeTransform(char* buffer, size_t &bufferSize, Transform const &transform) {
            // store the position
            serializePrimitive<uint16_t>(buffer, bufferSize, (uint16_t) transform.pos.x);
            serializePrimitive<uint16_t>(buffer, bufferSize, (uint16_t) transform.pos.y);
            
            // store the width and height
            serializePrimitive<uint16_t>(buffer, bufferSize, (uint16_t) transform.scale.x);
            serializePrimitive<uint16_t>(buffer, bufferSize, (uint16_t) transform.scale.y);

            // store the zIndex
            serializePrimitive<uint16_t>(buffer, bufferSize, (uint16_t) (transform.zIndex + 499));

            // store the rotation
            serializePrimitive<float>(buffer, bufferSize, transform.rotation);
        };

        // * ========================================================================================
        // * SpriteRenderer Serializer

        // Takes in spr as a pointer since the engine stores its SpriteRenderers as pointers in most parts
        static inline void serializeSpriteRenderer(char* buffer, size_t &bufferSize, SpriteRenderer* spr) {
            // store the color values
            serializePrimitive<uint8_t>(buffer, bufferSize, (uint8_t) (255*spr->color.r));
            serializePrimitive<uint8_t>(buffer, bufferSize, (uint8_t) (255*spr->color.g));
            serializePrimitive<uint8_t>(buffer, bufferSize, (uint8_t) (255*spr->color.b));
            serializePrimitive<uint8_t>(buffer, bufferSize, (uint8_t) (255*spr->color.a));

            // serialize the sprite
            serializeSprite(buffer, bufferSize, spr->sprite);

            // serialize the transform
            serializeTransform(buffer, bufferSize, spr->transform);
        };

        // * ========================================================================================
        // * GameObject Serializer

        // GameObjects are stored as pointers in most parts of the engine so it takes in GameObject as a pointer.
        static inline void serializeGameObject(char* buffer, size_t &bufferSize, GameObject* go) {
            // store the name
            serializeString(buffer, bufferSize, go->name.c_str());

            // store the spriteRenderer
            serializeSpriteRenderer(buffer, bufferSize, go->sprite);
        };

        // * ========================================================================================
    }


    // * =====================
    // * Deserializer Stuff
    // * =====================

    // Note: The deserializers expect the data at the given buffer index to be valid for the returned type.
    namespace Deserializer {
        // * ========================================================================================
        // * Primitive Deserializers

        // Deserialize an arbitrary primitive of type T.
        // Do NOT use this function on non-trivial datatypes.
        // It is not recommended to use on pointers as only the memory address will be serialized.
        template <typename T>
        static constexpr T deserializePrimitive(char* buffer, size_t &currIndex) {
            T n;
            std::memcpy(&n, &buffer[currIndex], sizeof(T));
            currIndex += sizeof(T);
            return n;
        };

        // Deserialize an arbitrary primitive of type T.
        // Do NOT use this function on non-trivial datatypes.
        // It is not recommended to use on pointers as only the memory address will be serialized.
        template <typename T>
        static constexpr T deserializePrimitive(std::vector<char> const &buffer, size_t &currIndex) {
            T n;
            std::memcpy(&n, &buffer[currIndex], sizeof(T));
            currIndex += sizeof(T);
            return n;
        };

        // * ========================================================================================
        // * String Deserializer

        static inline std::string deserializeString(char* buffer, size_t &currIndex) {
            char str[SERIALIZER_MAX_STRING_SIZE]; // read characters into a buffer used to instantiate a string
            int strSize = 0;

            // read in the string
            while(buffer[currIndex]) { str[strSize++] = buffer[currIndex++]; }
            str[strSize] = '\0';
            ++currIndex;

            // create a string object
            return std::string(str);
        };

        static inline std::string deserializeString(std::vector<char> const &buffer, size_t &currIndex) {
            char str[SERIALIZER_MAX_STRING_SIZE]; // read characters into a buffer used to instantiate a string
            int strSize = 0;

            // read in the string
            while(buffer[currIndex]) { str[strSize++] = buffer[currIndex++]; }
            str[strSize] = '\0';
            ++currIndex;

            // create a string object
            return std::string(str);
        };

        // * ========================================================================================
        // * Sprite Deserializer

        static inline Sprite deserializeSprite(char* buffer, size_t &currIndex) {
            Sprite sprite;

            // read in the width and height of the sprite
            sprite.width = deserializePrimitive<uint16_t>(buffer, currIndex);
            sprite.height = deserializePrimitive<uint16_t>(buffer, currIndex);

            // read in the texture coordinates
            sprite.texCoords[0].x = deserializePrimitive<float>(buffer, currIndex);
            sprite.texCoords[0].y = deserializePrimitive<float>(buffer, currIndex);
            sprite.texCoords[1].x = deserializePrimitive<float>(buffer, currIndex);
            sprite.texCoords[1].y = deserializePrimitive<float>(buffer, currIndex);
            sprite.texCoords[2].x = deserializePrimitive<float>(buffer, currIndex);
            sprite.texCoords[2].y = deserializePrimitive<float>(buffer, currIndex);
            sprite.texCoords[3].x = deserializePrimitive<float>(buffer, currIndex);
            sprite.texCoords[3].y = deserializePrimitive<float>(buffer, currIndex);

            // read in the texture's filepath and initialize it
            sprite.texture = AssetPool::getTexture("../../assets/images/spritesheets/" + deserializeString(buffer, currIndex) + ".png");
            return sprite;
        };

        static inline Sprite deserializeSprite(std::vector<char> const &buffer, size_t &currIndex) {
            Sprite sprite;

            // read in the width and height of the sprite
            sprite.width = deserializePrimitive<uint16_t>(buffer, currIndex);
            sprite.height = deserializePrimitive<uint16_t>(buffer, currIndex);

            // read in the texture coordinates
            sprite.texCoords[0].x = deserializePrimitive<float>(buffer, currIndex);
            sprite.texCoords[0].y = deserializePrimitive<float>(buffer, currIndex);
            sprite.texCoords[1].x = deserializePrimitive<float>(buffer, currIndex);
            sprite.texCoords[1].y = deserializePrimitive<float>(buffer, currIndex);
            sprite.texCoords[2].x = deserializePrimitive<float>(buffer, currIndex);
            sprite.texCoords[2].y = deserializePrimitive<float>(buffer, currIndex);
            sprite.texCoords[3].x = deserializePrimitive<float>(buffer, currIndex);
            sprite.texCoords[3].y = deserializePrimitive<float>(buffer, currIndex);

            // read in the texture's filepath and initialize it
            std::string str = deserializeString(buffer, currIndex);
            sprite.texture = AssetPool::getTexture("../../assets/images/spritesheets/" + str + ".png");
            return sprite;
        };

        // * ========================================================================================
        // * Transform Deserializer

        static inline Transform deserializeTransform(char* buffer, size_t &currIndex) {
            Transform transform;

            // deserialize the position
            transform.pos.x = deserializePrimitive<uint16_t>(buffer, currIndex);
            transform.pos.y = deserializePrimitive<uint16_t>(buffer, currIndex);

            // deserialize the width and height
            transform.scale.x = deserializePrimitive<uint16_t>(buffer, currIndex);
            transform.scale.y = deserializePrimitive<uint16_t>(buffer, currIndex);

            // deserialize the zIndex
            transform.zIndex = (int) deserializePrimitive<uint16_t>(buffer, currIndex) - 499;

            // deserialize the rotation
            transform.rotation = deserializePrimitive<float>(buffer, currIndex);

            return transform;
        };

        static inline Transform deserializeTransform(std::vector<char> const &buffer, size_t &currIndex) {
            Transform transform;

            // deserialize the position
            transform.pos.x = deserializePrimitive<uint16_t>(buffer, currIndex);
            transform.pos.y = deserializePrimitive<uint16_t>(buffer, currIndex);

            // deserialize the width and height
            transform.scale.x = deserializePrimitive<uint16_t>(buffer, currIndex);
            transform.scale.y = deserializePrimitive<uint16_t>(buffer, currIndex);

            // deserialize the zIndex
            transform.zIndex = (int) deserializePrimitive<uint16_t>(buffer, currIndex) - 499;

            // deserialize the rotation
            transform.rotation = deserializePrimitive<float>(buffer, currIndex);

            return transform;
        };

        // * ========================================================================================
        // * SpriteRenderer Deserializer

        static inline SpriteRenderer* deserializeSpriteRenderer(char* buffer, size_t &currIndex) {
            SpriteRenderer* spr = new SpriteRenderer();

            // deserialize the color values
            spr->color.r = deserializePrimitive<uint8_t>(buffer, currIndex)/255.0f;
            spr->color.g = deserializePrimitive<uint8_t>(buffer, currIndex)/255.0f;
            spr->color.b = deserializePrimitive<uint8_t>(buffer, currIndex)/255.0f;
            spr->color.a = deserializePrimitive<uint8_t>(buffer, currIndex)/255.0f;

            // deserialize the sprite
            spr->sprite = deserializeSprite(buffer, currIndex);

            // deserialize the transform
            spr->transform = deserializeTransform(buffer, currIndex);

            return spr;
        };

        static inline SpriteRenderer* deserializeSpriteRenderer(std::vector<char> const &buffer, size_t &currIndex) {
            SpriteRenderer* spr = new SpriteRenderer();

            // deserialize the color values
            spr->color.r = deserializePrimitive<uint8_t>(buffer, currIndex)/255.0f;
            spr->color.g = deserializePrimitive<uint8_t>(buffer, currIndex)/255.0f;
            spr->color.b = deserializePrimitive<uint8_t>(buffer, currIndex)/255.0f;
            spr->color.a = deserializePrimitive<uint8_t>(buffer, currIndex)/255.0f;

            // deserialize the sprite
            spr->sprite = deserializeSprite(buffer, currIndex);

            // deserialize the transform
            spr->transform = deserializeTransform(buffer, currIndex);

            return spr;
        };

        // * ========================================================================================
        // * GameObject Serializer

        static inline GameObject* deserializeGameObject(char* buffer, size_t &currIndex) {
            GameObject* go = new GameObject();

            // deserialize the name
            go->name = deserializeString(buffer, currIndex);

            // deserialize the sprite renderer
            go->sprite = deserializeSpriteRenderer(buffer, currIndex);

            // sync the game object's transform with the sprite renderer
            go->transform = go->sprite->transform;

            return go;
        };

        static inline GameObject* deserializeGameObject(std::vector<char> const &buffer, size_t &currIndex) {
            GameObject* go = new GameObject();

            // deserialize the name
            go->name = deserializeString(buffer, currIndex);

            // deserialize the sprite renderer
            go->sprite = deserializeSpriteRenderer(buffer, currIndex);

            // sync the game object's transform with the sprite renderer
            go->transform = go->sprite->transform;

            return go;
        };

        // * ========================================================================================
    }
}
