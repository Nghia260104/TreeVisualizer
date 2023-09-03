#include <Graph.hpp>
#include <FrontendGlobal.hpp>
#include <iostream>
#include <queue>
// #include <algorithm>
using namespace Backend;

Graph::Graph()
{
    size = 0;
    numEdge = 0;
    S[0] = 190;
    for (int i = 1; i < 19; i++)
        S[i] = S[i - 1] - (20 - i);
    vertex_chosen = -1;
}

void Graph::clear()
{
    for (int i = 0; i < numEdge; i++)
    {
        Edge[i].vertex1 = nullptr;
        Edge[i].vertex2 = nullptr;
        Edge[i].weight = 0;
    }
    size = 0;
    numEdge = 0;
    index.clear();
    for (int i = 0; i < 20; i++)
        Adj[i].clear();
    E_index.clear();
}

void Graph::link(Frontend::CircleNode *Table_, Frontend::Arrow *Arc_)
{
    Table = Table_;
    Arc = Arc_;
    for (int i = 0; i < 20; i++)
        Vertex[i].Cur = &Table[i];
    for (int i = 0; i < 190; i++)
    {
        Edge[i].Arc = &Arc[i];
        // Edge[20 * (i % 20) + i / 20].Arc = &Arc[i];
    }
}

void Graph::setPosition()
{
    srand(time(NULL));
    int cnt = 0;
    for (int i : index)
    {
        int rand_x = rand() % (W + 1), rand_y = rand() % (L + 1);
        Vertex[i].Cur->setPosition(Align.x + rand_x, Align.y + rand_y);
        Vertex[i].pos = MyVector(rand_x, rand_y);
        std::cerr << "Position of vertex " << i << ": " << Vertex[i].pos.x << " " << Vertex[i].pos.y << '\n';
    }
    for (int i : E_index)
    {
        Edge[i].Arc->setFirstPosition(sf::Vector2f(Edge[i].vertex1->pos.x, Edge[i].vertex1->pos.y));
        Edge[i].Arc->setSecondPosition(sf::Vector2f(Edge[i].vertex2->pos.x, Edge[i].vertex2->pos.y));
    }
}

