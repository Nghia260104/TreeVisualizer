#pragma once
#include <SFML/Graphics.hpp>
#include <Probing.hpp>
#include <Button.hpp>
#include <TextBox.hpp>
#include <CircleNode.hpp>
#include <Pattern.hpp>
#include <vector>

namespace Frontend
{
    class VisualProbing : public Pattern
    {
        sf::RectangleShape ToolBar;
        sf::Text Overload;
        TextBox f[5];
        Button Start[5];
        const int num = 16;
        const std::string S[5] = {"Randomize Data", "Create", "Insert", "Delete", "Search"};
        const int range = 1600, distance = 70, limit = 128;
        bool fail;
        const int upper_edge = 200;
        std::vector<Frontend::CircleNode> Table;
        Backend::Probing *Sys = nullptr;
        Backend::Probing::Type t;
        void setPosition();

    public:
        // Constructor
        VisualProbing();
        void create();

        // Draw
        void drawTexture();

        // Misc
        void processEvent(const sf::Event &event);
        void setType(Backend::Probing::Type t_);

        // Destructor
        virtual ~VisualProbing();
        void clear();
    };

    class LinearProbing : public VisualProbing
    {
    public:
        LinearProbing();
        ~LinearProbing();
    };

    class QuadraticProbing : public VisualProbing
    {
    public:
        QuadraticProbing();
        ~QuadraticProbing();
    };

    class DoubleHashing : public VisualProbing
    {
    public:
        DoubleHashing();
        ~DoubleHashing();
    };
}