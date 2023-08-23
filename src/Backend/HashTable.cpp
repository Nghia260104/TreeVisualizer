#include <HashTable.hpp>
#include <iostream>
using namespace Backend;

HashTable::HashTable(int num)
{
    std::cout << "Call constructor for Hash Table" << '\n';
    num %= limit;
    Table.resize(num);
    for (int i = 0; i < num; i++)
        Table[i] = nullptr;
}

HashNode *&HashTable::operator[](int index)
{
    return Table[index % Table.size()];
}

const HashNode *const &HashTable::operator[](int index) const
{
    return Table[index % Table.size()];
}

const HashNode *const &HashTable::nul() const
{
    return Empty;
}

const int HashTable::size() const
{
    return Table.size();
}

void HashTable::clear()
{
    for (int i = 0; i < Table.size(); i++)
    {
        HashNode *Cur = Table[i];
        while (Cur)
        {
            HashNode *Tmp = Cur;
            Cur = Cur->Child[0];
            delete Tmp;
            Tmp = nullptr;
        }
        Table[i] = nullptr;
    }
    Table.resize(0);
}

void HashTable::display() const
{
    for (int i = 0; i < size(); i++)
    {
        HashNode *Cur = Table[i];
        while (Cur)
        {
            std::cerr << Cur->val;
            if (Cur->f > 1)
                std::cerr << '-' << Cur->f;
            std::cerr << " ";
            Cur = Cur->Child[0];
        }
        std::cout << "x\n";
    }
}

HashTable::~HashTable()
{
    clear();
    std::cerr << "Call destructor for Hash Table" << '\n';
}

int HashTable::Hash(const int &val) const
{
    return val % Table.size();
}

void HashTable::resize(int n)
{
    for (int i = 0; i < Table.size(); i++)
    {
        HashNode *Cur = Table[i];
        while (Cur)
        {
            HashNode *Tmp = Cur;
            Cur = Cur->Child[0];
            delete Tmp;
            Tmp = nullptr;
        }
        Table[i] = nullptr;
    }
    Table.resize(n, nullptr);
}