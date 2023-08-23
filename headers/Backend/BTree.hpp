#include <Tree.hpp>

namespace Backend
{
    class BTree : public Tree
    {
    public:
        BTree(int k_ = 1);
        ~BTree();

        Node *newNode(bool leaf_);
        const int *const &nulVal();
        const int *const &SEARCH(const Node *const &Root, int val);
        const int *const &search(int val);
        bool insert(int val);
        void insertNonFull(Node *&Root, int val);
        void splitChild(Node *&Root, int id);

    private:
        int k; // Minimum of B-Tree
        const int *nullVal = nullptr;
    };
}