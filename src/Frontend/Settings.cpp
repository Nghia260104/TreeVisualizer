// #include <Settings.hpp>
// #include <FrontendGlobal.hpp>
// using namespace Frontend;

// Settings::Settings()
// {
// }

// void Settings::create()
// {
//     // Background
//     Texture.create(500, 550);
//     Texture.clear(BackgroundColor);
//     x = window.getSize().x / 2 - 250;
//     y = window.getSize().y / 2 - 275;
//     // Rec.setSize(sf::Vector2f(500, 550));

//     // Size
//     Title[0].setString("Size");
//     Title[0].setFont(Segoe);
//     Title[0].setStyle(sf::Text::Bold);
//     Title[0].setCharacterSize(18);
//     Title[0].setFillColor(SpecialTextColor);
//     Title[0].setPosition(Align, Align);

//     //// Size Component
//     Size[0].setString("Size of Visualization:");
//     Size[0].setFont(Segoe);
//     Size[0].setCharacterSize(16);
//     Size[0].setFillColor(SpecialTextColor);
//     Size[0].setPosition(2 * Align, Align + dis);

//     SizeVal[0].create(AlignVal, Align + dis - 5, 50, 30, 16, sf::Vector2f(20, 15));
//     SizeVal[0].setFillColor(ToolBarColor);
//     SizeVal[0].setTextColor(SpecialTextColor);
//     SizeVal[0].setOutlineColor(SpecialTextColor, SpecialTextColor);
//     SizeVal[0].setOpacity();
//     SizeVal[0].setFont(Consola);
//     SizeVal[0].setCaret();
//     SizeVal[0].setTyping();
//     SizeVal[0].setGlobalPosition(AlignVal + x, Align + dis + y - 5);
//     SizeVal[0].setNumber();
//     SizeVal[0].setLimit(1);
//     SizeVal[0].setText("");

//     Size[1].setString("Maximum height of Tree (Default = 8):");
//     Size[1].setFont(Segoe);
//     Size[1].setCharacterSize(16);
//     Size[1].setFillColor(SpecialTextColor);
//     Size[1].setPosition(2 * Align, Align + 2 * dis);

//     SizeVal[1].create(AlignVal, Align + 2 * dis - 5, 50, 30, 16, sf::Vector2f(20, 15));
//     SizeVal[1].setFillColor(ToolBarColor);
//     SizeVal[1].setTextColor(SpecialTextColor);
//     SizeVal[1].setOutlineColor(SpecialTextColor, SpecialTextColor);
//     SizeVal[1].setOpacity();
//     SizeVal[1].setFont(Consola);
//     SizeVal[1].setCaret();
//     SizeVal[1].setTyping();
//     SizeVal[1].setGlobalPosition(AlignVal + x, Align + 2 * dis + y - 5);
//     SizeVal[1].setNumber();
//     SizeVal[1].setLimit(1);
//     SizeVal[1].setText("");

//     Size[2].setString("Maximum length of Chaining (Default = 5):");
//     Size[2].setFont(Segoe);
//     Size[2].setCharacterSize(16);
//     Size[2].setFillColor(SpecialTextColor);
//     Size[2].setPosition(2 * Align, Align + 3 * dis);

//     SizeVal[2].create(AlignVal, Align + 3 * dis - 5, 50, 30, 16, sf::Vector2f(20, 15));
//     SizeVal[2].setFillColor(ToolBarColor);
//     SizeVal[2].setTextColor(SpecialTextColor);
//     SizeVal[2].setOutlineColor(SpecialTextColor, SpecialTextColor);
//     SizeVal[2].setOpacity();
//     SizeVal[2].setFont(Consola);
//     SizeVal[2].setCaret();
//     SizeVal[2].setTyping();
//     SizeVal[2].setGlobalPosition(AlignVal + x, Align + 3 * dis + y - 5);
//     SizeVal[2].setNumber();
//     SizeVal[2].setLimit(1);
//     SizeVal[2].setText("");
// }