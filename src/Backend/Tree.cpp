#include <Tree.hpp>
#include <iostream>
using namespace Backend;

Tree::Tree()
{
    Root = nullptr;
}

Tree::~Tree()
{
    clear();
    std::cerr << "Call destructor for Tree" << '\n';
}

void Tree::clear()
{
    clearChild(Root);
}

void Tree::clearChild(Node *&Cur)
{
    if (!Cur)
        return;
    for (Node *&i : (Cur->Child))
        clearChild(i);
    for (int i = 0; i < Cur->val.size(); i++)
    {
        delete Cur->val[i];
        Cur->val[i] = nullptr;
    }
    delete Cur;
    Cur = nullptr;
}

Node *&Tree::root()
{
    return Root;
}

const Node *const &Tree::const_root() const
{
    return Root;
}

const Node *const &Tree::nul() const
{
    return Empty;
}