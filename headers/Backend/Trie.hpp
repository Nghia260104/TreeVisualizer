#pragma once
#include <Node.hpp>

namespace Backend
{
    class Trie
    {
    public:
        Trie();
        virtual ~Trie();
        void clear();
        void clearChild(Node *&Cur);
        StrNode *&root();

    private:
        StrNode *Root;
    };
}