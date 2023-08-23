#include <Node.hpp>
using namespace Backend;

Node::Node(std::vector<int> a, int num, int numChild)
{
    h = f = 1;
    val.resize(num);
    // for (int *&i : val)
    //     i = nullptr;
    for (int i = 0; i < a.size(); i++)
        val[i] = a[i];
    numVal = a.size();
    x = y = 0;
    Par = nullptr;
    Child.resize(numChild);
    for (Node *&i : Child)
        i = nullptr;
    Cur = nullptr;
}

Node::~Node()
{
}

// Node::~Node()
// {
//     for (int *&i : val)
//     {
//         delete i;
//         i = nullptr;
//     }
// }

void Node::operator=(const Node &x)
{
    h = x.h;
    f = x.f;
    val = x.val;
    Child = x.Child;
}

int Node::height()
{
    if (this == nullptr)
        return 0;
    return h;
}

int Node::lowerbound(int x) const
{
    if (numVal == 0)
        return 0;

    int l = 0, r = numVal - 1;
    while (l < r)
    {
        int mid = (l + r) / 2;
        if (val[mid] < x)
            l = mid + 1;
        else
            r = mid;
    }

    if (l < numVal && val[l] < x)
        l++;
    return l;
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