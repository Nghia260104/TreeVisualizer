#pragma once
#include <BST.hpp>

namespace Backend
{
    class AVL : public BST
    {
    public:
        AVL();
        ~AVL();

        BST::Limit insert(int val);
        Node *INSERT(Node *Cur, int val);
        bool remove(int val);
        Node *REMOVE(Node *Cur, int val, bool &check);
    private:
        int getBalance(Node *Cur);
        Node *leftRotate(Node *Cur);
        Node *rightRotate(Node *Cur);
    };
}