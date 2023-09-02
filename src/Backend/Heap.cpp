#include <Heap.hpp>
#include <iostream>
#include <cmath>
#include <Status.hpp>
#include <FrontendGlobal.hpp>
using namespace Backend;

Heap::Heap()
    : Tree()
{
    size = 0;
}

Heap::~Heap()
{
    std::cerr << "Call destructor for Heap\n";
}

const int Heap::MAX_INT()
{
    return MAX;
}

const int Heap::MIN_INT()
{
    return MIN;
}

Node *Heap::newNode(int val)
{
    return new Node({val}, 1, 2);
}

void Heap::link(Frontend::CircleNode *Table_, Frontend::Arrow *Arc_)
{
    Table = Table_;
    Arc = Arc_;
}

Node *Heap::operator[](int index)
{
    if (!size)
        return nullptr;
    index = (index - 1) % size + 1;
    std::vector<Status> Tmp;
    if (!windowHandle.size())
    {
        for (int i = 0; i <= lim; i++)
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
        for (int i = 0; i <= lim; i++)
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
    }
    else
        Tmp = windowHandle.back();
    int it = log2(index);
    while (!(index & mask))
        index <<= 1;
    Node *Cur = root();
    Tmp[1].NodeFillColor = Highlight;
    Tmp[1].NodeTextColor = BackgroundColor;
    Tmp[1].OutlineColor = Highlight;
    windowHandle.push_back(Tmp);
    int vs_id = 1;
    for (int a = 0; a < it; a++)
    {
        Tmp = windowHandle.back();
        for (int i = 0; i <= lim; i++)
        {
            if (Tmp[i].NodeFillColor == Highlight)
            {
                Tmp[i].NodeFillColor = BackgroundColor;
                Tmp[i].NodeTextColor = Highlight;
                Tmp[i + lim + 1].thickness = 0.1f * g_radius;
                break;
            }
        }
        index <<= 1;
        vs_id = 2 * vs_id + (bool)(index & mask);
        Cur = Cur->Child[(bool)(index & mask)];
        Tmp[vs_id].NodeFillColor = Highlight;
        Tmp[vs_id].NodeTextColor = BackgroundColor;
        Tmp[vs_id].OutlineColor = Highlight;
        Tmp[vs_id + lim + 1].ArcColor = Highlight;
        Tmp[vs_id + lim + 1].thickness = 0.2f * g_radius;
        windowHandle.push_back(Tmp);
    }
    std::cerr << "Get *this[id] = " << Cur << "\n";
    return Cur;
}

bool Heap::Cmp(int x, int y, Type t)
{
    if (t == Max)
        return x > y;
    else
        return x <= y;
}

void Heap::swap(Node *x, Node *y)
{
    int val = x->val[0];
    x->val[0] = y->val[0];
    y->val[0] = val;
}

void Heap::ShiftUp(Node *Cur, Type t, std::vector<Status> &Tmp)
{
    while (Cur != root())
    {
        // std::cerr << Cur << " " << Cur->Par << "\n";
        int cur_id, par_id;
        for (int i = 1; i <= lim; i++)
        {
            Tmp[i].NormalNode();
            Tmp[i + lim + 1].NormalArc();
            if (Tmp[i].Node == Cur->Cur)
            {
                cur_id = i;
                Tmp[i].highlightNode();
            }
            if (Tmp[i].Node == Cur->Par->Cur)
            {
                par_id = i;
                Tmp[i].highlightNode();
            }
        }
        windowHandle.push_back(Tmp);
        if (Cmp(Cur->val[0], Cur->Par->val[0], t))
        {
            Tmp[cur_id + lim + 1].highlightArc();
            windowHandle.push_back(Tmp);
            Tmp[cur_id].nodeVal = std::to_string(Cur->Par->val[0]);
            Tmp[par_id].nodeVal = std::to_string(Cur->val[0]);
            windowHandle.push_back(Tmp);
            // std::cerr << "Swap Cur and Par\n";
            swap(Cur, Cur->Par);
            Cur = Cur->Par;
        }
        else
            break;
    }
    for (int i = 0; i <= lim; i++)
    {
        Tmp[i].NormalNode();
        Tmp[i + lim + 1].NormalArc();
    }
    windowHandle.push_back(Tmp);
}

