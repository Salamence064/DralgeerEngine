#pragma once

#include "component.h"
#include "assetpool.h"

namespace Dralgeer {
    // * ===================
    // * Serializer Stuff
    // * ===================

    namespace Serializer {
        // * ========================================================================================
        // * Uint Serializers

        inline void serializeUint64(char* buffer, size_t &bufferSize, uint64_t n) {
            buffer[bufferSize++] = n >> 56;
            buffer[bufferSize++] = n >> 48;
            buffer[bufferSize++] = n >> 40;
            buffer[bufferSize++] = n >> 32;
            buffer[bufferSize++] = n >> 24;
            buffer[bufferSize++] = n >> 16;
            buffer[bufferSize++] = n >> 8;
            buffer[bufferSize++] = n;
        };

        inline void serializeUint32(char* buffer, size_t &bufferSize, uint32_t n) {
            buffer[bufferSize++] = n >> 24;
            buffer[bufferSize++] = n >> 16;
            buffer[bufferSize++] = n >> 8;
            buffer[bufferSize++] = n;
        };

        inline void serializeUint16(char* buffer, size_t &bufferSize, uint16_t n) {
            buffer[bufferSize++] = n >> 8;
            buffer[bufferSize++] = n;
        };

        inline void serializeUint8(char* buffer, size_t &bufferSize, uint8_t n) {
            buffer[bufferSize++] = n;
        };

        // * ========================================================================================
        // * Float Serializer

        inline void serializeFloat(char* buffer, size_t &bufferSize, float n) {
            // assume the float size to be 32bits
            uint32_t num = *(uint32_t*) &n;

            // check endianness so that we know the order in which to serialize the float's bytes
            // PDP endianness is not supported
            // we cannot use a preprocessor macro due to the dependence on casting

            if (IS_BIG_ENDIAN) { // big endian
                serializeUint32(buffer, bufferSize, num);
                
            } else { // little endian
                buffer[bufferSize++] = num;
                buffer[bufferSize++] = num >> 8;
                buffer[bufferSize++] = num >> 16;
                buffer[bufferSize++] = num >> 24;
            }
        };

        // * ========================================================================================
        // * String Serializer

        inline void serializeString(char* buffer, size_t &bufferSize, const char* str) {
            int n = 0;
            while (str[n]) { buffer[bufferSize++] = str[n++]; } // null character = 00000000
            buffer[bufferSize++] = str[n]; // add the null character to the buffer to ensure we know when our string ends for deserializing
        };

        // * ========================================================================================
        // * Sprite Serializer

        inline void serializeSprite(char* buffer, size_t &bufferSize, Sprite const &sprite) {
            // store the width and height
            serializeUint16(buffer, bufferSize, (uint16_t) sprite.width);
            serializeUint16(buffer, bufferSize, (uint16_t) sprite.height);

            // store the texCoords
            serializeFloat(buffer, bufferSize, sprite.texCoords[0].x);
            serializeFloat(buffer, bufferSize, sprite.texCoords[0].y);
            serializeFloat(buffer, bufferSize, sprite.texCoords[1].x);
            serializeFloat(buffer, bufferSize, sprite.texCoords[1].y);
            serializeFloat(buffer, bufferSize, sprite.texCoords[2].x);
            serializeFloat(buffer, bufferSize, sprite.texCoords[2].y);
            serializeFloat(buffer, bufferSize, sprite.texCoords[3].x);
            serializeFloat(buffer, bufferSize, sprite.texCoords[3].y);

            // store the texture's filepath
            std::string filepath = sprite.texture->filepath.substr(sprite.texture->filepath.find_last_of('/') + 1, sprite.texture->filepath.find_last_of('.'));
            serializeString(buffer, bufferSize, filepath.c_str());
        };

        // * ========================================================================================
        // * Transform Serializer

        inline void serializeTransform(char* buffer, size_t &bufferSize, Transform const &transform) {
            // store the position
            serializeUint16(buffer, bufferSize, (uint16_t) transform.pos.x);
            serializeUint16(buffer, bufferSize, (uint16_t) transform.pos.y);
            
            // store the width and height
            serializeUint16(buffer, bufferSize, (uint16_t) transform.scale.x);
            serializeUint16(buffer, bufferSize, (uint16_t) transform.scale.y);

            // store the zIndex
            serializeUint16(buffer, bufferSize, (uint16_t) (transform.zIndex + 499));

            // pack the rotation data into 16 bits
            // first 9 bits are the non-decimal values
            // last 7 bits are the first 2 decimal places of the rotation
            serializeUint16(buffer, bufferSize, (((uint16_t) (transform.rotation - 360 * (int) std::floorf(transform.rotation)))<<7) | 
                                                ((uint16_t) ((transform.rotation - (int) transform.rotation)*100)));
            
            // more readable version of what's happening above
            // uint16_t n = (uint16_t) (transform.rotation - 360 * (int) std::floorf(transform.rotation));
            // uint16_t d = (uint16_t) ((transform.rotation - (int) transform.rotation)*100);
            // uint16_t r = n<<7|d; where r is the value serialized
        };

