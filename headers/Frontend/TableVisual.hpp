#pragma once
#include <SFML/Graphics.hpp>
#include <VisualProbing.hpp>
#include <Button.hpp>

namespace Frontend
{
    class TableVisual : public sf::Drawable
    {
        sf::RenderTexture Texture;
        sf::Text Name;
        Button DataType[3];
        LinearProbing Linear;
        QuadraticProbing Quadratic;
        DoubleHashing Hash;
        const int Table = 1, Li = 4, Quad = 5, DoubleHashing = 6, Chain = 7;

    public:
        // Constructor
        TableVisual();
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