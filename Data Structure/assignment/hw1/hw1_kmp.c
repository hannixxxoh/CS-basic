#define MAX_SIZE 9999999
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int pmatch(char* string, char* pat);
void fail(char* pat);
int failure[MAX_SIZE];
int* result;
char str[MAX_SIZE];
char pat[MAX_SIZE];


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
	else {
		fgets(str, MAX_SIZE, strFILE);
		fgets(pat, MAX_SIZE, patFILE);
		int count = 0;

		fail(pat);
		result = (int*)malloc(sizeof(int) * MAX_SIZE);
		count = pmatch(str, pat);
		FILE* fp;
		fp = fopen("result_kmp.txt", "w");
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


void fail(char* pat) {
	int i;
	int n = strlen(pat);
	failure[0] = -1;
	for (int j = 1; j < n; j++) {
		i = failure[j - 1];
		while ((pat[j] != pat[i + 1]) && (i >= 0)) i = failure[i];
		if (pat[j] == pat[i + 1]) failure[j] = i + 1;
		else failure[j] = -1;
	}
}

int pmatch(char* string, char* pat) {
	int i = 0;
	int j = 0;
	int lens = strlen(string);
	int lenp = strlen(pat);
	int count = 0;

	while (i < lens && j < lenp) {
		if (string[i] == pat[j]) {
			i++; j++;
			if (j == lenp) {
				count++;
				result[count - 1] = i - lenp;
				j = failure[j - 1] + 1;
			}
		}
		else if (j == 0) i++;
		else j = failure[j - 1] + 1;

	}
	return count;
}
