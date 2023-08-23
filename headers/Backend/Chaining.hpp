#pragma once
#include <HashTable.hpp>

namespace Backend
{
    class Chaining : public HashTable
    {
    public:
        Chaining(int num = 0);
        ~Chaining();
        bool insert(int val);
        bool remove(int val);
        const HashNode *const &search(int val) const;

    private:
        int ChainLim = 5;
        int numInserted;
    };
}