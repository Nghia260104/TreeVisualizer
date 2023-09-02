#include <Button.hpp>
#include <FrontendGlobal.hpp>
using namespace Frontend;

extern sf::RenderWindow window;

// Constructor //////////////////////////////////////////////////////////////////////////////////

Button::Button()
{
    Cover = sf::Color::Transparent;
}

Button::Button(sf::String S)
{
    setPosition();
    setSize();
    setFillColor();
    setOutline();
    setText(S);
    hasImage = 0;
    Image_x = Image_y = 0;
    i_outline_thickness = 0;
    hasImageOutline = 0;
    Cover = sf::Color::Transparent;
}

void Button::create(float a, float b, float w, float h, sf::Font &font, unsigned int fontsize, sf::String S)
{
    setPosition(a, b);
    setSize(w, h);
    setFillColor();
    setOutline();
    setFont(font);
    setFontSize(fontsize);
    setText(S);
    setTextPos();
    hasImage = 0;
    Image_x = Image_y = 0;
    i_outline_thickness = 0;
    hasImageOutline = 0;
    Cover = sf::Color::Transparent;
}

// Box ///////////////////////////////////////////////////////////////////////////////////////////////

void Button::setPosition(float a, float b)
{
    x = a;
    y = b;
    g_x = a;
    g_y = b;
}

void Button::setGlobalPosition(float a, float b)
{
    g_x = a;
    g_y = b;
}

void Button::setSize(float w, float h)
{
    Rec.setSize(sf::Vector2f(w, h));
    RecSize = sf::Vector2f(w, h);
    Texture.create(w, h);
}

void Button::setFillColor(sf::Color color, float ratio)
{
    Rec.setFillColor(color);
    if (ratio > 0)
    {
        if (ratio < 4.5)
            ratio = 4.5;
        Text.setFillColor(getContrastColor(color, ratio));
    }
}

const sf::Color &Button::getFillColor()
{
    return Rec.getFillColor();
}

void Button::setOutline(sf::Color color, float thick)
{
    Rec.setOutlineColor(color);
    Rec.setOutlineThickness(-1.0f * thick);
}

// Text ////////////////////////////////////////////////////////////////////////////////////////////////

void Button::setFont(sf::Font &font)
{
    Text.setFont(font);
}

void Button::setFontStyle(sf::Text::Style style)
{
    Text.setStyle(style);
}

void Button::setFontSize(unsigned int fontsize)
{
    Text.setCharacterSize(fontsize);
}

void Button::setText(sf::String S)
{
    Text.setString(S);
}

void Button::setTextPos()
{
    Text.setOrigin(Text.getGlobalBounds().width / 2, 1.0f * Text.getCharacterSize() / 2);
    Text.setPosition(RecSize.x / 2, RecSize.y / 2);
}

void Button::setTextPos(float y)
{
    Text.setOrigin(Text.getGlobalBounds().width / 2, 1.0f * Text.getCharacterSize() / 2);
    Text.setPosition(RecSize.x / 2, y);
}

void Button::setTextPos(float x, float y, Button::Align Type)
{
    switch (Type)
    {
    case Button::Align::Left:
        Text.setOrigin(0, 1.0f * Text.getCharacterSize() / 2);
        break;
    case Button::Align::Center:
        Text.setOrigin(Text.getGlobalBounds().width / 2, 1.0f * Text.getCharacterSize() / 2);
        break;
    case Button::Align::Right:
        Text.setOrigin(Text.getGlobalBounds().width, 1.0f * Text.getCharacterSize() / 2);
        break;
    default:
        break;
    }
    Text.setPosition(x, y);
}

void Button::setTextColor(sf::Color color)
{
    Text.setFillColor(color);
}

// Image ////////////////////////////////////////////////////////////////////////////////////////

void Button::setImage(const std::string &fileName)
{
    hasImage = 1;
    Image.loadFromFile(fileName);
}

void Button::setImagePosition(float x, float y)
{
    Image_x = x;
    Image_y = y;
}

void Button::setImageOutline(sf::Color color, float thick)
{
    hasImageOutline = 1;
    ImageOutlineColor = color;
    i_outline_thickness = thick;
}

void Button::setImageColor(sf::Color color)
{
    hasImageColor = true;
    CoverImage = color;
}

// Misc ///////////////////////////////////////////////////////////////////////////////////////////////

bool Button::isPressed(sf::Event event)
{
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    {
        sf::Vector2i MousePos = getMousePosition();
        if (mouseOn(MousePos))
            return true;
    }
    return false;
}

void Button::setCoverColor(sf::Color color)
{
    Cover = color;
}

sf::String Button::getText() const
{
    return Text.getString();
}

// Draw ///////////////////////////////////////////////////////////////////////////////////////////////

void Button::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    sf::Sprite sprite(Texture.getTexture());
    sprite.setPosition(x, y);
    if (mouseOn(getMousePosition()))
        sprite.setColor(Cover);
    target.draw(sprite);
}

void Button::drawTexture()
{
    Texture.draw(Rec);
    Texture.draw(Text);
    if (hasImage)
    {
        if (hasImageOutline)
        {
            sf::RectangleShape Tmp(sf::Vector2f(Image.getSize().x + 2 * i_outline_thickness, Image.getSize().y + 2 * i_outline_thickness));
            Tmp.setFillColor(ImageOutlineColor);
            Tmp.setPosition(Image_x - i_outline_thickness, Image_y - i_outline_thickness);
            Texture.draw(Tmp);
        }
        sf::Sprite sprite(Image);
        if (hasImageColor)
            sprite.setColor(CoverImage);     
        sprite.setPosition(Image_x, Image_y);
        Texture.draw(sprite);
    }
    Texture.display();
}

// Private ////////////////////////////////////////////////////////////////////////////////////////////

sf::Color Button::getContrastColor(sf::Color color, float ratio)
{
    const float Ratio = ratio;
    float L = (color.r * 299 + color.g * 587 + color.b * 114);
    float L1 = (L + 50) / Ratio - 50;
    float L2 = (L + 50) * Ratio - 50;
    sf::Color color10(L1 / 1000 * 299, L1 / 1000 * 587, L1 / 1000 * 114, 255);
    sf::Color color20(L2 / 1000 * 299, L2 / 1000 * 587, L2 / 1000 * 114, 255);
    if (L2 > 1000)
        return color10;
    if (L1 < 0)
        return color20;
    if (abs(L1 - L) > abs(L2 - L))
        return color10;
    else
        return color20;
}

sf::Vector2i Button::getMousePosition() const
{
    sf::Mouse mouse;
    return mouse.getPosition(window);
}

bool Button::mouseOn(const sf::Vector2i &MousePos) const
{
    if (g_x < MousePos.x && MousePos.x < g_x + RecSize.x &&
        g_y < MousePos.y && MousePos.y < g_y + RecSize.y)
        return true;
    return false;
}