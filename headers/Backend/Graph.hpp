#pragma once
#include <Node.hpp>
#include <unordered_map>
#include <math.h>

namespace Backend
{
    struct Graph
    {
        GraphNode Vertex[20];
        GraphEdge Edge[190];
        int S[19];
        Frontend::CircleNode *Table;
        Frontend::Arrow *Arc;
        std::vector<Adjacent> Adj[20];
        std::vector<int> index, E_index;
        const sf::Vector2f Align = sf::Vector2f(360, 100);
        int size;
        int numEdge;
        const int W = 1200, L = 700, lim_dis = 150;
        Graph();
        void clear();
        void link(Frontend::CircleNode *Table_, Frontend::Arrow *Arc_);

        void setPosition();
        void arrangePosition();
        void setup();
        bool addVertex(int u);
        bool addEdge(int a, int b, int w_);
        bool removeVertex(int u);
        bool removeEdge(int u, int v);
        void setVertexPosition(int u);
        void setChoosing(int u = -1);
        bool Dijkstra(int s);
        void reset();
        bool MST();
        bool cmpW(GraphEdge *a, GraphEdge *b);

    private:
        void swap(int &a, int &b);
        int vertex_chosen;
        struct Data
        {
            int u;
            int Dist;
            Data()
            {
                u = 0;
                Dist = 0;
            }
            Data(int u_, int dis_)
            {
                u = u_;
                Dist = dis_;
            }
        };
        struct cmp
        {
            bool operator()(Data a, Data b)
            {
                return a.Dist > b.Dist;
            }
        };
        class DSU
        {
            std::vector<int> par, rank;

        public:
            DSU(int n = 0)
            {
                par.resize(n, -1);
                rank.resize(n, 1);
            }
            int find(int u)
            {
                if (par[u] == -1)
                    return u;
                return par[u] = find(par[u]);
            }
            void unite(int u, int v)
            {
                int s1 = find(u), s2 = find(v);

                if (s1 != s2)
                {
                    if (rank[s1] < rank[s2])
                        par[s1] = s2;
                    else if (rank[s1] > rank[s2])
                        par[s2] = s1;
                    else
                    {
                        par[s2] = s1;
                        rank[s1]++;
                    }
                }
            }
        };
    };
}