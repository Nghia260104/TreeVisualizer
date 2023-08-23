#include <HeapVisual.hpp>
#include <FrontendGlobal.hpp>
#include <stdlib.h>
#include <thread>
#include <iostream>
using namespace Frontend;

HeapVisual::HeapVisual()
{
}

void HeapVisual::create()
{
    // Base class
    Pattern::create();

    // ToolBar
    ToolBar.setSize(sf::Vector2f(300, 200));
    ToolBar.setFillColor(ToolBarColor);
    ToolBar.setPosition(0, window.getSize().y - 200);
    std::string S[] = {"Randomize Data", "Insert", "Delete", "Search by index", "Update value", "Extract top", "Size"};

    for (int i = 0; i < 7; i++)
    {
        if (i < 4)
        {
            f[i].create(0, window.getSize().y - 350 + 50 * i, 150, 50, textsize, sf::Vector2f(8, 25));
            f[i].setFillColor(BackgroundColor);
            f[i].setTextColor(TextColor);
            f[i].setOutlineColor(TextColor, TextColor);
            f[i].setCaret();
            f[i].setOpacity();
            f[i].setTyping();
            f[i].setFont(Consola);
            f[i].setNumber();
            f[i].setLimit((i == 0 ? 2 : 3));
            f[i].drawTexture();
        }

        Start[i].create((i < 4 ? 150 : 0), window.getSize().y - 350 + 50 * i, 150, 50, Segoe, textsize, S[i]);
        Start[i].setFillColor(ToolBarColor);
        Start[i].setCoverColor(sf::Color(__max((ToolBarColor.r - 50) % 255, (ToolBarColor.r + 50) % 255),
                                         __max((ToolBarColor.g - 50) % 255, (ToolBarColor.g + 50) % 255),
                                         __max((ToolBarColor.b - 50) % 255, (ToolBarColor.b + 50) % 255), 50));
        Start[i].setTextColor(SpecialTextColor);
        Start[i].setOutline(SpecialTextColor);
        Start[i].drawTexture();
    }
    f[4].create(230, window.getSize().y - 150, 60, 50, textsize, sf::Vector2f(8, 25));
    f[4].setFillColor(BackgroundColor);
    f[4].setTextColor(TextColor);
    f[4].setOutlineColor(TextColor, TextColor);
    f[4].setCaret();
    f[4].setOpacity();
    f[4].setTyping();
    f[4].setFont(Consola);
    f[4].setNumber();
    f[4].setLimit(2);
    f[4].drawTexture();

    f[5].create(380, window.getSize().y - 150, 60, 50, textsize, sf::Vector2f(8, 25));
    f[5].setFillColor(BackgroundColor);
    f[5].setTextColor(TextColor);
    f[5].setOutlineColor(TextColor, TextColor);
    f[5].setCaret();
    f[5].setOpacity();
    f[5].setTyping();
    f[5].setFont(Consola);
    f[5].setNumber();
    f[5].setLimit(3);
    f[5].drawTexture();

    SizeBox.setSize(sf::Vector2f(150, 50));
    SizeBox.setFillColor(BackgroundColor);
    SizeBox.setOutlineColor(TextColor);
    SizeBox.setOutlineThickness(-1);
    SizeBox.setPosition(150, window.getSize().y - 50);

    ID_frame.setSize(sf::Vector2f(80, 50));
    ID_frame.setFillColor(BackgroundColor);
    ID_frame.setOutlineColor(TextColor);
    ID_frame.setOutlineThickness(-1);
    ID_frame.setPosition(150, window.getSize().y - 150);

    Val_frame.setSize(sf::Vector2f(90, 50));
    Val_frame.setFillColor(BackgroundColor);
    Val_frame.setOutlineColor(TextColor);
    Val_frame.setOutlineThickness(-1);
    Val_frame.setPosition(290, window.getSize().y - 150);

    Extract_frame.setSize(sf::Vector2f(150, 50));
    Extract_frame.setFillColor(BackgroundColor);
    Extract_frame.setOutlineColor(TextColor);
    Extract_frame.setOutlineThickness(-1);
    Extract_frame.setPosition(150, window.getSize().y - 100);

    Size.setString("Size: ");
    Size.setCharacterSize(textsize);
    Size.setFillColor(TextColor);
    Size.setFont(Segoe);
    Size.setOrigin(0, Size.getGlobalBounds().height / 2);
    Size.setPosition(158, window.getSize().y - 25);

    ID_title.setString("Index: ");
    ID_title.setCharacterSize(textsize);
    ID_title.setFillColor(TextColor);
    ID_title.setFont(Segoe);
    ID_title.setOrigin(0, ID_title.getGlobalBounds().height / 2);
    ID_title.setPosition(158, window.getSize().y - 125);

    Val_title.setString("New value: ");
    Val_title.setCharacterSize(textsize);
    Val_title.setFillColor(TextColor);
    Val_title.setFont(Segoe);
    Val_title.setOrigin(0, Val_title.getGlobalBounds().height / 2);
    Val_title.setPosition(298, window.getSize().y - 125);

    Extract_val.setString("Value: ");
    Extract_val.setCharacterSize(textsize);
    Extract_val.setFillColor(TextColor);
    Extract_val.setFont(Segoe);
    Extract_val.setOrigin(0, Extract_val.getGlobalBounds().height / 2);
    Extract_val.setPosition(158, window.getSize().y - 75);

    Overload.setCharacterSize(20);
    Overload.setFont(Segoe);
    Overload.setFillColor(sf::Color::Red);
    Overload.setString("Number of nodes can not be over 63!");
    Overload.setPosition(5, window.getSize().y - 375);

    RandomErr.setCharacterSize(20);
    RandomErr.setFont(Segoe);
    RandomErr.setFillColor(sf::Color::Red);
    RandomErr.setString("Number of randomize can not be over 31!");
    RandomErr.setPosition(5, window.getSize().y - 375);

    Null_Node.setCharacterSize(20);
    Null_Node.setFont(Segoe);
    Null_Node.setFillColor(sf::Color::Red);
    Null_Node.setString("Heap's size is 0!");
    Null_Node.setPosition(5, window.getSize().y - 375);

    // Prepare
    Table = new Frontend::CircleNode[limit + 1];
    Arc = new Frontend::Arrow[limit + 1];
    for (int i = 0; i <= 63; i++)
    {
        Table[i].toPar = &Arc[i];
        Table[i].hide();
        Arc[i].hide();
    }
    for (int i = 0; i <= 63; i++)
        Table[i].Child.resize(2, nullptr);

    Sys.link(Table, Arc);

    fail = 0;
    drawTexture();
}

