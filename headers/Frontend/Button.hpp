#pragma once
#include <SFML/Graphics.hpp>
#include <string>

namespace Frontend
{
    class Button : public sf::Drawable
    {
    public:
        // enum
        enum Align
        {
            Left,
            Center,
            Right
        };

        // Constructor

        Button();
        Button(sf::String S);
        void create(float a, float b, float w, float h, sf::Font &font, unsigned int fontsize, sf::String S);

        // Box

        void setPosition(float a = 0, float b = 0);
        void setGlobalPosition(float a = 0, float b = 0);
        void setSize(float w = 50, float h = 50);
        void setFillColor(sf::Color color = sf::Color::White, float ratio = 0);
        void setOutline(sf::Color color = sf::Color::Black, float thick = 1.0f);

        // Text

        void setFont(sf::Font &font);
        void setFontStyle(sf::Text::Style style);
        void setFontSize(unsigned int fontsize);
        void setText(sf::String S);
        void setTextPos();
        void setTextPos(float y);
        void setTextPos(float x, float y, Button::Align Type = Button::Align::Left);
        void setTextColor(sf::Color color = sf::Color::Black);

        // Image

        void setImage(const std::string &fileName);
        void setImagePosition(float x, float y);
        void setImageOutline(sf::Color color = sf::Color::Black, float thick = 1.0f);
        void setImageColor(sf::Color color);

        // Misc

        bool isPressed(sf::Event event);
        void setCoverColor(sf::Color color = sf::Color::Transparent);
        bool mouseOn(const sf::Vector2i &MousePos) const;
        sf::String getText() const;

        // Draw

        void drawTexture();

    protected:
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    private:
        float x, y, g_x, g_y;
        float Image_x, Image_y, i_outline_thickness;
        bool hasImage, hasImageOutline, hasImageColor;
        sf::Vector2f RecSize;
        sf::Text Text;
        sf::RectangleShape Rec;
        sf::RenderTexture Texture;
        sf::Texture Image;
        sf::Color Cover, ImageOutlineColor, CoverImage;
        sf::Color getContrastColor(sf::Color color, float ratio);
        sf::Vector2i getMousePosition() const;
    };
}