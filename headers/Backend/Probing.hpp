#pragma once
#include <HashTable.hpp>
#include <CircleNode.hpp>

namespace Backend
{
    class Probing : public HashTable
    {
    public:
        enum Type
        {
            Linear,
            Quadratic,
            Double
        };
        int sec;
        Probing(int num = 0);
        ~Probing();
        int index(const int &val, const int &steps, Type t) const;
        void resize(int n);
        bool canInsert(int val, Type t);
        bool INSERT(int val, std::vector<Frontend::CircleNode> &Art, Type t);
        bool REMOVE(int val, std::vector<Frontend::CircleNode> &Art, Type t);
        const HashNode *const &SEARCH(int val, std::vector<Frontend::CircleNode> &Art, Type t) const;
        const HashNode *const &trySearch(int val, Type t) const;

    private:
        int numInserted;
    };

    class LP : public Probing
    {
    public:
        LP(int num = 0);
        ~LP();
        bool insert(int val, std::vector<Frontend::CircleNode> &Art);
        bool remove(int val, std::vector<Frontend::CircleNode> &Art);
        const HashNode *const &search(int val, std::vector<Frontend::CircleNode> &Art) const;
    };

    class QP : public Probing
    {
    public:
        QP(int num = 0);
        ~QP();
        bool insert(int val, std::vector<Frontend::CircleNode> &Art);
        bool remove(int val, std::vector<Frontend::CircleNode> &Art);
        const HashNode *const &search(int val, std::vector<Frontend::CircleNode> &Art) const;
    };

    class DH : public Probing
    {
    public:
        DH(int num = 0);
        ~DH();
        bool insert(int val, std::vector<Frontend::CircleNode> &Art);
        bool remove(int val, std::vector<Frontend::CircleNode> &Art);
        const HashNode *const &search(int val, std::vector<Frontend::CircleNode> &Art) const;
    };
}