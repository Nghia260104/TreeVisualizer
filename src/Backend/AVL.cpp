#include <AVL.hpp>
#include <iostream>
#include <Execute.hpp>
#include <FrontendGlobal.hpp>
using namespace Backend;

AVL::AVL()
    : BST()
{
    Inc = 0;
    Table = nullptr;
    std::cerr << "Call constructor for AVL Tree\n";
}

AVL::~AVL()
{
    std::cerr << "Call destructor for AVL Tree\n";
}

void AVL::link(Frontend::CircleNode *Table_, int x_, Frontend::Arrow *Arc_)
{
    Table = Table_;
    left_side = x_;
    Arc = Arc_;
}

void AVL::clear()
{
    Tree::clear();
    Num() = 0;
}

BST::Limit AVL::insert(int val)
{
    Inc = 0;
    std::cerr << "Try search for: " << val << '\n';
    if (!trySearch(root(), val))
    {
        std::cerr << "Not found!\n";
        if (Num() >= limInsert())
        {
            std::cerr << "Oversize!\n";
            return Overload;
        }
        else if (!checkHeight(root(), val, 1))
        {
            std::cerr << "Overheight!";
            return Overheight;
        }
    }
    std::cerr << "Insert " << val << "\n";

    std::vector<Status> Tmp;
    for (int i = 0; i < limInsert(); i++)
    {
        Status a;
        a.Node = &Table[i];
        a.hideNode = Table[i].isHidden();
        a.nodeVal = Table[i].getText().getString();
        a.NodeFillColor = Table[i].getFillColor();
        a.NodePosition = Table[i].getPosition();
        a.OutlineColor = Table[i].getOutlineColor();
        a.NodeTextColor = Table[i].getTextColor();
        Tmp.push_back(a);
    }
    for (int i = 0; i < limInsert(); i++)
    {
        Status a;
        a.Arc = &Arc[i];
        a.ArcColor = Arc[i].getFillColor();
        a.hideArc = Arc[i].isHidden();
        a.ArcFirstPosition = Arc[i].getFirstPosition();
        a.ArcSecondPosition = Arc[i].getSecondPosition();
        a.thickness = Arc[i].getThickness();
        Tmp.push_back(a);
    }
    windowHandle.push_back(Tmp);
    root() = INSERT(root(), val, 1);
    std::cerr << "Go out insert for: " << val << '\n';
    Tmp = windowHandle.back();
    for (int i = 0; i < limInsert(); i++)
    {
        Tmp[i].NodeFillColor = BackgroundColor;
        Tmp[i].OutlineColor = TextColor;
        Tmp[i].NodeTextColor = TextColor;
    }
    for (int i = 0; i < limInsert(); i++)
    {
        Tmp[i + limInsert()].ArcColor = TextColor;
        Tmp[i + limInsert()].thickness = 0.1f * g_radius;
    }
    windowHandle.push_back(Tmp);
    return Accept;
}

void AVL::insertWithOrder(int val)
{
    Inc = 0;
    std::cerr << "Insert " << val << "\n";

    std::vector<Status> Tmp;
    for (int i = 0; i < limInsert(); i++)
    {
        Status a;
        a.Node = &Table[i];
        a.hideNode = Table[i].isHidden();
        a.nodeVal = Table[i].getText().getString();
        a.NodeFillColor = Table[i].getFillColor();
        a.NodePosition = Table[i].getPosition();
        a.OutlineColor = Table[i].getOutlineColor();
        a.NodeTextColor = Table[i].getTextColor();
        Tmp.push_back(a);
    }
    for (int i = 0; i < limInsert(); i++)
    {
        Status a;
        a.Arc = &Arc[i];
        a.ArcColor = Arc[i].getFillColor();
        a.hideArc = Arc[i].isHidden();
        a.ArcFirstPosition = Arc[i].getFirstPosition();
        a.ArcSecondPosition = Arc[i].getSecondPosition();
        a.thickness = Arc[i].getThickness();
        Tmp.push_back(a);
    }
    windowHandle.push_back(Tmp);
    root() = INSERT(root(), val, 0);
    std::cerr << "Go out insert for: " << val << '\n';
    Tmp = windowHandle.back();
    for (int i = 0; i < limInsert(); i++)
    {
        Tmp[i].NodeFillColor = BackgroundColor;
        Tmp[i].OutlineColor = TextColor;
        Tmp[i].NodeTextColor = TextColor;
    }
    for (int i = 0; i < limInsert(); i++)
    {
        Tmp[i + limInsert()].ArcColor = TextColor;
        Tmp[i + limInsert()].thickness = 0.1f * g_radius;
    }
    windowHandle.push_back(Tmp);
}

