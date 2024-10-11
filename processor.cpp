#include <stdio.h>
#include <math.h>

#include "processor.h"


int* read_code_file(int len_code_arr)
{
    struct text_params tp = constructur_text_params("program_code.txt");

    int* code = (int*) calloc(len_code_arr, sizeof(stack_elem));

    for(int num_of_str = 0; num_of_str < len_code_arr; num_of_str++)
    {
        int check = fscanf(tp.file, "%lf", code[num_of_str]);
        if (check != 1)
            printf("ERROR!!!!");
    }

    destructor_text_params(&tp);

    return code;
}

void Run(double code[], size_t size)
{
    struct Stack stk = {};
    Stack_init(&stk, 10);

    int pc = 0;
    bool hlt_check = true;

    while(hlt_check)
    {
        switch((int)code[pc])
        {
            case PUSH:
                Stack_push(&stk, code[pc + 1]);

                pc += 2;

                break;
            case POP:
                Stack_pop(&stk, &code[pc + 1]);

                pc += 2;

                printf("Удалили нахуй - %d\n", code[pc + 1]);

                break;
            case IN:
                stack_elem new_val = 0;

                scanf("%d", new_val);

                Stack_push(&stk, new_val);

                pc += 1;

                break;
            case OUT:
                stack_elem del_val = 0;

                Stack_pop(&stk, &del_val);
                printf("Удалили нахуй - %d\n", del_val);

                pc += 1;

                break;
            case ADD:
                stack_elem first_val  = 0;
                stack_elem second_val = 0;

                Stack_pop(&stk, &first_val);
                Stack_pop(&stk, &second_val);

                Stack_push(&stk, second_val + first_val);

                pc += 1;

                break;
            case SUB:
                stack_elem first_val  = 0;
                stack_elem second_val = 0;

                Stack_pop(&stk, &first_val);
                Stack_pop(&stk, &second_val);


                Stack_push(&stk, second_val - first_val);

                pc += 1;

                break;
            case MUL:
                stack_elem first_val  = 0;
                stack_elem second_val = 0;

                Stack_pop(&stk, &first_val);
                Stack_pop(&stk, &second_val);

                Stack_push(&stk, second_val * first_val);

                pc += 1;

                break;
            case DIV:
                stack_elem first_val  = 0;
                stack_elem second_val = 0;

                Stack_pop(&stk, &first_val);
                Stack_pop(&stk, &second_val);

                Stack_push(&stk, second_val / first_val);

                break;
            case SQRT:
                stack_elem val  = 0;

                Stack_pop(&stk, &val);

                Stack_push(&stk, sqrt(val));

                pc += 1;

                break;
            case SIN:
                stack_elem val  = 0;

                Stack_pop(&stk, &val);

                Stack_push(&stk, sin(val));

                pc += 1;

                break;
            case COS:
                stack_elem val  = 0;

                Stack_pop(&stk, &val);

                Stack_push(&stk, cos(val));

                pc += 1;

                break;
            case HLT:
                hlt_check = false;

                break;
            default:
                hlt_check = false;

                printf("пиздец, пиздец, пиздец, что за член???");
        }
    }
}


int main()
{
    int len_code_arr = assembler();

    read_code_file(len_code_arr);

    return 0;
}