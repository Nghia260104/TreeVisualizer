#pragma once
#include <Node.hpp>

namespace Backend
{
    class HashTable
    {
    public:
        const int limit = 30;

        HashTable(int num = 0);
        virtual ~HashTable();
        void clear();

        int Hash(const int &val) const;
        void resize(int n);
        HashNode *&operator[](int index);
        const HashNode *const &operator[](int index) const;
        const HashNode *const &nul() const;
        const int size() const;
        void display() const;

    private:
        std::vector<HashNode *> Table;
        const HashNode *Empty = nullptr;
    };
}