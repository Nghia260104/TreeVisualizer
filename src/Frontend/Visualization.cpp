#include <Visualization.hpp>
#include <FrontendGlobal.hpp>
// #include <cmath>
using namespace Frontend;

Visualization::Visualization()
{
}

void Visualization::create()
{
    // Background
    Texture.create(window.getSize().x, window.getSize().y);

    // Tool bar
    ToolBar[0].create(window.getSize().x - 200, 0, 100, 25, Segoe, 16, "Settings");
    ToolBar[0].setTextPos(35, 10);
    ToolBar[0].setTextColor(SpecialTextColor);
    ToolBar[0].setFillColor(ToolBarColor);
    ToolBar[0].setCoverColor(sf::Color(__max((ToolBarColor.r - 50) % 255, (ToolBarColor.r + 50) % 255),
                                       __max((ToolBarColor.g - 50) % 255, (ToolBarColor.g + 50) % 255),
                                       __max((ToolBarColor.b - 50) % 255, (ToolBarColor.b + 50) % 255), 50));
    ToolBar[0].setOutline(SpecialTextColor);
    ToolBar[0].setImage(UTILS_PATH + "settings.png");
    ToolBar[0].drawTexture();

    ToolBar[1].create(window.getSize().x - 100, 0, 100, 25, Segoe, 16, "About");
    ToolBar[1].setTextPos(35, 10);
    ToolBar[1].setTextColor(SpecialTextColor);
    ToolBar[1].setFillColor(ToolBarColor);
    ToolBar[1].setCoverColor(sf::Color(__max((ToolBarColor.r - 50) % 255, (ToolBarColor.r + 50) % 255),
                                       __max((ToolBarColor.g - 50) % 255, (ToolBarColor.g + 50) % 255),
                                       __max((ToolBarColor.b - 50) % 255, (ToolBarColor.b + 50) % 255), 50));
    ToolBar[1].setOutline(SpecialTextColor);
    ToolBar[1].setImage(UTILS_PATH + "info.png");
    ToolBar[1].drawTexture();

    // Back button
    Back.create(0, 0, 50, 35, Segoe, 1, "");
    Back.setFillColor(ToolBarColor);
    Back.setCoverColor(sf::Color(__max((ToolBarColor.r - 50) % 255, (ToolBarColor.r + 50) % 255),
                                 __max((ToolBarColor.g - 50) % 255, (ToolBarColor.g + 50) % 255),
                                 __max((ToolBarColor.b - 50) % 255, (ToolBarColor.b + 50) % 255), 50));
    Back.setOutline(SpecialTextColor);
    Back.setImage(UTILS_PATH + "back.png");
    Back.setImageColor(SpecialTextColor);
    Back.drawTexture();

    // Title
    Name.setString("Tree Visualization");
    Name.setCharacterSize(60);
    Name.setFont(Segoe);
    Name.setStyle(sf::Text::Bold);
    Name.setFillColor(TextColor);
    Name.setOrigin(Name.getGlobalBounds().width / 2, 0);
    Name.setPosition(window.getSize().x / 2, 50);

    // Data Type Button
    DataType[0].create(0, 0, 350, 300, Segoe, 20, "Hash Table");
    DataType[1].create(0, 0, 350, 300, Segoe, 20, "Tree");
    DataType[2].create(0, 0, 350, 300, Segoe, 20, "Graph");
    DataType[0].setImage(TABLE_PATH + "HashTable.png");
    DataType[1].setImage(TREE_PATH + "Tree.png");
    DataType[2].setImage(GRAPH_PATH + "Graph.png");
    DataType[0].setPosition(window.getSize().x / 2 - 625, 350);
    DataType[1].setPosition(window.getSize().x / 2 - 175, 350);
    DataType[2].setPosition(window.getSize().x / 2 + 275, 350);
    for (int i = 0; i < 3; i++)
    {
        // DataType[i].setFontStyle(sf::Text::Style::Bold);
        DataType[i].setFillColor(ToolBarColor);
        DataType[i].setTextColor(SpecialTextColor);
        DataType[i].setOutline(SpecialTextColor);
        DataType[i].setTextPos(25, 275);
        DataType[i].setImagePosition(25, 20);
        DataType[i].setImageOutline(SpecialTextColor);
        DataType[i].setCoverColor(sf::Color(__max((ToolBarColor.r - 50) % 255, (ToolBarColor.r + 50) % 255),
                                            __max((ToolBarColor.g - 50) % 255, (ToolBarColor.g + 50) % 255),
                                            __max((ToolBarColor.b - 50) % 255, (ToolBarColor.b + 50) % 255), 5));
        DataType[i].drawTexture();
    }

    // DataType Screen
    TableScreen.create();
    TreeScreen.create();
    SettingScreen.create();
    GraphScreen.create();

    // Initialize
    layer = 0;

    drawTexture();
}

// Draw ---------------------------------------------------------------------------

