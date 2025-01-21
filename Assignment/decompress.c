#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHAR_COUNT 256
#define MAX_CODE_LENGTH 256

// Node structure
typedef struct Node {
    char symbol;
    struct Node *left;
    struct Node *right;
} Node;

// Create a new node
Node* createNode() {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->symbol = 0;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Make Huffman tree
void makeHuffmanTree(Node *root, char symbol, const char *code) {
    if (strlen(code) == 0) {
        root->symbol = symbol;
        return;
    }
    if (code[0] == '0') {
        if (root->left == NULL) {
            root->left = createNode();
        }
        makeHuffmanTree(root->left, symbol, code + 1);
    } else {
        if (root->right == NULL) {
            root->right = createNode();
        }
        makeHuffmanTree(root->right, symbol, code + 1);
    }
}

// Traverse Huffman tree
void traverseHuffmanTree(Node *root, const char *code, char *decodedStr) {
    Node *current = root;
    while (*code != '\0') {
        if (*code == '0') {
            if (current->left == NULL) {
                strcat(decodedStr, "Invalid code!");
                return;
            }
            current = current->left;
        } else if (*code == '1') {
            if (current->right == NULL) {
                strcat(decodedStr, "Invalid code!");
                return;
            }
            current = current->right;
        } else {
            strcat(decodedStr, "Invalid direction in code!");
            return;
        }
        code++;
    }
    if (current->left == NULL && current->right == NULL) {
        if (current->symbol == ':') {
            strcat(decodedStr, " ");
        } else {
            size_t len = strlen(decodedStr);
            decodedStr[len] = current->symbol;
            decodedStr[len + 1] = '\0';
        }
    } else {
        strcat(decodedStr, "Invalid code!");
    }
}

int main() {
    FILE* fin = fopen("compressed.txt", "r");
    if (!fin) {
        printf("File not found\n");
        return 1;
    }

    int count;
    fscanf(fin, "%d\n", &count);

    char characters[count];
    char codes[count][MAX_CODE_LENGTH];

    for (int i = 0; i < count; i++) {
        fscanf(fin, "%c %s\n", &characters[i], codes[i]);
    }

    Node* root = createNode();
    for (int i = 0; i < count; i++) {
        makeHuffmanTree(root, characters[i], codes[i]);
    }

    char decString[MAX_CODE_LENGTH];
    fscanf(fin, "%s", decString);
    fclose(fin);

    char decodedStr[MAX_CODE_LENGTH * CHAR_COUNT] = {0};

    int startPos = 0;
    while (startPos < strlen(decString)) {
        for (int len = 1; len <= strlen(decString) - startPos; ++len) {
            char code[MAX_CODE_LENGTH];
            strncpy(code, decString + startPos, len);
            code[len] = '\0';
            int found = 0;
            for (int i = 0; i < count; i++) {
                if (strcmp(codes[i], code) == 0) {
                    traverseHuffmanTree(root, code, decodedStr);
                    startPos += len;
                    found = 1;
                    break;
                }
            }
            if (found)
                break;
        }
    }

    FILE* fout = fopen("decompressed.txt", "w");
    if (!fout) {
        printf("Error opening file\n");
        return 1;
    }
    fprintf(fout, "%s", decodedStr);
    fclose(fout);

    return 0;
}
