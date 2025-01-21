#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHAR_COUNT 256

// Node structure
typedef struct Node {
    int freq;
    char symbol[2];
    struct Node *left;
    struct Node *right;
} Node;

// Create a new node
Node* createNode(const char* sym, int frequency, Node* left, Node* right) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->freq = frequency;
    strcpy(newNode->symbol, sym);
    newNode->left = left;
    newNode->right = right;
    return newNode;
}

// Swap two nodes in the priority queue
void swap(Node** a, Node** b) {
    Node* temp = *a;
    *a = *b;
    *b = temp;
}

// Min-Heap structure
typedef struct {
    Node** array;
    int size;
    int capacity;
} MinHeap;

// Create a Min-Heap
MinHeap* createMinHeap(int capacity) {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    minHeap->array = (Node**)malloc(capacity * sizeof(Node*));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    return minHeap;
}

// Min-Heapify the heap
void minHeapify(MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq)
        smallest = right;

    if (smallest != idx) {
        swap(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

// Extract the minimum node from the heap
Node* extractMin(MinHeap* minHeap) {
    Node* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    minHeap->size--;
    minHeapify(minHeap, 0);
    return temp;
}

// Insert a node into the heap
void insertMinHeap(MinHeap* minHeap, Node* node) {
    minHeap->size++;
    int i = minHeap->size - 1;
    while (i && node->freq < minHeap->array[(i - 1) / 2]->freq) {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    minHeap->array[i] = node;
}

// Build the Min-Heap
void buildMinHeap(MinHeap* minHeap) {
    int n = minHeap->size - 1;
    int i;
    for (i = (n - 1) / 2; i >= 0; --i)
        minHeapify(minHeap, i);
}

// Print Huffman codes
void printHuffmanCode(Node* root, char* str, int top, FILE* outfile) {
    if (root->left) {
        str[top] = '0';
        printHuffmanCode(root->left, str, top + 1, outfile);
    }
    if (root->right) {
        str[top] = '1';
        printHuffmanCode(root->right, str, top + 1, outfile);
    }
    if (!root->left && !root->right) {
        str[top] = '\0';
        fprintf(outfile, "%s: %s\n", root->symbol, str);
    }
}

// Main function
int main() {
    int freqs[CHAR_COUNT] = {0};
    FILE* file = fopen("test.txt", "r");
    if (!file) {
        printf("Error opening file\n");
        return 1;
    }
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        if (ch >= 0 && ch < CHAR_COUNT && ch != '\n' && ch != '\r' && ch != '\t')
            freqs[(unsigned char)ch]++;
    }
    fclose(file);

    int count = 0;
    MinHeap* minHeap = createMinHeap(CHAR_COUNT);

    for (int i = 0; i < CHAR_COUNT; i++) {
        if (freqs[i] > 0) {
            count++;
            char sym[2] = { (char)i, '\0' };
            Node* newNode = createNode(sym, freqs[i], NULL, NULL);
            insertMinHeap(minHeap, newNode);
        }
    }

    buildMinHeap(minHeap);

    while (minHeap->size > 1) {
        Node* left = extractMin(minHeap);
        Node* right = extractMin(minHeap);
        Node* newNode = createNode("", left->freq + right->freq, left, right);
        insertMinHeap(minHeap, newNode);
    }

    FILE* file1 = fopen("compressed.txt", "w");
    if (!file1) {
        printf("Error opening file\n");
        return 1;
    }
    fprintf(file1, "%d\n", count);

    char str[100];
    Node* root = extractMin(minHeap);
    printHuffmanCode(root, str, 0, file1);
    fclose(file1);

    free(minHeap->array);
    free(minHeap);

    return 0;
}
