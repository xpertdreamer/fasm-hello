#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

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

#define ALLOC_GATE(ptr, type, inputs) do {                      \
    ptr = (Gate*)malloc(sizeof(Gate));                          \
    if ((ptr) == NULL) {                                        \
        fprintf(stderr, "Gate allocation failed\n");            \
        exit(EXIT_FAILURE);                                     \
    }                                                           \
    (ptr)->inputs_count = (inputs);                             \
    (ptr)->inputs = (_Bool*)malloc((inputs) * sizeof(_Bool));           \
    if ((ptr)->inputs == NULL) {                                        \
        fprintf(stderr, "Inputs allocation failed\n");                  \
        free(ptr);                                                      \
        exit(EXIT_FAILURE);                                             \
    }                                                                   \
} while (0)

#define FREE_GATE(ptr) do                       \
        if ((ptr) != NULL) {                    \
            if ((ptr)->inputs != NULL) {        \
                free((ptr)->inputs);            \
                (ptr)->inputs = NULL;           \
            }                                   \
            free(ptr);                          \
            (ptr) = NULL;                       \
        }                                       \
    free(ptr);                                  \
    (ptr) = NULL;                               \
} while(0)

int main(void) {

    return 0;
}
