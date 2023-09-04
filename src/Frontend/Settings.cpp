#include <Settings.hpp>
#include <FrontendGlobal.hpp>
using namespace Frontend;

Settings::Settings()
{
}

void Settings::create()
{
    // Background
    Texture.create(550, 900);
    Texture.clear(BackgroundColor);
    x = window.getSize().x / 2 - 275;
    y = window.getSize().y / 2 - 450;
    sz = g_size;
    cur = -1;
    // Rec.setSize(sf::Vector2f(500, 550));

    // Size
    Title[0].setString("Size");
    Title[0].setFont(Segoe);
    Title[0].setStyle(sf::Text::Bold);
    Title[0].setCharacterSize(18);
    Title[0].setFillColor(SpecialTextColor);
    Title[0].setPosition(Align, Align);

    //// Size Component
    Size.setString("Size of Visualization:");
    Size.setFont(Segoe);
    Size.setCharacterSize(16);
    Size.setFillColor(SpecialTextColor);
    Size.setPosition(2 * Align, Align + dis);

    SizeVal.create(AlignVal, Align + dis - 5, 50, 30, 16, sf::Vector2f(20, 15));
    SizeVal.setFillColor(BackgroundColor);
    SizeVal.setTextColor(SpecialTextColor);
    SizeVal.setOutlineColor(SpecialTextColor, SpecialTextColor);
    SizeVal.setOpacity();
    SizeVal.setFont(Consola);
    SizeVal.setCaret();
    SizeVal.setTyping();
    SizeVal.setGlobalPosition(AlignVal + x, Align + dis + y - 5);
    SizeVal.setNumber();
    SizeVal.setLimit(1);
    SizeVal.setText(std::to_string(sz));

    // Theme
    Title[2].setString("Theme");
    Title[2].setFont(Segoe);
    Title[2].setStyle(sf::Text::Bold);
    Title[2].setCharacterSize(18);
    Title[2].setFillColor(SpecialTextColor);
    Title[2].setPosition(Align, Align + 2 * dis);

    std::string th[] = {"Light Theme:", "Dark Theme:"};
    for (int i = 0; i < 2; i++)
    {
        Theme[i].setString(th[i]);
        Theme[i].setFont(Segoe);
        Theme[i].setCharacterSize(16);
        Theme[i].setFillColor(SpecialTextColor);
        Theme[i].setPosition(2 * Align, Align + (3 + i) * dis);

        ThemeType[i].create(AlignVal, Align + (3 + i) * dis - 5, 50, 30, Segoe, 1, "");
        if (i == 0)
        {
            ThemeType[i].setFillColor(sf::Color(255, 255, 255));
            ThemeType[i].setOutline(sf::Color(25, 25, 25));
        }
        else
        {
            ThemeType[i].setFillColor(sf::Color(25, 25, 25));
            ThemeType[i].setOutline(sf::Color::White);
        }
        ThemeType[i].setGlobalPosition(AlignVal + x, Align + y + (3 + i) * dis - 5);
    }

    // Color
    Title[3].setString("Color");
    Title[3].setFont(Segoe);
    Title[3].setStyle(sf::Text::Bold);
    Title[3].setCharacterSize(18);
    Title[3].setFillColor(SpecialTextColor);
    Title[3].setPosition(Align, Align + 5 * dis);

    std::string S[] = {"Background Color", "Text and Outline Color", "Toolbar Color", "Accessories Text Color", "Highlight Color"};
    sf::Color Tmp[] = {BackgroundColor, TextColor, ToolBarColor, SpecialTextColor, Highlight};

    for (int i = 0; i < 5; i++)
    {
        Color[i].setString(S[i]);
        Color[i].setFont(Segoe);
        Color[i].setCharacterSize(16);
        Color[i].setFillColor(SpecialTextColor);
        Color[i].setPosition(2 * Align, Align + (6 + i) * dis);

        Sample[i].create(AlignVal, Align + (6 + i) * dis - 5, 50, 30, Segoe, 1, "");
        Sample[i].setFillColor(Tmp[i]);
        Sample[i].setOutline(SpecialTextColor);
        Sample[i].setGlobalPosition(AlignVal + x, Align + y + (6 + i) * dis - 5);
    }

    sf::Color TmpSample[] = {
        sf::Color(255, 0, 0),
        sf::Color(255, 127, 0),
        sf::Color(255, 255, 0),
        sf::Color(127, 255, 0),
        sf::Color(0, 255, 0),
        sf::Color(0, 255, 127),
        sf::Color(0, 255, 255),
        sf::Color(0, 127, 255),
        sf::Color(0, 0, 255),
        sf::Color(127, 0, 255),
        sf::Color(255, 0, 255),
        sf::Color(255, 0, 127),
        sf::Color(0, 0, 0),
        sf::Color(150, 75, 0),
        sf::Color(127, 127, 127),
        sf::Color(255, 255, 255)};

    for (int i = 0; i < 16; i++)
    {
        Common[i].create(Align + (i % 8) * dis, Align + (11 + i / 8) * dis, 50, 30, Segoe, 1, "");
        Common[i].setOutline(SpecialTextColor);
        Common[i].setFillColor(TmpSample[i]);
        Common[i].setGlobalPosition(Align + (i % 8) * dis + x, Align + (11 + i / 8) * dis + y);
    }

    std::string Tmp_id[] = {"R:", "G:", "B:"};
    for (int i = 0; i < 3; i++)
    {
        index[i].setString(Tmp_id[i]);
        index[i].setFont(Segoe);
        index[i].setCharacterSize(16);
        index[i].setFillColor(SpecialTextColor);
        index[i].setPosition(2 * Align + 100 * i, Align + 13 * dis);
    }

    R.create(2 * Align + 20, Align + 13 * dis - 5, 70, 30, 16, sf::Vector2f(8, 15));
    R.setFillColor(BackgroundColor);
    R.setTextColor(SpecialTextColor);
    R.setOutlineColor(SpecialTextColor, SpecialTextColor);
    R.setOpacity();
    R.setFont(Consola);
    R.setCaret();
    R.setTyping();
    R.setGlobalPosition(2 * Align + x + 20, Align + 13 * dis + y - 5);
    R.setNumber();
    R.setLimit(3);
    R.setText("");

    G.create(2 * Align + 120, Align + 13 * dis - 5, 70, 30, 16, sf::Vector2f(8, 15));
    G.setFillColor(BackgroundColor);
    G.setTextColor(SpecialTextColor);
    G.setOutlineColor(SpecialTextColor, SpecialTextColor);
    G.setOpacity();
    G.setFont(Consola);
    G.setCaret();
    G.setTyping();
    G.setGlobalPosition(2 * Align + x + 120, Align + 13 * dis + y - 5);
    G.setNumber();
    G.setLimit(3);
    G.setText("");

    B.create(2 * Align + 220, Align + 13 * dis - 5, 70, 30, 16, sf::Vector2f(8, 15));
    B.setFillColor(BackgroundColor);
    B.setTextColor(SpecialTextColor);
    B.setOutlineColor(SpecialTextColor, SpecialTextColor);
    B.setOpacity();
    B.setFont(Consola);
    B.setCaret();
    B.setTyping();
    B.setGlobalPosition(2 * Align + 220 + x, Align + 13 * dis + y - 5);
    B.setNumber();
    B.setLimit(3);
    B.setText("");

    Cancel.create(150, Align + 14 * dis, 100, 50, Segoe, 16, "Cancel");
    Cancel.setFillColor(ToolBarColor);
    Cancel.setTextColor(SpecialTextColor);
    Cancel.setGlobalPosition(150 + x, y + Align + 14 * dis);
    Cancel.setCoverColor(sf::Color(__max((ToolBarColor.r - 50) % 255, (ToolBarColor.r + 50) % 255),
                                   __max((ToolBarColor.g - 50) % 255, (ToolBarColor.g + 50) % 255),
                                   __max((ToolBarColor.b - 50) % 255, (ToolBarColor.b + 50) % 255), 5));

    OK.create(300, Align + 14 * dis, 100, 50, Segoe, 16, "OK");
    OK.setFillColor(ToolBarColor);
    OK.setTextColor(SpecialTextColor);
    OK.setGlobalPosition(300 + x, y + Align + 14 * dis);
    OK.setCoverColor(sf::Color(__max((ToolBarColor.r - 50) % 255, (ToolBarColor.r + 50) % 255),
                               __max((ToolBarColor.g - 50) % 255, (ToolBarColor.g + 50) % 255),
                               __max((ToolBarColor.b - 50) % 255, (ToolBarColor.b + 50) % 255), 5));
}

