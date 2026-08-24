#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>

#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

#define WW 400
#define WH 400

#define BUTTON_WIDTH  (int)(WW / 3)
#define BUTTON_HEIGHT (int)(WH / 8)
#define BUTTON_Y WH - 50

#define GATE_RECT_X (int)(WW/3)
#define GATE_RECT_Y (int)(WH/4)
#define GATE_RECT_W (int)(WW/4)
#define GATE_RECT_H (int)(WH/2)

#define GATE_TEXT_X (int)(GATE_RECT_X + GATE_RECT_X/4)
#define GATE_TEXT_Y (int)(GATE_RECT_Y + GATE_RECT_Y/4)

#define LINE_X_START (GATE_RECT_X + GATE_RECT_W)
#define LINE_Y       (GATE_RECT_Y * 2)
#define LINE_X_END   (int)(LINE_X_START + WW/5)

#define RADIUS 10

#define AND_INPUTS_COUNT 2

#define INPUT_LINE_START_X (int)(GATE_RECT_X - WW / 5)
#define INPUT1_LINE_START_Y GATE_RECT_Y * 1.5
#define INPUT2_LINE_START_Y GATE_RECT_Y * 2.5
#define BUTTON_S (int)(WW / 10)

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

#define ALLOC_GATE(ptr, _type, _input) do {                     \
    ptr = (Gate*)malloc(sizeof(Gate));                          \
    if ((ptr) == NULL) {                                        \
        fprintf(stderr, "Gate allocation failed\n");            \
        exit(EXIT_FAILURE);                                     \
    }                                                           \
    (ptr)->inputs = (_Bool*)malloc((_input) * sizeof(_Bool));           \
    if ((ptr)->inputs == NULL) {                                        \
        fprintf(stderr, "Inputs allocation failed\n");                  \
        free(ptr);                                                      \
        exit(EXIT_FAILURE);                                             \
    }                                                                   \
    (ptr)->type = (_type);                                              \
    (ptr)->inputs[0] = false;                                           \
    if (_input > 1) (ptr)->inputs[1] = true;                            \
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

extern _Bool compute(GATETYPE type, _Bool *inputs);

void draw_inputs(Gate *ptr) {
    if (ptr == NULL) {
        fprintf(stderr, "Ptr is NULL (draw_inputs)\n");
        return;
    }
    GATETYPE type = ptr->type;
    if (type == GATE_NOT) {
        DrawCircleLines(GATE_RECT_X, GATE_RECT_Y * 2, RADIUS, GRAY);
        DrawLine(GATE_RECT_X - WW / 5, GATE_RECT_Y * 2, GATE_RECT_X, GATE_RECT_Y * 2, ptr->inputs[0] ? GREEN : RED);
        return;
    }
    DrawLine(INPUT_LINE_START_X, INPUT1_LINE_START_Y, GATE_RECT_X, GATE_RECT_Y * 1.5, ptr->inputs[0] ? GREEN : RED);
    DrawLine(INPUT_LINE_START_X, INPUT2_LINE_START_Y, GATE_RECT_X, GATE_RECT_Y * 2.5, ptr->inputs[1] ? GREEN : RED);
    return;
}

_Bool draw_gate(Gate* ptr) {
    if (ptr == NULL) {
        fprintf(stderr, "Ptr is NULL");
        return false;
    }
    GATETYPE type = ptr->type;
    if (type < 0 || type > 2) {
        fprintf(stderr, "Type '%d' is not supported\n", type);
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

    ptr->output = compute(type, ptr->inputs);
    DrawRectangle(GATE_RECT_X, GATE_RECT_Y, GATE_RECT_W, GATE_RECT_H, LIGHTGRAY);
    DrawText(str, GATE_TEXT_X, GATE_TEXT_Y, 25, BLACK);
    DrawLine(LINE_X_START, LINE_Y, LINE_X_END, LINE_Y, ptr->output == true ? GREEN : RED);
    draw_inputs(ptr);

    return true;
}

int main(void) {
    int exit_code = 0;

    InitWindow(WW, WH, "fasm-hello");
    SetTargetFPS(24);

    Gate* gate = NULL;
    ALLOC_GATE(gate, GATE_AND, AND_INPUTS_COUNT);

    Rectangle or  = { 0, BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT};
    Rectangle and = { BUTTON_WIDTH + 5, BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT };
    Rectangle not = {BUTTON_WIDTH * 2 + 10, BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT};
    Rectangle in1 = {INPUT_LINE_START_X - 50, INPUT1_LINE_START_Y - 25, BUTTON_S, BUTTON_S};
    Rectangle in2 = {INPUT_LINE_START_X - 50, INPUT2_LINE_START_Y - 25, BUTTON_S, BUTTON_S};

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));
        if (GuiButton(or, "OR")) gate->type = GATE_OR;
        if (GuiButton(and, "AND")) gate->type = GATE_AND;
        if (GuiButton(not, "NOT")) gate->type = GATE_NOT;
        if (GuiButton(in1, gate->inputs[0] ? "1" : "0")) gate->inputs[0] = !gate->inputs[0];
        if (gate->type != GATE_NOT) {
            if (GuiButton(in2, gate->inputs[1] ? "1" : "0")) gate->inputs[1] = !gate->inputs[1];
        }
        if (!draw_gate(gate)) {
            fprintf(stderr, "ERROR: Failed to draw gate\n");
            goto end;
        }
        EndDrawing();
    }

end:
    FREE_GATE(gate);
    puts("Freed");
    return exit_code;
}