void Heap::ShiftDown(Node *Cur, Type t, std::vector<Status> &Tmp)
{
    Node *Root = Cur;
    Node *l = Cur->Child[Left];
    Node *r = Cur->Child[Right];

    if (l && Cmp(l->val[0], Cur->val[0], t))
        Cur = l;
    if (r && Cmp(r->val[0], Cur->val[0], t))
        Cur = r;
    if (Cur != Root)
    {
        int cur_id, l_id = -1, r_id = -1;
        for (int i = 0; i <= lim; i++)
        {
            Tmp[i].NormalNode();
            Tmp[i + lim + 1].NormalArc();
            if (Tmp[i].Node == Root->Cur)
            {
                cur_id = i;
                Tmp[i].highlightNode();
            }
            if (l && Tmp[i].Node == l->Cur)
            {
                l_id = i;
                Tmp[i].highlightNode();
            }
            if (r && Tmp[i].Node == r->Cur)
            {
                r_id = i;
                Tmp[i].highlightNode();
            }
        }
        windowHandle.push_back(Tmp);
        if (Cur == l)
            Tmp[l_id + lim + 1].highlightArc();
        else
            Tmp[r_id + lim + 1].highlightArc();
        windowHandle.push_back(Tmp);
        if (Cur == l)
            Tmp[l_id].nodeVal = std::to_string(Root->val[0]);
        else Tmp[r_id].nodeVal = std::to_string(Root->val[0]);
        Tmp[cur_id].nodeVal = std::to_string(Cur->val[0]);
        windowHandle.push_back(Tmp);
        swap(Cur, Root);
        ShiftDown(Cur, t, Tmp);
    }
    else
    {
        for (int i = 0; i <= lim; i++)
        {
            Tmp[i].NormalNode();
            Tmp[i + lim + 1].NormalArc();
        }
        windowHandle.push_back(Tmp);
    }
}

bool Heap::INSERT(int val, Type t)
{
    if (size == lim)
        return false;
    std::vector<Status> Tmp;
    for (int i = 0; i <= lim; i++)
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
    for (int i = 0; i <= lim; i++)
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
    size++;
    int id = size;
    while (!(id & mask))
        id <<= 1;
    id <<= 1;
    int vs_id = 1;

    Node *Par = nullptr, *Cur = root();
    while (Cur)
    {
        for (int i = 0; i <= lim; i++)
            if (Tmp[i].NodeFillColor == Highlight)
            {
                Tmp[i].NodeOnPath();
                Tmp[i + lim + 1].ArcOnPath();
                break;
            }
        Tmp[vs_id].NodeFillColor = Highlight;
        Tmp[vs_id].OutlineColor = Highlight;
        Tmp[vs_id].NodeTextColor = BackgroundColor;
        Tmp[vs_id + lim + 1].ArcColor = Highlight;
        Tmp[vs_id + lim + 1].thickness = 0.2f * g_radius;
        windowHandle.push_back(Tmp);
        if (Cmp(val, Cur->val[0], t))
        {
            Tmp[vs_id].nodeVal = std::to_string(val);
            int Tmp_val = Cur->val[0];
            Cur->val[0] = val;
            val = Tmp_val;
            windowHandle.push_back(Tmp);
        }
        Par = Cur;

        vs_id = 2 * vs_id + (bool)(id & mask);
        Cur = Cur->Child[(bool)(id & mask)];
        if (Cur)
            id <<= 1;
    }
    for (int i = 0; i <= lim; i++)
        if (Tmp[i].NodeFillColor == Highlight)
        {
            Tmp[i].NodeOnPath();
            Tmp[i + lim + 1].ArcOnPath();
            break;
        }
    Node *New = newNode(val);
    New->Par = Par;
    New->Cur = &Table[size];
    Tmp[size].NodeFillColor = Highlight;
    Tmp[size].NodeTextColor = BackgroundColor;
    Tmp[size].OutlineColor = Highlight;
    Tmp[size].nodeVal = std::to_string(val);
    Tmp[size].hideNode = 0;

    if (!Par)
    {
        root() = New;
        Tmp[size].NodePosition = sf::Vector2f(window.getSize().x / 2, upper_edge);
    }
    else
    {
        Tmp[size + lim + 1].hideArc = 0;
        Tmp[size + lim + 1].ArcColor = Highlight;
        Tmp[size + lim + 1].thickness = 0.2f * g_radius;
        Par->Child[(bool)(id & mask)] = New;
        int order = 0;
        setPosition(root(), 0, order, Tmp);
        setArcPosition(root(), Tmp);
    }
    windowHandle.push_back(Tmp);
    for (int i = 0; i <= lim; i++)
    {
        Tmp[i].NodeFillColor = BackgroundColor;
        Tmp[i].OutlineColor = TextColor;
        Tmp[i].NodeTextColor = TextColor;
        Tmp[i + lim + 1].ArcColor = TextColor;
        Tmp[i + lim + 1].thickness = 0.1f * g_radius;
    }
    windowHandle.push_back(Tmp);
    return true;
}

