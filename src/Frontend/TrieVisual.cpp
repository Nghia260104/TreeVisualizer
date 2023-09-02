#include <TrieVisual.hpp>
#include <FrontendGlobal.hpp>
#include <stdlib.h>
#include <thread>
#include <iostream>
using namespace Frontend;

TrieVisual::TrieVisual()
{
}

void TrieVisual::create()
{
    // Base class
    Pattern::create();

    // ToolBar
    ToolBar.setSize(sf::Vector2f(300, 200));
    ToolBar.setFillColor(ToolBarColor);
    ToolBar.setPosition(0, window.getSize().y - 200);
    std::string S[] = {"Randomize Data", "Insert", "Delete", "Search"};

    for (int i = 0; i < 4; i++)
    {
        f[i].create(0, window.getSize().y - 200 + 50 * i, 150, 50, textsize, sf::Vector2f(8, 25));
        f[i].setFillColor(BackgroundColor);
        f[i].setTextColor(TextColor);
        f[i].setOutlineColor(TextColor, TextColor);
        f[i].setCaret();
        f[i].setOpacity();
        f[i].setTyping();
        f[i].setFont(Consola);
        if (i == 0)
            f[i].setNumber();
        else
            f[i].setOnlyText();
        f[i].setLimit((i == 0 ? 1 : 6));
        f[i].drawTexture();

        Start[i].create(150, window.getSize().y - 200 + 50 * i, 150, 50, Segoe, 16, S[i]);
        Start[i].setFillColor(ToolBarColor);
        Start[i].setCoverColor(sf::Color(__max((ToolBarColor.r - 50) % 255, (ToolBarColor.r + 50) % 255),
                                         __max((ToolBarColor.g - 50) % 255, (ToolBarColor.g + 50) % 255),
                                         __max((ToolBarColor.b - 50) % 255, (ToolBarColor.b + 50) % 255), 50));
        Start[i].setTextColor(SpecialTextColor);
        Start[i].setOutline(SpecialTextColor);
        Start[i].drawTexture();
    }

    Overload.setCharacterSize(20);
    Overload.setFont(Segoe);
    Overload.setFillColor(sf::Color::Red);
    Overload.setString("Number of branches can not be over 32!");
    Overload.setPosition(5, window.getSize().y - 225);

    heightError.setCharacterSize(20);
    heightError.setFont(Segoe);
    heightError.setFillColor(sf::Color::Red);
    heightError.setString("Word's length can not be over 6!");
    heightError.setPosition(5, window.getSize().y - 225);

    RandomErr.setCharacterSize(20);
    RandomErr.setFont(Segoe);
    RandomErr.setFillColor(sf::Color::Red);
    RandomErr.setString("Number of randomize can not be over 8!");
    RandomErr.setPosition(5, window.getSize().y - 225);

    // Prepare
    Table = new Frontend::CircleNode[total];
    Arc = new Frontend::Arrow[total];
    for (int i = 0; i < total; i++)
    {
        Table[i].toPar = &Arc[i];
        Table[i].hide();
        Arc[i].hide();
    }
    Table[0].show();
    Table[0].setPosition(window.getSize().x / 2, upper_edge);
    // for (int i = 0; i < 63; i++)
    //     Table[i].Child.resize(2, nullptr);

    Sys.link(Table, Arc);

    fail = 0;
    drawTexture();
}

void TrieVisual::drawTexture()
{
    Texture.clear(BackgroundColor);
    Texture.draw(Artwork);
    Texture.draw(ToolBar);
    for (int i = 0; i < total; i++)
        if (!Arc[i].isHidden())
            Texture.draw(Arc[i]);
    for (int i = 0; i < total; i++)
    {
        Table[i].drawTexture();
        if (!Table[i].isHidden())
            Texture.draw(Table[i]);
    }
    for (int i = 0; i < 4; i++)
    {
        f[i].drawTexture();
        Start[i].drawTexture();
        Texture.draw(f[i]);
        Texture.draw(Start[i]);
    }
    Texture.draw(NavigateBox);
    for (int i = 0; i < 3; i++)
    {
        Navigate[i].drawTexture();
        Texture.draw(Navigate[i]);
    }
    Spd.drawTexture();
    Texture.draw(Spd);
    if (fail == oversize)
        Texture.draw(Overload);
    else if (fail == h_err)
        Texture.draw(heightError);
    else if (fail == rand_size)
        Texture.draw(RandomErr);
    // std::cerr << "Called\n";
    Texture.display();
}

