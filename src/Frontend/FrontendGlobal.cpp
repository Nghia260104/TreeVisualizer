#include <SFML/Graphics.hpp>
#include <Visualization.hpp>
#include <Execute.hpp>
#include <Status.hpp>
#include <atomic>
#include <string>

sf::RenderWindow window;
sf::Clock Clock;
sf::Font RegularFont, BoldFont, MediumFont, LightFont, HeavyFont, Helvetica, RecRobot, RecOpen, Alga, JB, Arial, ArialBold, Times;
sf::Font TimesBold, Tahoma, Consola, Luvenia, Montelgo, Over, IA, Calibri, Segoe, Abril;
sf::Color BackgroundColor, TextColor, ToolBarColor, SpecialTextColor, Highlight, Blur;
sf::Cursor DefaultCursor, TextCursor, HandCursor;
sf::Mouse mouse;
std::string PICTURE_PATH, UTILS_PATH, DATA_PATH, TREE_PATH, TABLE_PATH, GRAPH_PATH;
int fontsize, interval, textsize, g_size; // 14 -> 18
float g_radius; // 21.5 -> 26
SingleExecute List;
Execute ExtendList;
Handle windowHandle;
std::atomic<bool> keepRunning, run1step;
Frontend::Visualization Visual;