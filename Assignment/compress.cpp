#include <iostream>
#include <string>
#include <queue>
#include <memory>
#include <fstream>

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

void print_queue(priority_queue<Node> pq)
{
    while (!pq.empty())
    {
        Node tmp1 = pq.top();
        pq.pop();

        cout << tmp1.symbol << ": " << tmp1.freq << endl;
    }
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
void find_and_traverse(Node *root, string str, char ch, ofstream &outfile)
{
    if (root == nullptr)
        return;

    if (root->left == nullptr && root->right == nullptr)
    {
        if (root->symbol[0] == ch)
        {
            outfile << str;
        }
        return;
    }

    find_and_traverse(root->left, str + "0", ch, outfile);
    find_and_traverse(root->right, str + "1", ch, outfile);
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

    ifstream file2("test.txt");
    if (!file2.is_open())
    {
        cout << "Error opening file" << endl;
        return 1;
    }
    ofstream outfile("compressed.txt", ios::app);
    if (!outfile.is_open())
    {
        cout << "Error opening file" << endl;
        return 1;
    }

    while (file2.get(ch))
    {
        find_and_traverse(&root,"", ch, outfile);
    }
    outfile.close();

    return 0;
}
