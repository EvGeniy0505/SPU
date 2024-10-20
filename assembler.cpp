#include <math.h>

#include "processor.h"

#define FUNC_MAX_LEN 5

const double no_val = 0xdedbed;

void assembler(const char* asm_code)
{
    struct text_params tp = constructur_text_params(asm_code);

    called_segment* all_segments = (called_segment*)calloc(tp.quantity_strs, sizeof(called_segment));

    for (size_t num_of_str = 0; num_of_str < tp.quantity_strs; num_of_str++)
    {
        char* command       = (char*) calloc(FUNC_MAX_LEN, sizeof(char));        //[FUNC_MAX_LEN] = {};
        double val_1        = 0;
        double val_2        = 0;
        int quantity_vals   = 0;

        sscanf(tp.arr_of_ptrs[num_of_str].begin , "%s %d %lf %lf", command, &quantity_vals, &val_1, &val_2);

        #define DEF_CMD(NAME, ...)                      \
        if (strcasecmp(command, #NAME) == 0)            \
        {                                               \
            all_segments[num_of_str].command = (NAME);  \
            if(called_segment.quantity_vals == 2)       \
                all_segments[num_of_str].val = val_1;   \
                all_segments[num_of_str].val = val_2;   \
            else if (called_segment.quantity_vals == 1) \
                all_segments[num_of_str].val = val;     \
            else                                        \
                all_segments[num_of_str].val = no_val;  \
        }

        #include "commands.txt"

        #undef DEF_CMD

        free(command);
    }

    program_code_to_file("program_code.txt", all_segments, tp.quantity_strs);

    free(all_segments);
    destructor_text_params(&tp);

}


void program_code_to_file(const char* name_code_file, called_segment* all_segments, size_t quantity_commands)
{
    FILE* prog_code = fopen(name_code_file, "w");

    int len_code_arr = 0;

    for(size_t num_of_str = 0; num_of_str < quantity_commands; num_of_str++)
    {
        if(all_segments[num_of_str].val == no_val)
        {
            fprintf(prog_code, "%d ", all_segments[num_of_str].command);
        }
        else
        {
            fprintf(prog_code, "%d %lf ", all_segments[num_of_str].command, all_segments[num_of_str].val);
        }
    }

    fclose(prog_code);
}