void Visualization::drawTexture()
{
    Texture.clear(BackgroundColor);
    if (layer == option)
    {
        SettingScreen.drawTexture();
        Texture.draw(SettingScreen);
    }
    if (layer == Home)
    {
        Texture.clear(BackgroundColor);
        Texture.draw(Name);
        for (int i = 0; i < 3; i++)
            Texture.draw(DataType[i]);
    }
    if (layer == Table || layer == Linear || layer == Quad || layer == DoubleHashing || layer == Chain)
    {
        TableScreen.drawTexture(layer);
        Texture.draw(TableScreen);
    }
    if (layer == Tree || layer == avl || layer == B4 || layer == MaxHeap || layer == MinHeap || layer == Trie)
    {
        TreeScreen.drawTexture(layer);
        Texture.draw(TreeScreen);
    }
    if (layer == Graph)
    {
        GraphScreen.drawTexture();
        Texture.draw(GraphScreen);
    }
    if (layer != Home && layer != option && layer != Info)
    {
        Texture.draw(Back);
    }
    for (int i = 0; i < 2; i++)
        Texture.draw(ToolBar[i]);
    Texture.display();
}

void Visualization::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    sf::Sprite sprite(Texture.getTexture());
    target.draw(sprite);
}

// Misc ----------------------------------------------------------------------------------

void Visualization::processEvent(const sf::Event &event)
{
    if (layer == option)
    {
        Texture.draw(SettingScreen);
        SettingScreen.processEvent(event);
    }
    if (layer == Home)
    {
        for (int i = 0; i < 3; i++)
        {
            Texture.draw(DataType[i]);
            if (DataType[i].isPressed(event))
            {
                layer = i + 1;
                if (layer == Graph)
                {
                    GraphScreen.clear();
                    windowHandle.setGraph();
                }
                else windowHandle.setNonGraph();
                drawTexture();
                return;
            }
        }
    }
    if (layer == Table || layer == Linear || layer == Quad || layer == DoubleHashing || layer == Chain)
    {
        TableScreen.processEvent(event, layer);
        Texture.draw(TableScreen);
    }
    if (layer == Tree || layer == avl || layer == B4 || layer == MaxHeap || layer == MinHeap || layer == Trie)
    {
        TreeScreen.processEvent(event, layer);
        Texture.draw(TreeScreen);
    }
    if (layer == Graph)
    {
        GraphScreen.processEvent(event);
        Texture.draw(GraphScreen);
    }

    if (layer != option && layer != Info)
        for (int i = 0; i < 2; i++)
        {
            Texture.draw(ToolBar[i]);
            if (ToolBar[i].isPressed(event))
            {
                if (i == 0)
                {
                    prev_layer = layer;
                    layer = option;
                    SettingScreen.Prepare();
                    drawTexture();
                    return;
                }
            }
        }
    if (layer != Home && layer != option && layer != Info)
    {
        Texture.draw(Back);
        if (Back.isPressed(event))
        {
            if (layer == Table || layer == Tree || layer == Graph)
            {
                layer = Home;
            }
            if (layer == Linear || layer == Quad || layer == DoubleHashing)
            {
                layer = Table;
            }
            if (layer == avl || layer == B4 || layer == MaxHeap || layer == MinHeap || layer == Trie)
            {
                layer = Tree;
            }
            drawTexture();
        }
    }
}

bool Visualization::mouseOnButton(const sf::Vector2i &MousePos)
{
    bool check = 0;
    check |= Back.mouseOn(MousePos);
    for (int i = 0; i < 2; i++)
        check |= ToolBar[i].mouseOn(MousePos);
    for (int i = 0; i < 3; i++)
        check |= DataType[i].mouseOn(MousePos);
    return check;
}

void Visualization::setLayer()
{
    layer = prev_layer;
    drawTexture();
}

void Visualization::ReSetting()
{
    setLayer();
    List.clear();
    windowHandle.clear();
    for (int i = 0; i < 2; i++)
    {
        ToolBar[i].setTextColor(SpecialTextColor);
        ToolBar[i].setFillColor(ToolBarColor);
        ToolBar[i].setCoverColor(sf::Color(__max((ToolBarColor.r - 50) % 255, (ToolBarColor.r + 50) % 255),
                                           __max((ToolBarColor.g - 50) % 255, (ToolBarColor.g + 50) % 255),
                                           __max((ToolBarColor.b - 50) % 255, (ToolBarColor.b + 50) % 255), 5));
        ToolBar[i].drawTexture();
    }
    for (int i = 0; i < 3; i++)
    {
        DataType[i].setTextColor(SpecialTextColor);
        DataType[i].setFillColor(ToolBarColor);
        DataType[i].setCoverColor(sf::Color(__max((ToolBarColor.r - 50) % 255, (ToolBarColor.r + 50) % 255),
                                            __max((ToolBarColor.g - 50) % 255, (ToolBarColor.g + 50) % 255),
                                            __max((ToolBarColor.b - 50) % 255, (ToolBarColor.b + 50) % 255), 5));
        DataType[i].drawTexture();
    }
    Name.setFillColor(TextColor);
    Back.setFillColor(ToolBarColor);
    Back.setImageColor(SpecialTextColor);
    Back.setCoverColor(sf::Color(__max((ToolBarColor.r - 50) % 255, (ToolBarColor.r + 50) % 255),
                                 __max((ToolBarColor.g - 50) % 255, (ToolBarColor.g + 50) % 255),
                                 __max((ToolBarColor.b - 50) % 255, (ToolBarColor.b + 50) % 255), 5));
    Back.drawTexture();
    SettingScreen.ReSetting();
    TableScreen.ReSetting();
    TreeScreen.ReSetting();
    GraphScreen.ReSetting();
    Texture.clear(BackgroundColor);
    drawTexture();
}