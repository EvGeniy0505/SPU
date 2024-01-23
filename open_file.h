#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>

struct AllFile{
    char **Ptrs;
    size_t SizePtrs;
    char *Buff;


};

int QuantityOfStrs(char * str);

int QuanOfSymbInStr(char * str);

int SizeOfStr(char * str);

int AllStrsAndReplace(char *Str, size_t SizeOfFile, char FirstSymb, char SecondSymb, size_t *NumOfStrs);

void PrintText(char **ArrOfPtr, int QuantityOfStrs);

size_t LenFile(FILE * fp);

int compare(const void *str1, const void *str2);

AllFile ScanfFile(const char *NameFile);

void DTor(char *Buff, char **Ptrs);
