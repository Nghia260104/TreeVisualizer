#pragma once
#include <SFML/Graphics.hpp>

class Button : public sf::Drawable
{
public:
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
    void setFontSize(unsigned int fontsize);
    void setText(sf::String S);
    void setTextPos();
    void setTextPos(float y);
    void setTextColor(sf::Color color = sf::Color::Black);

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
    sf::Vector2f RecSize;
    sf::Text Text;
    sf::RectangleShape Rec;
    sf::RenderTexture Texture;
    sf::Color Cover;
    sf::Color getContrastColor(sf::Color color, float ratio);
    sf::Vector2i getMousePosition() const;
};