void Graph::arrangePosition()
{
    run1step = 1;
    if (size)
    {
        srand(time(NULL));
        // float t = L / 10;
        float t = 8;
        int A = W * L;
        int k = sqrt(A / size);
        // int k = 150;
        int it = 1500;
        sf::Clock MyClock;
        MyClock.restart();
        while (MyClock.getElapsedTime().asMilliseconds() < it)
        {
            float time = MyClock.getElapsedTime().asMilliseconds();
            if ((int)time % 15)
                continue;
            std::cerr << "Iteration: " << time / 15 << "\n\n";
            for (int i : index)
            {
                if (i == vertex_chosen)
                    continue;
                Vertex[i].disp = MyVector(0, 0);
                for (int j : index)
                {
                    if (i == j)
                    {
                        // MyVector Center = MyVector(W / 2 - Vertex[i].pos.x, L / 2 - Vertex[i].pos.y);
                        // float tmp_dis = Center.x * Center.x + Center.y * Center.y;
                        // if (tmp_dis > 0)
                        // {
                        //     Vertex[i].disp.x -= k * k * Center.x / tmp_dis;
                        //     Vertex[i].disp.y -= k * k * Center.y / tmp_dis;
                        // }
                        continue;
                    }
                    MyVector delta = MyVector(Vertex[i].pos.x - Vertex[j].pos.x, Vertex[i].pos.y - Vertex[j].pos.y);
                    float dis = delta.x * delta.x + delta.y * delta.y;
                    if (dis > 0 && dis <= 200 * 200)
                    // if (dis >= 0)
                    {
                        std::cerr << "Distance between " << j << " and " << i << ": " << dis << '\n';
                        std::cerr << "Repulsive force: " << k * k * delta.x / dis << " ; " << k * k * delta.y / dis << '\n';
                        Vertex[i].disp.x += k * k * delta.x / sqrt(dis);
                        Vertex[i].disp.y += k * k * delta.y / sqrt(dis);
                    }
                }
                std::cerr << '\n';
            }
            std::cerr << "\n\n";
            for (int e : E_index)
            {
                MyVector delta = MyVector(Edge[e].vertex2->pos.x - Edge[e].vertex1->pos.x, Edge[e].vertex2->pos.y - Edge[e].vertex1->pos.y);
                float dis = delta.x * delta.x + delta.y * delta.y;
                if (dis >= 0)
                {
                    if (Edge[e].vertex1->numVal != vertex_chosen)
                    {
                        Edge[e].vertex1->disp.x += dis / k * delta.x;
                        Edge[e].vertex1->disp.y += dis / k * delta.y;
                    }
                    if (Edge[e].vertex2->numVal != vertex_chosen)
                    {
                        Edge[e].vertex2->disp.x -= dis / k * delta.x;
                        Edge[e].vertex2->disp.y -= dis / k * delta.y;
                    }
                    std::cerr << "Distance between " << Edge[e].vertex1->numVal << " and " << Edge[e].vertex2->numVal << ": " << dis << '\n';
                    std::cerr << "Attractive force: " << dis / k * delta.x << " ; " << dis / k * delta.y << '\n';
                }
            }

            for (int i : index)
            {
                if (i == vertex_chosen)
                    continue;
                MyVector Center = MyVector(W / 2 - Vertex[i].pos.x, L / 2 - Vertex[i].pos.y);
                float tmp_dis = Center.x * Center.x + Center.y * Center.y;
                if (tmp_dis > 400 * 400)
                {
                    Vertex[i].disp.x += tmp_dis / k * Center.x;
                    Vertex[i].disp.y += tmp_dis / k * Center.y;
                }
                float delta = Vertex[i].disp.x * Vertex[i].disp.x + Vertex[i].disp.y + Vertex[i].disp.y;
                if (delta > 0)
                {
                    Vertex[i].pos.x += Vertex[i].disp.x * __min(1, t / sqrt(delta));
                    Vertex[i].pos.y += Vertex[i].disp.y * __min(1, t / sqrt(delta));
                    Vertex[i].pos.x = __min(W, __max(0, Vertex[i].pos.x));
                    Vertex[i].pos.y = __min(L, __max(0, Vertex[i].pos.y));
                }
            }
            // std::vector<float> Tmp_x, Tmp_y;
            // for (int i : index)
            // {
            //     Tmp_x.push_back(Vertex[i].pos.x);
            //     Tmp_y.push_back(Vertex[i].pos.y);
            // }
            // sort(Tmp_x.begin(), Tmp_x.end());
            // sort(Tmp_y.begin(), Tmp_y.end());
            // for (int i : index)
            // {
            //     Vertex[i].pos.x += W/2 - Tmp_x[size / 2];
            //     Vertex[i].pos.y += L/2 - Tmp_y[size / 2];
            // }
            for (int i : index)
            {
                if (i == vertex_chosen)
                    continue;
                Vertex[i].Cur->setPosition(Align.x + Vertex[i].pos.x, Align.y + Vertex[i].pos.y);
                std::cerr << "Position of vertex " << i << " : "
                          << Vertex[i].pos.x << " " << Vertex[i].pos.y << '\n';
            }
            for (int i : E_index)
            {
                Edge[i].Arc->setFirstPosition(Edge[i].vertex1->Cur->getPosition());
                Edge[i].Arc->setSecondPosition(Edge[i].vertex2->Cur->getPosition());
            }
            t = (it - time) / it * 8;
        }
        // for (int i : index)
        //     std::cerr << "Position of vertex " << i << ": " << Vertex[i].pos.x << " " << Vertex[i].pos.y << '\n';
        std::cerr << "Number of vertices: " << size << '\n'
                  << "Number of edges: " << E_index.size() << '\n';
    }
    run1step = 0;
}

void Graph::setup()
{
    run1step = 1;
    setPosition();
    arrangePosition();
}

bool Graph::addVertex(int u)
{
    if (u >= 20)
        return false;
    for (int x : index)
        if (x == u)
            return false;
    std::cerr << "Add vertex " << u << ", Visual: " << Vertex[u].Cur << '\n';
    Vertex[u].Cur->show();
    Vertex[u].Cur->setInt(u);
    Vertex[u].numVal = u;
    Vertex[u].pos = MyVector(0, 0);
    Vertex[u].Cur->setPosition(Align.x, Align.y);
    index.push_back(u);
    size++;
    return true;
}

