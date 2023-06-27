#include <Probing.hpp>
#include <iostream>
using namespace Backend;

Probing::Probing(int num)
    : HashTable{num}
{
    std::cout << "Call constructor for Probing" << '\n';
    numInserted = 0;
    num %= limit;
    // HashTable(num);
}

Probing::~Probing()
{
}

int Probing::index(const int &val, const int &steps, Type t) const
{
    if (t == Linear)
        return Hash(val + steps);
    else if (t == Quadratic)
        return Hash(val + steps * steps);
    else
        return Hash(val + steps * (sec - val % sec));
}

bool Probing::canInsert(int val, Type t)
{
    return (numInserted < size() || SEARCH(val, t));
}

bool Probing::INSERT(int val, Type t)
{
    if (numInserted >= size() && !SEARCH(val, t))
        return false;
    for (int i = 0; i < size(); i++)
    {
        HashNode *&Tmp = (*this)[index(val, i, t)];
        if (!Tmp)
        {
            Tmp = new HashNode(val);
            numInserted++;
            return true;
        }
        else if (Tmp->val == val)
        {
            (Tmp->f)++;
            return true;
        }
        else if (Tmp->grave)
        {
            Tmp->val = val;
            Tmp->grave = 0;
            numInserted++;
            return true;
        }
    }
    return false;
}

bool Probing::REMOVE(int val, Type t)
{
    for (int i = 0; i < size(); i++)
    {
        HashNode *Tmp = (*this)[index(val, i, t)];
        if (!Tmp)
            return false;
        if (Tmp->val == val)
        {
            Tmp->grave = 1;
            return true;
            numInserted--;
        }
    }
    return false;
}

const HashNode *const &Probing::SEARCH(int val, Type t) const
{
    for (int i = 0; i < size(); i++)
    {
        int id = index(val, i, t);
        if (!(*this)[id])
            return nul();
        if ((*this)[id]->val == val)
            return (*this)[id];
    }
    return nul();
}

// Linear Probing ////////////////////////////////////////////////////////////////////

LP::LP(int num)
    : Probing{num}
{
    std::cout << "Call constructor for LP" << '\n';
    // Probing(num);
}

bool LP::insert(int val)
{
    // std::cout << index(val, 0, Linear) << '\n';
    return INSERT(val, Linear);
}

bool LP::remove(int val)
{
    return REMOVE(val, Linear);
}

const HashNode *const &LP::search(int val) const
{
    return SEARCH(val, Linear);
}

LP::~LP()
{
    std::cout << "Call destructor of Linear Probing" << '\n';
}

// Quadratic Probing ///////////////////////////////////////////////////////////////////////

QP::QP(int num)
    : Probing{num}
{
    // Probing(num);
}

bool QP::insert(int val)
{
    return INSERT(val, Quadratic);
}

bool QP::remove(int val)
{
    return REMOVE(val, Quadratic);
}

const HashNode *const &QP::search(int val) const
{
    return SEARCH(val, Quadratic);
}

QP::~QP()
{
    std::cout << "Call destructor of Quadratic Probing" << '\n';
}

// Double Hashing ////////////////////////////////////////////////////////////////////////////

DH::DH(int num)
    : Probing{num}
{
    // Probing(num);
    sec = num - 1;
    for (int i = num - 1; i >= 2; i--)
    {
        bool prime = 1;
        for (int j = 2; j * j <= i; j++)
            if (i % j == 0)
            {
                prime = 0;
                break;
            }
        if (prime)
        {
            sec = i;
            break;
        }
    }
}

bool DH::insert(int val)
{
    return INSERT(val, Double);
}

bool DH::remove(int val)
{
    return REMOVE(val, Double);
}

const HashNode *const &DH::search(int val) const
{
    return SEARCH(val, Double);
}

DH::~DH()
{
    std::cout << "Call destructor of Double Hashing" << '\n';
}