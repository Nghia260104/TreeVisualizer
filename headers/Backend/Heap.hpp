#include <Tree.hpp>

namespace Backend
{
    class Heap : public Tree
    {
    public:
        const int Left = 0, Right = 1;
        enum Type
        {
            Max, Min
        };
        Heap();
        ~Heap();

        Node *newNode(int val = 0);
        Node *operator[](int index);
        const int MAX_INT();
        const int MIN_INT();
        void swap(Node *x, Node *y);
        bool Cmp(int x, int y, Type t);
        void ShiftUp(Node *Cur, Type t);
        void ShiftDown(Node *Cur, Type t);
        bool INSERT(int val, Type t);
        bool UpdateKey(int id, int val, Type t);
        int extract(Type t);
        bool REMOVE(int id, Type t);

    private:
        const int MIN = -1, MAX = 1000;
        const int lim = 63;
        const int mask = 64;
        int size;
    };
}