#pragma once

#include <stdint.h>
#include <cmath>

namespace Dralgeer {
    namespace Serializer {
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

        inline void serializeFloat(unsigned char* buffer, size_t &bufferSize, float n) {
            int exp;
            float mantissa = std::frexpf(n, &exp);

            // todo not sure how you use this to convert the mantissa to a non-float
            // todo  representation is m * 2^(exp) with m = mantissa
            
        };
    }
}