Node *AVL::INSERT(Node *Cur, int val, bool rotate)
{
    // std::vector<Status> Tmp;
    std::vector<Status> Tmp = windowHandle.back();
    for (int i = 0; i < limInsert(); i++)
    {
        if (Tmp[i].NodeFillColor == Highlight)
        {
            Tmp[i].NodeFillColor = BackgroundColor;
            Tmp[i].NodeTextColor = Highlight;
            Tmp[i + limInsert()].thickness = 0.1f * g_radius;
            break;
        }
    }
    if (!Cur)
    {
        std::cerr << "NULL -> Create new Node\n";
        Node *New = newNode(val);
        New->Cur = &Table[Num()];
        if (Num() == 0)
            Tmp[Num()].NodePosition = sf::Vector2f(window.getSize().x / 2, upper_edge);
        Tmp[Num()].NodeFillColor = Highlight;
        Tmp[Num()].OutlineColor = Highlight;
        Tmp[Num()].NodeTextColor = BackgroundColor;
        Tmp[Num()].hideNode = 0;
        Tmp[Num()].nodeVal = std::to_string(val);
        if (Num() != 0)
        {
            Tmp[Num() + limInsert()].hideArc = 0;
            Tmp[Num() + limInsert()].ArcColor = Highlight;
            Tmp[Num() + limInsert()].thickness = 0.2f * g_radius;
        }
        windowHandle.push_back(Tmp);
        Num()++;
        Inc = 1;
        return New;
    }

    int cur_id;
    for (int i = 0; i < limInsert(); i++)
        if (Tmp[i].Node == Cur->Cur)
        {
            cur_id = i;
            Tmp[i].NodeFillColor = Highlight;
            Tmp[i].OutlineColor = Highlight;
            Tmp[i].NodeTextColor = BackgroundColor;
            if (Cur != root())
            {
                Tmp[i + limInsert()].ArcColor = Highlight;
                Tmp[i + limInsert()].thickness = 0.2f * g_radius;
            }
            break;
        }
    windowHandle.push_back(Tmp);
    std::cerr << "Current Node value: " << Cur->val[0] << '\n';

    if (val < Cur->val[0])
    {
        std::cerr << "Go left\n";
        Cur->Child[Left] = INSERT(Cur->Child[Left], val, rotate);
        std::cerr << "Go up\n";
        if (Inc)
        {
            Cur->Child[Left]->Par = Cur;
            Inc = 0;
            int order = 0;
            setPosition(root(), 0, order, windowHandle.back());
            setArcPosition(root(), windowHandle.back());
        }
    }
    else if (val > Cur->val[0])
    {
        std::cerr << "Go right\n";
        Cur->Child[Right] = INSERT(Cur->Child[Right], val, rotate);
        std::cerr << "Go up\n";
        if (Inc)
        {
            Cur->Child[Right]->Par = Cur;
            Inc = 0;
            int order = 0;
            setPosition(root(), 0, order, windowHandle.back());
            setArcPosition(root(), windowHandle.back());
        }
    }
    else
    {
        if (Cur->f < 9)
        {
            (Cur->f)++;
            Tmp[cur_id].nodeVal = std::to_string(Cur->val[0]) + "-" + std::to_string(Cur->f);
            windowHandle.push_back(Tmp);
        }
        return Cur;
    }

    // Recalculate height
    Tmp = windowHandle.back();
    std::cerr << "Recalculate height of Current\n";
    Cur->h = 1 + max(Cur->Child[Left]->height(), Cur->Child[Right]->height());
    if (rotate)
    {
        std::cerr << "Rotation\n";

        for (int i = 0; i < limInsert(); i++)
        {
            if (i == cur_id)
            {
                Tmp[i].NodeFillColor = Highlight;
                Tmp[i].OutlineColor = Highlight;
                Tmp[i].NodeTextColor = BackgroundColor;
            }
            else
            {
                Tmp[i].NodeFillColor = BackgroundColor;
                Tmp[i].OutlineColor = TextColor;
                Tmp[i].NodeTextColor = TextColor;
            }
            Tmp[i + limInsert()].ArcColor = TextColor;
            Tmp[i + limInsert()].thickness = 0.1f * g_radius;
        }
        windowHandle.push_back(Tmp);

        std::cerr << "Get balance factor ...\n";
        int bf = getBalance(Cur);
        std::cerr << "Balance factor: " << bf << '\n';
        std::cerr << "Check right rotate\n";
        if (bf > 1 && val < Cur->Child[Left]->val[0])
        {
            std::cerr << "Right rotate\n";
            // Node *Par = Cur->Par;
            Node *Child = rightRotate(Cur, Tmp);
            // if (Par->Child[Left] == Cur)
            //     Par->Child[Left] = Child;
            // else
            //     Par->Child[Right] = Child;

            // int order = 0;
            // setPosition(root(), 0, order, Tmp);
            // setArcPosition(root(), Tmp);

            // windowHandle.push_back(Tmp);
            return Child;
        }
        std::cerr << "Check left rotate\n";
        if (bf < -1 && val > Cur->Child[Right]->val[0])
        {
            std::cerr << "Left rotate\n";
            // Node *Par = Cur->Par;
            Node *Child = leftRotate(Cur, Tmp);
            // if (Par->Child[Left] == Cur)
            //     Par->Child[Left] = Child;
            // else
            //     Par->Child[Right] = Child;
            // int order = 0;
            // setPosition(root(), 0, order, Tmp);
            // setArcPosition(root(), Tmp);

            // windowHandle.push_back(Tmp);
            return Child;
        }
        std::cerr << "Check left-right rotate\n";
        if (bf > 1 && val > Cur->Child[Left]->val[0])
        {
            std::cerr << "Left-right rotate\n";
            Cur->Child[Left] = leftRotate(Cur->Child[Left], Tmp);
            return rightRotate(Cur, Tmp);
        }
        std::cerr << "Check right-left rotate\n";
        if (bf < -1 && val < Cur->Child[Right]->val[0])
        {
            std::cerr << "Right-left rotate\n";
            Cur->Child[Right] = rightRotate(Cur->Child[Right], Tmp);
            return leftRotate(Cur, Tmp);
        }
        std::cerr << "Return current Node\n";
    }
    return Cur;
}

