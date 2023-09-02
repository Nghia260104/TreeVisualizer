#pragma once
#include <SFML/Graphics.hpp>
#include <Button.hpp>
#include <TextBox.hpp>
#include <CircleNode.hpp>
#include <Pattern.hpp>
#include <Arrow.hpp>
#include <Trie.hpp>

namespace Frontend
{
    class TrieVisual : public Pattern
    {
        sf::RectangleShape ToolBar;
        TextBox f[4];
        Button Start[4];
        sf::Text heightError, Overload, RandomErr;
        const int range = 1600, distance = 60, h_err = 1, oversize = 2, rand_size = 3, limit = 32, total = 193, upper_edge = 200;
        int fail;
        CircleNode *Table;
        Arrow *Arc;
        Backend::Trie Sys;
        void Navigating(const sf::Event &event);
    public:
        // Constructor
        TrieVisual();
        void create();

        // Draw
        void drawTexture();

        // Misc
        void processEvent(const sf::Event &event);
        void ReSetting();

        // Destructor
        void clear();
        void clearGpx();
        ~TrieVisual();
    };
}