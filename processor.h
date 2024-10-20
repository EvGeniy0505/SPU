#ifndef PROCESSOR
#define PROCESSOR

#include <string.h>
#include "stack.h"
#include "read_from_file.h"

enum commands{

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
    SIN,
    COS,
    JA,
    JAE,
    JB,
    JBE,
    JE,
    JNE,
    JMP
};

struct SPU
{
    double* code;
    int len_code_arr;
    int pc;
    Stack stk;
    double* registers;
};

void Run(SPU* spu);

void read_code_file(SPU* spu);

/*----------------assembler.h----------------------*/
struct called_segment
{
    int command;
    int quantity_vals;
    double val;
};

void assembler(const char* asm_code);

void program_code_to_file(const char* name_code_file, called_segment* all_segments, size_t quantity_commands);

/*-------------------------------------------------*/

#endif // PROCESSOR