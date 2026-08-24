#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>

#define RAYGUI_IMPLEMENTATION
#include "thirdparty/raygui.h"

#define WW 400
#define WH 400

#define BUTTON_WIDTH  (int)(WW / 3)
#define BUTTON_HEIGHT (int)(WH / 8)
#define BUTTON_Y WH - 50

#define GATE_RECT_X (int)(WW/4)
#define GATE_RECT_Y (int)(WH/4)
#define GATE_RECT_W (int)(WW/4)
#define GATE_RECT_H (int)(WH/2)

#define GATE_TEXT_X (int)(GATE_RECT_X + GATE_RECT_X/3)
#define GATE_TEXT_Y (int)(GATE_RECT_Y + GATE_RECT_Y/3)

#define LINE_X_START (GATE_RECT_X + GATE_RECT_W)
#define LINE_Y       (GATE_RECT_Y * 2)
#define LINE_X_END   (int)(LINE_X_START + WW/5)

#define NOT_INPUTS_COUNT    1
#define AND_OR_INPUTS_COUNT 2

typedef enum {
   GATE_AND = 0,
   GATE_OR = 1,
   GATE_NOT = 2
} GATETYPE;

typedef struct {
    GATETYPE type;
    _Bool output;
    _Bool *inputs;
} Gate;

#define ALLOC_GATE(ptr, type, input_c) do {                     \
    ptr = (Gate*)malloc(sizeof(Gate));                          \
    if ((ptr) == NULL) {                                        \
        fprintf(stderr, "Gate allocation failed\n");            \
        exit(EXIT_FAILURE);                                     \
    }                                                           \
    (ptr)->inputs = (_Bool*)malloc((input_c) * sizeof(_Bool));          \
    if ((ptr)->inputs == NULL) {                                        \
        fprintf(stderr, "Inputs allocation failed\n");                  \
        free(ptr);                                                      \
        exit(EXIT_FAILURE);                                             \
    }                                                                   \
} while (0)

#define FREE_GATE(ptr) do {                     \
        if ((ptr) != NULL) {                    \
            if ((ptr)->inputs != NULL) {        \
                free((ptr)->inputs);            \
                (ptr)->inputs = NULL;           \
            }                                   \
            free(ptr);                          \
            (ptr) = NULL;                       \
        }                                       \
} while(0)

_Bool draw_gate(GATETYPE type , Gate* ptr) {
    // TODO: draw inputs
    if (type < 0 || type > 2) {
        fprintf(stderr, "Type '%d' is not supported\n", type);
        return false;
    }
    if (ptr == NULL) {
        fprintf(stderr, "Ptr is NULL");
        return false;
    }
    const char* str = NULL;
    switch (type) {
        case GATE_AND: {
            str = "AND";
            break;
        }
        case GATE_OR: {
            str = "OR";
            break;
        }
        case GATE_NOT: {
            str = "NOT";
            break;
        }
        default: return false;
    }



    DrawRectangle(GATE_RECT_X, GATE_RECT_Y, GATE_RECT_W, GATE_RECT_H, LIGHTGRAY);
    DrawText(str, GATE_TEXT_X, GATE_TEXT_Y, 25, BLACK);
    DrawLine(LINE_X_START, LINE_Y, LINE_X_END, LINE_Y, GRAY);
    return true;
}

int main(void) {
    InitWindow(WW, WH, "fasm-hello");
    SetTargetFPS(24);

    Gate* gate = NULL;
    ALLOC_GATE(gate, GATE_AND, AND_OR_INPUTS_COUNT);

    Rectangle or  = { 0, BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT};
    Rectangle and = { BUTTON_WIDTH + 5, BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT };
    Rectangle not = {BUTTON_WIDTH * 2 + 10, BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT};

    uint8_t clicked = 0;
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));
        if (GuiButton(or, "OR")) {
            clicked = GATE_OR;
        }
        if (GuiButton(and, "AND")) {
            clicked = GATE_AND;
        }
        if (GuiButton(not, "NOT")) {
            clicked = GATE_NOT;
        }
        if (!draw_gate(clicked)) {
            // TODO: handle error
        }
        EndDrawing();
    }

    FREE_GATE(gate);
}
