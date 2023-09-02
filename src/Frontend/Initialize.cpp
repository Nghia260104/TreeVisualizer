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
    Blur = TextColor = sf::Color::Black;
    Blur.a = 50;
    ToolBarColor = sf::Color(22, 120, 224, 255);
    SpecialTextColor = sf::Color::Black;
    Highlight = sf::Color(199, 75, 8, 255);

    // Fonts
    loadFont();

    // Size
    g_size = 9;
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