void Settings::Prepare()
{
    SizeVal.setText(std::to_string(g_size));
    R.setText("");
    G.setText("");
    B.setText("");
    sf::Color Tmp[] = {BackgroundColor, TextColor, ToolBarColor, SpecialTextColor, Highlight};
    for (int i = 0; i < 5; i++)
        Sample[i].setFillColor(Tmp[i]);
    cur = -1;
    drawTexture();
}

void Settings::drawTexture()
{
    Texture.clear(BackgroundColor);
    for (int i = 0; i < 3; i++)
        Texture.draw(Title[i]);
    Texture.draw(Size);
    SizeVal.drawTexture();
    Texture.draw(SizeVal);
    for (int i = 0; i < 2; i++)
    {
        Texture.draw(Theme[i]);
        ThemeType[i].drawTexture();
        Texture.draw(ThemeType[i]);
    }
    for (int i = 0; i < 5; i++)
    {
        Texture.draw(Color[i]);
        Sample[i].drawTexture();
        Texture.draw(Sample[i]);
    }
    for (int i = 0; i < 16; i++)
    {
        Common[i].drawTexture();
        Texture.draw(Common[i]);
    }
    for (int i = 0; i < 3; i++)
        Texture.draw(index[i]);
    R.drawTexture();
    G.drawTexture();
    B.drawTexture();
    Texture.draw(R);
    Texture.draw(G);
    Texture.draw(B);
    Cancel.drawTexture();
    OK.drawTexture();
    Texture.draw(Cancel);
    Texture.draw(OK);
    Texture.display();
}

