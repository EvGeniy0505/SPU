#include <stdio.h>
#include <math.h>

#include "processor.h"



    // FILE* proc = fopen("processor.bin", "rb");

    // AllFile programm = ScanfFile("processor.bin");

    // for(int num_of_str = 0; num_of_str < num_command; num_of_str++)
    // {
    //     programm.Ptrs[] =
    // }

void Run(int code[], size_t size)
{
    Stack stk = {};
    Stack_init(&stk, 10);

    int pc = 0;
    bool hlt_check = true;

    while(hlt_check)
    {
        switch(code[pc])
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
                int new_val = 0;

                scanf("%d", new_val);

                Stack_push(&stk, new_val);

                pc += 1;

                break;
            case OUT:
                int del_val = 0;

                Stack_pop(&stk, &del_val);
                printf("Удалили нахуй - %d\n", del_val);

                pc += 1;

                break;
            case ADD:
                int first_val  = 0;
                int second_val = 0;

                Stack_pop(&stk, &first_val);
                Stack_pop(&stk, &second_val);

                Stack_push(&stk, second_val + first_val);

                pc += 1;

                break;
            case SUB:
                int first_val  = 0;
                int second_val = 0;

                Stack_pop(&stk, &first_val);
                Stack_pop(&stk, &second_val);


                Stack_push(&stk, second_val - first_val);

                pc += 1;

                break;
            case MUL:
                int first_val  = 0;
                int second_val = 0;

                Stack_pop(&stk, &first_val);
                Stack_pop(&stk, &second_val);

                Stack_push(&stk, second_val * first_val);

                pc += 1;

                break;
            case DIV:
                int first_val  = 0;
                int second_val = 0;

                Stack_pop(&stk, &first_val);
                Stack_pop(&stk, &second_val);

                Stack_push(&stk, second_val / first_val);

                break;
            case SQRT:
                int val  = 0;

                Stack_pop(&stk, &val);

                Stack_push(&stk, sqrt(val));

                pc += 1;

                break;
            case SIN:
                int val  = 0;

                Stack_pop(&stk, &val);

                Stack_push(&stk, sin(val));

                pc += 1;

                break;
            case COS:
                int val  = 0;

                Stack_pop(&stk, &val);

                Stack_push(&stk, cos(val));

                pc += 1;

                break;
            case HLT:
                hlt_check = false;

                pc += 1;

                break;
            default:
                hlt_check = false;

                printf("пиздец, пиздец, пиздец, что за член???");
        }
    }
}
