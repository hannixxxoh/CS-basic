#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



#define MAX_SIZE 9999999
#define ascii_num 128

typedef struct node
{
    char ascii;
    int freq;
    struct node* left;
    struct node* right;
} node;

node* Huffman_tree(char arr[], int n);
node* make_node(char ascii, int freq, struct node* left, struct node* right);
void encode(node* node, char str[], int len, char* table[]);
void decode(char* str, node* root);
node node_arr[ascii_num] = { 0 };
unsigned char bitCal(char* str);
//int argc, const char* argv[]
int ind = 0;
int main(int argc, const char* argv[])
{
    //char* argv[3];
    //argv[1] = "-d";
    char option[3];
    strcpy(option, argv[1]);
    char c[3] = "-c";
    char d[3] = "-d";
    int resultc = strcmp(option, c);
    int resultd = strcmp(option, d);

    if (resultc != 0 && resultd != 0) printf("option error\n");
    else {
        int n = 0;
        node* root;
        if (resultc == 0) {

            //파일 입출력
            FILE* fp;
            char filename[200];
            //argv[2] = "input.txt";
            strcpy(filename, argv[2]);
            fp = fopen(filename, "r");
            char* arr;
            arr = (char*)malloc(sizeof(char) * MAX_SIZE);
            if (fp != NULL) {
                fgets(arr, MAX_SIZE, fp);

                // 허프만 트리 생성
                n = (int)strlen(arr);
                root = Huffman_tree(arr, n);

                // 아스키 코드별 인코딩 코드
                char* code[ascii_num] = { 0 };
                char* str;
                str = (char*)malloc(MAX_SIZE);
                encode(root, str, 0, code);
                //free(str);

                //출력값 확인
                //for (int i = 0; i < ind; i++)
                    //printf("%c : %d : %s\n", node_arr[i].ascii, node_arr[i].freq, code[node_arr[i].ascii]);


                // 인코딩 파일
                char* zz = (char*)".zz";
                char enfile[100] = { 0 };
                strcpy(enfile, filename);
                strcat(enfile, zz);
                FILE* encoded = fopen(enfile, "wb");

                // 파일 정보
                fwrite(&ind, sizeof(int), 1, encoded); // 문자 개수
                char writeBuf[100] = { 0 };
                for (int i = 0; i < ascii_num; i++) {
                    if (code[i] != NULL) {
                        writeBuf[0] = (char)i; // 아스키 문자
                        writeBuf[1] = (char)strlen(code[i]); // 코드 길이
                        strcpy(&writeBuf[2], code[i]); // 코드
                        fwrite(writeBuf, sizeof(char), 2 + strlen(code[i]), encoded);
                    }

                }


                // 비트 개수 위치 저장
                int locationtotalbit;
                locationtotalbit = ftell(encoded);

                if (fseek(encoded, 4, SEEK_CUR) != 0)
                {
                    printf("failed to write total bit location\n");
                }

                char buf[4];
                char bitbuf[4];
                int idx = 0;
                int bitshift = 7;
                int totalbitnum = 0;
                char flag = 0; // 0: 기록x 1: 기록o

                memset(buf, 0, 4);
                memset(bitbuf, 0, 4);

                fp = fopen(filename, "r");

                while (fgets(buf, 4, fp) != 0)
                {
                    //printf("%s", buf);
                    int len = strlen(buf);
                    for (int i = 0; i < len; i++) {
                        char* huffman = code[buf[i]];
                        //printf("%s", code[buf[i]]);
                        for (int j = 0; j < strlen(huffman); j++) {
                            char val = 0;
                            if (huffman[j] == '0') {
                                val = 0;
                            }
                            else if (huffman[j] == '1') {
                                val = 1;
                            }
                            else {
                                printf("huffman code errer\n");
                            }
                            val = val << bitshift;
                            bitshift--;

                            bitbuf[idx] |= val;
                            flag = 1;

                            totalbitnum++;
                            if (bitshift < 0) {
                                bitshift = 7;
                                idx++;
                                if (idx >= 4) {
                                    fwrite(bitbuf, 1, 4, encoded);
                                    flag = 0;
                                    idx = 0;
                                    memset(bitbuf, 0, 4);
                                }
                            }
                        }
                    }
                }

                if (flag == 1) {
                    fwrite(bitbuf, 1, idx + 1, encoded);
                }
                if (fseek(encoded, locationtotalbit, SEEK_SET) == 0) {
                    fwrite(&totalbitnum, 1, sizeof(totalbitnum), encoded);
                }
                else {
                    printf("failed to write totalbit\n");
                }
                fclose(fp);
                fclose(encoded);
            }
            else printf("input file errer\n");
        }
        else if (resultd == 0) {

            char filename[200];
            //argv[2] = "input.txt.zz";
            strcpy(filename, argv[2]);
            FILE* encoded = fopen(filename, "rb");

            if (encoded != NULL) {
                ind = 0;
                fread(&ind, sizeof(int), 1, encoded);
                //printf("ind is %d\n", ind);


                // 허프만 트리 복구
                node* root;
                root = (struct node*)malloc(sizeof(struct node));
                root->left = 0;
                root->right = 0;
                node* cur = root;

                //char* code[ascii_num] = { 0 };

                // 문자와 코드 복구
                for (int i = 0; i < ind; i++) {
                    //printf("%d:", i);
                    char asciileng[2];
                    fread(asciileng, 2, 1, encoded); // 문자와 코드길이
                    char buf[100] = { 0 };
                    fread(buf, 1, (int)asciileng[1], encoded); // 코드
                    buf[(int)asciileng[1]] = 0;
                    //code[(int)asciileng[0]] = (char*)malloc(sizeof(char));
                    //strcpy(code[(int)asciileng[0]], buf);
                    //허프만트리 복구
                    cur = root;
                    for (int i = 0; i < (int)asciileng[1]; i++) {
                        //printf("%d", i);
                        if (buf[i] == '0') {
                            if (cur->left == 0) {
                                cur->left = (node*)malloc(sizeof(node*));
                                cur->left->left = 0;
                                cur->left->right = 0;
                            }
                            cur = cur->left;
                        }
                        else if (buf[i] == '1') {
                            if (cur->right == 0) {
                                cur->right = (node*)malloc(sizeof(node*));
                                cur->right->left = 0;
                                cur->right->right = 0;
                            }
                            cur = cur->right;
                        }
                        else {
                            printf("Error!!\n");
                            exit(0);
                        }
                    }
                    cur->ascii = asciileng[0];
                    //printf("%c/%s ", asciileng[0], code[(int)asciileng[0]]);
                    //printf("%c (%d) -> %s\n", asciileng[0], asciileng[1], buf); 
                }

                int totalbits = 0;
                fread(&totalbits, sizeof(int), 1, encoded);


                cur = root;
                char buff[8] = { 0 };

                char* yy = (char*)".yy";
                char defile[200] = { 0 };
                strcpy(defile, filename);
                strcat(defile, yy);
                FILE* decoded = fopen(defile, "w");
                while (1) {
                    int size = 0;
                    size = fread(buff, 1, 8, encoded);
                    if (size == 0) break;
                    else {
                        for (int i = 0; i < size; i++) {
                            for (int j = 0; j < 8; j++) {
                                if ((char)(buff[i] & 0x80) == 0) cur = cur->left;
                                else cur = cur->right;

                                buff[i] = buff[i] << 1;
                                totalbits--;

                                if (cur->left == 0 && cur->right == 0) {
                                    //printf("%c", cur->ascii);
                                    //printf("%d ", totalbits);
                                    fputc(cur->ascii, decoded);
                                    cur = root;
                                }
                                if (totalbits == 0) {
                                    break;
                                    fclose(encoded);
                                }
                            }
                        }
                    }
                }

            }
            else printf("input file error\n");

        }
    }
    return 0;
}

