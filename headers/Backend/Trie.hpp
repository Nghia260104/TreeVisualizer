#pragma once
#include <Node.hpp>
#include <CircleNode.hpp>
#include <Arrow.hpp>
#include <Status.hpp>
#include <vector>

namespace Backend
{
    class Trie
    {
    public:
        Trie();
        virtual ~Trie();
        void clear();
        void clearChild(StrNode *&Cur);
        void link(Frontend::CircleNode *Table_, Frontend::Arrow *Arc_);
        StrNode *&root();
        void insert(const std::string &val);
        bool search(const std::string &val);
        void remove(const std::string &val);
        StrNode *REMOVE(StrNode *Cur, const std::string &val, int depth = 0);
        const int &Inserted();
        void displayPos();

    private:
        const int limWord = 32, limHeight = 6, MAX_NUM = 26;
        int numInserted, numNode;
        StrNode *Root;
        Frontend::CircleNode *Table;
        Frontend::Arrow *Arc;
        const int range = 1600, distance = 90, upper_edge = 200, total = 193;
        bool Inc, Dec;
        void align(StrNode *Cur, int h, int &order);
        void edit(StrNode *Cur, const int &Num, std::vector<Status> &Tmp);
        void setPosition(std::vector<Status> &Tmp);
        void setArcPosition(StrNode *Cur, std::vector<Status> &Tmp);
        void traverse(StrNode *Cur);
    };
}