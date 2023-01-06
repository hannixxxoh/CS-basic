#define SWAP(a, b) {int temp; temp = a; a = b; b = temp;}
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void insertion_sort(int*, int, int);
void quick_sort(int*, int, int);
int partition(int*, int, int);
void merge_sort(int*, int, int);
void merge(int*, int, int, int);
void threesort(int*, int, int, int);
void bet_quick_sort(int*, int, int);

int main(int argc, const char* argv[]) {
    double start, end;
    start = (double)clock() / CLOCKS_PER_SEC;
   
    char filename[100];
    strcpy(filename, argv[1]);
    FILE* fp;
    fp = fopen(filename, "r");

    // copy the list
    int n, i, result = 0;
    result = fscanf(fp, "%d", &n);
    int* list;
    list = malloc(sizeof(int) * n);
    for (i = 0; i < n; i++) {
        result = fscanf(fp, "%d", &list[i]);
    }

    int user = atoi(argv[2]);


    if (user == 1) {
        insertion_sort(list, 0, n);
    }
    else if (user == 2) {
        quick_sort(list, 0, n-1);
    }
    else if (user == 3) {
        merge_sort(list, 0, n-1);
    }
    else if (user == 4) {
        bet_quick_sort(list, 0, n-1);
    }

    end = (((double)clock()) / CLOCKS_PER_SEC);

    // save the file
    char output[100];
    sprintf(output, "result_%d_%s", user, filename);
    FILE* outputFILE;
    outputFILE = fopen(output, "w");

    fprintf(outputFILE, "%s\n", filename);
    fprintf(outputFILE, "%d\n", user);
    fprintf(outputFILE, "%d\n", n);
    fprintf(outputFILE, "%lf\n", end - start);
    for (i = 0; i < n; i++) {
        fprintf(outputFILE, "%d ", list[i]);
    }
    fclose(outputFILE);
    return 0;
}


void insertion_sort(int* list, int left, int right) {
    int i, j, key = 0;

    for (i = left + 1; i < right; i++) {
        key = list[i];

        for (j = i - 1; list[j] > key && j >= 0; j--) {
            list[j + 1] = list[j];
        }

        list[j + 1] = key;
    }
}

void quick_sort(int* list, int left, int right) {
    int pivot = 0;

    if (left < right) {
        pivot = partition(list, left, right);
        
        quick_sort(list, left, pivot - 1);
        quick_sort(list, pivot + 1, right);
    }
}

int partition(int* list, int left, int right) {
    int pivot = 0; 
    int i = 0;

    pivot = left;
    for (i = left; i < right; i++) {
        if (list[i] < list[right]) {
            SWAP(list[i], list[pivot]);
            pivot++;
        }
    }

    SWAP(list[right], list[pivot]);
    return pivot;
}

void merge_sort(int* list, int start, int end) {
    if (start >= end) return;

    int mid = (start + end) / 2;

    merge_sort(list, start, mid);
    merge_sort(list, mid + 1, end);
    merge(list, start, mid, end);
}

void merge(int* list, int start, int mid, int end) {
    int lengl = mid - start + 1;
    int lengr = end - mid;
    int* left = malloc(sizeof(int) * lengl);
    int* right = malloc(sizeof(int) * lengr);

    // copy the list
    for (int i = 0; i < lengl; i++) {
        left[i] = list[start + i];
    }
    for (int j = 0; j < lengr; j++) {
        right[j] = list[mid + j + 1];
    }

    int i = 0;
    int j = 0;
    int k = start;

    while (i < lengl && j < lengr) {
        if (left[i] <= right[j]) {
            list[k] = left[i];
            i = i + 1;
        }
        else {
            list[k] = right[j];
            j = j + 1;
        }
        k = k + 1;
    }

    while (i < lengl) {
        list[k] = left[i];
        i = i + 1;
        k = k + 1;
    }
    while (j < lengr) {
        list[k] = right[j];
        j = j + 1;
        k = k + 1;
    }
}

void threesort(int* list, int left, int mid, int right) {
    if (list[left] > list[mid]) SWAP(list[left], list[mid]);
    if (list[mid] > list[right]) SWAP(list[mid], list[right]);
    if (list[left] > list[mid]) SWAP(list[left], list[mid]);
}

void bet_quick_sort(int* list, int left, int right) {
    int i, j, pivot = 0;
    int mid = left + (right - left) / 2;
    threesort(list, left, mid, right);

    int check = right - left + 1;
    if(check > 3) {
        pivot = list[mid];
        SWAP(list[mid], list[right - 1]);
        i = left;
        j = right - 1;

        while (1) {
            while (list[++i] < pivot && i < right);
            while (list[--j] > pivot && left < j);
            if (i >= j) break;
            SWAP(list[i], list[j]);
        }
        SWAP(list[i], list[right - 1]);

        bet_quick_sort(list, left, i - 1);
        bet_quick_sort(list, i + 1, right);
    }
}