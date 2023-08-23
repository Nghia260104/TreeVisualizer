#pragma once
#include <vector>
#include <string>
#include <CircleNode.hpp>

namespace Backend
{
    struct Node
    {
        int h, f;
        int x, y;
        int numVal;
        bool leaf;
        Node *Par;
        std::vector<int> val;
        std::vector<Node *> Child;
        Frontend::CircleNode *Cur;
        
        Node(std::vector<int> a = {}, int num = 1, int numChild = 1);
        ~Node();
        void operator=(const Node& x);
        int height();
        int lowerbound(int x) const;
    };

    struct HashNode
    {
        bool grave;
        int val, f;
        float x, y;
        std::vector<HashNode *> Child;

        HashNode(int a = 0, int numChild = 1);
    };

    struct StrNode
    {
        std::string val;
        float x, y;
        std::vector<StrNode *> Child;

        StrNode(std::string a = "", int numChild = 26);
    };
}