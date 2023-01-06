#define MAX_SIZE 50000001
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define HEAP_FULL(n) (n == MAX_SIZE -1)
#define HEAP_EMPTY(n) (!n)

typedef struct {
	int sp;
	int ep;
	int key;
} element;
element heap[MAX_SIZE];
element T[MAX_SIZE];

int n = 0;
int parent[MAX_SIZE];
void insert_min_heap(element item, int* n);
element delete_min_heap(int* n);

int simpleFind(int i) { // O(logn)
	for (; parent[i] >= 0; i = parent[i])
		;
	//printf("SimpleFind 내부 %d\n", i);
	return i;
}

void simpleUnion(int i, int j) { // O(1)
	parent[i] = j;
}

void insert_min_heap(element item, int* n) { // O(loge)
	int i;
	if (HEAP_FULL(*n)) {
		fprintf(stderr, "The heap is full.\n");
		exit(1);
	}
	i = ++(*n);
	while ((i != 1) && (item.key < heap[i / 2].key)) {
		heap[i] = heap[i / 2];
		i /= 2;
	}
	heap[i] = item;
}

element delete_min_heap(int* n) { // log(n)
	int parent, child;
	element item, temp;
	if (HEAP_EMPTY(*n)) {
		fprintf(stderr, "The heap is empty");
		exit(1);
	}

	item = heap[1];
	temp = heap[(*n)--];
	parent = 1;
	child = 2;

	while (child <= *n) {
		if ((child < *n) && (heap[child].key > heap[child + 1].key)) child++;
		if (temp.key <= heap[child].key) break;
		heap[parent] = heap[child];
		parent = child;
		child *= 2;
	}
	heap[parent] = temp;
	return item;
}


void main(int argc, char** argv) {

	double start, end;
	start = (double)clock() / CLOCKS_PER_SEC;

	if (argc == 2) {
		FILE* inputFILE;
		inputFILE = fopen(argv[1], "r");

		if (inputFILE == NULL) {
			printf("The input file does not exist");
		}
		else {
			//minimum spanning tree
			int edge, vertex = 0;
			int result = 0;
			result = fscanf(inputFILE, "%d", &vertex);
			result = fscanf(inputFILE, "%d", &edge);

			int sp = 0;
			int ep = 0;
			int weight = 0;

			for (int i = 0; i < vertex; i++) {
				parent[i] = -1;
			}

			element item;
			result = fscanf(inputFILE, "%d %d %d", &sp, &ep, &weight);
			for (int i = 0; i < edge; i++) { // O(eloge)
				//printf("%d %d %d\n", sp, ep, weight);
				item.sp = sp;
				item.key = weight;
				item.ep = ep;
				insert_min_heap(item, &n);
				result = fscanf(inputFILE, "%d %d %d", &sp, &ep, &weight);
			}

			int weights = 0;
			int line = 0;
			while (line < vertex - 1 && n != 0) { // nlog(n)
				item = delete_min_heap(&n);

				if (simpleFind(item.sp) != simpleFind(item.ep)) {
					if (simpleFind(item.sp) == item.sp) simpleUnion(item.sp, item.ep); // sp가 부모 없을때
					else if (simpleFind(item.ep) == item.ep) simpleUnion(item.ep, item.sp); // ep가 부모 없을때
					else {
						int root = 0;
						root = simpleFind(item.sp);
						simpleUnion(root, item.ep); //둘다 부모있을때
					}
					T[line] = item;
					line++;
					weights += item.key;
				}
				else;

				if (n == 0) break;
			}

			FILE* fp;
			fp = fopen("fp1_result.txt", "w");
			if (fp != NULL) {
				for (int i = 0; i < line; i++) {
					fprintf(fp, "%d %d %d\n", T[i].sp, T[i].ep, T[i].key);
				}
				fprintf(fp, "%d\n", weights);
				if (line < vertex - 1) {
					fprintf(fp, "DISCONNECTED");
				}
				else {
					fprintf(fp, "CONNECTED");
				}
			
			}
			fclose(fp);
			fclose(inputFILE);
			end = (((double)clock()) / CLOCKS_PER_SEC);
			printf("output written to fp1_result.txt");
			printf("\nrunning time: %lf seconds", (end - start));
		}
	}

	else {
		printf("usage ./fp1 input_filename");
	}



}
