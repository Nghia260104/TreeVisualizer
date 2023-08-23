// #pragma once
#include <SFML/Graphics.hpp>
#include <Visualization.hpp>
#include <Execute.hpp>
#include <Status.hpp>
#include <atomic>
#include <string>

extern sf::RenderWindow window;
extern sf::Clock Clock;
extern sf::Font RegularFont, BoldFont, MediumFont, LightFont, HeavyFont, Helvetica, RecRobot, RecOpen, Alga, JB, Arial, ArialBold, Times;
extern sf::Font TimesBold, Tahoma, Consola, Luvenia, Montelgo, Over, IA, Calibri, Segoe, Abril;
extern sf::Color BackgroundColor, TextColor, ToolBarColor, SpecialTextColor, Highlight;
extern sf::Cursor DefaultCursor, TextCursor, HandCursor;
extern sf::Mouse mouse;
extern std::string PICTURE_PATH, UTILS_PATH, DATA_PATH, TREE_PATH, TABLE_PATH, GRAPH_PATH;
extern int fontsize, interval, textsize;
extern float g_radius;
extern SingleExecute List;
extern Execute ExtendList;
extern Handle windowHandle;
extern std::atomic<bool> keepRunning, run1step;
extern Frontend::Visualization Visual;
// extern int LeftWindowWidth, RightWindowWidth;