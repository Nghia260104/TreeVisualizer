#pragma once
#include <Node.hpp>

namespace Backend
{
    class Tree
    {
    public:
        Tree();
        virtual ~Tree();
        void clear();
        void clearChild(Node *&Cur);
        Node *&root();
        const Node *const &const_root() const;
        const Node *const &nul() const;

    private:
        Node *Root;
        const Node *Empty = nullptr;
    };
}