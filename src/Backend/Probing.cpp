#include <Probing.hpp>
#include <iostream>
#include <FrontendGlobal.hpp>
using namespace Backend;

Probing::Probing(int num)
    : HashTable{num}
{
    std::cout << "Call constructor for Probing" << '\n';
    numInserted = 0;
    num %= limit;
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
    return (numInserted < size() || trySearch(val, t));
}

void Probing::resize(int n)
{
    HashTable::resize(n);
    numInserted = 0;
}

bool Probing::INSERT(int val, std::vector<Frontend::CircleNode> &Art, Type t)
{
    // if (numInserted >= size() && !trySearch(val, t))
    //     return false;
    Process a;
    for (int i = 0; i < size(); i++)
    {
        a.reset();
        int id = index(val, i, t);
        HashNode *&Tmp = (*this)[id];
        a.color = Highlight;
        a.color_c = true;
        a.emph = true;
        a.Cur = &Art[id];
        List.push_back(a);
        if (!Tmp)
        {
            Tmp = new HashNode(val);
            a.val = std::to_string(val);
            a.val_c = true;
            a.emph = false;
            numInserted++;
            List.push_back(a);
            return true;
        }
        else if (Tmp->val == val)
        {
            if (Tmp->f < 9)
            {
                (Tmp->f)++;
                a.val = sf::String(std::to_string(Tmp->val) + "-" + std::to_string(Tmp->f));
                a.val_c = true;
            }
            a.emph = false;
            List.push_back(a);
            return true;
        }
        else if (Tmp->grave)
        {
            Tmp->val = val;
            Tmp->grave = 0;
            a.val = std::to_string(val);
            a.val_c = true;
            numInserted++;
            a.emph = false;
            List.push_back(a);
            return true;
        }
    }
    a.emph = false;
    List.push_back(a);
    return false;
}

bool Probing::REMOVE(int val, std::vector<Frontend::CircleNode> &Art, Type t)
{
    Process a;
    for (int i = 0; i < size(); i++)
    {
        a.reset();
        int id = index(val, i, t);
        HashNode *Tmp = (*this)[id];
        a.color = Highlight;
        a.color_c = true;
        a.Cur = &Art[id];
        a.emph = true;
        List.push_back(a);
        if (!Tmp || Tmp->grave)
        {
            a.emph = false;
            List.push_back(a);
            return false;
        }
        if (Tmp->val == val)
        {
            a.emph = false;
            a.val_c = true;
            if (Tmp->f > 1)
            {
                Tmp->f--;
                if (Tmp->f != 1)
                    a.val = sf::String(std::to_string(Tmp->val) + "-" + std::to_string(Tmp->f));
                else
                    a.val = sf::String(std::to_string(Tmp->val));
            }
            else
            {
                Tmp->val = -1;
                Tmp->f = 1;
                Tmp->grave = 1;
                numInserted--;
                a.val = "DEL";
            }
            List.push_back(a);
            return true;
        }
    }
    a.emph = false;
    List.push_back(a);
    return false;
}

const HashNode *const &Probing::SEARCH(int val, std::vector<Frontend::CircleNode> &Art, Type t) const
{
    Process a;
    for (int i = 0; i < size(); i++)
    {
        a.reset();
        int id = index(val, i, t);
        a.Cur = &Art[id];
        a.color = Highlight;
        a.color_c = true;
        a.emph = true;
        List.push_back(a);
        if (!(*this)[id])
        {
            a.emph = false;
            List.push_back(a);
            return nul();
        }
        if ((*this)[id]->val == val)
        {
            a.emph = false;
            List.push_back(a);
            return (*this)[id];
        }
    }
    a.emph = false;
    List.push_back(a);
    return nul();
}

const HashNode *const &Probing::trySearch(int val, Type t) const
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

bool LP::insert(int val, std::vector<Frontend::CircleNode> &Art)
{
    // std::cout << index(val, 0, Linear) << '\n';
    return INSERT(val, Art, Linear);
}

bool LP::remove(int val, std::vector<Frontend::CircleNode> &Art)
{
    return REMOVE(val, Art, Linear);
}

const HashNode *const &LP::search(int val, std::vector<Frontend::CircleNode> &Art) const
{
    return SEARCH(val, Art, Linear);
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

bool QP::insert(int val, std::vector<Frontend::CircleNode> &Art)
{
    return INSERT(val, Art, Quadratic);
}

bool QP::remove(int val, std::vector<Frontend::CircleNode> &Art)
{
    return REMOVE(val, Art, Quadratic);
}

const HashNode *const &QP::search(int val, std::vector<Frontend::CircleNode> &Art) const
{
    return SEARCH(val, Art, Quadratic);
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

bool DH::insert(int val, std::vector<Frontend::CircleNode> &Art)
{
    return INSERT(val, Art, Double);
}

bool DH::remove(int val, std::vector<Frontend::CircleNode> &Art)
{
    return REMOVE(val, Art, Double);
}

const HashNode *const &DH::search(int val, std::vector<Frontend::CircleNode> &Art) const
{
    return SEARCH(val, Art, Double);
}

DH::~DH()
{
    std::cout << "Call destructor of Double Hashing" << '\n';
}