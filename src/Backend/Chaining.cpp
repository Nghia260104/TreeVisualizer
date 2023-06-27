#include <Chaining.hpp>
#include <iostream>
using namespace Backend;

Chaining::Chaining(int num)
    : HashTable{num}
{
    std::cerr << "Call constructor for Chaining Hash Table\n";
    numInserted = 0;
}

bool Chaining::insert(int val)
{
    if (numInserted > size() * ChainLim)
        return false;
    int id = Hash(val);
    if (!(*this)[id])
    {
        (*this)[id] = new HashNode(val);
        numInserted++;
        return true;
    }
    int cnt = 1;
    HashNode *Cur = (*this)[id];
    if (Cur->val == val)
    {
        (Cur->f)++;
        return true;
    }
    while (Cur->Child[0])
    {
        if (Cur->Child[0]->val == val)
        {
            (Cur->Child[0]->f)++;
            return true;
        }
        Cur = Cur->Child[0];
        cnt++;
    }
    if (cnt >= 4)
        return false;
    Cur->Child[0] = new HashNode(val);
    numInserted++;
    return true;
}

bool Chaining::remove(int val)
{
    int id = Hash(val);
    if ((*this)[id] && (*this)[id]->val == val)
    {
        HashNode *Tmp = (*this)[id];
        (*this)[id] = (*this)[id]->Child[0];
        delete Tmp;
        Tmp = nullptr;
        return true;
    }

    if (!(*this)[id])
        return false;

    HashNode *Cur = (*this)[id];
    while (Cur->Child[0] && Cur->Child[0]->val != val)
        Cur = Cur->Child[0];
    if (Cur->Child[0] && Cur->Child[0]->val == val)
    {
        HashNode *Tmp = Cur->Child[0];
        Cur->Child[0] = Tmp->Child[0];
        delete Tmp;
        Tmp = nullptr;
        return true;
    }
    return false;
}

const HashNode *const &Chaining::search(int val) const
{
    int id = Hash(val);
    HashNode const *const *Cur = &(*this)[id];
    while (Cur)
    {
        if ((*Cur)->val == val)
            break;
        Cur = (&((*Cur)->Child[0]));
    }
    if (Cur)
        return *Cur;
    else
        return nul();
}

Chaining::~Chaining()
{
    std::cout << "Call destructor of Chaining Hash Table" << '\n';
}