bool AVL::remove(int val)
{
    bool check = 0;
    std::vector<Status> Tmp;
    for (int i = 0; i < limInsert(); i++)
    {
        Status a;
        a.Node = &Table[i];
        a.hideNode = Table[i].isHidden();
        a.nodeVal = Table[i].getText().getString();
        a.NodeFillColor = Table[i].getFillColor();
        a.NodePosition = Table[i].getPosition();
        a.OutlineColor = Table[i].getOutlineColor();
        a.NodeTextColor = Table[i].getTextColor();
        Tmp.push_back(a);
    }
    for (int i = 0; i < limInsert(); i++)
    {
        Status a;
        a.Arc = &Arc[i];
        a.ArcColor = Arc[i].getFillColor();
        a.hideArc = Arc[i].isHidden();
        a.ArcFirstPosition = Arc[i].getFirstPosition();
        a.ArcSecondPosition = Arc[i].getSecondPosition();
        a.thickness = Arc[i].getThickness();
        Tmp.push_back(a);
    }
    windowHandle.push_back(Tmp);
    REMOVE(root(), val, check);
    Tmp = windowHandle.back();
    for (int i = 0; i < limInsert(); i++)
    {
        Tmp[i].NodeFillColor = BackgroundColor;
        Tmp[i].OutlineColor = TextColor;
        Tmp[i].NodeTextColor = TextColor;
    }
    for (int i = 0; i < limInsert(); i++)
    {
        Tmp[i + limInsert()].ArcColor = TextColor;
        Tmp[i + limInsert()].thickness = 0.1f * g_radius;
    }
    windowHandle.push_back(Tmp);
    return check;
}

