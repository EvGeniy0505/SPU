#include <math.h>

#include "processor.h"

const unsigned long int no_val = 0xdedbed;

void assembler(const char* asm_code)
{
    struct text_params tp = constructur_text_params(asm_code);

    int* code = (int*) calloc(tp.len_buff, sizeof(int));
    int num_symb = 0;
    int num_bin_elem = 0;

    while(num_symb < tp.len_buff)
    {
        one_command com = read_command(&tp, num_symb);
        num_symb += com.len;

        ++num_symb;           // проходим пробел или '\0'

        one_register reg = read_register(&tp, num_symb);
        num_symb += reg.len;

        #define DEF_CMD(NAME, NUM, ARGS, ...)                     \
        if (strcasecmp(com.name, #NAME) == 0)                     \
        {                                                         \
            code[num_bin_elem] = NUM;                             \
            ++num_bin_elem;                                       \
            if (ARGS == 1)                                        \
            {                                                     \
                code[num_bin_elem] = atoi(tp.buff + num_symb);    \
                ++num_bin_elem;                                   \
                num_symb += 2;                                    \
            }                                                     \
        }
        #include "commands.txt"

        #undef DEF_CMD
    }

    write_bin_code_to_file("program_code.bin", code, num_bin_elem);

    destructor_text_params(&tp);
    free(code);
}


void write_bin_code_to_file(const char* name_file, int* code, int num_elems)
{
    FILE* fp = fopen(name_file, "wb");

    fwrite(code, num_elems, sizeof(int), fp);

    fclose(fp);
}

one_command read_command(text_params* tp, int num_symb)
{
    one_command com = {0, ""};

    while(tp -> buff[num_symb] != ' '  && tp -> buff[num_symb] != '\0')
    {
        memcpy(&com.name[com.len], &tp -> buff[num_symb], sizeof(char));
        ++com.len;
        ++num_symb;
    }

    return com;
}

one_register read_register(text_params* tp, int num_symb)
{
    one_register reg = {};
    reg.len = 0;

    if(tp -> buff[num_symb - 1] == ' ')
    {
        while(tp -> buff[num_symb] != '\0' && tp -> buff[num_symb] > 96 && tp -> buff[num_symb] < 123)
        {
            memcpy(&reg.name_reg[reg.len], &tp -> buff[num_symb], sizeof(char));
            ++reg.len;
            ++num_symb;

        }
    }

    return reg;
}