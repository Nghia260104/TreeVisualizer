#include <Trie.hpp>
#include <FrontendGlobal.hpp>
#include <iostream>
using namespace Backend;

Trie::Trie()
{
    Table = nullptr;
    Arc = nullptr;
    numInserted = 0;
    numNode = 0;
    Inc = Dec = 0;
}

Trie::~Trie()
{
    clear();
    delete Root;
    Root = nullptr;
}

void Trie::clear()
{
    numNode = 0;
    numInserted = 0;
    clearChild(Root);
}

void Trie::clearChild(StrNode *&Cur)
{
    if (!Cur)
        return;
    for (StrNode *&i : (Cur->Child))
        clearChild(i);
    if (Cur != Root)
    {
        delete Cur;
        Cur = nullptr;
    }
}

void Trie::link(Frontend::CircleNode *Table_, Frontend::Arrow *Arc_)
{
    Table = Table_;
    Arc = Arc_;
    Root = new StrNode;
    Root->Cur = &Table[numNode];
    Root->vs_id = numNode;
    Table[numNode].setPosition(window.getSize().x / 2, 50);
}

StrNode *&Trie::root()
{
    return Root;
}

void Trie::insert(const std::string &val)
{
    if (val.size() > limHeight || numInserted >= limWord)
        return;
    Inc = 0;
    std::vector<Status> Tmp;
    for (int i = 0; i < total; i++)
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
    for (int i = 0; i < total; i++)
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
    StrNode *Cur = Root, *Par = nullptr;
    Tmp[Cur->vs_id].highlightNode();
    windowHandle.push_back(Tmp);
    for (int i = 0; i < val.length(); i++)
    {
        for (int j = 0; j < total; j++)
        {
            if (Tmp[j].NodeFillColor == Highlight)
            {
                Tmp[j].NodeOnPath();
                Tmp[j + total].ArcOnPath();
                break;
            }
        }
        int id = val[i] - 'a';
        if (!Cur->Child[id])
        {
            numNode++;
            StrNode *New = new StrNode;
            New->vs_id = numNode;
            New->Cur = &Table[numNode];
            Cur->Child[id] = New;
            Cur->Child[id]->Par = Cur;
            setPosition(Tmp);
        }
        Par = Cur;
        Cur = Cur->Child[id];
        Tmp[Cur->vs_id].highlightNode();
        Tmp[Cur->vs_id + total].highlightArc();
        Tmp[Cur->vs_id].hideNode = 0;
        Tmp[Cur->vs_id + total].hideArc = 0;
        Tmp[Cur->vs_id + total].Arc->setWeight(val[i]);
        windowHandle.push_back(Tmp);
    }

    // std::cerr << "Check word\n";
    if (!Cur->isEndOfWord)
    {
        Cur->isEndOfWord = true;
        Tmp[Cur->vs_id].nodeVal = "x";
        windowHandle.push_back(Tmp);
    }
    for (int i = 0; i < total; i++)
    {
        Tmp[i].NormalNode();
        Tmp[i + total].NormalArc();
    }
    windowHandle.push_back(Tmp);
}

bool Trie::search(const std::string &val)
{
    StrNode *Cur = Root;
    std::vector<Status> Tmp;
    for (int i = 0; i < total; i++)
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
    for (int i = 0; i < total; i++)
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
    Tmp[Cur->vs_id].highlightNode();
    windowHandle.push_back(Tmp);
    for (int i = 0; i < val.length(); i++)
    {
        int id = val[i] - 'a';
        if (!Cur->Child[id])
        {
            for (int j = 0; j < total; j++)
            {
                Tmp[j].NormalNode();
                Tmp[j + total].NormalArc();
            }
            windowHandle.push_back(Tmp);
            return false;
        }
        Cur = Cur->Child[id];
        Tmp[Cur->vs_id].highlightNode();
        Tmp[Cur->vs_id + total].highlightArc();
        windowHandle.push_back(Tmp);
    }
    for (int j = 0; j < total; j++)
    {
        Tmp[j].NormalNode();
        Tmp[j + total].NormalArc();
    }
    windowHandle.push_back(Tmp);
    return Cur->isEndOfWord;
}

