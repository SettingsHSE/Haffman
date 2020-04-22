#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Huffman
{
public:
    void build()
    {
        while(nodes.size() != 1)
        {
            Node* left = nodes.back();
            nodes.pop_back();

            Node* right = nodes.back();
            nodes.pop_back();

            Node* node = new Node(left, right);
            nodes.push_back(node);

            for (int i = nodes.size() - 1; i > 0; i--)
            {
                if(nodes[i - 1]->key >= nodes[i]->key)
                    break;
                swap(nodes[i - 1], nodes[i]);
            }
        }

        makeCode(nodes.back());
    }

    void addChance (int chance)
    {
        nodes.push_back(new Node(nodes.size(), chance));
        result.push_back("");
    }

    string get (int i)
    {
        return result[i];
    }

private:
    struct Node
    {
        int index, key;
        Node* left;
        Node* right;

        Node(int i, int k)
        {
            index = i;
            key = k;
            left = nullptr;
            right = nullptr;
        }

        Node(Node* l, Node* r)
        {
            left = l;
            right = r;
            key = left->key + right->key;
        }

        ~Node()
        {
            delete left;
            delete right;
        }
    };

    vector<Node*> nodes;
    vector<string> result;
    string currentCode;


    void makeCode(Node* node)
    {
        Node* left = node->left;
        Node* right = node->right;

        if(right != nullptr)
        {
            if(right->key >= left->key)
                currentCode += "1";
            else
                currentCode += "0";

            makeCode(right);
        }

        if(left != nullptr)
        {
            if(left->key > right->key)
                currentCode += "1";
            else
                currentCode += "0";

            makeCode(left);
        }

        if(left == nullptr && right == nullptr)
        {
            result[node->index] = currentCode;
        }


        if (!currentCode.empty())
            currentCode.pop_back();
    }
};

int main() {

    int n;
    Huffman * huff = new Huffman();
    fstream fin;
    fin.open("input.txt",ios::in);
    if(fin.is_open()) {
        fin >> n;
        for (int i = 0; i < n; i++) {
            int x;
            fin >> x;
            huff->addChance (x);
        }

        fin.close();

        huff->build();
        fstream fout;
        fout.open("output.txt",ios::out);
        for (int i = 0; i < n; i++){
            fout << huff->get(i) << (i==n-1?"":" ");
        }
        fout.close();
        delete huff;

    }

    return 0;

}

