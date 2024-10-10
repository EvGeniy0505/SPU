#ifndef ASSEMBLER
#define ASSEMBLER

#include <string.h>
#include "stack.h"

enum {

    HLT = -1,
    PUSH = 1,
    POP = 2,
    IN = 3,
    OUT = 4,
    ADD = 5,
    SUB = 6,
    MUL = 7,
    DIV = 8,
    SQRT = 9,
    SIN = 10,
    COS = 11,

};


struct called_segment
{
    int command;
    int val;
};


char* input_str(char *str);

void Run(int code[], size_t size)


#endif // ASSEMBLER