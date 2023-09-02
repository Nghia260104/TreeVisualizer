#include <Arrow.hpp>
#include <math.h>
#include <FrontendGlobal.hpp>
using namespace Frontend;

Arrow::Arrow()
{
    lines.setPrimitiveType(sf::Quads);
    lines.resize(4);
    for (int i = 0; i < 4; i++)
    {
        lines[i].position = sf::Vector2f(0, 0);
        lines[i].color = TextColor;
    }
    point1 = point2 = sf::Vector2f(0, 0);
    thickness = 0.1f * g_radius;
    weight.setString("");
    weight.setCharacterSize(fontsize);
    weight.setFillColor(TextColor);
    weight.setFont(Segoe);
}

Arrow::Arrow(sf::Vector2f pos1, sf::Vector2f pos2, float thick)
    : Arrow()
{
    point1 = pos1;
    point2 = pos2;
    sf::Vector2f dir = point2 - point1;
    sf::Vector2f unit_dir = dir / std::sqrt(dir.x * dir.x + dir.y * dir.y);
    sf::Vector2f unit_perpendicular(-unit_dir.y, unit_dir.x);
    sf::Vector2f sum = point1 + point2;

    thickness = thick;
    sf::Vector2f offset = (thickness / 2.f) * unit_perpendicular;
    sf::Vector2f offset_w = (((thickness + 20) / 2.f) * unit_perpendicular);
    float Tmp_x = offset_w.x, Tmp_y = offset_w.y;
    if (offset_w.y > 0 || (offset_w.y == 0 && offset_w.x > 0))
    {
        Tmp_x *= -1;
        Tmp_y *= -1;
    }
    weight.setPosition(sum.x / 2 + Tmp_x, sum.y / 2 + Tmp_y);
    lines[0].position = point1 - offset;
    lines[1].position = point1 + offset;
    lines[2].position = point2 + offset;
    lines[3].position = point2 - offset;
    for (int i = 0; i < 4; i++)
        lines[i].color = TextColor;
}

void Arrow::setFirstPosition(sf::Vector2f pos)
{
    point1 = pos;
    sf::Vector2f dir = point2 - point1;
    sf::Vector2f unit_dir = dir / std::sqrt(dir.x * dir.x + dir.y * dir.y);
    sf::Vector2f unit_perpendicular(-unit_dir.y, unit_dir.x);
    sf::Vector2f sum = point2 + point1;

    sf::Vector2f offset = (thickness / 2.f) * unit_perpendicular;
    sf::Vector2f offset_w = (((thickness + 20) / 2.f) * unit_perpendicular);
    float Tmp_x = offset_w.x, Tmp_y = offset_w.y;
    if (offset_w.y > 0 || (offset_w.y == 0 && offset_w.x > 0))
    {
        Tmp_x *= -1;
        Tmp_y *= -1;
    }
    weight.setPosition(sum.x / 2 + Tmp_x, sum.y / 2 + Tmp_y);
    lines[0].position = pos - offset;
    lines[1].position = pos + offset;
}

void Arrow::setSecondPosition(sf::Vector2f pos)
{
    point2 = pos;
    sf::Vector2f dir = point2 - point1;
    sf::Vector2f unit_dir = dir / std::sqrt(dir.x * dir.x + dir.y * dir.y);
    sf::Vector2f unit_perpendicular(-unit_dir.y, unit_dir.x);
    sf::Vector2f sum = point2 + point1;

    sf::Vector2f offset = (thickness / 2.f) * unit_perpendicular;
    sf::Vector2f offset_w = (((thickness + 20) / 2.f) * unit_perpendicular);
    float Tmp_x = offset_w.x, Tmp_y = offset_w.y;
    if (offset_w.y > 0 || (offset_w.y == 0 && offset_w.x > 0))
    {
        Tmp_x *= -1;
        Tmp_y *= -1;
    }
    weight.setPosition(sum.x / 2 + Tmp_x, sum.y / 2 + Tmp_y);
    lines[3].position = pos - offset;
    lines[2].position = pos + offset;
}

const sf::Vector2f Arrow::getFirstPosition()
{
    return point1;
}

const sf::Vector2f Arrow::getSecondPosition()
{
    return point2;
}

void Arrow::setThickness(float thick)
{
    thickness = thick;
    sf::Vector2f dir = point2 - point1;
    sf::Vector2f unit_dir = dir / std::sqrt(dir.x * dir.x + dir.y * dir.y);
    sf::Vector2f unit_perpendicular(-unit_dir.y, unit_dir.x);
    sf::Vector2f offset = (thickness / 2.f) * unit_perpendicular;
    sf::Vector2f offset_w = (((thickness + 20) / 2.f) * unit_perpendicular);
    sf::Vector2f sum = point1 + point2;
    float Tmp_x = offset_w.x, Tmp_y = offset_w.y;
    if (offset_w.y > 0 || (offset_w.y == 0 && offset_w.x > 0))
    {
        Tmp_x *= -1;
        Tmp_y *= -1;
    }
    weight.setPosition(sum.x / 2 + Tmp_x, sum.y / 2 + Tmp_y);
    lines[0].position = point1 - offset;
    lines[1].position = point1 + offset;
    lines[2].position = point2 + offset;
    lines[3].position = point2 - offset;
}

const float &Arrow::getThickness()
{
    return thickness;
}

void Arrow::setFillColor(sf::Color color)
{
    for (int i = 0; i < 4; i++)
        lines[i].color = color;
    weight.setFillColor(color);
}

const sf::Color &Arrow::getFillColor()
{
    return lines[0].color;
}

void Arrow::setTextColor(sf::Color color)
{
    weight.setFillColor(color);
}

void Arrow::setFontSize(int size)
{
    weight.setCharacterSize(size);
}

void Arrow::setWeight(const sf::String &val)
{
    sf::Vector2f dir = point2 - point1;
    sf::Vector2f unit_dir = dir / std::sqrt(dir.x * dir.x + dir.y * dir.y);
    sf::Vector2f unit_perpendicular(-unit_dir.y, unit_dir.x);
    sf::Vector2f offset_w = (((thickness + 20) / 2.f) * unit_perpendicular);
    sf::Vector2f sum = point1 + point2;
    float Tmp_x = offset_w.x, Tmp_y = offset_w.y;
    if (offset_w.y > 0 || (offset_w.y == 0 && offset_w.x > 0))
    {
        Tmp_x *= -1;
        Tmp_y *= -1;
    }
    weight.setPosition(sum.x / 2 + Tmp_x, sum.y / 2 + Tmp_y);
    weight.setString(val);
    weight.setOrigin((weight.getFont()->getGlyph(val[0], weight.getCharacterSize(), false)).advance / 2, fontsize / 2);
    hasWeight = 1;
}

const sf::String &Arrow::getWeight()
{
    return weight.getString();
}

bool Arrow::isHidden()
{
    return hidden;
}

void Arrow::hide()
{
    hidden = 1;
}

void Arrow::show()
{
    hidden = 0;
}

void Arrow::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(lines);
    if (hasWeight)
        target.draw(weight);
}
