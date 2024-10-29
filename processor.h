#ifndef PROCESSOR
#define PROCESSOR

#include <string.h>
#include "stack.h"
#include "read_from_file.h"

#define FUNC_MAX_LEN 5
#define REG_MAX_VAL  4

enum commands
{
    #define DEF_CMD(NAME, NUM, ...) \
            CMD_##NAME = NUM,
    #include "commands.txt"
    #undef DEF_CMD
};

struct SPU
{
    double* code;
    int len_code_arr;
    int pc;
    Stack stk;
    double* registers;
};

struct one_command
{
    int len;
    char name[FUNC_MAX_LEN];
};

struct one_register
{
    int len;
    char name_reg[REG_MAX_VAL];
};

void Run(SPU* spu);

void read_code_file(SPU* spu);

/*----------------assembler.h----------------------*/

void assembler(const char* asm_code);

one_command read_command(text_params* tp, int num_symb);

void write_bin_code_to_file(const char* name_file, int* code, int num_elems);

one_register read_register(text_params* tp, int num_symb);

/*-------------------------------------------------*/

#endif // PROCESSOR