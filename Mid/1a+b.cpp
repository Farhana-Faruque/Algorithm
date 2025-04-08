#include <iostream>
#include <fstream>
#include <queue>
#include <unordered_map>
#include <string>
using namespace std;

struct Node {
    char ch;
    int freq;
    Node* left;
    Node* right;

    Node(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
};

struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};

void generateHuffmanCodes(Node* root, string code, unordered_map<char, string>& huffmanCodes) {
    if (!root) return;

    if (!root->left && !root->right) {
        huffmanCodes[root->ch] = code;
    }

    generateHuffmanCodes(root->left, code + "0", huffmanCodes);
    generateHuffmanCodes(root->right, code + "1", huffmanCodes);
}

string decodeHuffmanTree(Node* root, const string& bitstream) {
    string decodedString = "";
    Node* current = root;
    for (char bit : bitstream) {
        if (bit == '0') current = current->left;
        else current = current->right;

        if (!current->left && !current->right) {
            decodedString += current->ch;
            current = root;
        }
    }
    return decodedString;
}

int main() {
    vector<pair<char, int>> charFreq = {
        {'A', 5}, {'B', 9}, {'C', 12}, {'D', 13}, {'E', 16}, {'F', 45}
    };

    priority_queue<Node*, vector<Node*>, Compare> pq;
    for (auto& p : charFreq) {
        pq.push(new Node(p.first, p.second));
    }

    while (pq.size() > 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();

        Node* combined = new Node('\0', left->freq + right->freq);
        combined->left = left;
        combined->right = right;
        pq.push(combined);
    }

    Node* root = pq.top();

    unordered_map<char, string> huffmanCodes;
    generateHuffmanCodes(root, "", huffmanCodes);

    ofstream outFile("huffman_codes.txt");
    if (!outFile) {
        cerr << "Error: Could not open file for writing!" << endl;
        return 1;
    }

    cout << "Huffman Codes:\n";
    outFile << "Huffman Codes:\n";
    for (auto& p : huffmanCodes) {
        cout << p.first << " : " << p.second << endl;
        outFile << p.first << " : " << p.second << endl;
    }

    outFile.close();

    string bitstream = "111101101110101000111100"; // Example bitstream
    string decodedString = decodeHuffmanTree(root, bitstream);

    cout << "\nDecoded String: " << decodedString << endl;

    return 0;
}
