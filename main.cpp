#include "processor.h"



int main()
{
        assembler("/home/evgeniy/Документы/DED_Projects/SPU/program_asm.txt");

        SPU spu = {};

        read_code_file(&spu);

    return 0;
}
