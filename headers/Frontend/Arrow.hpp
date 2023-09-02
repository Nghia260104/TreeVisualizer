#pragma once
#include <SFML/Graphics.hpp>

namespace Frontend
{
    class Arrow : public sf::Drawable
    {
        sf::VertexArray lines;
        float thickness;
        bool hidden, hasWeight;
        sf::Vector2f point1, point2;
        sf::Text weight;
    public:
        Arrow();
        Arrow(sf::Vector2f pos1, sf::Vector2f pos2, float thick);
        void setThickness(float thick);
        const float &getThickness();
        void setFirstPosition(sf::Vector2f pos);
        void setSecondPosition(sf::Vector2f pos);
        const sf::Vector2f getFirstPosition();
        const sf::Vector2f getSecondPosition();
        void setFillColor(sf::Color color);
        void setTextColor(sf::Color color);
        void setFontSize(int size);
        const sf::Color &getFillColor();
        void setWeight(const sf::String &val);
        const sf::String &getWeight();
        bool isHidden();
        void hide();
        void show();
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    };
}