void TrieVisual::processEvent(const sf::Event &event)
{
    changeSpd(event);
    Navigating(event);
    for (int i = 0; i < 4; i++)
    {
        if (!keepRunning)
            Texture.draw(Start[i]);
        if (f[i].checkEvent(event))
            if (!keepRunning)
                Texture.draw(f[i]);
        if (Start[i].isPressed(event) && !keepRunning)
        {
            if (f[i].getText() == "")
                return;
            if (i == 0)
            {
                int val = std::stoi(std::string(f[i].getText()));
                if (val > 9)
                {
                    fail = rand_size;
                    drawTexture();
                    return;
                }
                fail = 0;
                windowHandle.clear();
                clearGpx();
                Sys.clear();
                std::vector<std::string> Tmp;
                for (int j = 0; j < val; j++)
                {
                    int random = rand() % 6 + 1;
                    std::string Generate = "";
                    for (int a = 0; a < random; a++)
                    {
                        int r = rand() % 26;
                        Generate += char(int(r + 'a'));
                    }
                    Tmp.push_back(Generate);
                    std::cerr << Generate << " ";
                }
                // std::sort(Tmp.begin(), Tmp.end());
                // std::cerr << "Random vector: ";
                // for (int j = 0; j < val; j++)
                //     std::cerr << Tmp[j] << " ";
                // std::cerr << "\nSorted vector: ";
                // for (int j = 0; j < val; j++)
                //     std::cerr << Input[j] << " ";
                // std::cerr << '\n';
                for (int j = 0; j < val; j++)
                {
                    // Sys.insert(Input[j]);
                    Sys.insert(Tmp[j]);
                    windowHandle.clear();
                }
                // for (int j = 0; j < val; j++)
                //     std::cerr << (!Table[j].isHidden() ? "Show " : "Hide ");
                // std::cerr << "\n";
                // for (int j = 0; j < val; j++)
                // {
                //     std::cerr << (!Arc[j].isHidden() ? "Show-" : "Hide-");
                //     std::cerr << (Arc[j].getThickness()) << " ";
                // }
                drawTexture();
            }
            else if (i == 1)
            {
                std::string val = f[i].getText();
                windowHandle.clear();
                if (Sys.Inserted() >= limit)
                {
                    fail = oversize;
                    drawTexture();
                }
                else if (val.size() > 6)
                {
                    fail = h_err;
                    drawTexture();
                }
                else
                {
                    Sys.insert(val);
                    keepRunning = 1;
                    std::thread Run(&Handle::run, &windowHandle);
                    Run.detach();
                    // Sys.displayPos();
                }
            }
            else if (i == 2)
            {
                std::string val = f[i].getText();
                fail = 0;
                windowHandle.clear();
                Sys.remove(val);
                keepRunning = 1;
                std::thread Run(&Handle::run, &windowHandle);
                Run.detach();
            }
            else if (i == 3)
            {
                std::string val = f[i].getText();
                fail = 0;
                windowHandle.clear();
                Sys.search(val);
                keepRunning = 1;
                std::thread Run(&Handle::run, &windowHandle);
                Run.detach();
            }
            return;
        }
    }
}

void TrieVisual::clear()
{
    windowHandle.clear();
    clearGpx();
    Sys.clear();
    for (int i = 0; i < 4; i++)
        f[i].erase();
    interval = 1200;
}

void TrieVisual::clearGpx()
{
    for (int i = 0; i < total; i++)
    {
        sf::String Tmp("");
        Table[i].setFillColor(BackgroundColor);
        Table[i].setTextColor(TextColor);
        Table[i].setOutline(TextColor);
        Table[i].setText(Tmp);
        if (i != 0)
            Table[i].setPosition(0, 0);
        else
            Table[i].setPosition(window.getSize().x / 2, 50);
        Table[i].drawTexture();
        if (i != 0)
            Table[i].hide();
        Arc[i].setFillColor(TextColor);
        Arc[i].setFirstPosition(sf::Vector2f(0, 0));
        Arc[i].setSecondPosition(sf::Vector2f(0, 0));
        Arc[i].setThickness(1);
        Arc[i].hide();
    }
}

// Private

void TrieVisual::Navigating(const sf::Event &event)
{
    for (int i = 0; i < 3; i++)
    {
        if (!keepRunning && !run1step)
            Texture.draw(Navigate[i]);
        if (Navigate[i].isPressed(event))
        {
            if (keepRunning)
            {
                keepRunning = 0;
                return;
            }
            if (!keepRunning && !run1step)
            {
                if (i == 0)
                {
                    run1step = 1;
                    std::thread th(&Handle::stepback, &windowHandle);
                    th.detach();
                }
                else if (i == 1)
                {
                    keepRunning = 1;
                    run1step = 1;
                    std::thread th(&Handle::run, &windowHandle);
                    th.detach();
                }
                else if (i == 2)
                {
                    run1step = 1;
                    std::thread th(&Handle::stepforw, &windowHandle);
                    th.detach();
                }
            }
            return;
        }
    }
}

TrieVisual::~TrieVisual()
{
    delete[] Table;
    delete[] Arc;
    Table = nullptr;
    Arc = nullptr;
}

void TrieVisual::ReSetting()
{
    ToolBar.setFillColor(ToolBarColor);
    for (int i = 0; i < 4; i++)
    {
        f[i].setFillColor(BackgroundColor);
        f[i].setTextColor(TextColor);
        Start[i].setFillColor(ToolBarColor);
        Start[i].setTextColor(SpecialTextColor);
        Start[i].setCoverColor(sf::Color(__max((ToolBarColor.r - 50) % 255, (ToolBarColor.r + 50) % 255),
                                         __max((ToolBarColor.g - 50) % 255, (ToolBarColor.g + 50) % 255),
                                         __max((ToolBarColor.b - 50) % 255, (ToolBarColor.b + 50) % 255), 50));
    }
    heightError.setFillColor(TextColor);
    Overload.setFillColor(TextColor);
    RandomErr.setFillColor(TextColor);
    if (Table)
        for (int i = 0; i < total; i++)
        {
            Table[i].setRadius(g_radius);
            Table[i].setFillColor(BackgroundColor);
            Table[i].setTextColor(TextColor);
            Table[i].setOutline(TextColor);
        }
    if (Arc)
        for (int i = 0; i < total; i++)
        {
            Arc[i].setThickness(0.1f * g_radius);
            Arc[i].setFillColor(TextColor);
        }
}