Node *AVL::REMOVE(Node *Cur, int val, bool &check)
{
    std::vector<Status> Tmp = windowHandle.back();
    for (int i = 0; i < limInsert(); i++)
    {
        if (Tmp[i].NodeFillColor == Highlight)
        {
            Tmp[i].NodeFillColor = BackgroundColor;
            Tmp[i].NodeTextColor = Highlight;
            Tmp[i + limInsert()].thickness = 0.1f * g_radius;
            break;
        }
    }
    if (!Cur)
        return Cur;

    int cur_id;
    for (int i = 0; i < limInsert(); i++)
        if (Tmp[i].Node == Cur->Cur)
        {
            cur_id = i;
            Tmp[i].NodeFillColor = Highlight;
            Tmp[i].OutlineColor = Highlight;
            Tmp[i].NodeTextColor = BackgroundColor;
            if (Cur != root())
            {
                Tmp[i + limInsert()].ArcColor = Highlight;
                Tmp[i + limInsert()].thickness = 0.2f * g_radius;
            }
            break;
        }
    windowHandle.push_back(Tmp);

    if (Cur->val[0] > val)
        Cur->Child[Left] = REMOVE(Cur->Child[Left], val, check);
    else if (Cur->val[0] < val)
        Cur->Child[Right] = REMOVE(Cur->Child[Right], val, check);
    else
    {
        if (Cur->f > 1)
        {
            (Cur->f)--;
            if (Cur->f > 1)
                Tmp[cur_id].nodeVal = std::to_string(Cur->val[0]) + "-" + std::to_string(Cur->f);
            else
                Tmp[cur_id].nodeVal = std::to_string(Cur->val[0]);
            windowHandle.push_back(Tmp);
            return Cur;
        }
        check = 1;
        Num()--;
        if (!Cur->Child[Left] || !Cur->Child[Right])
        {
            Node *temp_node = (Cur->Child[Left]) ? Cur->Child[Left] : Cur->Child[Right];
            Node *Par = Cur->Par;
            if (!temp_node)
            {
                temp_node = Cur;
                if (Par)
                {
                    if (Par->Child[Left] == Cur)
                        Par->Child[Left] = nullptr;
                    else
                        Par->Child[Right] = nullptr;
                }
                Cur = nullptr;
            }
            else
            {
                Node *Swap = Cur;
                Cur = temp_node;
                temp_node = Swap;
                Cur->Par = Par;
                if (Par)
                {
                    if (Par->Child[Left] == temp_node)
                        Par->Child[Left] = Cur;
                    else
                        Par->Child[Right] = Cur;
                }
            }
            Tmp[cur_id].hideNode = 1;
            Tmp[cur_id + limInsert()].hideArc = 1;
            delete temp_node;
            temp_node = nullptr;
            int order = 0;
            if (Num() == 1)
            {
                for (int i = 0; i < limInsert(); i++)
                {
                    if (Tmp[i].Node == root()->Cur)
                    {
                        Tmp[i].NodePosition = sf::Vector2f(window.getSize().x / 2, upper_edge);
                        break;
                    }
                }
            }
            else if (Num() > 1)
            {
                setPosition(root(), 0, order, Tmp);
                setArcPosition(root(), Tmp);
            }
            windowHandle.push_back(Tmp);
            return Cur;
        }
        else
        {
            Node *InOrder = minValue(Cur->Child[Right]); // In_order successor
            for (int i = 0; i < limInsert(); i++)
                if (Tmp[i].Node == InOrder->Cur)
                {
                    Tmp[i].NodeFillColor = Highlight;
                    Tmp[i].OutlineColor = Highlight;
                    Tmp[i].NodeTextColor = BackgroundColor;
                    break;
                }
            windowHandle.push_back(Tmp);
            Cur->val = InOrder->val;
            Cur->f = InOrder->f;
            if (Cur->f > 1)
            {
                Tmp[cur_id].nodeVal = std::to_string(Cur->val[0]) + "-" + std::to_string(Cur->f);
                InOrder->f = 1;
            }
            else
                Tmp[cur_id].nodeVal = std::to_string(Cur->val[0]);
            windowHandle.push_back(Tmp);
            for (int i = 0; i < limInsert(); i++)
            {
                if (i != cur_id)
                {
                    Tmp[i].NodeFillColor = BackgroundColor;
                    Tmp[i].OutlineColor = TextColor;
                    Tmp[i].NodeTextColor = TextColor;
                }
                Tmp[i + limInsert()].ArcColor = TextColor;
                Tmp[i + limInsert()].thickness = 0.1f * g_radius;
            }
            windowHandle.push_back(Tmp);
            Cur->Child[Right] = REMOVE(Cur->Child[Right], InOrder->val[0], check);
        }
    }

    if (!Cur)
        return Cur;
    Tmp = windowHandle.back();
    Cur->h = 1 + max(Cur->Child[Left]->height(), Cur->Child[Right]->height());

    for (int i = 0; i < limInsert(); i++)
    {
        if (i == cur_id)
        {
            Tmp[i].NodeFillColor = Highlight;
            Tmp[i].OutlineColor = Highlight;
            Tmp[i].NodeTextColor = BackgroundColor;
        }
        else
        {
            Tmp[i].NodeFillColor = BackgroundColor;
            Tmp[i].OutlineColor = TextColor;
            Tmp[i].NodeTextColor = TextColor;
        }
        Tmp[i + limInsert()].ArcColor = TextColor;
        Tmp[i + limInsert()].thickness = 0.1f * g_radius;
    }
    windowHandle.push_back(Tmp);

    int bf = getBalance(Cur);
    if (bf > 1 &&
        getBalance(Cur->Child[Left]) >= 0)
        return rightRotate(Cur, Tmp);
    if (bf < -1 &&
        getBalance(Cur->Child[Right]) <= 0)
        return leftRotate(Cur, Tmp);
    if (bf > 1 &&
        getBalance(Cur->Child[Left]) < 0)
    {
        Cur->Child[Left] = leftRotate(Cur->Child[Left], Tmp);
        return rightRotate(Cur, Tmp);
    }
    if (bf < -1 &&
        getBalance(Cur->Child[Right]) > 0)
    {
        Cur->Child[Right] = rightRotate(Cur->Child[Right], Tmp);
        return leftRotate(Cur, Tmp);
    }
    return Cur;
}