void Settings::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    sf::Sprite sprite(Texture.getTexture());
    sprite.setPosition(x, y);
    target.draw(sprite);
}

void Settings::processEvent(const sf::Event &event)
{
    if (SizeVal.checkEvent(event))
        Texture.draw(SizeVal);
    for (int i = 0; i < 2; i++)
    {
        Texture.draw(ThemeType[i]);
        if (ThemeType[i].isPressed(event))
        {
            if (i == 0)
            {
                Sample[0].setFillColor(sf::Color(246, 241, 241, 255));
                Sample[1].setFillColor(sf::Color::Black);
                Sample[2].setFillColor(sf::Color(22, 120, 224, 255));
                Sample[3].setFillColor(sf::Color::Black);
                Sample[4].setFillColor(sf::Color(199, 75, 8, 255));
            }
            if (i == 1)
            {
                Sample[0].setFillColor(sf::Color(25, 25, 25, 255));
                Sample[1].setFillColor(sf::Color(246, 241, 241, 255));
                Sample[2].setFillColor(sf::Color(58, 209, 44, 255));
                Sample[3].setFillColor(sf::Color(246, 241, 241, 255));
                Sample[4].setFillColor(sf::Color(22, 83, 224, 255));
            }
            if (cur != -1)
            {
                R.setText(std::to_string(Sample[cur].getFillColor().r));
                G.setText(std::to_string(Sample[cur].getFillColor().g));
                B.setText(std::to_string(Sample[cur].getFillColor().b));
            }
            drawTexture();
            return;
        }
    }
    bool check = 0;
    for (int i = 0; i < 5; i++)
    {
        Texture.draw(Sample[i]);
        if (Sample[i].isPressed(event))
        {
            cur = i;
            R.setText(std::to_string(Sample[i].getFillColor().r));
            G.setText(std::to_string(Sample[i].getFillColor().g));
            B.setText(std::to_string(Sample[i].getFillColor().b));
            drawTexture();
            return;
        }
        else check |= 1;
    }
    for (int i = 0; i < 16; i++)
    {
        Texture.draw(Common[i]);
        if (Common[i].isPressed(event) && cur != -1)
        {
            Sample[cur].setFillColor(Common[i].getFillColor());
            R.setText(std::to_string(Sample[cur].getFillColor().r));
            G.setText(std::to_string(Sample[cur].getFillColor().g));
            B.setText(std::to_string(Sample[cur].getFillColor().b));
            drawTexture();
            return;
        }
    }
    if (R.checkEvent(event))
    {
        if (cur != -1)
        {
            sf::Color Tmp = Sample[cur].getFillColor();
            if (R.getText() == "")
                Tmp.r = 0;
            else
                Tmp.r = (std::stoi(std::string(R.getText()))) % 256;
            Sample[cur].setFillColor(Tmp);
            drawTexture();
        }
        Texture.draw(R);
    }
    if (G.checkEvent(event))
    {
        if (cur != -1)
        {
            sf::Color Tmp = Sample[cur].getFillColor();
            if (G.getText() == "")
                Tmp.g = 0;
            else
                Tmp.g = (std::stoi(std::string(G.getText()))) % 256;
            Sample[cur].setFillColor(Tmp);
            drawTexture();
        }
        Texture.draw(G);
    }
    if (B.checkEvent(event))
    {
        if (cur != -1)
        {
            sf::Color Tmp = Sample[cur].getFillColor();
            if (B.getText() == "")
                Tmp.b = 0;
            else
                Tmp.b = (std::stoi(std::string(B.getText()))) % 256;
            Sample[cur].setFillColor(Tmp);
            drawTexture();
        }
        Texture.draw(B);
    }
    if (Cancel.isPressed(event))
    {
        Visual.setLayer();
        return;
    }
    if (OK.isPressed(event))
    {
        g_size = std::stoi(std::string(SizeVal.getText()));
        g_radius = radius[g_size];
        fontsize = font[g_size / 2];
        BackgroundColor = Sample[0].getFillColor();
        Blur = TextColor = Sample[1].getFillColor();
        Blur.a = 50;
        ToolBarColor = Sample[2].getFillColor();
        SpecialTextColor = Sample[3].getFillColor();
        Highlight = Sample[4].getFillColor();
        Visual.ReSetting();
        return;
    }
}

