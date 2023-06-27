#pragma once
#include <vector>
#include <string>

namespace Backend
{
    struct Node
    {
        int h, f;
        float x, y;
        std::vector<int*> val;
        std::vector<Node *> Child;

        Node(std::vector<int> a = {0}, int numVal = 1, int numChild = 1);
        void operator=(const Node& x);
        int numVal();
        int height();
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