        // * ========================================================================================
        // * SpriteRenderer Serializer

        // Takes in spr as a pointer since the engine stores its SpriteRenderers as pointers in most parts
        inline void serializeSpriteRenderer(char* buffer, size_t &bufferSize, SpriteRenderer* spr) {
            // store the color values
            serializeUint8(buffer, bufferSize, (uint8_t) (255*spr->color.r));
            serializeUint8(buffer, bufferSize, (uint8_t) (255*spr->color.g));
            serializeUint8(buffer, bufferSize, (uint8_t) (255*spr->color.b));
            serializeUint8(buffer, bufferSize, (uint8_t) (255*spr->color.a));

            // serialize the sprite
            serializeSprite(buffer, bufferSize, spr->sprite);

            // serialize the transform
            serializeTransform(buffer, bufferSize, spr->transform);
        };

        // * ========================================================================================
        // * GameObject Serializer

        // GameObjects are stored as pointers in most parts of the engine so it takes in GameObject as a pointer.
        inline void serializeGameObject(char* buffer, size_t &bufferSize, GameObject* go) {
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

    // ? Note: The deserializers expect the data at the given buffer index to be valid for the retuned type.
    namespace Deserializer {
        // * ========================================================================================
        // * Uint Deserializers

        inline uint64_t deserializeUint64(char* buffer, size_t &currIndex) {
            return (uint64_t) buffer[currIndex++] << 56
                    | (uint64_t) buffer[currIndex++] << 48
                    | (uint64_t) buffer[currIndex++] << 40
                    | (uint64_t) buffer[currIndex++] << 32
                    | (uint32_t) buffer[currIndex++] << 24
                    | (uint32_t) buffer[currIndex++] << 16
                    | (uint16_t) buffer[currIndex++] << 8
                    | (uint8_t) buffer[currIndex++];
        };

        inline uint32_t deserializeUint32(char* buffer, size_t &currIndex) {
            return (uint32_t) buffer[currIndex++] << 24
                    | (uint32_t) buffer[currIndex++] << 16
                    | (uint16_t) buffer[currIndex++] << 8
                    | (uint8_t) buffer[currIndex++];
        };

        inline uint16_t deserializeUint16(char* buffer, size_t &currIndex) {
            return (uint16_t) buffer[currIndex++] << 8
                    | (uint8_t) buffer[currIndex++];
        };

        inline uint8_t deserializeUint8(char* buffer, size_t &currIndex) { return (uint8_t) buffer[currIndex++]; };


        // * =======================
        // * STD Library Friendly
        // * =======================

        inline uint64_t deserializeUint64(std::vector<char> const &buffer, size_t &currIndex) {
            return (uint64_t) buffer[currIndex++] << 56
                    | (uint64_t) buffer[currIndex++] << 48
                    | (uint64_t) buffer[currIndex++] << 40
                    | (uint64_t) buffer[currIndex++] << 32
                    | (uint32_t) buffer[currIndex++] << 24
                    | (uint32_t) buffer[currIndex++] << 16
                    | (uint16_t) buffer[currIndex++] << 8
                    | (uint8_t) buffer[currIndex++];
        };

        inline uint32_t deserializeUint32(std::vector<char> const &buffer, size_t &currIndex) {
            return (uint32_t) buffer[currIndex++] << 24
                    | (uint32_t) buffer[currIndex++] << 16
                    | (uint16_t) buffer[currIndex++] << 8
                    | (uint8_t) buffer[currIndex++];
        };

        inline uint16_t deserializeUint16(std::vector<char> const &buffer, size_t &currIndex) {
            return (uint16_t) buffer[currIndex++] << 8
                    | (uint8_t) buffer[currIndex++];
        };

        inline uint8_t deserializeUint8(std::vector<char> const &buffer, size_t &currIndex) { return (uint8_t) buffer[currIndex++]; };

        // * ========================================================================================
        // * Float Deserializer

        inline float deserializeFloat(char* buffer, size_t &currIndex) {
            // ? It is assumed that floats are 32bit
            // ? If your machine is PDP Endian you will not get the proper float value back as it will not have serialized properly

            uint32_t n = deserializeUint32(buffer, currIndex);
            return *(float*) &n;
        };


        // * =======================
        // * STD Library Friendly
        // * =======================

        inline float deserializeFloat(std::vector<char> const &buffer, size_t &currIndex) {
            // ? It is assumed that floats are 32bit
            // ? If your machine is PDP Endian you will not get the proper float value back as it will not have serialized properly

            uint32_t n = deserializeUint32(buffer, currIndex);
            return *(float*) &n;
        };

        // * ========================================================================================
        // * String Deserializer

        inline std::string deserializeString(char* buffer, size_t &currIndex) {
            char str[SERIALIZER_MAX_STRING_SIZE]; // read characters into a buffer used to instantiate a string
            int strSize = 0;

            // read in the string
            while(buffer[currIndex+strSize]) { str[strSize] = buffer[(currIndex++)+strSize++]; }
            str[strSize] = '\0';
            ++currIndex;

            // create a string object
            return std::string(str);
        };


        // * =======================
        // * STD Library Friendly
        // * =======================

        inline std::string deserializeString(std::vector<char> const &buffer, size_t &currIndex) {
            char str[SERIALIZER_MAX_STRING_SIZE]; // read characters into a buffer used to instantiate a string
            int strSize = 0;

            // read in the string
            while(buffer[currIndex+strSize]) { str[strSize] = buffer[(currIndex++)+strSize++]; }
            str[strSize] = '\0';
            ++currIndex;

            // create a string object
            return std::string(str);
        };

        // * ========================================================================================
        // * Sprite Deserializer

        inline Sprite deserializeSprite(char* buffer, size_t &currIndex) {
            Sprite sprite;

            // read in the width and height of the sprite
            sprite.width = deserializeUint16(buffer, currIndex);
            sprite.height = deserializeUint16(buffer, currIndex);

            // read in the texture coordinates
            sprite.texCoords[0].x = deserializeFloat(buffer, currIndex);
            sprite.texCoords[0].y = deserializeFloat(buffer, currIndex);
            sprite.texCoords[1].x = deserializeFloat(buffer, currIndex);
            sprite.texCoords[1].y = deserializeFloat(buffer, currIndex);
            sprite.texCoords[2].x = deserializeFloat(buffer, currIndex);
            sprite.texCoords[2].y = deserializeFloat(buffer, currIndex);
            sprite.texCoords[3].x = deserializeFloat(buffer, currIndex);
            sprite.texCoords[3].y = deserializeFloat(buffer, currIndex);

            // read in the texture's filepath and initialize it
            sprite.texture = AssetPool::getTexture("../../assets/images/spritesheets/" + deserializeString(buffer, currIndex) + ".png");
            return sprite;
        };

        inline Sprite deserializeSprite(std::vector<char> const &buffer, size_t &currIndex) {
            Sprite sprite;

            // read in the width and height of the sprite
            sprite.width = deserializeUint16(buffer, currIndex);
            sprite.height = deserializeUint16(buffer, currIndex);

            // read in the texture coordinates
            sprite.texCoords[0].x = deserializeFloat(buffer, currIndex);
            sprite.texCoords[0].y = deserializeFloat(buffer, currIndex);
            sprite.texCoords[1].x = deserializeFloat(buffer, currIndex);
            sprite.texCoords[1].y = deserializeFloat(buffer, currIndex);
            sprite.texCoords[2].x = deserializeFloat(buffer, currIndex);
            sprite.texCoords[2].y = deserializeFloat(buffer, currIndex);
            sprite.texCoords[3].x = deserializeFloat(buffer, currIndex);
            sprite.texCoords[3].y = deserializeFloat(buffer, currIndex);

            // read in the texture's filepath and initialize it
            sprite.texture = AssetPool::getTexture("../../assets/images/spritesheets/" + deserializeString(buffer, currIndex) + ".png");
            return sprite;
        };

        // * ========================================================================================
        // * Transform Deserializer

        inline Transform deserializeTransform(char* buffer, size_t &currIndex) {
            Transform transform;

            // bit masks
            const uint16_t nonDecimal = 0b1111111110000000;
            const uint16_t decimal = 0b0000000001111111;

            // deserialize the position
            transform.pos.x = deserializeUint16(buffer, currIndex);
            transform.pos.y = deserializeUint16(buffer, currIndex);

            // deserialize the width and height
            transform.scale.x = deserializeUint16(buffer, currIndex);
            transform.scale.y = deserializeUint16(buffer, currIndex);

            // deserialize the zIndex
            transform.zIndex = (int) deserializeUint16(buffer, currIndex) - 499;

            // deserialize and unpack the rotation
            uint16_t n = deserializeUint16(buffer, currIndex);
            transform.rotation = (n&nonDecimal) + ((n&decimal)/100.0f);

            return transform;
        };

        inline Transform deserializeTransform(std::vector<char> const &buffer, size_t &currIndex) {
            Transform transform;

            // bit masks
            const uint16_t nonDecimal = 0b1111111110000000;
            const uint16_t decimal = 0b0000000001111111;

            // deserialize the position
            transform.pos.x = deserializeUint16(buffer, currIndex);
            transform.pos.y = deserializeUint16(buffer, currIndex);

            // deserialize the width and height
            transform.scale.x = deserializeUint16(buffer, currIndex);
            transform.scale.y = deserializeUint16(buffer, currIndex);

            // deserialize the zIndex
            transform.zIndex = (int) deserializeUint16(buffer, currIndex) - 499;

            // deserialize and unpack the rotation
            uint16_t n = deserializeUint16(buffer, currIndex);
            transform.rotation = (n&nonDecimal) + ((n&decimal)/100.0f);

            return transform;
        };

        // * ========================================================================================
        // * SpriteRenderer Deserializer

        // * ========================================================================================
        // * GameObject Serializer

        // * ========================================================================================
    }
}
