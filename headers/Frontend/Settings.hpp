// #pragma once
// #include <SFML/Graphics.hpp>
// #include <Button.hpp>
// #include <TextBox.hpp>

// namespace Frontend
// {
//     class Settings : public sf::Drawable
//     {
//     public:
//         // Constructor
//         Settings();
//         void create();

//         // Misc
//         void processEvent(const sf::Event &event);

//         // Draw
//         virtual void draw(sf::RenderTarget &target, sf::RenderStates state) const;

//     private:
//         float x, y;
//         const int Align = 50, dis = 70, AlignVal = 450;
//         sf::RenderTexture Texture;
//         // sf::RectangleShape Rec;
//         sf::Text Title[3];
//         sf::Text Size[3];
//         TextBox SizeVal[3];
//         sf::Text Color[4];
//         // Background Color
//         // Text and Outline Color
//         // ToolBar and Accessories Color
//         // Accessories Text and Outline Color
//         Button Sample[4];
//         Button Common[16];
//         // Red 255, 0, 0
//         // Orange 255, 127, 0
//         // Yellow 255, 255, 0
//         // Chartreuse Green 127, 255, 0
//         // Green 0, 255, 0
//         // Spring Green 0, 255, 127
//         // Cyan 0, 255, 255
//         // Azure 0, 127, 255
//         // Blue 0, 0, 255
//         // Violet 127, 0, 255
//         // Magenta 255, 0, 255
//         // Rose 255, 0, 127
//         //--------------------------------------------------------------------------------------
//         // Black 0, 0, 0
//         // Brown 150, 75, 0
//         // Gray 127, 127, 127
//         // White 255, 255, 255
//         sf::Text index[3];
//         TextBox R, G, B;
//         sf::Text Theme;
//         Button ThemeType[2];
//         // Dark Theme
//         // Light Theme
//         Button Cancel, OK;
//     };
// }