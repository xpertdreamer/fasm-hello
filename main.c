#include <stdint.h>
#include <stdbool.h>



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

int main(void) {

    return 0;
}
