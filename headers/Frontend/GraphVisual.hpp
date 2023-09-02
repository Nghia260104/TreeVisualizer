#pragma once
#include <SFML/Graphics.hpp>
#include <Button.hpp>
#include <Pattern.hpp>
#include <TextBox.hpp>
#include <Graph.hpp>

namespace Frontend
{
    class GraphVisual : public Pattern
    {
        Backend::Graph Sys;
        Frontend::CircleNode *Table;
        Frontend::Arrow *Arc;
        TextBox f[9];
        Button Start[7];
        sf::RectangleShape ToolBar;
        sf::Text Overload, RandomErr, Exist, NonExist;
        sf::Vector2f delta = sf::Vector2f(0, 0);
        const int oversize = 1, rand_size = 2, existed = 3, notExisted = 4 ,limit = 20;
        int fail;
        bool dragging[20];

    public:
        // Constructor
        GraphVisual();
        void create();
        ~GraphVisual();

        // Misc
        void processEvent(const sf::Event &event);
        bool mouseOnButton(const sf::Vector2i &MousePos);
        void ReSetting();
        void Navigating(const sf::Event &event);
        // bool mouseOnTextBox(const sf::Vector2i &MousePos);

        // Draw
        void Predraw();
        void drawTexture();
        void clear();
        void clearGpx();
        void resetColor();
    };
}
