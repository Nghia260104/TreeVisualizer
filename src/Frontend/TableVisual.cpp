#include <TableVisual.hpp>
#include <FrontendGlobal.hpp>
using namespace Frontend;

TableVisual::TableVisual()
{
}

void TableVisual::create()
{
    // Background
    Texture.create(window.getSize().x, window.getSize().y);

    // Title
    Name.setString("Hash Table");
    Name.setCharacterSize(60);
    Name.setFont(Segoe);
    Name.setStyle(sf::Text::Bold);
    Name.setFillColor(TextColor);
    Name.setOrigin(Name.getGlobalBounds().width / 2, 0);
    Name.setPosition(window.getSize().x / 2, 50);

    // Data Type Button
    DataType[0].create(0, 0, 350, 300, Segoe, 20, "Linear Probing");
    DataType[1].create(0, 0, 350, 300, Segoe, 20, "Quadratic Probing");
    DataType[2].create(0, 0, 350, 300, Segoe, 20, "Double Hashing");
    // DataType[3].create(0, 0, 350, 300, Segoe, 20, "Chaining");
    DataType[0].setImage(TABLE_PATH + "LinearProbing.png");
    DataType[1].setImage(TABLE_PATH + "QuadraticProbing.png");
    DataType[2].setImage(TABLE_PATH + "DoubleHashing.png");
    // DataType[3].setImage(TABLE_PATH + "Chaining.png");
    DataType[0].setPosition(window.getSize().x / 2 - 625, 300);
    DataType[1].setPosition(window.getSize().x / 2 - 175, 300);
    DataType[2].setPosition(window.getSize().x / 2 + 275, 300);
    // DataType[3].setPosition(window.getSize().x / 2 + 500, 300);
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

    // Create DataType
    Linear.create();
    Quadratic.create();
    Hash.create();
    // Tmp.setType(Backend::Probing::Linear);
    // Tmp.create();

    Predraw();
}

// Draw --------------------------------------------------------------------------------------

void TableVisual::Predraw()
{
    Texture.clear(BackgroundColor);
    Texture.draw(Name);
    for (int i = 0; i < 3; i++)
        Texture.draw(DataType[i]);
    Texture.display();
}

void TableVisual::drawTexture(const int &layer)
{
    Texture.clear(BackgroundColor);
    if (layer == Table)
    {
        Texture.draw(Name);
        for (int i = 0; i < 3; i++)
            Texture.draw(DataType[i]);
    }
    if (layer == Li)
    {
        Linear.drawTexture();
        Texture.draw(Linear);
    }
    if (layer == Quad)
    {
        Quadratic.drawTexture();
        Texture.draw(Quadratic);
    }
    if (layer == DoubleHashing)
    {
        Hash.drawTexture();
        Texture.draw(Hash);
    }
    Texture.display();
}

void TableVisual::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    sf::Sprite sprite(Texture.getTexture());
    target.draw(sprite);
}

// Misc -----------------------------------------------------------------------------------------

void TableVisual::processEvent(const sf::Event &event, int &layer)
{
    if (layer == Table)
    {
        for (int i = 0; i < 3; i++)
        {
            Texture.draw(DataType[i]);
            if (DataType[i].isPressed(event))
            {
                switch (i)
                {
                case 0:
                    layer = Li;
                    Linear.clear();
                    Linear.drawTexture();
                    drawTexture(layer);
                    break;
                case 1:
                    layer = Quad;
                    Quadratic.clear();
                    Quadratic.drawTexture();
                    drawTexture(layer);
                    break;
                case 2:
                    layer = DoubleHashing;
                    Hash.clear();
                    Hash.drawTexture();
                    drawTexture(layer);
                    break;
                default:
                    break;
                }
            }
        }
    }
    if (layer == Li)
    {
        Linear.processEvent(event);
        Texture.draw(Linear);
    }
    if (layer == Quad)
    {
        Quadratic.processEvent(event);
        Texture.draw(Quadratic);
    }
    if (layer == DoubleHashing)
    {
        Hash.processEvent(event);
        Texture.draw(Hash);
    }
    Texture.display();
}

bool TableVisual::mouseOnButton(const sf::Vector2i &MousePos)
{
    bool check = 0;
    for (int i = 0; i < 3; i++)
        check |= DataType[i].mouseOn(MousePos);
    return check;
}