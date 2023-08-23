#include <BTree.hpp>
#include <iostream>
using namespace Backend;

BTree::BTree(int k_)
    : Tree()
{
    k = (k_ > 1) ? k_ : 1;
    std::cerr << "Call constructor for B-Tree" << '\n';
}

BTree::~BTree()
{
    std::cerr << "Call destructor for B-Tree" << '\n';
}

Node *BTree::newNode(bool leaf_)
{
    Node *Tmp = new Node({}, 2 * k - 1, 2 * k);
    Tmp->leaf = leaf_;
    return Tmp;
}

const int *const &BTree::nulVal()
{
    return nullVal;
}

const int *const &BTree::SEARCH(const Node *const &Root, int val)
{
    if (!Root)
        return nulVal();

    int id = Root->lowerbound(val);
    if (id < Root->numVal && Root->val[id] == val)
        return &Root->val[id];
    else
        return SEARCH(Root->Child[id], val);
}

const int *const &BTree::search(int val)
{
    return SEARCH(root(), val);
}

bool BTree::insert(int val)
{
    if (search(val))
        return false;

    if (!root())
    {
        root() = newNode(true);
        root()->val[0] = val;
        root()->numVal++;
    }
    else
    {
        if (root()->numVal >= 2 * k - 1)
        {
            Node *Tmp = newNode(false);
            Tmp->Child[0] = root();
            splitChild(Tmp, 0);
            int i = 0;
            if (Tmp->val[0] < val)
                i++;
            insertNonFull(Tmp->Child[i], val);
        }
        else
            insertNonFull(root(), val);
    }
    return true;
}

void BTree::insertNonFull(Node *&Root, int val)
{
    if (Root->leaf)
    {
        int i = Root->numVal - 1;
        while (i >= 0 && Root->val[i] > val)
        {
            Root->val[i + 1] = Root->val[i];
            i--;
        }
        Root->val[i + 1] = val;
        Root->numVal++;
        return;
    }
    else
    {
        int i = Root->lowerbound(val);
        if (Root->Child[i]->numVal >= 2 * k - 1)
        {
            splitChild(Root, i);
            if (Root->val[i] < val)
                i++;
        }
        insertNonFull(Root->Child[i], val);
    }
}

void BTree::splitChild(Node *&Root, int id)
{
    Node *First = Root->Child[id];
    Node *Second = newNode(First->leaf);

    Second->numVal = k - 1;
    First->numVal = k - 1;
    for (int i = 0; i < k - 1; i++)
    {
        Second->val[i] = First->val[k + i];
        First->val[k + i] = 0;
    }
    if (!First->leaf)
    {
        for (int i = 0; i < k; i++)
        {
            Second->Child[i] = First->Child[k + i];
            First->Child[k + i] = nullptr;
        }
    }
    for (int i = Root->numVal; i >= id + 1; i--)
    {
        Root->Child[i + 1] = Root->Child[i];
        Root->val[i] = Root->val[i - 1];
    }
    Root->Child[id + 1] = Second;
    Root->val[id] = First->val[k - 1];
    Root->numVal++;
}