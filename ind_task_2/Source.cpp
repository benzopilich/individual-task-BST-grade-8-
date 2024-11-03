#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

ofstream out("out.txt");

class Node
{
public:
    int val;
    Node* left;
    Node* right;
    int leftch;
    int rightch;
    Node(int val1)
    {
        val = val1;
        left = 0;
        right = 0;
        leftch = 0;
        rightch = 0;
    }
    ~Node() {};
};

class BST
{
private:
    Node* root = nullptr;

    Node* AddNode(Node* node, int v)
    {
        if (node == nullptr) {
            node = new Node(v);
        }
        if (v > node->val) {
            node->right = AddNode(node->right, v);
        }
        else if (v < node->val) {
            node->left = AddNode(node->left, v);
        }
        return node;
    }

    Node* Search_otec(Node* root, int v) {
        Node* tmp = root;
        Node* tmp1 = nullptr;
        while (tmp != nullptr && tmp->val != v) {
            tmp1 = tmp;
            if (v > tmp->val) {
                tmp = tmp->right;
            }
            else {
                tmp = tmp->left;
            }
        }
        return tmp1;
    }

    void Remove(Node*& root, Node*& toPop) {
        Node* tmp = toPop;
        if (tmp == nullptr) return;
        Node* tmp1 = Search_otec(root, toPop->val);

        if (tmp->left == nullptr && tmp->right == nullptr) {
            if (tmp1 == nullptr) {
                root = nullptr;
            }
            else if (tmp1->left == tmp) {
                tmp1->left = nullptr;
            }
            else {
                tmp1->right = nullptr;
            }
            delete tmp;
        }
        else if (tmp->left == nullptr) {
            if (tmp1 == nullptr) {
                root = tmp->right;
            }
            else if (tmp1->left == tmp) {
                tmp1->left = tmp->right;
            }
            else {
                tmp1->right = tmp->right;
            }
            delete tmp;
        }
        else if (tmp->right == nullptr) {
            if (tmp1 == nullptr) {
                root = tmp->left;
            }
            else if (tmp1->left == tmp) {
                tmp1->left = tmp->left;
            }
            else {
                tmp1->right = tmp->left;
            }
            delete tmp;
        }
        else {
            Node* min = tmp->right;
            Node* minParent = tmp;
            while (min->left != nullptr) {
                minParent = min;
                min = min->left;
            }
            tmp->val = min->val;
            if (minParent->left == min) {
                minParent->left = min->right;
            }
            else {
                minParent->right = min->right;
            }
            delete min;
        }
    }

    void Remove(Node*& root, Node*& toPop, Node*& toPop_otec) {
        Node* tmp = toPop;
        if (tmp == nullptr) return;
        Node* tmp1 = toPop_otec;

        if (tmp->left == nullptr && tmp->right == nullptr) {
            if (tmp1 == nullptr) {
                root = nullptr;
            }
            else if (tmp1->left == tmp) {
                tmp1->left = nullptr;
            }
            else {
                tmp1->right = nullptr;
            }
            delete tmp;
        }
        else if (tmp->left == nullptr) {
            if (tmp1 == nullptr) {
                root = tmp->right;
            }
            else if (tmp1->left == tmp) {
                tmp1->left = tmp->right;
            }
            else {
                tmp1->right = tmp->right;
            }
            delete tmp;
        }
        else if (tmp->right == nullptr) {
            if (tmp1 == nullptr) {
                root = tmp->left;
            }
            else if (tmp1->left == tmp) {
                tmp1->left = tmp->left;
            }
            else {
                tmp1->right = tmp->left;
            }
            delete tmp;
        }
        else {
            Node* min = tmp->right;
            Node* minParent = tmp;
            while (min->left != nullptr) {
                minParent = min;
                min = min->left;
            }
            tmp->val = min->val;
            if (minParent->left == min) {
                minParent->left = min->right;
            }
            else {
                minParent->right = min->right;
            }
            delete min;
        }
    }

