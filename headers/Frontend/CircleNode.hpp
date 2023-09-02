#pragma once
#include <SFML/Graphics.hpp>
#include <Arrow.hpp>
#include <string>
#include <vector>

namespace Frontend
{
    class CircleNode : public sf::Drawable
    {
        float x, y;
        float r;
        bool hidden;
        sf::RenderTexture Texture;
        sf::VertexArray Circle, Outline;
        sf::Text Text;
        sf::Color Fill, Cover;

        int numVertices(float r_, float &angle);

    public:
        // Pointer
        CircleNode *Par = nullptr;
        std::vector<CircleNode *> Child;
        Arrow *toPar = nullptr;

        // Constructor
        CircleNode();
        CircleNode(const CircleNode &val);
        CircleNode(const CircleNode &&val);
        CircleNode(int val);
        CircleNode(const std::string &str);

        // Shape
        sf::Vector2f getPosition();
        void setPosition(float a, float b);
        void setRadius(float r_ = 25); // 20.5 -> 25
        void setFillColor(sf::Color fill = sf::Color::White);
        void setOutline(sf::Color out = sf::Color::Black);
        const sf::Color &getOutlineColor();
        const sf::Color &getFillColor();

        // Value
        void setInt(int val);
        void setStr(const std::string &str);
        void setText(const sf::String &str);
        void setText(const sf::Text &TmpText);
        void setTextColor(sf::Color color);
        const sf::Color &getTextColor();
        const sf::Text &getText();

        // Draw
        void hide();
        void show();
        bool isHidden();
        void drawTexture();
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

        // Misc
        bool mouseOn(const sf::Vector2i &MousePos);

        // Destructor
        ~CircleNode(){};
    };
}