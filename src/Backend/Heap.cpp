#include <Heap.hpp>
#include <iostream>
#include <cmath>
using namespace Backend;

Heap::Heap()
    : Tree()
{
    size = 0;
}

Heap::~Heap()
{
    std::cerr << "Call destructor for Heap\n";
}

const int Heap::MAX_INT()
{
    return MAX;
}

const int Heap::MIN_INT()
{
    return MIN;
}

Node *Heap::newNode(int val)
{
    return new Node({val});
}

Node *Heap::operator[](int index)
{
    index %= size;
    if (index == 0)
        return nullptr;
    int it = log2(index);
    while (!(index & mask))
        index <<= 1;
    Node *Cur = root();
    for (int i = 0; i < it; i++)
    {
        index <<= 1;
        Cur = Cur->Child[(bool)(index & mask)];
    }
    return Cur;
}

bool Heap::Cmp(int x, int y, Type t)
{
    if (t == Max)
        return x > y;
    else
        return x <= y;
}

void Heap::swap(Node *x, Node *y)
{
    int val = x->val[0];
    x->val[0] = y->val[0];
    y->val[0] = val;
}

void Heap::ShiftUp(Node *Cur, Type t)
{
    while (Cur != root() && Cmp(Cur->val[0], Cur->Par->val[0], t))
    {
        swap(Cur, Cur->Par);
        Cur = Cur->Par;
    }
}

void Heap::ShiftDown(Node *Cur, Type t)
{
    Node *Root = Cur;
    Node *l = Cur->Child[Left];
    Node *r = Cur->Child[Right];

    if (l && Cmp(l->val[0], Cur->val[0], t))
        Cur = l;
    if (r && Cmp(r->val[0], Cur->val[0], t))
        Cur = r;
    if (Cur != Root)
    {
        swap(Cur, Root);
        ShiftDown(Cur, t);
    }
}

bool Heap::INSERT(int val, Type t)
{
    size++;
    int id = size;
    while (!(id & mask))
        id <<= 1;
    id <<= 1;

    Node *Par = nullptr, *Cur = root();
    while (Cur)
    {
        if (Cmp(val, Cur->val[0], t))
        {
            int Tmp = Cur->val[0];
            Cur->val[0] = val;
            val = Tmp;
        }
        Par = Cur;

        Cur = Cur->Child[(bool)(id & mask)];
        if (Cur)
            id <<= 1;
    }

    if (!Par)
    {
        root() = newNode(val);
        return true;
    }

    Par->Child[(bool)(id & mask)] = newNode(val);
    Par->Child[(bool)(id & mask)]->Par = Par;
    return true;
}

bool Heap::UpdateKey(int id, int val, Type t)
{
    if (!root())
        return false;
        
    Node *Cur = (*this)[id];
    int oldVal = Cur->val[0];
    if (val == oldVal)
        return false;

    Cur->val[0] = val;
    if (Cmp(val, oldVal, t))
        ShiftUp(Cur, t);
    else
        ShiftDown(Cur, t);
    return true;
}

int Heap::extract(Type t)
{
    if (!root())
        return (t == MAX) ? INT_MIN : INT_MAX;

    if (size == 1)
    {
        int val = root()->val[0];
        delete root();
        size--;
        root() = nullptr;
        return val;
    }

    Node *Cur = (*this)[size];
    int val = root()->val[0];
    root()->val[0] = Cur->val[0];
    Cur->Par->Child[size % 2] = nullptr;
    delete Cur;
    size--;
    ShiftDown(root(), t);
    return val;
}

bool Heap::REMOVE(int id, Type t)
{
    if (!root())
        return false;
    UpdateKey(id, (t == MAX) ? root()->val[0] + 1 : root()->val[0] - 1, t);
    extract(t);
    return true;
}