const Node *const &AVL::search(int val)
{
    std::vector<Status> Tmp;
    for (int i = 0; i < limInsert(); i++)
    {
        Status a;
        a.Node = &Table[i];
        a.hideNode = Table[i].isHidden();
        a.nodeVal = Table[i].getText().getString();
        a.NodeFillColor = Table[i].getFillColor();
        a.NodePosition = Table[i].getPosition();
        a.OutlineColor = Table[i].getOutlineColor();
        a.NodeTextColor = Table[i].getTextColor();
        Tmp.push_back(a);
    }
    for (int i = 0; i < limInsert(); i++)
    {
        Status a;
        a.Arc = &Arc[i];
        a.ArcColor = Arc[i].getFillColor();
        a.hideArc = Arc[i].isHidden();
        a.ArcFirstPosition = Arc[i].getFirstPosition();
        a.ArcSecondPosition = Arc[i].getSecondPosition();
        a.thickness = Arc[i].getThickness();
        Tmp.push_back(a);
    }
    windowHandle.push_back(Tmp);
    return SEARCH(const_root(), val);
    Tmp = windowHandle.back();
    for (int i = 0; i < limInsert(); i++)
    {
        Tmp[i].NodeFillColor = BackgroundColor;
        Tmp[i].OutlineColor = TextColor;
        Tmp[i].NodeTextColor = TextColor;
    }
    for (int i = 0; i < limInsert(); i++)
    {
        Tmp[i + limInsert()].ArcColor = TextColor;
        Tmp[i + limInsert()].thickness = 0.1f * g_radius;
    }
    windowHandle.push_back(Tmp);
}

const Node *const &AVL::trySearch(const Node *const &Cur, int val)
{
    if (!Cur)
        return nul();
    if (Cur->val[0] == val)
        return Cur;

    if (Cur->val[0] > val)
        return trySearch(Cur->Child[Left], val);
    else if (Cur->val[0] < val)
        return trySearch(Cur->Child[Right], val);

    return nul();
}

