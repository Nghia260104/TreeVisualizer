#pragma once
#include <Tree.hpp>
#include <CircleNode.hpp>
#include <vector>
#include <Arrow.hpp>
#include <Status.hpp>

namespace Backend
{
    class Heap : public Tree
    {
    public:
        const int Left = 0, Right = 1;
        enum Type
        {
            Max,
            Min
        };
        Heap();
        ~Heap();

        void link(Frontend::CircleNode *Table_, Frontend::Arrow *Arc_);
        Node *newNode(int val = 0);
        Node *operator[](int index);
        const int MAX_INT();
        const int MIN_INT();
        void swap(Node *x, Node *y);
        bool Cmp(int x, int y, Type t);
        void ShiftUp(Node *Cur, Type t, std::vector<Status> &Tmp);
        void ShiftDown(Node *Cur, Type t, std::vector<Status> &Tmp);
        bool INSERT(int val, Type t);
        bool UpdateKey(int id, int val, Type t);
        int extract(Type t);
        bool REMOVE(int id, Type t);
        int getSize();
        void clear();

    private:
        Frontend::CircleNode *Table;
        Frontend::Arrow *Arc;
        const int MIN = -1, MAX = 1000;
        const int lim = 63;
        const int mask = 64;
        int size;
        const int range = 1600, distance = 60, upper_edge = 200;
        void setPosition(Node *Cur, int h, int &order, std::vector<Status> &x);
        void setArcPosition(Node *Cur, std::vector<Status> &x);
    };
}