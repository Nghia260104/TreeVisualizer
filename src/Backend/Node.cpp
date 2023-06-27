#include <Node.hpp>
using namespace Backend;

Node::Node(std::vector<int> a, int numVal, int numChild)
{
    h = f = 1;
    val.resize(numVal);
    for (int *i : val)
        i = nullptr;
    for (int i = 0; i < a.size(); i++)
        val[i] = new int(a[i]);
    x = y = 0;
    Child.resize(numChild);
    for (Node *i : Child)
        i = nullptr;
}

void Node::operator=(const Node& x)
{
    h = x.h;
    f = x.f;
    val = x.val;
    Child = x.Child;
}

int Node::numVal()
{
    int cnt = 0;
    for (int i = 0; i < val.size(); i++)
        if (val[i])
            cnt++;
    return cnt;
}

int Node::height()
{
    if (this == nullptr)
        return 0;
    return h;
}

HashNode::HashNode(int a, int numChild)
{
    grave = 0;
    val = a;
    f = 1;
    x = y = 0;
    Child.resize(numChild);
    for (HashNode *i : Child)
        i = nullptr;
}

StrNode::StrNode(std::string a, int numChild)
{
    val = a;
    x = y = 0;
    Child.resize(numChild);
    for (StrNode *i : Child)
        i = nullptr;
}