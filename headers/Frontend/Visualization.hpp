#pragma once
#include <SFML/Graphics.hpp>
#include <TableVisual.hpp>
#include <TreeVisual.hpp>

namespace Frontend
{
    class Visualization : public sf::Drawable
    {
    public:
        // Constructor
        Visualization();
        void create();

        // Misc
        void processEvent(const sf::Event &event);
        bool mouseOnButton(const sf::Vector2i &MousePos);
        // bool mouseOnTextBox(const sf::Vector2i &MousePos);

        // Draw
        void drawTexture();
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    private:
        sf::RenderTexture Texture;
        TableVisual TableScreen;
        TreeVisual TreeScreen;
        Button ToolBar[2];
        sf::Text Name;
        Button DataType[3];
        Button Back;
        const int Home = 0,
                  Table = 1, Linear = 4, Quad = 5, DoubleHashing = 6, Chain = 7,
                  Tree = 2, avl = 8, B4 = 9, MaxHeap = 10, MinHeap = 11, Trie = 12,
                  Graph = 3, Connect = 13, MinSpan = 14, Dijkstra = 15,
                  Settings = 16, Info = 17;
        int layer;
    };
}