#pragma once
#include <Tree.hpp>

namespace Backend
{
    class BST : public Tree
    {
    public:
        const int Left = 0, Right = 1;
        enum Limit
        {
            Accept,
            Overload,
            Overheight
        };
        BST();
        ~BST();
        Node *newNode(int val = 0);
        Node *INSERT(Node *Cur, int val);
        Limit insert(int val);
        bool checkHeight(Node *Cur, int val, int h);
        bool remove(int val);
        Node *REMOVE(Node *Cur, int val, bool &check);
        Node *minValue(Node *Cur);
        const Node *const &search(int val) const;
        const Node *const &SEARCH(const Node *const &Cur, int val) const;
        void display();
        void print(Node *Cur);
        int max(int a, int b);
        int &Num();
        const int &limHeight();
        const int &limInsert();

    private:
        const int limH = 8;
        const int limI = 50;
        int numInserted;
    };
}