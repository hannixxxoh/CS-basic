#define MAX_SIZE 100
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

struct node {
	struct node* prev;
	int data;
	struct node* next;
};
typedef struct node* listPointer;

listPointer head;
listPointer curr;

void dinsert(int);
void ddelete(int);
void print_forward(listPointer list);
void print_reverse(listPointer list);

int main(int argc, char** argv)
{
	char sen[100];
	char* order;
	int num;

	if (argc == 2) {
		FILE* inputFILE;
		inputFILE = fopen(argv[1], "r");

		if (inputFILE == NULL)
		{
			printf("The input file does not exist");
		}
		else {
			while (fgets(sen, MAX_SIZE, inputFILE) != NULL) {
				order = strtok(sen, " \n");

				if (!strcmp(order, "INSERT")) {
					num = atoi(strtok(NULL, " "));
					dinsert(num);
				}
				else if (!strcmp(order, "DELETE")) {
					num = atoi(strtok(NULL, " "));
					ddelete(num);
				}
				else if (!(strcmp(order, "ASCEND"))) {
					print_forward(head);
				}
				else {
					print_reverse(head);
				}
			}
		}
	}

	else {
		printf("usage: ./hw2 input_filename");
	}

	return 0;
	
}



void dinsert(int input) {
	listPointer newnode;

	newnode = (listPointer)malloc(sizeof(struct node));
	newnode->prev = NULL;
	newnode->next = NULL;
	newnode->data = input;

	if (head == NULL) {
		head = newnode;
		head->next = head;
		head->prev = head;
	}

	else {
		curr = head;
		while (1) {
			if (head->data > newnode->data) { // head 앞에 삽입
				head->prev->next = newnode;
				newnode->prev = head->prev;
				newnode->next = head;
				head->prev = newnode;
				head = newnode;
				break;
			}
			else if (curr->data == newnode->data) { // 중복 데이터
				break;
			}
			else {
				if (curr->next == head || curr->next->data > newnode->data) { // node 우측에 삽입

					newnode->prev = curr;
					newnode->next = curr->next;
					curr->next->prev = newnode;
					curr->next = newnode;
					
					break;
				}
			}
			curr = curr->next; // 노드를 하나씩 돌면서 확인
		}

	}
}

void ddelete(int input) {
	listPointer delnode;

	delnode = (listPointer)malloc(sizeof(struct node));
	delnode->prev = NULL;
	delnode->next = NULL;
	delnode->data = input;


	if (head->data == delnode->data) {
		delnode = head;
		head = head->next;
		head->prev = head->prev->prev;
		head->prev->next = head;
		free(delnode);
	}
	else {
		curr = head->next;
		while (curr != head) {
			if (curr->data == delnode->data) {
				delnode = curr;
				curr = curr->next;
				curr->prev = curr->prev->prev;
				curr->prev->next = curr;
				free(delnode);
				break;
			}
			curr = curr->next;
		}
	}
}

void print_forward(listPointer list) {
	listPointer curr;
	FILE* outfile;

	outfile = fopen("hw2_result.txt", "a");
	if (list) {
		curr = list;
		while (1) {
			fprintf(outfile, "%d ", curr->data);
			printf("%d ", curr->data);
			curr = curr->next;
			if (curr == list) break;
		}
	}
	fprintf(outfile, "\n");
	printf("\n");
	fclose(outfile);
}

void print_reverse(listPointer list) {
	listPointer curr;
	FILE* outfile;

	outfile = fopen("hw2_result.txt", "a");
	if (list) {
		curr = list->prev;

		while (curr != list) {
			fprintf(outfile, "%d ", curr->data);
			printf("%d ", curr->data);
			curr = curr->prev;
		}
		fprintf(outfile, "%d ", curr->data);
		printf("%d ", curr->data);
	}
	fprintf(outfile, "\n");
	printf("\n");
	fclose(outfile);

}