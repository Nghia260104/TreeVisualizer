#pragma once
#include <SFML/Graphics.hpp>
#include <Button.hpp>
#include <TextBox.hpp>
#include <CircleNode.hpp>
#include <Pattern.hpp>
#include <AVL.hpp>
#include <Arrow.hpp>
#include <vector>

namespace Frontend
{
    class AVLVisual : public Pattern
    {
        sf::RectangleShape ToolBar;
        TextBox f[4];
        Button Start[4];
        sf::Text heightError, Overload, RandomErr;
        const int range = 1600, distance = 60, h_err = 1, oversize = 2, rand_size = 3, limit = 63;
        int fail;
        CircleNode *Root;
        CircleNode *Table;
        Arrow *Arc;
        Backend::AVL Sys;
        void PreparedArray(std::vector<int> &Given, int l, int r, std::vector<int> &Res);
        void Navigating(const sf::Event &event);
    public:
        // Constructor
        AVLVisual();
        void create();

        // Draw
        void drawTexture();

        // Misc
        void processEvent(const sf::Event &event);

        // Destructor
        void clear();
        void clearGpx();
        ~AVLVisual();
    };
}