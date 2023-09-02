#pragma once
#include <SFML/Graphics.hpp>
#include <Button.hpp>
#include <CircleNode.hpp>
#include <string>

namespace Frontend
{
    class Pattern : public sf::Drawable
    {
        int speed;
        const std::string S[4] = {"1x", "1.5x", "2x", "4x"};
        const int timeInterval[4] = {1200, 900, 600, 300};
    public:
        sf::RenderTexture Texture;
        sf::RectangleShape Artwork, NavigateBox;
        Button Navigate[3];
        Button Spd;

        // Constructor
        Pattern();
        void create();

        // Draw
        void draw(sf::RenderTarget &target, sf::RenderStates states) const;
        virtual void drawTexture();
        void ReSetting();

        void Navigating(const sf::Event &event);
        void changeSpd(const sf::Event &event);
    };
}