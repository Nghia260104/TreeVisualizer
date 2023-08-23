#pragma once
#include <SFML/Graphics.hpp>
#include <Button.hpp>
#include <CircleNode.hpp>

namespace Frontend
{
    class Pattern : public sf::Drawable
    {
    public:
        sf::RectangleShape Tmp;
        sf::RenderTexture Texture;
        sf::RectangleShape Artwork, NavigateBox;
        Button Navigate[3];

        // Constructor
        Pattern();
        void create();

        // Draw
        void draw(sf::RenderTarget &target, sf::RenderStates states) const;
        virtual void drawTexture();

        void Navigating(const sf::Event &event);
    };
}