node* make_node(char ascii, int freq, struct node* left, struct node* right) {

    node* new_node = (node*)malloc(sizeof(node));
    new_node->ascii = ascii;
    new_node->freq = freq;
    new_node->left = left;
    new_node->right = right;

    return new_node;
}

node* Huffman_tree(char arr[], int n) {

    int i = 0;
    int j = 0;

    int ascii_freq[ascii_num] = { 0 };
    int see[ascii_num] = { 0 };
    node* tree[ascii_num] = { NULL };

    for (i = 0; i < n; i++) {
        ascii_freq[arr[i]]++;
    }

    for (i = 0; i < ascii_num; i++) {
        if (ascii_freq[i] != 0) {
            node_arr[ind] = *make_node(i, ascii_freq[i], NULL, NULL);
            tree[ind] = make_node(i, ascii_freq[i], NULL, NULL);
            //printf("%c: %d\n", tree[ind]->ascii, tree[ind]->freq);
            ind++;
        }
    }

    int min = 0;
    int min2 = 0;

    for (i = 0; i < ind - 1; i++) {
        // min 찾기
        j = 0;
        while (see[j] == -1) j++;
        min = j;

        for (j = min; j < ind - 1; j++)
            if (see[j] != -1)
                if (tree[min]->freq > tree[j]->freq)
                    min = j;

        // min2 찾기
        j = 0;
        while (see[j] == -1 || j == min) j++;
        min2 = j;

        for (j = min2; j < ind; j++)
            if (see[j] != -1)
                if (tree[min2]->freq > tree[j]->freq)
                    if (j != min)
                        min2 = j;

        tree[min] = make_node(0, tree[min]->freq + tree[min2]->freq, tree[min], tree[min2]);
        see[min2] = -1;
    }
    return tree[min];
}

void encode(node* node, char str[], int len, char* table[]) {
    if (node->left == 0 && node->right == 0) {
        str[len] = '\0';
        table[node->ascii] = (char*)malloc(sizeof(char));
        strcpy(table[node->ascii], str);
        //printf("%s ", table[node->ascii]);
    }
    else {
        if (node->left != 0) {
            str[len] = '0';
            encode(node->left, str, len + 1, table);
        }
        if (node->right != 0) {
            str[len] = '1';
            encode(node->right, str, len + 1, table);
        }
    }

}

void decode(char* str, node* root) {
    int i = 0;
    node* j = root;
    while (str[i] != '\0') {
        if (str[i] == '0')
            j = j->left;
        else if (str[i] == '1')
            j = j->right;
        if (j->left == NULL && j->right == NULL) {
            printf("%c", j->ascii);
            j = root;
        }
        i++;
    }
    printf("\n");
}