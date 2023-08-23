#pragma once
#include <BST.hpp>
#include <CircleNode.hpp>
#include <Arrow.hpp>
#include <Status.hpp>

namespace Backend
{
    class AVL : public BST
    {
        Frontend::CircleNode *Table;
        Frontend::Arrow *Arc;
        const int range = 1600, distance = 60, upper_edge = 200;
        int left_side;
        bool Inc;

    public:
        AVL();
        ~AVL();

        void link(Frontend::CircleNode *Table_, int x_, Frontend::Arrow *Arc_);
        void clear();
        BST::Limit insert(int val);
        void insertWithOrder(int val);
        Node *INSERT(Node *Cur, int val, bool rotate);
        bool remove(int val);
        Node *REMOVE(Node *Cur, int val, bool &check);
        const Node *const &search(int val);
        const Node *const &trySearch(const Node *const &Cur, int val);
        const Node *const &SEARCH(const Node *const &Cur, int val);

    private:
        int getBalance(Node *Cur);
        Node *leftRotate(Node *Cur, std::vector<Status> &Tmp);
        Node *rightRotate(Node *Cur, std::vector<Status> &Tmp);
        void setPosition(Node *Cur, int h, int &order, std::vector<Status> &x);
        void setArcPosition(Node *Cur, std::vector<Status> &x);
        std::vector<Status> getResetStatus();
    };
}