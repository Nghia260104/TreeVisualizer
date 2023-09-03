#pragma once
#include <vector>
#include <string>
#include <CircleNode.hpp>
#include <Arrow.hpp>

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
        void operator=(const Node &x);
        int height();
        int lowerbound(int x) const;
    };

    struct HashNode
    {
        bool grave;
        int val, f;
        float x, y;
        std::vector<HashNode *> Child;

        HashNode(int a = -1, int numChild = 1);
    };

    struct StrNode
    {
        std::string val;
        float min_x, max_x, y;
        StrNode *Par;
        std::vector<StrNode *> Child;
        Frontend::CircleNode *Cur;
        int vs_id;
        bool isEndOfWord;

        StrNode(std::string a = "", int numChild_ = 26);
        int numChild();
    };

    struct MyVector
    {
        float x, y;
        
        MyVector(int x_ = 0, int y_ = 0)
        {
            x = x_;
            y = y_;
        }

    };

    struct GraphNode
    {
        int numVal;
        float x, y;
        MyVector pos, disp;
        Frontend::CircleNode *Cur;
        bool hidden;
        GraphNode()
        {
            x = y = 0;
            numVal = -1;
            Cur = nullptr;
            pos = disp = MyVector(0, 0);
            hidden = 1;
        }
    };

    struct GraphEdge
    {
        int weight;
        sf::Vector2f pos1, pos2;
        Frontend::Arrow *Arc;
        GraphNode *vertex1, *vertex2;
        GraphEdge()
        {
            pos1 = pos2 = sf::Vector2f(0, 0);
            weight = 0;
            Arc = nullptr;
            vertex1 = vertex2 = nullptr;
        }
    };

    struct Adjacent
    {
        int v;
        GraphEdge *val;
    };
}