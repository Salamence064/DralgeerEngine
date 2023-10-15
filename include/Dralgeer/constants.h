// ? Include the constants for the dralgeer engine.

#pragma once

// determine if the architecture is little or big endian
#define IS_BIG_ENDIAN (*(uint16_t *)"\0\xff" < 0x100)

// Width and height of a grid tile in pixels
#define GRID_WIDTH 32
#define GRID_HEIGHT 32

// equivalent of 16:9 aspect ratio
#define TARGET_ASPECT_RATIO 1.77778f

// sprite's ImGui color picker
#define IMGUI_COLOR_PICKER_X 1370
#define IMGUI_COLOR_PCIKER_Y 35
#define IMGUI_COLOR_PICKER_WIDTH 550
#define IMGUI_COLOR_PCIKER_HEIGHT 450

// debug draw
#define MAX_DEBUG_LINES 500
#define DEBUG_VERTEX_ARR_SIZE 6000
#define DEBUG_VERTEX_SIZE 5
#define DEBUG_VERTEX_SIZE_BYTES (DEBUG_VERTEX_SIZE * sizeof(float))
#define DEBUG_COLOR_OFFSET (2 * sizeof(float))

// renderer
#define MAX_RENDER_BATCHES 2500
#define MAX_RENDER_BATCH_SIZE 1000
#define MAX_RENDER_VERTICES_LIST_SIZE 40000
#define MAX_RENDER_INDICES_LIST_SIZE 6000
#define MAX_TEXTURES 16

#define COLOR_OFFSET (2 * sizeof(float))
#define TEX_COORDS_OFFSET (6 * sizeof(float))
#define TEX_ID_OFFSET (8 * sizeof(float))
#define ENTITY_ID_OFFSET (9 * sizeof(float))

#define VERTEX_SIZE 10
#define SPRITE_SIZE 40
#define VERTEX_SIZE_BYTES (VERTEX_SIZE * sizeof(float))
#define SPRITE_SIZE_BYTES (SPRITE_SIZE * sizeof(float))

// static batch
#define MAX_STATIC_BATCH_SIZE 1000
#define MAX_STATIC_VERTICES_SIZE 40000
#define MAX_STATIC_INDICES_SIZE 6000

// dynamic batch

// // gizmo batch specifics
// #define GIZMO_BATCH_SIZE 4
// #define GIZMO_BATCH_VERTICES_SIZE (40 * sizeof(float))
// #define GIZMO_BATCH_INDICES_SIZE 24

// editor camera
#define EDITOR_DRAG_SENSITIVITY 30.0f
#define EDITOR_SCROLL_SENSITIVITY 0.1f

// editor ImGui stuff
#define DEFAULT_WIDGET_WIDTH 220.0f
