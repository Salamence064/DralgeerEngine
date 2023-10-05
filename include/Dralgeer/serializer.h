#pragma once

#include <stdint.h>

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
            // todo not sure how you use this to convert the mantissa to a non-float
            // todo  representation is (sign * 2^(exponent-127) * 1.mantissa)
        };

        // todo can just serialize the filename (without extension) of each scene since they will all be stored in the same directory
        // todo  (since directory will be dependent on type: root or sub)
    }
}
