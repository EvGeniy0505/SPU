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

        reg_plus_val reg_val = read_reg_plus_num(&tp, num_symb);
        num_symb += reg_val.len;

        // printf("%s ", com.name);
        // printf("%d\n", atoi(tp.buff + num_symb));
        // printf("num_symb = %d\n", num_symb);

        #define DEF_CMD(NAME, NUM, ARGS, ...)                         \
        if (strcasecmp(com.name, #NAME) == 0)                         \
        {                                                             \
            code[num_bin_elem] = NUM;                                 \
            ++num_bin_elem;                                           \
            if (ARGS == 1)                                            \
            {                                                         \
                if(strcasecmp(&reg_val.flag, "[") == 0)               \
                {                                                     \
                    code[num_bin_elem] = 3;                           \
                    ++num_bin_elem;                                   \
                    code[num_bin_elem] = num_reg(reg_val.name_reg);   \
                    ++num_bin_elem;                                   \
                    code[num_bin_elem] = reg_val.val;                 \
                    ++num_bin_elem;                                   \
                    ++num_symb;                                       \
                }                                                     \
                else if(strcasecmp(reg.name_reg, "") != 0)            \
                {                                                     \
                    code[num_bin_elem] = 2;                           \
                    ++num_bin_elem;                                   \
                    code[num_bin_elem] = num_reg(reg.name_reg);       \
                    ++num_bin_elem;                                   \
                }                                                     \
                else                                                  \
                {                                                     \
                    code[num_bin_elem] = 1;                           \
                    ++num_bin_elem;                                   \
                    code[num_bin_elem] = atoi(tp.buff + num_symb);    \
                    ++num_bin_elem;                                   \
                    num_symb += 2;                                    \
                }                                                     \
            }                                                         \
        }
        #include "commands.txt"

        #undef DEF_CMD

        // printf("Code:\n");
        // for(int i = 0; i < tp.len_buff; i++)
        // {
        //     printf("%d ", code[i]);
        // }
        // putchar('\n');
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
    one_register reg = {0, ""};

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

reg_plus_val read_reg_plus_num(text_params* tp, int num_symb)
{
    reg_plus_val reg_val = {0, no_val, "", '\0'};

    if(num_symb + 7 < tp -> len_buff && num_symb + 8 < tp -> len_buff)
    {
        if (tp -> buff[num_symb] == '[' && (tp -> buff[num_symb + 7] == ']' || tp -> buff[num_symb + 8] == ']'))
        {
            reg_val.flag = '[';
            ++num_symb;
            while(tp -> buff[num_symb] != ' ')
            {
                memcpy(&reg_val.name_reg[reg_val.len], &tp -> buff[num_symb], sizeof(char));
                ++reg_val.len;
                ++num_symb;
            }

            reg_val.len += 3;
            num_symb    += 3;

            reg_val.val =  atoi(&tp -> buff[num_symb]);

            reg_val.len += 3;
            num_symb    += 2;
        }
    }

    return reg_val;
}

#define REG_NAME(REG) #REG

registers num_reg(const char* reg)
{
    if(strcasecmp(reg, REG_NAME(ax)) == 0)
    {
        return ax;
    }
    else if(strcasecmp(reg, REG_NAME(bx)) == 0)
    {
        return bx;
    }
    else if(strcasecmp(reg, REG_NAME(cx)) == 0)
    {
        return cx;
    }
    else if(strcasecmp(reg, REG_NAME(dx)) == 0)
    {
        return dx;
    }
}
