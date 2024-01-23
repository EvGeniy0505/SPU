#ifndef ASSEMBLER
#define ASSEMBLER

// TODO: Обычно инклюды сортируют сначала <> потом ""
#include <string.h>
#include "stack.h"
#include "open_file.h"

enum {

    HLT = -1,
    PUSH = 1,
    POP = 2,
    IN = 3,
    OUT = 4,
    MUL = 5,       // умножение
    DIV = 6,       // частное
    SUB = 7,       // вычитание
    ADD = 8,       // сложение
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


#endif // ASSEMBLER
