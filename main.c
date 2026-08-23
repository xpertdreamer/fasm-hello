#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <raylib.h>

#define RAYGUI_IMPLEMENTATION
#include "thirdparty/raygui.h"

typedef enum {
   GATE_AND = 0,
   GATE_OR = 1,
   GATE_NOT = 2
} GATETYPE;

typedef struct {
    GATETYPE type;
    int x;
    int y;
    uint8_t inputs_count;
    _Bool output;
    _Bool *inputs;
} Gate;

#define ALLOC_GATE(ptr, type, input_c) do {                     \
    ptr = (Gate*)malloc(sizeof(Gate));                          \
    if ((ptr) == NULL) {                                        \
        fprintf(stderr, "Gate allocation failed\n");            \
        exit(EXIT_FAILURE);                                     \
    }                                                           \
    (ptr)->inputs_count = (input_c);                                    \
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

int main(void) {
    InitWindow(400, 400, "fasm-hello");
    SetTargetFPS(24);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));
        EndDrawing();
    }
}
