#pragma once
#include <vector>
#include <CircleNode.hpp>
#include <Arrow.hpp>

struct Status
{
    Frontend::CircleNode *Node;
    sf::Color NodeFillColor, OutlineColor, NodeTextColor, ArcColor;
    Frontend::Arrow *Arc;
    bool hideNode, hideArc;
    float thickness;
    sf::Vector2f NodePosition, ArcFirstPosition, ArcSecondPosition;
    sf::String nodeVal;

    Status();
    void highlightNode();
    void NodeOnPath();
    void NormalNode();
    void highlightArc();
    void ArcOnPath();
    void NormalArc();
};

class Handle
{
    std::vector<std::vector<Status>> list;
    int step;
    sf::Clock clock;
    bool graph;

public:
    Handle();
    void push_back(std::vector<Status> Tmp);
    std::vector<Status> &back();
    std::vector<Status> &operator[](int id);
    int size();
    void setGraph();
    void setNonGraph();
    void clear();
    void stepforw();
    void stepback();
    void run();
};