void HeapVisual::drawTexture()
{
    Texture.clear(BackgroundColor);
    Texture.draw(Artwork);
    Texture.draw(ToolBar);
    for (int i = 1; i <= limit; i++)
        if (!Arc[i].isHidden())
            Texture.draw(Arc[i]);
    for (int i = 1; i <= limit; i++)
    {
        Table[i].drawTexture();
        if (!Table[i].isHidden())
            Texture.draw(Table[i]);
    }
    for (int i = 0; i < 6; i++)
    {
        f[i].drawTexture();
        Texture.draw(f[i]);
    }
    for (int i = 0; i < 7; i++)
    {
        Start[i].drawTexture();
        Texture.draw(Start[i]);
    }
    Texture.draw(ID_frame);
    Texture.draw(Val_frame);
    Texture.draw(Extract_frame);
    Texture.draw(SizeBox);
    Texture.draw(Size);
    Texture.draw(Extract_val);
    Texture.draw(ID_title);
    Texture.draw(Val_title);
    Texture.draw(NavigateBox);
    for (int i = 0; i < 3; i++)
    {
        Navigate[i].drawTexture();
        Texture.draw(Navigate[i]);
    }
    if (fail == oversize)
        Texture.draw(Overload);
    else if (fail == rand_size)
        Texture.draw(RandomErr);
    else if (fail == nullity)
        Texture.draw(Null_Node);
    // std::cerr << "Called\n";
    Texture.display();
}