const Node *const &AVL::SEARCH(const Node *const &Cur, int val)
{
    if (!Cur)
        return nul();
    std::vector<Status> Tmp = windowHandle.back();
    for (int i = 0; i < limInsert(); i++)
    {
        if (Tmp[i].NodeFillColor == Highlight)
        {
            Tmp[i].NodeFillColor = BackgroundColor;
            Tmp[i].NodeTextColor = Highlight;
            Tmp[i + limInsert()].thickness = 0.1f * g_radius;
            break;
        }
    }
    for (int i = 0; i < limInsert(); i++)
        if (Tmp[i].Node == Cur->Cur)
        {
            Tmp[i].NodeFillColor = Highlight;
            Tmp[i].OutlineColor = Highlight;
            Tmp[i].NodeTextColor = BackgroundColor;
            if (Cur != root())
            {
                Tmp[i + limInsert()].ArcColor = Highlight;
                Tmp[i + limInsert()].thickness = 0.2f * g_radius;
            }
            break;
        }
    windowHandle.push_back(Tmp);
    if (Cur->val[0] == val)
        return Cur;

    if (Cur->val[0] > val)
        return SEARCH(Cur->Child[Left], val);
    else if (Cur->val[0] < val)
        return SEARCH(Cur->Child[Right], val);

    return nul();
}

// Private /////////////////////////////////////////////////////////////////////////////////

int AVL::getBalance(Node *Cur)
{
    if (!Cur)
        return 0;
    return (Cur->Child[Left]->height() -
            Cur->Child[Right]->height());
}

Node *AVL::leftRotate(Node *Cur, std::vector<Status> &Tmp)
{
    // Initialize
    Node *x = Cur->Child[Right];
    Node *y = x->Child[Left];
    Node *Par = Cur->Par;
    int dir = 0;
    if (Par)
    {
        if (Par->Child[Left] == Cur)
            dir = Left;
        else
            dir = Right;
    }

    int cur_id, x_id, y_id = -1, cur_par_id = -1;
    for (int i = 0; i < limInsert(); i++)
    {
        if (Tmp[i].Node == Cur->Cur)
            cur_id = i;
        if (Tmp[i].Node == x->Cur)
            x_id = i;
        if (y && Tmp[i].Node == y->Cur)
            y_id = i;
        if (Cur->Par && Tmp[i].Node == Cur->Par->Cur)
            cur_par_id = i;
    }

    // Rotation

    Tmp[x_id].NodeFillColor = Highlight;
    Tmp[x_id].OutlineColor = Highlight;
    Tmp[x_id].NodeTextColor = BackgroundColor;
    Tmp[cur_id + limInsert()].ArcSecondPosition = Tmp[x_id].NodePosition;
    Tmp[cur_id + limInsert()].ArcColor = Highlight;
    Tmp[cur_id + limInsert()].thickness = 0.2f * g_radius;
    Tmp[cur_id + limInsert()].hideArc = 0;
    if (y_id != -1)
    {
        Tmp[y_id].NodeFillColor = Highlight;
        Tmp[y_id].OutlineColor = Highlight;
        Tmp[y_id].NodeTextColor = BackgroundColor;
        Tmp[y_id + limInsert()].ArcSecondPosition = Tmp[cur_id].NodePosition;
        Tmp[y_id + limInsert()].ArcColor = Highlight;
        Tmp[y_id + limInsert()].thickness = 0.2f * g_radius;
    }
    if (cur_par_id != -1)
    {
        Tmp[x_id + limInsert()].ArcSecondPosition = Tmp[cur_par_id].NodePosition;
        Tmp[x_id + limInsert()].ArcColor = Highlight;
        Tmp[x_id + limInsert()].thickness = 0.2f * g_radius;
    }
    else
        Tmp[x_id + limInsert()].hideArc;

    windowHandle.push_back(Tmp);

    x->Child[Left] = Cur;
    x->Par = Par;
    Cur->Par = x;
    Cur->Child[Right] = y;
    if (y)
        y->Par = Cur;
    if (Par)
        Par->Child[dir] = x;

    int order = 0;
    setPosition(root(), 0, order, Tmp);
    setArcPosition(root(), Tmp);

    windowHandle.push_back(Tmp);

    // Recalculate the height
    Cur->h = 1 + max(Cur->Child[Left]->height(),
                     Cur->Child[Right]->height());
    x->h = 1 + max(x->Child[Left]->height(),
                   x->Child[Right]->height());

    return x;
}