bool Graph::addEdge(int a, int b, int w_)
{
    if (size * (size - 1) <= numEdge)
        return false;

    a = a % 20;
    b = b % 20;
    if (a == b)
        return false;

    if (a > b)
        swap(a, b);
    int id = S[0] - S[a] + b - a - 1;
    if (!Edge[id].Arc->isHidden() || Vertex[a].Cur->isHidden() || Vertex[b].Cur->isHidden())
        return false;

    Edge[id].vertex1 = &Vertex[a];
    Edge[id].vertex2 = &Vertex[b];
    Edge[id].weight = w_;
    Edge[id].Arc->show();
    Edge[id].Arc->setWeight(std::to_string(w_));
    Edge[id].Arc->setFirstPosition(sf::Vector2f(Vertex[a].pos.x, Vertex[a].pos.y));
    Edge[id].Arc->setSecondPosition(sf::Vector2f(Vertex[b].pos.x, Vertex[b].pos.y));
    Adjacent x, y;
    x.v = b;
    y.v = a;
    x.val = y.val = &Edge[id];
    Adj[a].push_back(x);
    Adj[b].push_back(y);
    E_index.push_back(id);
    numEdge++;
    return true;
}

bool Graph::removeVertex(int u)
{
    if (u >= 20)
        return false;

    int cnt = 0;
    for (int i : index)
    {
        if (i == u)
            break;
        cnt++;
    }
    if (cnt == index.size())
        return false;

    Vertex[u].Cur->hide();
    index.erase(std::find(index.begin(), index.end(), u));
    for (auto i : Adj[u])
    {
        int a = u;
        int b = i.v;
        for (int j = 0; j < Adj[b].size(); j++)
            if (Adj[b][j].v == u)
            {
                Adj[b].erase(Adj[b].begin() + j);
                break;
            }
        if (a > b)
            swap(a, b);
        int id = S[0] - S[a] + b - a - 1;
        Edge[id].Arc->hide();
        E_index.erase(std::find(E_index.begin(), E_index.end(), id));
    }
    Adj[u].clear();
    return true;
}

bool Graph::removeEdge(int u, int v)
{
    u = u % 20;
    v = v % 20;
    if (u > v)
        swap(u, v);

    int id = S[0] - S[u] + v - u - 1;
    if (Edge[id].Arc->isHidden())
        return false;

    Edge[id].Arc->hide();
    E_index.erase(std::find(E_index.begin(), E_index.end(), id));
    for (int j = 0; j < Adj[u].size(); j++)
        if (Adj[u][j].v == v)
        {
            Adj[u].erase(Adj[u].begin() + j);
            break;
        }
    for (int j = 0; j < Adj[v].size(); j++)
        if (Adj[v][j].v == u)
        {
            Adj[v].erase(Adj[v].begin() + j);
            break;
        }
    return true;
}

void Graph::setVertexPosition(int u)
{
    Vertex[u].pos = MyVector(Vertex[u].Cur->getPosition().x - Align.x, Vertex[u].Cur->getPosition().y - Align.y);
    for (auto j : Adj[u])
    {
        int b = j.v;
        int a = u;
        if (a > b)
            swap(a, b);
        int id = S[0] - S[a] + b - a - 1;
        Edge[id].Arc->setFirstPosition(sf::Vector2f{Vertex[a].pos.x + Align.x, Vertex[a].pos.y + Align.y});
        Edge[id].Arc->setSecondPosition(sf::Vector2f(Vertex[b].pos.x + Align.x, Vertex[b].pos.y + Align.y));
    }
}

void Graph::setChoosing(int u)
{
    vertex_chosen = u;
}

