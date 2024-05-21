#include <stdio.h>
#include <stdlib.h>
#include "bfp.h"

int main(int argc, char* argv[])
{
    if(argc == 2)
    {
        FILE* fp;
        char* buf;
        long fileSize;

        fp = fopen(argv[1], "r");
        if(fp == NULL)
        {
            return -1;
        }

        fseek(fp, 0, SEEK_END);
        fileSize = ftell(fp);
        fseek(fp, 0, SEEK_SET);

        buf = (char*)malloc(fileSize * sizeof(char));
        fread(buf, sizeof(char), fileSize, fp);

        runBrainfuckPlus(buf);

        free(buf);
        fclose(fp);
    }
    else
    {
        fprintf(stderr, "Please enter \"%s <file path>\"\n", argv[0]);
        return -1;
    }

    return 0;
}
