#pragma once
#include <SFML/Graphics.hpp>
#include <Button.hpp>
#include <TextBox.hpp>

namespace Frontend
{
    class Settings : public sf::Drawable
    {
    public:
        // Constructor
        Settings();
        void create();
        void ReSetting();
        void Prepare();

        // Misc
        void processEvent(const sf::Event &event);

        // Draw
        void drawTexture();
        virtual void draw(sf::RenderTarget &target, sf::RenderStates state) const;

    private:
        float x, y;
        const int Align = 50, dis = 50, AlignVal = 450;
        const float radius[10] = {21.5, 22, 22.5, 23, 23.5, 24, 24.5, 25, 25.5, 26};
        const int font[5] = {14, 15, 16, 17, 18};
        int sz, cur;
        sf::RenderTexture Texture;
        // sf::RectangleShape Rec;
        sf::Text Title[3];
        sf::Text Size;
        TextBox SizeVal;
        sf::Text Color[5];
        // Background Color
        // Text and Outline Color
        // ToolBar and Accessories Color
        // Accessories Text and Outline Color
        // Highlight Color
        Button Sample[5];
        Button Common[16];
        // Red 255, 0, 0
        // Orange 255, 127, 0
        // Yellow 255, 255, 0
        // Chartreuse Green 127, 255, 0
        // Green 0, 255, 0
        // Spring Green 0, 255, 127
        // Cyan 0, 255, 255
        // Azure 0, 127, 255
        // Blue 0, 0, 255
        // Violet 127, 0, 255
        // Magenta 255, 0, 255
        // Rose 255, 0, 127
        //--------------------------------------------------------------------------------------
        // Black 0, 0, 0
        // Brown 150, 75, 0
        // Gray 127, 127, 127
        // White 255, 255, 255
        sf::Text index[3];
        TextBox R, G, B;
        sf::Text Theme[2];
        Button ThemeType[2];
        // Dark Theme
        // Light Theme
        Button Cancel, OK;
    };
}