bool Heap::UpdateKey(int id, int val, Type t)
{
    if (!root())
        return false;

    Node *Cur = (*this)[id];
    if (!Cur)
        return false;
    std::vector<Status> Tmp = windowHandle.back();
    int oldVal = Cur->val[0];
    if (val == oldVal)
    {
        for (int i = 0; i <= lim; i++)
        {
            Tmp[i].NodeFillColor = BackgroundColor;
            Tmp[i].OutlineColor = TextColor;
            Tmp[i].NodeTextColor = TextColor;
            Tmp[i + lim + 1].ArcColor = TextColor;
            Tmp[i + lim + 1].thickness = 0.1f * g_radius;
        }
        windowHandle.push_back(Tmp);
        return false;
    }

    std::cerr << "Change value\n";
    Cur->val[0] = val;
    for (int i = 0; i <= lim; i++)
    {
        if (Tmp[i].Node == Cur->Cur)
        {
            Tmp[i].nodeVal = std::to_string(val);
            break;
        }
    }
    windowHandle.push_back(Tmp);
    std::cerr << "Shift Up or Down ...\n";
    if (Cmp(val, oldVal, t))
    {
        std::cerr << "Shift Up\n";
        ShiftUp(Cur, t, Tmp);
    }
    else
    {
        std::cerr << "Shift Down\n";
        ShiftDown(Cur, t, Tmp);
    }
    std::cerr << "Done Update\n";
    return true;
}

int Heap::extract(Type t)
{
    if (!root())
        return (t == Max) ? INT_MIN : INT_MAX;

    Node *Cur = (*this)[size];
    std::vector<Status> Tmp = windowHandle.back();
    if (size == 1)
    {
        int val = root()->val[0];
        delete root();
        Tmp[size].hideNode = 1;
        size--;
        root() = nullptr;
        windowHandle.push_back(Tmp);
        return val;
    }
    int val = root()->val[0];
    Tmp[1].highlightNode();
    Tmp[size + lim + 1].ArcOnPath();
    windowHandle.push_back(Tmp);
    Tmp[1].nodeVal = std::to_string(Cur->val[0]);
    root()->val[0] = Cur->val[0];
    Cur->Par->Child[size % 2] = nullptr;
    Tmp[size].hideNode = 1;
    Tmp[size + lim + 1].hideArc = 1;
    for (int i = 0; i <= lim; i++)
        Tmp[i + lim + 1].NormalArc();
    size--;
    if (size == 1)
    {
        Tmp[1].NodePosition = sf::Vector2f(window.getSize().x / 2, upper_edge);
    }
    else
    {
        int order = 0;
        setPosition(root(), 0, order, Tmp);
        setArcPosition(root(), Tmp);
    }
    windowHandle.push_back(Tmp);
    delete Cur;
    ShiftDown(root(), t, Tmp);
    return val;
}

bool Heap::REMOVE(int id, Type t)
{
    if (!root())
        return false;
    UpdateKey(id, (t == Max) ? MAX : MIN, t);
    extract(t);
    return true;
}

void Heap::setPosition(Node *Cur, int h, int &order, std::vector<Status> &x)
{
    if (!Cur)
        return;
    setPosition(Cur->Child[Left], h + 1, order, x);
    for (int i = 0; i <= lim; i++)
        if (x[i].Node == Cur->Cur)
        {
            x[i].NodePosition = sf::Vector2f(window.getSize().x / 2 + (order - size / 2) * __min(400, range / size), upper_edge + h * distance);
            break;
        }
    Cur->x = order;
    Cur->y = h;
    order++;
    setPosition(Cur->Child[Right], h + 1, order, x);
}
void Heap::setArcPosition(Node *Cur, std::vector<Status> &x)
{
    if (!Cur)
        return;

    setArcPosition(Cur->Child[Left], x);
    if (Cur != root())
        for (int i = 0; i <= lim; i++)
            if (x[i].Node == Cur->Cur)
            {
                x[i + lim + 1].ArcSecondPosition = sf::Vector2f(window.getSize().x / 2 + (Cur->Par->x - size / 2) * __min(400, range / size), upper_edge + Cur->Par->y * distance);
                x[i + lim + 1].ArcFirstPosition = sf::Vector2f(window.getSize().x / 2 + (Cur->x - size / 2) * __min(400, range / size), upper_edge + Cur->y * distance);
                break;
            }
    setArcPosition(Cur->Child[Right], x);
}

int Heap::getSize()
{
    return size;
}