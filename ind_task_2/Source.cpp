#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

ofstream out("out.txt");

class Node
{
public:
    long long val;
    Node* left;
    Node* right;
    long long leftch;
    long long rightch;
    long long sumL;
    long long sumR;
    long long sum;
    Node(long long val1)
    {
        val = val1;
        left = 0;
        right = 0;
        leftch = -1;
        rightch = -1;
        sumL = 0;
        sumR = 0;
        sum = val1;
    }
    ~Node() {};
};

class BST
{
private:
    Node* root = nullptr;

    Node* AddNode(Node* node, long long v)
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

    Node* Search_otec(Node* root, long long v) {
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

    void leftobhodspr(Node* head, long long& maxhod, long long& minsum)
    {
        Node* mov = head;
        if (mov->left != 0)
        {
            leftobhodspr(mov->left, maxhod, minsum);
            if (mov->left->leftch < mov->left->rightch)
            {
                if (mov->left->leftch > 0)
                {
                    mov->leftch = mov->left->leftch + 1;
                }
                else if (mov->left->rightch > 0)
                {
                    mov->leftch = mov->left->rightch + 1;
                }
                else
                {
                    mov->leftch = 1;
                }
                if (mov->left->right != nullptr && mov->left->left != nullptr)
                {
                    mov->sumL += min(mov->left->sumL, mov->left->sumR) + mov->left->val;
                    mov->sum += mov->sumL;
                }
                else if (mov->left->left != nullptr)
                {
                    mov->sumL += mov->left->sumL + mov->left->val;
                    mov->sum += mov->sumL;
                }
                else
                {
                    mov->sumL += mov->left->sumR + mov->left->val;
                    mov->sum += mov->sumL;
                }
            }
            else
            {
                if (mov->left->rightch > 0)
                {
                    mov->leftch = mov->left->rightch + 1;
                }
                else  if (mov->left->leftch > 0)
                {
                    mov->leftch = mov->left->leftch + 1;
                }
                else
                {
                    mov->leftch = 1;
                }
                if (mov->left->right != nullptr && mov->left->left != nullptr)
                {
                    mov->sumL += min(mov->left->sumL, mov->left->sumR) + mov->left->val;
                    mov->sum += mov->sumL;
                }
                else if (mov->left->left != nullptr)
                {
                    mov->sumL += mov->left->sumL + mov->left->val;
                    mov->sum += mov->sumL;
                }
                else
                {
                    mov->sumL += mov->left->sumR + mov->left->val;
                    mov->sum += mov->sumL;
                }
            }
        }
        if (mov->right != 0)
        {
            leftobhodspr(mov->right, maxhod, minsum);
            if (mov->right->leftch < mov->right->rightch)
            {
                if (mov->right->leftch > 0)
                {
                    mov->rightch = mov->right->leftch + 1;
                }
                else if (mov->right->rightch > 0)
                {
                    mov->rightch = mov->right->rightch + 1;
                }
                else
                {
                    mov->rightch = 1;
                }
                if (mov->right->left != nullptr && mov->right->right != nullptr)
                {
                    mov->sumR += min(mov->right->sumL, mov->right->sumR) + mov->right->val;
                    mov->sum += mov->sumR;
                }
                else if (mov->right->right != nullptr)
                {
                    mov->sumR += mov->right->sumR + mov->right->val;
                    mov->sum += mov->sumR;
                }
                else
                {
                    mov->sumR += mov->right->sumL + mov->right->val;
                    mov->sum += mov->sumR;
                }
            }
            else
            {
                if (mov->right->rightch > 0)
                {
                    mov->rightch = mov->right->rightch + 1;
                }
                else if (mov->right->leftch > 0)
                {
                    mov->rightch = mov->right->leftch + 1;
                }
                else
                {
                    mov->rightch = 1;
                }
                if (mov->right->left != nullptr && mov->right->right != nullptr)
                {
                    mov->sumR += min(mov->right->sumL, mov->right->sumR) + mov->right->val;
                    mov->sum += mov->sumR;
                }
                else if (mov->right->right != nullptr)
                {
                    mov->sumR += mov->right->sumR + mov->right->val;
                    mov->sum += mov->sumR;
                }
                else
                {
                    mov->sumR += mov->right->sumL + mov->right->val;
                    mov->sum += mov->sumR;
                }
            }

        }
        if ((mov->leftch > 0 && mov->rightch > 0) && (mov->leftch + mov->rightch <= maxhod))
        {
            maxhod = mov->leftch + mov->rightch;
            minsum = min(minsum, mov->sum);
        }
    }

    void leftobhodspr1(Node* head, vector<Node*>& toPop, long long maxhod, long long minsum)
    {
        if (head == nullptr)return;
        if ((head->leftch + head->rightch == maxhod) && (head->sum == minsum))
        {
            toPop.push_back(head);
        }
        leftobhodspr1(head->left, toPop, maxhod, minsum);
        leftobhodspr1(head->right, toPop, maxhod, minsum);
    }
public:
    void leftobhodspr(long long& maxhod, long long& minsum)
    {
        leftobhodspr(root, maxhod, minsum);
    }
    void leftobhodspr1(vector<Node*>& toPop, long long maxhod, long long minsum)
    {
        leftobhodspr1(root, toPop, maxhod, minsum);
    }
    void AddNode(long long v) {
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
                    long long tmp = (toPop[0]->leftch + toPop[0]->rightch) / 2;
                    if (toPop[0]->leftch > toPop[0]->rightch)
                    {
                        Node* node = toPop[0]->left;
                        Node* node_otec = toPop[0];
                        for (long long i = 2; i < tmp; i++)
                        {
                            node_otec = node;
                            if (node->left != nullptr && node->right != nullptr)
                            {
                                long long l_min = node->left->leftch;
                                if (l_min == -1 || (node->left->rightch > 0 && node->left->rightch < node->left->leftch))
                                {
                                    l_min = node->left->rightch;
                                }
                                long long r_min = node->right->leftch;
                                if (r_min == -1 || (node->right->rightch > 0 && node->right->rightch < node->right->leftch))
                                {
                                    r_min = node->right->rightch;
                                }
                                if (l_min <= r_min)
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
                        for (long long i = 2; i < tmp; i++)
                        {
                            node_otec = node;
                            if (node->left != nullptr && node->right != nullptr)
                            {
                                long long l_min = node->left->leftch;
                                if (l_min == -1 || (node->left->rightch > 0 && node->left->rightch < node->left->leftch))
                                {
                                    l_min = node->left->rightch;
                                }
                                long long r_min = node->right->leftch;
                                if (r_min == -1 || (node->right->rightch > 0 && node->right->rightch < node->right->leftch))
                                {
                                    r_min = node->right->rightch;
                                }
                                if (l_min <= r_min)
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
            long long q = LLONG_MAX;
            for (long long i = 0; i < toPop.size(); i++)
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
                    long long tmp = (toDel->leftch + toDel->rightch) / 2;
                    if (toDel->leftch > toDel->rightch)
                    {
                        Node* node = toDel->left;
                        Node* node_otec = toDel;
                        for (long long i = 2; i < tmp; i++)
                        {
                            node_otec = node;
                            if (node->left != nullptr && node->right != nullptr)
                            {
                                long long l_min = node->left->leftch;
                                if (l_min == -1 || (node->left->rightch > 0 && node->left->rightch < node->left->leftch))
                                {
                                    l_min = node->left->rightch;
                                }
                                long long r_min = node->right->leftch;
                                if (r_min == -1 || (node->right->rightch > 0 && node->right->rightch < node->right->leftch))
                                {
                                    r_min = node->right->rightch;
                                }
                                if (l_min <= r_min)
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
                        for (long long i = 2; i < tmp; i++)
                        {
                            node_otec = node;
                            if (node->left != nullptr && node->right != nullptr)
                            {
                                long long l_min = node->left->leftch;
                                if (l_min == -1 || (node->left->rightch > 0 && node->left->rightch < node->left->leftch))
                                {
                                    l_min = node->left->rightch;
                                }
                                long long r_min = node->right->leftch;
                                if (r_min == -1 || (node->right->rightch > 0 && node->right->rightch < node->right->leftch))
                                {
                                    r_min = node->right->rightch;
                                }
                                if (l_min <= r_min)
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
    long long tmp = 0;
    while (!in.eof())
    {
        in >> tmp;
        T.AddNode(tmp);
    }
    long long maxhod = LLONG_MAX;
    long long minsum = LLONG_MAX;
    T.leftobhodspr(maxhod, minsum);
    vector<Node*> toPop;
    T.leftobhodspr1(toPop, maxhod, minsum);
    T.Result(toPop);
    T.printBST();

    in.close();
    out.close();
}