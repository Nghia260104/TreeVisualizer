#include <TreeVisual.hpp>
#include <FrontendGlobal.hpp>
using namespace Frontend;

TreeVisual::TreeVisual()
{
}

void TreeVisual::create()
{
    // Background
    Texture.create(window.getSize().x, window.getSize().y);

    // Title
    Name.setString("Tree");
    Name.setCharacterSize(60);
    Name.setFont(Segoe);
    Name.setStyle(sf::Text::Bold);
    Name.setFillColor(TextColor);
    Name.setOrigin(Name.getGlobalBounds().width / 2, 0);
    Name.setPosition(window.getSize().x / 2, 50);

    // Data Type Button
    DataType[0].create(0, 0, 350, 300, Segoe, 20, "AVL Tree");
    DataType[1].create(0, 0, 350, 300, Segoe, 20, "Max Heap Tree");
    DataType[2].create(0, 0, 350, 300, Segoe, 20, "Min Heap Tree");
    DataType[3].create(0, 0, 350, 300, Segoe, 20, "Trie");
    DataType[4].create(0, 0, 350, 300, Segoe, 20, "234-Tree");
    DataType[0].setImage(TREE_PATH + "AVL.png");
    DataType[1].setImage(TREE_PATH + "MaxHeap.png");
    DataType[2].setImage(TREE_PATH + "MinHeap.png");
    DataType[3].setImage(TREE_PATH + "Trie.png");
    DataType[4].setImage(TREE_PATH + "234Tree.png");
    DataType[0].setPosition(window.getSize().x / 2 - 725, 250);
    DataType[1].setPosition(window.getSize().x / 2 - 175, 250);
    DataType[2].setPosition(window.getSize().x / 2 + 375, 250);
    DataType[3].setPosition(window.getSize().x / 2 - 450, 650);
    DataType[4].setPosition(window.getSize().x / 2 + 100, 650);
    for (int i = 0; i < 5; i++)
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

    // Create DataType
    Avl_tree.create();

    Predraw();
}

// Draw --------------------------------------------------------------------------------------

void TreeVisual::Predraw()
{
    Texture.clear(BackgroundColor);
    Texture.draw(Name);
    for (int i = 0; i < 5; i++)
        Texture.draw(DataType[i]);
    Texture.display();
}

void TreeVisual::drawTexture(const int &layer)
{
    Texture.clear(BackgroundColor);
    if (layer == Tree)
    {
        Texture.draw(Name);
        for (int i = 0; i < 5; i++)
            Texture.draw(DataType[i]);
    }
    if (layer == avl)
    {
        Avl_tree.drawTexture();
        Texture.draw(Avl_tree);
    }
    Texture.display();
}

void TreeVisual::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    sf::Sprite sprite(Texture.getTexture());
    target.draw(sprite);
}

// Misc -----------------------------------------------------------------------------------------

void TreeVisual::processEvent(const sf::Event &event, int &layer)
{
    if (layer == Tree)
    {
        for (int i = 0; i < 5; i++)
        {
            Texture.draw(DataType[i]);
            if (DataType[i].isPressed(event))
            {
                switch (i)
                {
                case 0:
                    layer = avl;
                    Avl_tree.clear();
                    Avl_tree.drawTexture();
                    drawTexture(layer);
                    break;
                
                default:
                    break;
                }
            }
        }
    }
    if (layer == avl)
    {
        Avl_tree.processEvent(event);
        Texture.draw(Avl_tree);
    }
    Texture.display();
}

bool TreeVisual::mouseOnButton(const sf::Vector2i &MousePos)
{
    bool check = 0;
    for (int i = 0; i < 5; i++)
        check |= DataType[i].mouseOn(MousePos);
    return check;
}