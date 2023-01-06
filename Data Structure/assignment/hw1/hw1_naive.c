#define _CRT_SECURE_NO_WARNINGS
#define MAX_SIZE 9999999


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int nfind(char*, char*);
int* result;
char str[MAX_SIZE];
char pat[MAX_SIZE];


int nfind(char* string, char* pat) {
    int i = 0, j = 0, start = 0;
    int lasts = strlen(string) - 1;
    int lastp = strlen(pat) - 1;
    int endmatch = lastp;
    int count = 0;


    for (i = 0; endmatch <= lasts; endmatch++, start++) {
        if (string[endmatch] == pat[lastp])
        {
            for (j = 0, i = start; j < lastp && string[i] == pat[j]; i++, j++);
            if (j == lastp) {
                count++;
                result[count - 1] = start;}
        }
    }


    return count;
}




int main() {
    FILE* strFILE;
    strFILE = fopen("string.txt", "r");
    FILE* patFILE;
    patFILE = fopen("pattern.txt", "r");


    if (strFILE == NULL)
    {
        printf("The string file does not exist.");
    }
    else if (patFILE == NULL)
    {
        printf("The pattern file does not exist.");
    }
    else
    {

        fgets(str, MAX_SIZE, strFILE);
        fgets(pat, MAX_SIZE, patFILE);
        int count = 0;

        result = (int*)malloc(sizeof(int) * MAX_SIZE);
        count = nfind(str, pat);

        FILE* fp;
        fp = fopen("result_naive.txt", "w");

        if (fp != NULL)
        {
            fprintf(fp, "%d\n", count);
            for (int i = 0; i < count; i++) {
                fprintf(fp, "%d ", result[i]);
            }

        }
    }

    return 0;
}

