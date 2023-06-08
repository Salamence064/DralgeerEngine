// todo add renderbatch and render in here

#pragma once

#include "../components/sprite.h"

#define POS_SIZE 2
#define COLOR_SIZE 4
#define TEX_CORDS_SIZE 2
#define TEX_ID_SIZE 1
#define ENTITY_ID_SIZE 1

#define COLOR_OFFSET (POS_SIZE * sizeof(float))
#define TEX_CORDS_OFFSET (COLOR_OFFSET + (COLOR_SIZE * sizeof(float)))
#define TEX_ID_OFFSET (TEX_CORDS_OFFSET + (TEX_CORDS_SIZE * sizeof(float)))
#define ENTITY_ID_OFFSET (TEX_ID_OFFSET + sizeof(float))

#define VERTEX_SIZE 10
#define VERTEX_SIZE_BYTES (VERTEX_SIZE * sizeof(float))

namespace Dralgeer {
    class RenderBatch {

    };
}
