// ? Include the constants for the dralgeer engine.

#ifndef CONSTANTS_H
#define CONSTANTS_H

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

// renderer
#define MAX_RENDER_BATCHES 2500
#define MAX_RENDER_BATCH_SIZE 1000
#define MAX_RENDER_VERTICES_LIST_SIZE 40000
#define MAX_TEXTURES 16

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

// editor camera
#define EDITOR_DRAG_SENSITIVITY 30.0f
#define EDITOR_SCROLL_SENSITIVITY 0.1f

// editor ImGui stuff
#define DEFAULT_WIDGET_WIDTH 220.0f

#endif // !CONSTANTS_H
