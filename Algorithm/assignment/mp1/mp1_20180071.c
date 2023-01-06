#define MAX_SIZE 50000001
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int NaiveMaxSum(int**, int, int);
int N4MaxSum(int**, int, int);
int N3MaxSum(int**, int, int);


int main(int argc, char** argv) {
	double start, end;
	start = (double)clock() / CLOCKS_PER_SEC;


	FILE* inputFILE;
	inputFILE = fopen(argv[1], "r");
	int result, m, n = 0;
	result = fscanf(inputFILE, "%d", &m);
	result = fscanf(inputFILE, "%d", &n);

	// declare the matrix
	int** arr2d = (int**)malloc(sizeof(int*) * m);

	for (int i = 0; i < m; i++)
	{
		arr2d[i] = (int*)malloc(sizeof(int) * n);
	}

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			result = fscanf(inputFILE, "%d", &arr2d[i][j]);
		}
	}

	// check the components of the matrix
	/*for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			printf("%d ", arr2d[i][j]);
		}
		printf("\n");
	}*/

	int user = atoi(argv[2]);
	int maxSum = 0;

	if (user == 1) {
		maxSum = NaiveMaxSum(arr2d, m, n);
	}
	else if (user == 2) {
		maxSum = N4MaxSum(arr2d, m, n);
	}
	else if (user == 3) {
		maxSum = N3MaxSum(arr2d, m, n);
	}

	end = (((double)clock()) / CLOCKS_PER_SEC);

	// save the file
	char output[100] = "result_";
	strcat(output, argv[1]);
	FILE* outputFILE;
	outputFILE = fopen(output, "w");

	fprintf(outputFILE, "%s\n", argv[1]);
	fprintf(outputFILE, "%d\n", user);
	fprintf(outputFILE, "%d\n", m);
	fprintf(outputFILE, "%d\n", n);
	fprintf(outputFILE, "%d\n", maxSum);
	fprintf(outputFILE, "%lf\n", end - start);
	return 0;
}

int NaiveMaxSum(int** arr2d, int m, int n) {

	int neg = arr2d[0][0];
	int isnegative = 1;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (arr2d[i][j] > 0) {
				isnegative = 0;
			}
			else if (arr2d[i][j] > neg) {
				neg = arr2d[i][j];
			}
		}
	}

  int maxSum = arr2d[0][0];

	// All negative
	if (isnegative == 1) {
		return neg;
	}


	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < m; k++) {
				for (int l = 0; l < n; l++) {
					int currSum = 0;
					for (int a = i; a <= k; a++) {
						for (int b = j; b <= l; b++) {
							currSum += arr2d[a][b];
						}
					}
					if (currSum > maxSum) {
						maxSum = currSum;
						// printf("%d %d %d %d %d \n", currSum, i, j, k, l);
					}
				}
			}
		}
	}
	return maxSum;
}

int N4MaxSum(int** arr2d, int m, int n) {

	// preprocess the matrix filled with the sum of the arr2d
	int** sub2d = (int**)malloc(sizeof(int*) * m+1);
	for (int i = 0; i <= m; i++)
	{
		sub2d[i] = (int*)malloc(sizeof(int) * n+1);
	}
	for (int i = 0; i <= m; i++)
	{
		for (int j = 0; j <= n; j++) {
			if (i == 0) {
				sub2d[i][j] = 0;
			}
			else if(j == 0){
				sub2d[i][j] = 0;
			}
			else {
				sub2d[i][j] = sub2d[i - 1][j] + sub2d[i][j - 1] - sub2d[i - 1][j - 1] + arr2d[i - 1][j - 1];
			}
		}
	}

	int maxSum = arr2d[0][0];
	for (int i = 0; i < m; i++) {
		for (int j = i; j < m; j++) {
			for (int k = 0; k < n; k++) {
				for (int l = k; l < n; l++) {
					int subrectangle_sum = sub2d[j + 1][l + 1] - sub2d[j + 1][k] - sub2d[i][l + 1] + sub2d[i][k];

					if (subrectangle_sum > maxSum) {
						maxSum = subrectangle_sum;
					}
				}
			}
		}
	}
	return maxSum;
}

int N3MaxSum(int** arr2d, int m, int n) {
	int neg = arr2d[0][0];
	int isnegative = 1;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (arr2d[i][j] > 0) {
				isnegative = 0;
			}
			else if (arr2d[i][j] > neg) {
				neg = arr2d[i][j];
			}
		}
	}

	// All negative
	if (isnegative == 1) {
		return neg;
	}

	// kadane algorithm
	else {
		int maxSum = 0;

		for (int left = 0; left < n; left++) {
			int* row_sum;

			// reset row_sum
			row_sum = (int*)malloc(sizeof(int) * m);
			for (int i = 0; i < m; i++) {
				row_sum[i] = 0;
			}

			// from left to right
			for (int right = left; right < n; right++) {
				// calculate the sum of row
				for (int i = 0; i < m; i++) {
					row_sum[i] += arr2d[i][right];
				}

				// calculate maxSum
				int sum = 0;
				for (int i = 0; i < m; i++) {
					sum += row_sum[i]; // sum each element of row_sum
					if (sum > maxSum) {
						maxSum = sum;
					}
					else if (sum < 0) {
						sum = 0;
					}
				}
			}
		}
		return maxSum;
	}

}
