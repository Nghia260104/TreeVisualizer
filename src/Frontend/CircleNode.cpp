#include <CircleNode.hpp>
#include <FrontendGlobal.hpp>
#include <math.h>
using namespace Frontend;

// Constructor ----------------------------------------------------------------------------

CircleNode::CircleNode()
{
    Par = nullptr;
    toPar = nullptr;
    hidden = false;
    Child.resize(0);
    setRadius(g_radius);
    x = y = 0;
    setFillColor(BackgroundColor);
    setOutline(TextColor);
    Circle.setPrimitiveType(sf::TriangleFan);
    Outline.setPrimitiveType(sf::TriangleFan);
    Texture.create(68, 68);
    Texture.setSmooth(true);
    Text.setFont(Segoe);
    Text.setCharacterSize(fontsize);
    Text.setFillColor(TextColor);
    Text.setPosition(34, 34);
}

CircleNode::CircleNode(const CircleNode &val)
{
    Par = val.Par;
    toPar = val.toPar;
    Child = val.Child;
    hidden = val.hidden;
    setRadius(val.r);
    x = val.x;
    y = val.y;
    setFillColor(BackgroundColor);
    setOutline(TextColor);
    Circle.setPrimitiveType(sf::TriangleFan);
    Outline.setPrimitiveType(sf::TriangleFan);
    Texture.create(68, 68);
    Texture.setSmooth(true);
    Text.setFont(Segoe);
    Text.setCharacterSize(fontsize);
    Text.setFillColor(TextColor);
    Text.setPosition(34, 34);
    setText(val.Text);
}

CircleNode::CircleNode(const CircleNode &&val)
{
    Par = val.Par;
    toPar = val.toPar;
    Child = val.Child;
    hidden = val.hidden;
    setRadius(val.r);
    x = val.x;
    y = val.y;
    setFillColor(BackgroundColor);
    setOutline(TextColor);
    Circle.setPrimitiveType(sf::TriangleFan);
    Outline.setPrimitiveType(sf::TriangleFan);
    Texture.create(68, 68);
    Texture.setSmooth(true);
    Text.setFont(Segoe);
    Text.setCharacterSize(fontsize);
    Text.setFillColor(TextColor);
    Text.setPosition(34, 34);
    setText(val.Text);
}

CircleNode::CircleNode(int val)
    : CircleNode()
{
    setInt(val);
}

CircleNode::CircleNode(const std::string &str)
{
    setStr(str);
}

// Shape ---------------------------------------------------------------------------------------------

sf::Vector2f CircleNode::getPosition()
{
    return sf::Vector2f(x, y);
}

void CircleNode::setPosition(float a, float b)
{
    x = a;
    y = b;
}

void CircleNode::setRadius(float r_)
{
    r = r_;
    float angle;
    Circle.resize(2 + numVertices(0.9f * r, angle));
    Circle[0].position = sf::Vector2f(34, 34);
    for (int i = 1; i < Circle.getVertexCount(); i++)
        Circle[i].position = sf::Vector2f(34 + 0.9f * r * cos((i - 1) * angle),
                                          34 + 0.9f * r * sin((i - 1) * angle));
    Outline.resize(2 + numVertices(r, angle));
    Outline[0].position = sf::Vector2f(34, 34);
    for (int i = 1; i < Outline.getVertexCount(); i++)
        Outline[i].position = sf::Vector2f(34 + r * cos((i - 1) * angle),
                                           34 + r * sin((i - 1) * angle));
    setFillColor(Fill);
    setOutline(Cover);
}

void CircleNode::setFillColor(sf::Color fill)
{
    Fill = fill;
    for (int i = 0; i < Circle.getVertexCount(); i++)
        Circle[i].color = fill;
}

void CircleNode::setOutline(sf::Color out)
{
    Cover = out;
    for (int i = 0; i < Outline.getVertexCount(); i++)
        Outline[i].color = out;
}

const sf::Color &CircleNode::getOutlineColor()
{
    return Cover;
}

const sf::Color &CircleNode::getFillColor()
{
    return Fill;
}

// Value ----------------------------------------------------------------------------------------------------

void CircleNode::setInt(int val)
{
    Text.setString(std::to_string(val));
    Text.setOrigin(Text.getGlobalBounds().width / 2, Text.getGlobalBounds().height);
    Text.setPosition(34, 34);
}

void CircleNode::setStr(const std::string &str)
{
    Text.setString(str);
    Text.setOrigin(Text.getGlobalBounds().width / 2, Text.getGlobalBounds().height);
    Text.setPosition(34, 34);
}

void CircleNode::setText(const sf::String &str)
{
    Text.setString(str);
    Text.setOrigin(Text.getGlobalBounds().width / 2, Text.getGlobalBounds().height);
    Text.setPosition(34, 34);
}

void CircleNode::setText(const sf::Text &TmpText)
{
    Text = TmpText;
    Text.setOrigin(Text.getGlobalBounds().width / 2, Text.getGlobalBounds().height);
    Text.setPosition(34, 34);
}

void CircleNode::setTextColor(sf::Color color)
{
    Text.setFillColor(color);
}

const sf::Color &CircleNode::getTextColor()
{
    return Text.getFillColor();
}

const sf::Text &CircleNode::getText()
{
    return Text;
}

// Misc ---------------------------------------------------------------------------------------------

int CircleNode::numVertices(float r_, float &angle)
{
    angle = acos(2. * (1.0f - 0.25 / r_) * (1.0f - 0.25 / r_) - 1);
    return ceil(2 * std::numbers::pi / angle);
}

// Draw -------------------------------------------------------------------------------------------

void CircleNode::hide()
{
    hidden = true;
}

void CircleNode::show()
{
    hidden = false;
}

bool CircleNode::isHidden()
{
    return hidden;
}

void CircleNode::drawTexture()
{
    Texture.clear(sf::Color::Transparent);
    Texture.draw(Outline);
    Texture.draw(Circle);
    Texture.draw(Text);
    Texture.display();
}

void CircleNode::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    sf::Sprite sprite(Texture.getTexture());
    sprite.setPosition(x - 34, y - 34);
    target.draw(sprite);
}