void HeapVisual::processEvent(const sf::Event &event)
{
    Navigating(event);
    for (int i = 0; i < 6; i++)
        if (f[i].checkEvent(event) && !keepRunning)
            Texture.draw(f[i]);
    for (int i = 0; i < 7; i++)
    {
        Texture.draw(Start[i]);
        if (Start[i].isPressed(event) && !keepRunning)
        {
            if (i == 0)
            {
                if (f[i].getText() == "")
                    return;
                int val = std::stoi(std::string(f[i].getText()));
                if (val > limit / 2)
                {
                    fail = rand_size;
                    drawTexture();
                    return;
                }
                fail = 0;
                windowHandle.clear();
                clearGpx();
                Sys.clear();
                std::vector<int> Tmp;
                for (int j = 0; j < val; j++)
                {
                    int random = rand() % 1000;
                    Tmp.push_back(random);
                }
                std::sort(Tmp.begin(), Tmp.end());
                if (t == Backend::Heap::Type::Max)
                    std::reverse(Tmp.begin(), Tmp.end());
                std::cerr << "Random vector: ";
                for (int j = 0; j < val; j++)
                    std::cerr << Tmp[j] << " ";
                std::cerr << '\n';
                for (int j = 0; j < val; j++)
                {
                    Sys.INSERT(Tmp[j], t);
                    windowHandle.clear();
                }
                drawTexture();
            }
            else if (i == 1)
            {
                if (f[i].getText() == "")
                    return;
                fail = 0;
                int val = std::stoi(std::string(f[i].getText()));
                windowHandle.clear();
                bool check = Sys.INSERT(val, t);
                if (!check)
                {
                    fail = oversize;
                    drawTexture();
                }
                else
                {
                    keepRunning = 1;
                    std::thread Run(&Handle::run, &windowHandle);
                    Run.detach();
                }
            }
            else if (i == 2)
            {
                if (f[i].getText() == "")
                    return;
                int val = std::stoi(std::string(f[i].getText()));
                fail = 0;
                windowHandle.clear();
                Sys.REMOVE(val, t);
                keepRunning = 1;
                std::thread Run(&Handle::run, &windowHandle);
                Run.detach();
            }
            else if (i == 3)
            {
                if (f[i].getText() == "")
                    return;
                int val = std::stoi(std::string(f[i].getText()));
                fail = 0;
                windowHandle.clear();
                Backend::Node *Tmp_val = Sys[val];
                if (Tmp_val)
                {
                    keepRunning = 1;
                    std::thread Run(&Handle::run, &windowHandle);
                    Run.detach();
                }
            }
            else if (i == 4)
            {
                if (f[i].getText() == "" || f[i + 1].getText() == "")
                    return;
                int id = std::stoi(std::string(f[i].getText()));
                int val = std::stoi(std::string(f[i + 1].getText()));
                fail = 0;
                windowHandle.clear();
                if (Sys.UpdateKey(id, val, t))
                {
                    keepRunning = 1;
                    std::thread Run(&Handle::run, &windowHandle);
                    Run.detach();
                }
                else
                {
                    fail = nullity;
                    drawTexture();
                }
            }
            else if (i == 5)
            {
                fail = 0;
                windowHandle.clear();
                int val = Sys.extract(t);
                Extract_val.setString("Value: " + std::to_string(val));
                if (Sys.getSize())
                {
                    keepRunning = 1;
                    std::thread Run(&Handle::run, &windowHandle);
                    Run.detach();
                }
            }
            else if (i == 6)
            {
                fail = 0;
                Size.setString("Size: " + std::to_string(Sys.getSize()));
                drawTexture();
            }
            return;
        }
    }
}

void HeapVisual::clear()
{
    windowHandle.clear();
    clearGpx();
    Sys.clear();
    for (int i = 0; i < 6; i++)
        f[i].erase();
    Size.setString("Size: ");
    Extract_val.setString("Value: ");
}

void HeapVisual::clearGpx()
{
    for (int i = 0; i < 63; i++)
    {
        sf::String Tmp("");
        Table[i].setFillColor(BackgroundColor);
        Table[i].setTextColor(TextColor);
        Table[i].setOutline(TextColor);
        Table[i].setText(Tmp);
        Table[i].setPosition(0, 0);
        Table[i].drawTexture();
        Table[i].hide();
        Arc[i].setFillColor(TextColor);
        Arc[i].setFirstPosition(sf::Vector2f(0, 0));
        Arc[i].setSecondPosition(sf::Vector2f(0, 0));
        Arc[i].setThickness(1);
        Arc[i].hide();
    }
}

// Private

void HeapVisual::Navigating(const sf::Event &event)
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

HeapVisual::~HeapVisual()
{
    delete[] Table;
    delete[] Arc;
    Table = nullptr;
    Arc = nullptr;
}

void HeapVisual::setType(Backend::Heap::Type t_)
{
    t = t_;
}