    void printBST(Node* node) {
        if (node == nullptr)return;
        out << node->val << endl;
        if (node->left != nullptr)
        {
            printBST(node->left);
        }
        if (node->right != nullptr)
        {
            printBST(node->right);
        }
    }

    void leftobhodspr(Node* head, int& maxhod)
    {
        Node* mov = head;
        if (mov->left != 0)
        {
            leftobhodspr(mov->left, maxhod);
            if (mov->left->leftch < mov->left->rightch)
            {
                mov->leftch = mov->left->leftch + 1;
            }
            else
            {
                mov->leftch = mov->left->rightch + 1;
            }

        }
        if (mov->right != 0)
        {
            leftobhodspr(mov->right, maxhod);
            if (mov->right->leftch < mov->right->rightch)
            {
                mov->rightch = mov->right->leftch + 1;
            }
            else
            {
                mov->rightch = mov->right->rightch + 1;
            }

        }
        if ((mov->leftch != 0 && mov->rightch != 0) && (mov->leftch + mov->rightch < maxhod)) maxhod = mov->leftch + mov->rightch;
    }

    void leftobhodspr1(Node* head, vector<Node*>& toPop, int maxhod)
    {
        Node* mov = head;
        if (mov->left != 0)
        {
            leftobhodspr1(mov->left, toPop, maxhod);
            if (mov->left->leftch + mov->left->rightch == maxhod)
            {
                toPop.push_back(mov->left);
            }
        }
        if (mov->right != 0)
        {
            leftobhodspr1(mov->right, toPop, maxhod);
            if (mov->right->leftch + mov->right->rightch == maxhod)
            {
                toPop.push_back(mov->right);
            }
        }
    }
    public:
        void leftobhodspr(int& maxhod)
        {
            leftobhodspr(root, maxhod);
        }
        void leftobhodspr1(vector<Node*>& toPop, int maxhod)
        {
            leftobhodspr1(root, toPop, maxhod);
        }
        void AddNode(int v) {
            root = AddNode(root, v);
        }
        void printBST() {
            printBST(root);
        }
        void Result(vector<Node*>& toPop)
        {
            if (toPop.size() == 0) return;
            if (toPop.size() == 1)
            {
                if ((toPop[0]->leftch + toPop[0]->rightch) % 2 == 0)
                {
                    if (toPop[0]->leftch == toPop[0]->rightch)
                    {
                        Remove(root, toPop[0]);
                        return;
                    }
                    else
                    {
                        int tmp = (toPop[0]->leftch + toPop[0]->rightch) / 2;
                        if (toPop[0]->leftch > toPop[0]->rightch)
                        {
                            Node* node = toPop[0]->left;
                            Node* node_otec = toPop[0];
                            for (int i = 1; i < tmp; i++)
                            {
                                node_otec = node;
                                if (node->left != nullptr && node->right != nullptr)
                                {
                                    int l_min = node->left->leftch;
                                    if (l_min == 0 || (node->left->rightch != 0 && node->left->rightch < node->left->leftch))
                                    {
                                        l_min = node->left->rightch;
                                    }
                                    int r_min = node->right->leftch;
                                    if (r_min == 0 || (node->right->rightch != 0 && node->right->rightch < node->right->leftch))
                                    {
                                        r_min = node->right->rightch;
                                    }
                                    if (l_min < r_min)
                                    {
                                        node = node->left;
                                    }
                                    else
                                    {
                                        node = node->right;
                                    }
                                }
                                else if (node->left != nullptr)
                                {
                                    node = node->left;
                                }
                                else
                                {
                                    node = node->right;
                                }
                            }
                            Remove(root, node, node_otec);
                            return;
                        }
                        else
                        {
                            Node* node = toPop[0]->right;
                            Node* node_otec = toPop[0];
                            for (int i = 1; i < tmp; i++)
                            {
                                node_otec = node;
                                if (node->left != nullptr && node->right != nullptr)
                                {
                                    int l_min = node->left->leftch;
                                    if (l_min == 0 || (node->left->rightch != 0 && node->left->rightch < node->left->leftch))
                                    {
                                        l_min = node->left->rightch;
                                    }
                                    int r_min = node->right->leftch;
                                    if (r_min == 0 || (node->right->rightch != 0 && node->right->rightch < node->right->leftch))
                                    {
                                        r_min = node->right->rightch;
                                    }
                                    if (l_min < r_min)
                                    {
                                        node = node->left;
                                    }
                                    else
                                    {
                                        node = node->right;
                                    }
                                }
                                else if (node->left != nullptr)
                                {
                                    node = node->left;
                                }
                                else
                                {
                                    node = node->right;
                                }
                            }
                            Remove(root, node, node_otec);
                            return;
                        }
                    }
                }
                else
                {
                    return;
                }
            }
            else
            {
                Node* toDel = nullptr;
                int q = INT_MAX;
                for (int i=0;i<toPop.size();i++)
                {
                    if (toPop[i]->val < q)
                    {
                        q = toPop[i]->val;
                        toDel = toPop[i];
                    }
                }
                if ((toDel->leftch + toDel->rightch) % 2 == 0)
                {
                    if (toDel->leftch == toDel->rightch)
                    {
                        Remove(root, toDel);
                        return;
                    }
                    else
                    {
                        int tmp = (toDel->leftch + toDel->rightch) / 2;
                        if (toDel->leftch > toDel->rightch)
                        {
                            Node* node = toDel->left;
                            Node* node_otec = toDel;
                            for (int i = 1; i < tmp; i++)
                            {
                                node_otec = node;
                                if (node->left != nullptr && node->right != nullptr)
                                {
                                    int l_min = node->left->leftch;
                                    if (l_min == 0 || (node->left->rightch != 0 && node->left->rightch < node->left->leftch))
                                    {
                                        l_min = node->left->rightch;
                                    }
                                    int r_min = node->right->leftch;
                                    if (r_min == 0 || (node->right->rightch != 0 && node->right->rightch < node->right->leftch))
                                    {
                                        r_min = node->right->rightch;
                                    }
                                    if (l_min < r_min)
                                    {
                                        node = node->left;
                                    }
                                    else
                                    {
                                        node = node->right;
                                    }
                                }
                                else if (node->left != nullptr)
                                {
                                    node = node->left;
                                }
                                else
                                {
                                    node = node->right;
                                }
                            }
                            Remove(root, node, node_otec);
                            return;
                        }
                        else
                        {
                            Node* node = toDel->right;
                            Node* node_otec = toDel;
                            for (int i = 1; i < tmp; i++)
                            {
                                node_otec = node;
                                if (node->left != nullptr && node->right != nullptr)
                                {
                                    int l_min = node->left->leftch;
                                    if (l_min == 0 || (node->left->rightch != 0 && node->left->rightch < node->left->leftch))
                                    {
                                        l_min = node->left->rightch;
                                    }
                                    int r_min = node->right->leftch;
                                    if (r_min == 0 || (node->right->rightch != 0 && node->right->rightch < node->right->leftch))
                                    {
                                        r_min = node->right->rightch;
                                    }
                                    if (l_min < r_min)
                                    {
                                        node = node->left;
                                    }
                                    else
                                    {
                                        node = node->right;
                                    }
                                }
                                else if (node->left != nullptr)
                                {
                                    node = node->left;
                                }
                                else
                                {
                                    node = node->right;
                                }
                            }
                            Remove(root, node, node_otec);
                            return;
                        }
                    }
                }
                else
                {
                    return;
                }
            }
        }

        ~BST() {}
};
int main()
{
    ifstream in("in.txt");

    BST T;
    int tmp = 0;
    while (!in.eof())
    {
        in >> tmp;
        T.AddNode(tmp);
    }
    int maxhod = INT_MAX;
    T.leftobhodspr(maxhod);
    vector<Node*> toPop;
    T.leftobhodspr1(toPop, maxhod);
    T.Result(toPop);
    T.printBST();

    in.close();
    out.close();
}