bool Graph::Dijkstra(int s)
{
    int cnt = 0;
    for (int i : index)
    {
        if (i == s)
            break;
        cnt++;
    }
    if (cnt == index.size())
        return false;

    std::vector<Status> Tmp;
    for (int i = 0; i < 20; i++)
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
    for (int i = 0; i < 190; i++)
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
    std::vector<int> Dis;
    Dis.resize(20, INT_MAX);
    std::vector<bool> visited;
    visited.resize(20, 0);

    Dis[s] = 0;
    std::priority_queue<Data, std::vector<Data>, cmp> q;
    q.push({s, Dis[s]});

    while (!q.empty())
    {
        Data x = q.top();
        q.pop();

        int u = x.u;
        if (visited[u])
            continue;

        for (int i = 0; i < 20; i++)
            if (Tmp[i].NodeFillColor == Highlight)
            {
                Tmp[i].NodeOnPath();
                break;
            }
        for (int i = 0; i < 190; i++)
            if (Tmp[i + 20].thickness == 0.2f * g_radius)
                Tmp[i + 20].ArcOnPath();

        Tmp[u].highlightNode();
        windowHandle.push_back(Tmp);

        if (u == s)
        {
            Tmp[u].nodeVal = std::to_string(u) + "-0";
            windowHandle.push_back(Tmp);
        }

        visited[u] = true;
        for (auto j : Adj[u])
        {
            int v = j.v;
            int w = j.val->weight;
            if (visited[v])
                continue;

            for (int i = 0; i < 20; i++)
                if (Tmp[i].NodeFillColor == Highlight)
                    Tmp[i].NodeOnPath();

            for (int i = 0; i < 190; i++)
                if (Tmp[i + 20].thickness == 0.2f * g_radius)
                {
                    Tmp[i + 20].ArcOnPath();
                    break;
                }

            // Tmp[u].highlightNode();
            Tmp[v].highlightNode();

            int a = u, b = v;
            if (a > b)
                swap(a, b);
            int id = S[0] - S[a] + b - a - 1;
            Tmp[id + 20].highlightArc();
            windowHandle.push_back(Tmp);

            if (Dis[v] > Dis[u] + w)
            {
                Dis[v] = Dis[u] + w;
                q.push({v, Dis[v]});
                Tmp[v].nodeVal = std::to_string(v) + '-' + std::to_string(Dis[v]);
                windowHandle.push_back(Tmp);
            }
        }
    }

    for (int i = 0; i < 20; i++)
        Tmp[i].NormalNode();
    for (int i = 0; i < 190; i++)
        Tmp[i + 20].NormalArc();
    windowHandle.push_back(Tmp);
    return true;
}

void Graph::reset()
{
    for (int i = 0; i < 20; i++)
        if (Vertex[i].numVal != -1)
        {
            Table[i].setInt(Vertex[i].numVal);
            Table[i].drawTexture();
        }
}

void Graph::swap(int &a, int &b)
{
    int Tmp = a;
    a = b;
    b = Tmp;
}

bool Graph::cmpW(GraphEdge *a, GraphEdge *b)
{
    return (*a).weight < (*b).weight;
}

bool Graph::MST()
{
    if (size <= 0)
        return false;
    std::vector<Status> Tmp;
    for (int i = 0; i < 20; i++)
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
    for (int i = 0; i < 190; i++)
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
    std::vector<GraphEdge *> SortE_index;
    for (int i : E_index)
        SortE_index.push_back(&Edge[i]);
    for (int i = 0; i + 1 < SortE_index.size(); i++)
        for (int j = i + 1; j < SortE_index.size(); j++)
        {
            if (!cmpW(SortE_index[i], SortE_index[j]))
            {
                GraphEdge *Tmp_Edge = SortE_index[i];
                SortE_index[i] = SortE_index[j];
                SortE_index[j] = Tmp_Edge; 
            }
        }
    DSU s(20);
    for (auto e : SortE_index)
    {
        int u = e->vertex1->numVal, v = e->vertex2->numVal;
        if (u > v)
            swap(u, v);
        int id = S[0] - S[u] + v - u - 1;
        for (int i = 0; i < 20; i++)
            if (Tmp[i].NodeFillColor == Highlight)
                Tmp[i].NodeOnPath();
        Tmp[u].highlightNode();
        Tmp[v].highlightNode();
        Tmp[id + 20].highlightArc();
        windowHandle.push_back(Tmp);
        if (s.find(u) != s.find(v))
        {
            s.unite(u, v);
            Tmp[id + 20].thickness = 0.15f * g_radius;
        }
        else
        {
            Tmp[id + 20].ArcColor = Blur;
            Tmp[id + 20].thickness = 0.1f * g_radius;
        }
        windowHandle.push_back(Tmp);
    }
    for (int i = 0; i < 20; i++)
        if (Tmp[i].NodeFillColor == Highlight)
            Tmp[i].NodeOnPath();
    for (int i = 0; i < 190; i++)
        if (Tmp[i + 20].thickness == 0.2f * g_radius)
            Tmp[i + 20].ArcOnPath();
    windowHandle.push_back(Tmp);
    return true;
}