void Settings::ReSetting()
{
    Texture.clear(BackgroundColor);
    Size.setFillColor(SpecialTextColor);
    for (int i = 0; i < 3; i++)
        Title[i].setFillColor(SpecialTextColor);
    SizeVal.setFillColor(BackgroundColor);
    SizeVal.setTextColor(SpecialTextColor);
    SizeVal.setOutlineColor(SpecialTextColor, SpecialTextColor);
    for (int i = 0; i < 2; i++)
        Theme[i].setFillColor(SpecialTextColor);
    sf::Color Tmp[] = {BackgroundColor, TextColor, ToolBarColor, SpecialTextColor, Highlight};
    for (int i = 0; i < 5; i++)
    {
        Color[i].setFillColor(SpecialTextColor);
        Sample[i].setFillColor(Tmp[i]);
        Sample[i].setOutline(SpecialTextColor);
    }
    for (int i = 0; i < 16; i++)
        Common[i].setOutline(SpecialTextColor);
    for (int i = 0; i < 3; i++)
        index[i].setFillColor(SpecialTextColor);
    R.setFillColor(BackgroundColor);
    R.setTextColor(SpecialTextColor);
    R.setOutlineColor(SpecialTextColor);
    G.setFillColor(BackgroundColor);
    G.setTextColor(SpecialTextColor);
    G.setOutlineColor(SpecialTextColor);
    B.setFillColor(BackgroundColor);
    B.setTextColor(SpecialTextColor);
    B.setOutlineColor(SpecialTextColor);
    Cancel.setFillColor(ToolBarColor);
    Cancel.setTextColor(SpecialTextColor);
    Cancel.setCoverColor(sf::Color(__max((ToolBarColor.r - 50) % 255, (ToolBarColor.r + 50) % 255),
                                   __max((ToolBarColor.g - 50) % 255, (ToolBarColor.g + 50) % 255),
                                   __max((ToolBarColor.b - 50) % 255, (ToolBarColor.b + 50) % 255), 5));
    OK.setFillColor(ToolBarColor);
    OK.setTextColor(SpecialTextColor);
    OK.setCoverColor(sf::Color(__max((ToolBarColor.r - 50) % 255, (ToolBarColor.r + 50) % 255),
                               __max((ToolBarColor.g - 50) % 255, (ToolBarColor.g + 50) % 255),
                               __max((ToolBarColor.b - 50) % 255, (ToolBarColor.b + 50) % 255), 5));
    drawTexture();
}
