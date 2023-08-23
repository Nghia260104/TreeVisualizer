#include <Initialize.hpp>
#include <stdlib.h>

void Frontend::Initialize()
{
    // Data path

    PICTURE_PATH = "../resources/Pictures/";
    UTILS_PATH = PICTURE_PATH + "Utils/";
    DATA_PATH = PICTURE_PATH + "Data Structure/";
    TREE_PATH = DATA_PATH + "Tree/";
    TABLE_PATH = DATA_PATH + "Hash Table/";
    GRAPH_PATH = DATA_PATH + "Graph/";

    // Cursor
    DefaultCursor.loadFromSystem(sf::Cursor::Arrow);
    TextCursor.loadFromSystem(sf::Cursor::Text);
    HandCursor.loadFromSystem(sf::Cursor::Hand);

    // Color
    BackgroundColor = sf::Color(246, 241, 241, 255);
    TextColor = sf::Color::Black;
    ToolBarColor = sf::Color::Cyan;
    SpecialTextColor = sf::Color::Black;
    Highlight = sf::Color(255, 127, 0, 255);

    // Fonts
    loadFont();

    // Size
    g_radius = 26;
    fontsize = 18;
    textsize = 16;
    interval = 1200;

    // Random things
    srand(time(NULL));

    // Bool variable
    keepRunning = 0;
    run1step = 0;

    // Main window
    Visual.create();
}