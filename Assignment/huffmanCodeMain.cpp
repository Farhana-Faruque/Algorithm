#include <iostream>
#include <fstream>
#include <queue>
#include <string>

const int CHAR_COUNT = 256;
using namespace std;

struct Node
{
    int freq;
    string symbol;
    Node *left;
    Node *right;
};

bool operator<(const Node &x, const Node &y)
{
    return x.freq > y.freq;
}

int count = 0;
Node createNode(string sym, int frequency, Node *left, Node *right)
{
    Node newNode;
    newNode.freq = frequency;
    newNode.symbol = sym;
    newNode.left = left;
    newNode.right = right;

    return newNode;
}

void printHuffmanCode(Node *root, string str, ofstream &outfile)
{
    if (root == nullptr)
        return;
    if (root->left == nullptr && root->right == nullptr)
    {
        outfile << root->symbol << ": " << str << endl;
        return;
    }
    printHuffmanCode(root->left, str + "0", outfile);
    printHuffmanCode(root->right, str + "1", outfile);
}

int main()
{
    int freqs[CHAR_COUNT] = {0};
    ifstream file("test.txt");
    if (!file.is_open())
    {
        cout << "Error opening file" << endl;
        return 1;
    }
    char ch;
    while (file.get(ch))
    {
        if (ch >= 0 && ch < CHAR_COUNT && ch != '\n' && ch != '\r' && ch != '\t')
            freqs[ch]++;
    }
    file.close();

    for (int i = 0; i < CHAR_COUNT; ++i)
    {
        if (freqs[i] > 0)
        {
            count++;
            // cout << "'" << static_cast<char>(i) << "' : " << freqs[i] << '\n';
        }
    }

    priority_queue<Node> pq;
    for (int i = 0; i < CHAR_COUNT; i++)
    {
        if (freqs[i] > 0)
        {
            Node newNode = createNode(string(1, static_cast<char>(i)), freqs[i], nullptr, nullptr);
            pq.push(newNode);
        }
    }

    while (pq.size() > 1)
    {
        // cout << "------------------" << endl;
        Node tmp1 = pq.top();
        pq.pop();
        Node tmp2 = pq.top();
        pq.pop();

        Node newNode = createNode(
            tmp1.symbol + tmp2.symbol,
            tmp1.freq + tmp2.freq,
            new Node(tmp1),
            new Node(tmp2));

        pq.push(newNode);

        // print_queue(pq);
    }

    ofstream file1("compressed.txt");
    if (!file1.is_open())
    {
        cout << "Error opening file" << endl;
        return 1;
    }
    file1 << count << endl;
    Node root = pq.top();
    printHuffmanCode(&root, "", file1);
    file1.close();

    return 0;
}
