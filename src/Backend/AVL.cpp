#include <AVL.hpp>
#include <iostream>
using namespace Backend;

AVL::AVL()
    : BST()
{
    std::cerr << "Call constructor for AVL Tree\n";
}

AVL::~AVL()
{
    std::cerr << "Call destructor for AVL Tree\n";
}

BST::Limit AVL::insert(int val)
{
    if (!search(val))
    {
        if (Num() >= limInsert())
            return Overload;
        else if (!checkHeight(root(), val, 1))
            return Overheight;
    }

    root() = INSERT(root(), val);
    return Accept;
}

Node *AVL::INSERT(Node *Cur, int val)
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
    Num()++;

    int bf = getBalance(Cur);
    if (bf > 1 && val < *Cur->Child[Left]->val[0])
        return rightRotate(Cur);
    if (bf < -1 && val > *Cur->Child[Right]->val[0])
        return leftRotate(Cur);
    if (bf > 1 && val > *Cur->Child[Left]->val[0])
    {
        Cur->Child[Left] = leftRotate(Cur->Child[Left]);
        return rightRotate(Cur);
    }
    if (bf < -1 && val < *Cur->Child[Right]->val[0])
    {
        Cur->Child[Right] = rightRotate(Cur->Child[Right]);
        return leftRotate(Cur);
    }
    return Cur;
}

bool AVL::remove(int val)
{
    bool check = 0;
    REMOVE(root(), val, check);
    return check;
}

Node *AVL::REMOVE(Node *Cur, int val, bool &check)
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
            Num()--;
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

    if (!Cur)
        return Cur;
    Cur->h = 1 + max(Cur->Child[Left]->height(), Cur->Child[Right]->height());

    int bf = getBalance(Cur);
    if (bf > 1 &&
        getBalance(Cur->Child[Left]) >= 0)
        return rightRotate(Cur);
    if (bf < -1 &&
        getBalance(Cur->Child[Right]) <= 0)
        return leftRotate(Cur);
    if (bf > 1 &&
        getBalance(Cur->Child[Left]) < 0)
    {
        Cur->Child[Left] = leftRotate(Cur->Child[Left]);
        return rightRotate(Cur);
    }
    if (bf < -1 &&
        getBalance(Cur->Child[Right]) > 0)
    {
        Cur->Child[Right] = rightRotate(Cur->Child[Right]);
        return leftRotate(Cur);
    }
    return Cur;
}

// Private /////////////////////////////////////////////////////////////////////////////////

int AVL::getBalance(Node *Cur)
{
    if (!Cur)
        return 0;
    return (Cur->Child[Left]->height() -
            Cur->Child[Right]->height());
}

Node *AVL::leftRotate(Node *Cur)
{
    // Initialize
    Node *x = Cur->Child[Right];
    Node *y = x->Child[Left];

    // Rotation
    x->Child[Left] = Cur;
    Cur->Child[Right] = y;

    // Recalculate the height
    Cur->h = 1 + max(Cur->Child[Left]->height(),
                     Cur->Child[Right]->height());
    x->h = 1 + max(x->Child[Left]->height(),
                   x->Child[Right]->height());

    return x;
}

Node *AVL::rightRotate(Node *Cur)
{
    // Initialize
    Node *x = Cur->Child[Left];
    Node *y = x->Child[Right];

    // Rotation
    x->Child[Right] = Cur;
    Cur->Child[Left] = y;

    // Recalculate the height
    Cur->h = 1 + max(Cur->Child[Left]->height(),
                     Cur->Child[Right]->height());
    x->h = 1 + max(x->Child[Left]->height(),
                   x->Child[Right]->height());

    return x;
}