StrNode *Trie::REMOVE(StrNode *Cur, const std::string &val, int depth)
{
    if (!Cur)
        return nullptr;

    std::vector<Status> Tmp = windowHandle.back();
    for (int i = 0; i < total; i++)
        if (Tmp[i].NodeFillColor == Highlight)
        {
            Tmp[i].NodeOnPath();
            Tmp[i + total].ArcOnPath();
            break;
        }
    Tmp[Cur->vs_id].highlightNode();
    Tmp[Cur->vs_id + total].highlightArc();
    windowHandle.push_back(Tmp);
    if (depth == val.size())
    {
        if (Cur->isEndOfWord)
        {
            Cur->isEndOfWord = false;
            Tmp[Cur->vs_id].nodeVal = "";
        }

        if (Cur->numChild() == 0)
        {
            Tmp[Cur->vs_id].hideNode = 1;
            Tmp[Cur->vs_id + total].hideArc = 1;
            Cur->Par->Child[int(val.back() - 'a')] = nullptr;
            if (Cur->Par->numChild() > 0)
                setPosition(Tmp);
            delete Cur;
            numNode--;
            Cur = nullptr;
        }
        windowHandle.push_back(Tmp);
        return Cur;
    }

    int id = val[depth] - 'a';
    Cur->Child[id] = REMOVE(Cur->Child[id], val, depth + 1);

    if (Cur->numChild() == 0)
    {
        Tmp[Cur->vs_id].hideNode = 1;
        Tmp[Cur->vs_id + total].hideArc = 1;
        windowHandle.push_back(Tmp);
        Cur->Par->Child[int(val.back() - 'a')] = nullptr;
        if (Cur->Par->numChild() > 0)
            setPosition(Tmp);
        delete Cur;
        numNode--;
        Cur = nullptr;
    }
    return Cur;
}

void Trie::remove(const std::string &val)
{
    std::vector<Status> Tmp;
    for (int i = 0; i < total; i++)
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
    for (int i = 0; i < total; i++)
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
    REMOVE(Root, val);
    Tmp = windowHandle.back();
    for (int i = 0; i < total; i++)
    {
        Tmp[i].NormalNode();
        Tmp[i + total].NormalArc();
    }
    windowHandle.push_back(Tmp);
}

void Trie::align(StrNode *Cur, int h, int &order)
{
    if (!Cur)
        return;
    float min_x = order, max_x = order;
    for (int i = 0; i < MAX_NUM; i++)
        align(Cur->Child[i], h + 1, order);
    if (Cur != Root)
    {
        if (Cur->numChild() == 0)
            order++;
        else
        {
            for (int i = 0; i < MAX_NUM; i++)
            {
                if (Cur->Child[i])
                {
                    min_x = __min(min_x, Cur->Child[i]->min_x);
                    max_x = __max(max_x, Cur->Child[i]->max_x);
                }
            }
        }
        Cur->min_x = min_x;
        Cur->max_x = max_x;
        Cur->y = h;
    }
}

void Trie::edit(StrNode *Cur, const int &Num, std::vector<Status> &Tmp)
{
    if (!Cur)
        return;
    for (int i = 0; i < MAX_NUM; i++)
        edit(Cur->Child[i], Num, Tmp);
    if (Cur != Root)
    {
        Tmp[Cur->vs_id].NodePosition = sf::Vector2f(window.getSize().x / 2 + ((Cur->max_x + Cur->min_x) / 2 - 1.0f * Num / 2) * __min(150, range / Num),
                                                    upper_edge + Cur->y * distance);
    }
}

void Trie::setArcPosition(StrNode *Cur, std::vector<Status> &Tmp)
{
    if (!Cur)
        return;
    for (int i = 0; i < MAX_NUM; i++)
        setArcPosition(Cur->Child[i], Tmp);
    if (Cur != Root)
    {
        Tmp[Cur->vs_id + total].ArcFirstPosition = Tmp[Cur->vs_id].NodePosition;
        Tmp[Cur->vs_id + total].ArcSecondPosition = Tmp[Cur->Par->vs_id].NodePosition;
    }
}

void Trie::setPosition(std::vector<Status> &Tmp)
{
    int order = 0;
    align(Root, 0, order);
    edit(Root, order, Tmp);
    setArcPosition(Root, Tmp);
    numInserted = order;
}

const int &Trie::Inserted()
{
    return numInserted;
}

void Trie::displayPos()
{
    traverse(Root);
}

void Trie::traverse(StrNode *Cur)
{
    if (!Cur)
        return;
    std::cerr << Cur->min_x << " " << Cur->max_x << " " << Cur->y << '\n';
    for (int i = 0; i < MAX_NUM; i++)
        traverse(Cur->Child[i]);
}