Node *AVL::rightRotate(Node *Cur, std::vector<Status> &Tmp)
{
    // Initialize
    Node *x = Cur->Child[Left];
    Node *y = x->Child[Right];
    Node *Par = Cur->Par;
    int dir = 0;
    if (Par)
    {
        if (Par->Child[Left] == Cur)
            dir = Left;
        else
            dir = Right;
    }

    int cur_id, x_id, y_id = -1, cur_par_id = -1;
    for (int i = 0; i < limInsert(); i++)
    {
        if (Tmp[i].Node == Cur->Cur)
            cur_id = i;
        if (Tmp[i].Node == x->Cur)
            x_id = i;
        if (y && Tmp[i].Node == y->Cur)
            y_id = i;
        if (Cur->Par && Tmp[i].Node == Cur->Par->Cur)
            cur_par_id = i;
    }

    // Rotation

    Tmp[x_id].NodeFillColor = Highlight;
    Tmp[x_id].OutlineColor = Highlight;
    Tmp[x_id].NodeTextColor = BackgroundColor;
    Tmp[cur_id + limInsert()].ArcSecondPosition = Tmp[x_id].NodePosition;
    Tmp[cur_id + limInsert()].ArcColor = Highlight;
    Tmp[cur_id + limInsert()].thickness = 0.2f * g_radius;
    Tmp[cur_id + limInsert()].hideArc = 0;
    if (y_id != -1)
    {
        Tmp[y_id].NodeFillColor = Highlight;
        Tmp[y_id].OutlineColor = Highlight;
        Tmp[y_id].NodeTextColor = BackgroundColor;
        Tmp[y_id + limInsert()].ArcSecondPosition = Tmp[cur_id].NodePosition;
        Tmp[y_id + limInsert()].ArcColor = Highlight;
        Tmp[y_id + limInsert()].thickness = 0.2f * g_radius;
    }
    if (cur_par_id != -1)
    {
        Tmp[x_id + limInsert()].ArcSecondPosition = Tmp[cur_par_id].NodePosition;
        Tmp[x_id + limInsert()].ArcColor = Highlight;
        Tmp[x_id + limInsert()].thickness = 0.2f * g_radius;
    }
    else
        Tmp[x_id + limInsert()].hideArc;
    windowHandle.push_back(Tmp);

    x->Child[Right] = Cur;
    x->Par = Par;
    Cur->Par = x;
    Cur->Child[Left] = y;
    if (y)
        y->Par = Cur;
    if (Par)
        Par->Child[dir] = x;

    int order = 0;
    setPosition(root(), 0, order, Tmp);
    setArcPosition(root(), Tmp);

    windowHandle.push_back(Tmp);

    // Recalculate the height
    Cur->h = 1 + max(Cur->Child[Left]->height(),
                     Cur->Child[Right]->height());
    x->h = 1 + max(x->Child[Left]->height(),
                   x->Child[Right]->height());

    return x;
}

void AVL::setPosition(Node *Cur, int h, int &order, std::vector<Status> &x)
{
    if (!Cur)
        return;

    setPosition(Cur->Child[Left], h + 1, order, x);
    for (int i = 0; i < limInsert(); i++)
        if (x[i].Node == Cur->Cur)
        {
            x[i].NodePosition = sf::Vector2f(window.getSize().x / 2 + (order - Num() / 2) * __min(400, range / Num()), upper_edge + h * distance);
            break;
        }
    Cur->x = order;
    Cur->y = h;
    order++;
    setPosition(Cur->Child[Right], h + 1, order, x);
}

void AVL::setArcPosition(Node *Cur, std::vector<Status> &x)
{
    if (!Cur)
        return;

    setArcPosition(Cur->Child[Left], x);
    if (Cur != root())
        for (int i = 0; i < limInsert(); i++)
            if (x[i].Node == Cur->Cur)
            {
                x[i + limInsert()].ArcSecondPosition = sf::Vector2f(window.getSize().x / 2 + (Cur->Par->x - Num() / 2) * __min(400, range / Num()), upper_edge + Cur->Par->y * distance);
                x[i + limInsert()].ArcFirstPosition = sf::Vector2f(window.getSize().x / 2 + (Cur->x - Num() / 2) * __min(400, range / Num()), upper_edge + Cur->y * distance);
                break;
            }
    setArcPosition(Cur->Child[Right], x);
}

std::vector<Status> AVL::getResetStatus()
{
}