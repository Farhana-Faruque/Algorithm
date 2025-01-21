#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Node
{
    char symbol;
    Node *left;
    Node *right;

    Node() : symbol(0), left(nullptr), right(nullptr) {}
};

void makeHuffmanTree(Node *root, char symbol, string code)
{
    if (code.length() == 0)
    {
        root->symbol = symbol;
        return;
    }
    if (code[0] == '0')
    {
        if (root->left == nullptr)
        {
            root->left = new Node();
        }
        makeHuffmanTree(root->left, symbol, code.substr(1));
    }
    else
    {
        if (root->right == nullptr)
        {
            root->right = new Node();
        }
        makeHuffmanTree(root->right, symbol, code.substr(1));
    }
}

void traverseHuffmanTree(Node *root, string code, string &decodedStr)
{
    Node *current = root;
    for (char direction : code)
    {
        if (direction == '0')
        {
            if (current->left == nullptr)
            {
                decodedStr += "Invalid code!";
                return;
            }
            current = current->left;
        }
        else if (direction == '1')
        {
            if (current->right == nullptr)
            {
                decodedStr += "Invalid code!";
                return;
            }
            current = current->right;
        }
        else
        {
            decodedStr += "Invalid direction in code!";
            return;
        }
    }

    if (current->left == nullptr && current->right == nullptr)
    {
        if (current->symbol == ':')
        {
            decodedStr += " ";
        }
        else
        {
            decodedStr += current->symbol;
        }
    }
    else
    {
        decodedStr += "Invalid code!";
    }
}

int main()
{
    ifstream fin("compressed.txt");
    if (!fin)
    {
        cout << "File not found" << endl;
        return 1;
    }

    int count;
    fin >> count;
    fin.ignore();

    char characters[count];
    string codes[count];

    for (int i = 0; i < count; i++)
    {
        char symbol;
        string code;

        fin >> symbol;
        fin.ignore(1);
        fin >> code;

        characters[i] = symbol;
        codes[i] = code;
    }

    Node *root = new Node();
    for (int i = 0; i < count; i++)
    {
        makeHuffmanTree(root, characters[i], codes[i]);
    }

    string decString;
    fin >> decString;
    fin.close();

    string decodedStr;

    int startPos = 0;
    while (startPos < decString.length())
    {
        for (int len = 1; len <= decString.length() - startPos; ++len)
        {
            string code = decString.substr(startPos, len);
            bool found = false;
            for (int i = 0; i < count; i++)
            {
                if (codes[i] == code)
                {
                    traverseHuffmanTree(root, code, decodedStr);
                    startPos += len;
                    found = true;
                    break;
                }
            }
            if (found)
                break;
        }
    }

    ofstream fout("decompressed.txt");
    if (!fout)
    {
        cout << "Error opening file" << endl;
        return 1;
    }
    fout << decodedStr;
    fout.close();

    return 0;
}
