#pragma once
#include <SFML/Graphics.hpp>
#include <Button.hpp>
#include <TextBox.hpp>
#include <CircleNode.hpp>
#include <Pattern.hpp>
#include <Heap.hpp>
#include <Arrow.hpp>
#include <vector>

namespace Frontend
{
    class HeapVisual : public Pattern
    {
        sf::RectangleShape ToolBar;
        TextBox f[6];
        Button Start[7];
        sf::RectangleShape SizeBox, ID_frame, Val_frame, Extract_frame;
        sf::Text Overload, RandomErr, Null_Node, Size, ID_title, Val_title, Extract_val;
        const int range = 1600, distance = 60, nullity = 1, oversize = 2, rand_size = 3, limit = 63;
        int fail;
        CircleNode *Table;
        Arrow *Arc;
        Backend::Heap Sys;
        Backend::Heap::Type t;
        void Navigating(const sf::Event &event);

    public:
        // Constructor
        HeapVisual();
        void create();

        // Draw
        void drawTexture();

        // Misc
        void processEvent(const sf::Event &event);
        void setType(Backend::Heap::Type t_);

        // Destructor
        void clear();
        void clearGpx();
        ~HeapVisual();
    };

    class MinHeapVisual : public HeapVisual
    {
    public:
        MinHeapVisual()
        {
            setType(Backend::Heap::Type::Min);
        }
    };

    class MaxHeapVisual : public HeapVisual
    {
    public:
        MaxHeapVisual()
        {
            setType(Backend::Heap::Type::Max);
        }
    };
}