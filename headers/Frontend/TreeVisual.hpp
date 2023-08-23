#pragma once
#include <SFML/Graphics.hpp>
#include <AVLVisual.hpp>
#include <Button.hpp>

namespace Frontend
{
    class TreeVisual : public sf::Drawable
    {
        sf::RenderTexture Texture;
        sf::Text Name;
        Button DataType[5];
        AVLVisual Avl_tree;
        const int Tree = 2, avl = 8, B4 = 9, MaxHeap = 10, MinHeap = 11, Trie = 12;

    public:
        // Constructor
        TreeVisual();
        void create();

        // Misc
        void processEvent(const sf::Event &event, int &layer);
        bool mouseOnButton(const sf::Vector2i &MousePos);
        // bool mouseOnTextBox(const sf::Vector2i &MousePos);

        // Draw
        void Predraw();
        void drawTexture(const int &layer);
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    };
}