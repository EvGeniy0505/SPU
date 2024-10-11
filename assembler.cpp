#include "processor.h"

int main()
{

    struct text_params tp = constructur_text_params();

    called_segment* all_segments = (called_segment*)calloc(tp.quantity_strs, sizeof(called_segment));  //кол-во команд

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
        }

        #include "commands.txt"

        #undef DEF_CMD
    }

    destructor_text_params(&tp);

    FILE* prog_code = fopen("program_code.txt", "a");

    for(int i = 0; i < tp.quantity_strs; i++)
         fprintf(prog_code, "%d %lf\n", all_segments -> command, all_segments -> val);

    fclose(prog_code);

    for(int i = 0; i < tp.quantity_strs; i++)
         fprintf(stdout, "%d %lf\n", all_segments -> command, all_segments -> val);

    free(all_segments);

    return 0;
}


char* input_str(char *str)
{
    char c;
    int len = 1;


    while((c = getchar()) != '\n')
    {
        str[len - 1] = c;
        len++;
        str = (char*) realloc(str, len);
    }
    str[len - 1] = '\0';

    return str;

}
