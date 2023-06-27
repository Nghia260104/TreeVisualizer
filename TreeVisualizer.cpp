#include <bits/stdc++.h>
#include <BST.hpp>
#include <Probing.hpp>
#include <Chaining.hpp>
#include <stdlib.h>

signed main()
{
    srand(time(NULL));
    // Backend::BST MyBST;
    // for (int i = 0; i < 10; i++)
    //     for (int j = 0; j < 4; j++)
    //     {
    //         int Tmp = rand() % 10;
    //         MyBST.insert(Tmp);
    //     }
    // for (int i = 0; i < 10; i++)
    //     MyBST.insert(i);
    // MyBST.display();
    // MyBST.remove(1);
    // MyBST.remove(5);
    // MyBST.display();
    Backend::LP MyChaining(10);
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 4; j++)
            if (!MyChaining.insert(rand() % 10))
                std::cerr << "Fail" << '\n';
    MyChaining.display();
}