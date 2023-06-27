#include <BST.hpp>
#include <iostream>
using namespace Backend;

BST::BST()
    : Tree()
{
    numInserted = 0;
}

BST::~BST()
{
    std::cerr << "Call destructor for Binary Search Tree" << '\n';
}

Node *BST::newNode(int val)
{
    Node *Tmp = new Node({val}, 1, 2);
    return Tmp;
}

BST::Limit BST::insert(int val)
{
    if (!search(val))
    {
        if (numInserted >= limInsert())
            return Overload;
        else if (!checkHeight(root(), val, 1))
            return Overheight;
    }

    root() = INSERT(root(), val);
    return Accept;
}

bool BST::checkHeight(Node *Cur, int val, int h)
{
    if (!Cur)
        return true;

    if (h >= limHeight())
        return false;

    if (*Cur->val[0] > val)
        return checkHeight(Cur->Child[Left], val, h + 1);
    else if (*Cur->val[0] < val)
        return checkHeight(Cur->Child[Right], val, h + 1);
    else
        return true;
}

Node *BST::INSERT(Node *Cur, int val)
{
    if (!Cur)
        return newNode(val);

    if (val < *Cur->val[0])
        Cur->Child[Left] = INSERT(Cur->Child[Left], val);
    else if (val > *Cur->val[0])
        Cur->Child[Right] = INSERT(Cur->Child[Right], val);
    else
    {
        (Cur->f)++;
        return Cur;
    }

    Cur->h = 1 + max(Cur->Child[Left]->height(), Cur->Child[Right]->height());
    numInserted++;
    return Cur;
}

Node *BST::minValue(Node *Cur)
{
    Node *Next = Cur;
    while (Next->Child[Left])
        Next = Next->Child[Left];
    return Next;
}

bool BST::remove(int val)
{
    bool check = 0;
    REMOVE(root(), val, check);
    return check;
}

Node *BST::REMOVE(Node *Cur, int val, bool &check)
{
    if (!Cur)
        return Cur;

    if (*Cur->val[0] > val)
        Cur->Child[Left] = REMOVE(Cur->Child[Left], val, check);
    else if (*Cur->val[0] < val)
        Cur->Child[Right] = REMOVE(Cur->Child[Right], val, check);
    else
    {
        if (Cur->f > 1)
        {
            (Cur->f)--;
            return Cur;
        }
        check = 1;
        if (!Cur->Child[Left] || !Cur->Child[Right])
        {
            numInserted--;
            Node *Tmp = (Cur->Child[Left]) ? Cur->Child[Left] : Cur->Child[Right];
            if (!Tmp)
            {
                Tmp = Cur;
                Cur = nullptr;
            }
            else
            {
                Node *Swap = Cur;
                Cur = Tmp;
                Tmp = Swap;
            }
            delete Tmp;
            Tmp = nullptr;
        }
        else
        {
            Node *InOrder = minValue(Cur->Child[Right]); // In_order successor
            *Cur = *InOrder;
            Cur->Child[Right] = REMOVE(Cur->Child[Right], *InOrder->val[0], check);
        }
    }

    if (Cur)
        Cur->h = 1 + max(Cur->Child[Left]->height(), Cur->Child[Right]->height());
    return Cur;
}

const Node *const &BST::search(int val) const
{
    return SEARCH(const_root(), val);
}

const Node *const &BST::SEARCH(const Node *const &Cur, int val) const
{
    if (!Cur)
        return nul();
    if (*Cur->val[0] == val)
        return Cur;

    if (*Cur->val[0] > val)
        return SEARCH(Cur->Child[Left], val);
    else if (*Cur->val[0] < val)
        return SEARCH(Cur->Child[Right], val);
    
    return nul();
}

void BST::display()
{
    print(root());
    std::cerr << '\n';
}

void BST::print(Node *Cur)
{
    if (!Cur)
        return;
    print(Cur->Child[Left]);
    std::cerr << *Cur->val[0];
    if (Cur->f > 1)
        std::cerr << '-' << Cur->f;
    std::cerr << " ";
    print(Cur->Child[Right]);
}

int BST::max(int a, int b)
{
    return (a < b) ? b : a;
}

int &BST::Num()
{
    return numInserted;
}

const int &BST::limHeight()
{
    return limH;
}

const int &BST::limInsert()
{
    return limI;
}