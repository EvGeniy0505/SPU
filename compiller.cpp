#include "processor.h"

int main()
{
    // TODO: Make separate file for allllll
    AllFile programm = {};

    char *code = (char*)malloc(sizeof(char));

    printf("%s", "Enter file name:");

    input_str(name_of_file);



    programm = ScanfFile(name_of_file);

    free(name_of_file);

    size_t num_func = programm.SizePtrs;

    char command[5] = {}; // TODO: Remove magic number
    int val = 0;
    int how_many = 0;     // *1
    int num_command = 0;

    called_segment* all_segments = (called_segment*)calloc(num_func, sizeof(called_segment));

    int *final_proc = (int *)calloc(num_func * 2, sizeof(int)); // TODO: magic number, mb realloc


    for (int num_of_str = 0; num_of_str < num_func; num_of_str++)
    {
        // TODO: ������� ��� ������� � ��������� ��������
        how_many = sscanf(programm.Ptrs[num_of_str], "%s %d", command, &val);

        #define DEF_CMD(NAME, HAS_VALUE, ...)           \
        if (strcasecmp(command, #NAME) == 0)            \
        {                                               \
            all_segments[num_of_str].command = NAME;    \
            if (HAS_VALUE)                              \
                all_segments[num_of_str].val = val;     \
        }                                               \



        // TODO: make code generation               commands.txt
        if (strcasecmp(command, "HLT") == 0)
        {
            all_segments[num_of_str].command = HLT;
        }
        else if (strcasecmp(command, "PUSH") == 0)
        {
            all_segments[num_of_str].command = PUSH;
            all_segments[num_of_str].val = val;
        }
        else if (strcasecmp(command, "POP") == 0)
        {
            all_segments[num_of_str].command = POP;
            all_segments[num_of_str].val = val;
        }
        else if (strcasecmp(command, "IN") == 0)
        {
            all_segments[num_of_str].command = IN;
        }
        else if (strcasecmp(command, "OUT") == 0)
        {
            all_segments[num_of_str].command = OUT;
        }
        else if (strcasecmp(command, "MUL") == 0)
        {
            all_segments[num_of_str].command = MUL;
        }
        else if (strcasecmp(command, "DIV") == 0)
        {
            all_segments[num_of_str].command = DIV;
        }
        else if (strcasecmp(command, "SUB") == 0)
        {
            all_segments[num_of_str].command = SUB;
        }
        else if (strcasecmp(command, "ADD") == 0)
        {
            all_segments[num_of_str].command = ADD;
        }
        else if (strcasecmp(command, "SQRT") == 0)
        {
            all_segments[num_of_str].command = SQRT;
        }
        else if (strcasecmp(command, "SIN") == 0)
        {
            all_segments[num_of_str].command = SIN;
        }
        else if (strcasecmp(command, "COS") == 0)
        {
            all_segments[num_of_str].command = COS;
        }
        else
        {
            printf("huina kakaya to\n");

        }


        if (how_many == 1)
        {
            final_proc[num_command] = (all_segments[num_of_str].command);

            num_command++;

        }
        else
        {
            final_proc[num_command] = (all_segments[num_of_str].command);
            final_proc[num_command + 1] = (all_segments[num_of_str].val);


            num_command = num_command + 2;

        }


    }


    free(all_segments);

    DTor(programm.Buff, programm.Ptrs);

    for (int i = 0; i < num_command; i++)
        printf("final_proc[%d] = %d;\n", i, final_proc[i]);

    FILE* proc = fopen("processor.bin", "wb");

    fwrite(final_proc, sizeof(int), num_command, proc); // TODO: �������� �������� ��� ��������� ����������


    fclose(proc); // TODO: �������� �������� ��� ���� ��������

    free(final_proc);

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
