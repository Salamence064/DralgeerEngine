#pragma once

#include "component.h"

namespace Dralgeer {
    namespace Serializer {
        // * ========================================================================================
        // * Uint Serializers

        inline void serializeUint64(unsigned char* buffer, size_t &bufferSize, uint64_t n) {
            buffer[bufferSize++] = n >> 56;
            buffer[bufferSize++] = n >> 48;
            buffer[bufferSize++] = n >> 40;
            buffer[bufferSize++] = n >> 32;
            buffer[bufferSize++] = n >> 24;
            buffer[bufferSize++] = n >> 16;
            buffer[bufferSize++] = n >> 8;
            buffer[bufferSize++] = n;
        };

        inline void serializeUint32(unsigned char* buffer, size_t &bufferSize, uint32_t n) {
            buffer[bufferSize++] = n >> 24;
            buffer[bufferSize++] = n >> 16;
            buffer[bufferSize++] = n >> 8;
            buffer[bufferSize++] = n;
        };

        inline void serializeUint16(unsigned char* buffer, size_t &bufferSize, uint16_t n) {
            buffer[bufferSize++] = n >> 8;
            buffer[bufferSize++] = n;
        };

        inline void serializeUint8(unsigned char* buffer, size_t &bufferSize, uint8_t n) {
            buffer[bufferSize++] = n;
        };

        // * ========================================================================================
        // * Float Serializer

        inline void serializeFloat(unsigned char* buffer, size_t &bufferSize, float n) {
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

        inline void serializeString(unsigned char* buffer, size_t &bufferSize, const char* str) {
            int n = 0;
            while (str[n] != '\0') { buffer[bufferSize++] = str[n++]; }
            buffer[bufferSize++] = str[n]; // add the null character to the buffer to ensure we know when our string ends for deserializing
        };

        // * ========================================================================================
        // * Sprite Serializer

        inline void serializeSprite(unsigned char* buffer, size_t &bufferSize, Sprite const &sprite) {
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

            // store the texture's filepath // todo will have to figure out how to get the 
            std::string filepath = sprite.texture->filepath.substr(sprite.texture->filepath.find_last_of('/') + 1, sprite.texture->filepath.find_last_of('.'));
            serializeString(buffer, bufferSize, filepath.c_str());
        };

        // * ========================================================================================
        // * Transform Serializer

        

        // * ========================================================================================
        // * SpriteRenderer Serializer

        // * ========================================================================================
        // * GameObject Serializer

        // * ========================================================================================
        // * SpriteArea Serializer

        // * ========================================================================================
    }
}
