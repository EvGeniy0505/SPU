#include <stdio.h>
#include <math.h>

#include "processor.h"


void read_code_file(SPU* spu)
{
    struct text_params tp = constructur_text_params("/home/evgeniy/Документы/DED_Projects/SPU/program_code.txt");

    spu -> code = (double*) calloc(tp.quantity_strs * 3 / 2, sizeof(stack_elem));

    int num_of_symb = 0;

    while(spu -> code[num_of_symb] != -1)
    {
        int check = fscanf(tp.file, "%lf", spu -> code[num_of_symb]);

        if (check != 1)
            color_printf(stderr, RED, "ERROR!!!!\n\n\n");

        num_of_symb++;
    }

    for (int i = 0; i < num_of_symb; ++i)
        printf("%f ; ", spu -> code[num_of_symb]);

    destructor_text_params(&tp);
}

void Run(SPU* spu)
{
    spu -> stk = {};
    Stack_init(&spu -> stk, 10);

    spu -> pc = 0;
    bool hlt_check = true;

    while(hlt_check)
    {
        switch((int)spu -> code[spu -> pc])
        {
            #define DEF_CODE_CMD(NAME, HAS_VALUE, ...) \
            case NAME:{                                 \
                __VA_ARGS__                              \
                if(HAS_VALUE)                             \
                    spu -> pc += 2;                        \
                else                                        \
                    spu -> pc += 1;                          \
                break;}

            #include "commands_code.txt"

            #undef DEF_CODE_CMD

            case HLT:{
                hlt_check = false;
                break;}
            default:{
                hlt_check = false;
                color_printf(stderr, RED, "пиздец, пиздец, пиздец, что за хуй???\n");}
        }
    }
}
