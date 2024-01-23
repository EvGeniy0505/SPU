#include "assembler.h"


int main(void)
{

    FILE* proc = fopen("processor.bin", "rb"); // TODO: добавить проверку что файл открылся

    AllFile programm = ScanfFile("processor.bin");

    for(int num_of_str = 0; num_of_str < num_command; num_of_str++)
    {
        programm.Ptrs[] =
    }


    return 0;
}



