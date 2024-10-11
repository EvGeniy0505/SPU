#include <math.h>

#include "processor.h"

const double no_val = 0xdedbed;                                     // уточнить

int assembler()
{
    struct text_params tp = constructur_text_params("program_asm.txt");

    called_segment* all_segments = (called_segment*)calloc(tp.quantity_strs, sizeof(called_segment));  //кол-во команд

    int len_arr = 0;

    for (int num_of_str = 0; num_of_str < tp.quantity_strs; num_of_str++)
    {
        char command[5] = {};
        double val      = 0;

        sscanf(tp.arr_of_ptrs[num_of_str].begin , "%s %lf", command, &val);

        #define DEF_CMD(NAME, HAS_VALUE, ...)           \
        if (strcasecmp(command, #NAME) == 0)            \
        {                                               \
            all_segments[num_of_str].command = (NAME);  \
            if (HAS_VALUE)                              \
                all_segments[num_of_str].val = val;     \
            else                                        \
                all_segments[num_of_str].val = no_val;  \
        }

        #include "commands.txt"

        #undef DEF_CMD
    }

    FILE* prog_code = fopen("program_code.txt", "w");

    for(int num_of_str = 0; num_of_str < tp.quantity_strs; num_of_str++)
    {
        if(all_segments[num_of_str].val == no_val)
        {
            fprintf(prog_code, "%d\n", all_segments[num_of_str].command);
            len_arr++;
        }
        else
            fprintf(prog_code, "%d %lf\n", all_segments[num_of_str].command, all_segments[num_of_str].val);
            len_arr += 2;
    }

    free(all_segments);
    fclose(prog_code);
    destructor_text_params(&tp);

    return len_arr;
}

