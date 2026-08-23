#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <raylib.h>

#define RAYGUI_IMPLEMENTATION
#include "thirdparty/raygui.h"

#define WW 400
#define WH 400

#define BUTTON_WIDTH  (int)(WW / 3)
#define BUTTON_HEIGHT (int)(WH / 8)
#define BUTTON_Y WH - 50

#define MSG_BOX_X (int)(WW/4)
#define MSG_BOX_Y (int)(WH/3)
#define MSG_BOX_W (int)(WW/2)
#define MSG_BOX_H (int)(WH/4)

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
    InitWindow(WW, WH, "fasm-hello");
    SetTargetFPS(24);

    Rectangle or  = { 0, BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT};
    Rectangle and = { BUTTON_WIDTH + 5, BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT };
    Rectangle not = {BUTTON_WIDTH * 2 + 10, BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT};

    uint8_t clicked = 8;
    _Bool show_msg_box = false;
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
        switch (clicked) {
            case GATE_OR: {
                // TODO: draw or
                puts("OR clicked");
                clicked = 8;
                break;
            }
            case GATE_AND: {
                // TODO: draw and
                puts("AND clicked");
                clicked = 8;
                break;
            }
            case GATE_NOT: {
                // TODO: draw not
                puts("NOT clicked");
                clicked = 8;
                break;
            }
            case 8: break;
            default: {
                show_msg_box = clicked;
                clicked = 8;
                break;
            }
        }
        if (show_msg_box == true) {
            int btnActive = -1;
            GuiMessageBox((Rectangle){MSG_BOX_X, MSG_BOX_Y, MSG_BOX_W, MSG_BOX_H},
                          GuiIconText(ICON_CROSS, "Unknown"),
                          "Unknown element occured!",
                          "OK",
                          &btnActive
                          );
            if (btnActive >= 0) {
                show_msg_box = false;
                clicked = 8;
            }
        }

        EndDrawing();
    }
}
