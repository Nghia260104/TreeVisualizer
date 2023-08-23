#include <VisualProbing.hpp>
#include <FrontendGlobal.hpp>
#include <stdlib.h>
#include <thread>
#include <iostream>
using namespace Frontend;

VisualProbing::VisualProbing()
{
    // x = window.getSize().x / 2 - 600;
    fail = 0;
}

void VisualProbing::create()
{
    // Base class
    Pattern::create();

    // ToolBar
    ToolBar.setSize(sf::Vector2f(300, 250));
    ToolBar.setFillColor(ToolBarColor);
    ToolBar.setPosition(0, window.getSize().y - 250);

    for (int i = 0; i < 5; i++)
    {
        f[i].create(0, window.getSize().y - 250 + 50 * i, 150, 50, textsize, sf::Vector2f(8, 25));
        f[i].setFillColor(BackgroundColor);
        f[i].setTextColor(TextColor);
        f[i].setOutlineColor(TextColor, TextColor);
        f[i].setCaret();
        f[i].setOpacity();
        f[i].setTyping();
        f[i].setFont(Consola);
        f[i].setNumber();
        f[i].setLimit(3);
        f[i].drawTexture();

        Start[i].create(150, window.getSize().y - 250 + 50 * i, 150, 50, Segoe, 16, S[i]);
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
    Overload.setString("Size can not be greater than 128!");
    Overload.setPosition(5, window.getSize().y - 275);

    if (t == Backend::Probing::Type::Linear)
    {
        Sys = dynamic_cast<Backend::LP *>(Sys);
        Sys = new Backend::LP;
    }
    if (t == Backend::Probing::Type::Quadratic)
    {
        Sys = dynamic_cast<Backend::QP *>(Sys);
        Sys = new Backend::QP;
    }
    if (t == Backend::Probing::Type::Double)
    {
        Sys = dynamic_cast<Backend::DH *>(Sys);
        Sys = new Backend::DH;
    }
    drawTexture();
}

void VisualProbing::drawTexture()
{
    Texture.clear(BackgroundColor);
    Texture.draw(Artwork);
    Texture.draw(ToolBar);
    for (int i = 0; i < Table.size(); i++)
    {
        Table[i].drawTexture();
        Texture.draw(Table[i]);
    }
    for (int i = 0; i < 5; i++)
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
    if (fail)
    {
        Texture.draw(Overload);
    }
    // std::cerr << "Called\n";
    Texture.display();
}

void VisualProbing::processEvent(const sf::Event &event)
{
    // std::thread Nav(Navigating, this, std::ref(event));
    Navigating(event);
    // if (keepRunning)
        // drawTexture();
    for (int i = 0; i < 5; i++)
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
            int val = std::stoi(std::string(f[i].getText()));
            if (i == 0)
            {
                if (val > limit)
                {
                    fail = 1;
                    drawTexture();
                    return;
                }
                fail = 0;
                List.clear();
                Table.clear();
                Table.resize(val);
                setPosition();
                Sys->resize(val);
                for (int j = 0; j < 3 * val / 7; j++)
                {
                    int ins = rand() % 1000;
                    Sys->INSERT(ins, Table, t);
                }
                for (int i = 0; i < List.size(); i++)
                    if (List[i].val_c)
                        List[i].Cur->setText(List[i].val);
                drawTexture();
                // for (int i = 0; i < Table.size(); i++)
                //     if (Table[i].getText().getString() == "")
                //         std::cerr << "x ";
                //     else
                //         std::cerr << std::string(Table[i].getText().getString()) << " ";
                // std::cerr << "\n\n";
            }
            else if (i == 1)
            {
                if (val > limit)
                {
                    fail = 1;
                    drawTexture();
                    return;
                }
                fail = 0;
                List.clear();
                Table.clear();
                Table.resize(val);
                setPosition();
                Sys->resize(val);
                drawTexture();
            }
            else if (i == 2)
            {
                fail = 0;
                List.clear();
                Sys->INSERT(val, Table, t);
                keepRunning = 1;
                std::thread Run(&SingleExecute::run, &List, std::ref(event));
                Run.detach();
                // for (int i = 0; i < Table.size(); i++)
                //     std::cerr << &Table[i] << " ";
                // std::cerr << '\n';
                // for (int i = 0; i < List.size(); i++)
                // {
                //     std::cerr << List[i].Cur << '\n';
                // }
                // std::cerr << "\n\n";
            }
            else if (i == 3)
            {
                fail = 0;
                List.clear();
                Sys->REMOVE(val, Table, t);
                keepRunning = 1;
                std::thread Run(&SingleExecute::run, &List, std::ref(event));
                Run.detach();
            }
            else if (i == 4)
            {
                fail = 0;
                List.clear();
                Sys->SEARCH(val, Table, t);
                keepRunning = 1;
                std::thread Run(&SingleExecute::run, &List, std::ref(event));
                Run.detach();
            }
            return;
        }
    }
}

void VisualProbing::setPosition()
{
    for (int i = 0; i < Table.size(); i++)
        Table[i].setPosition(window.getSize().x / 2 - range / 2 + 1.0f * (i % num) * range / (__min(num, Table.size())),
                             upper_edge + (i / 16) * distance);
}

void VisualProbing::setType(Backend::Probing::Type t_)
{
    t = t_;
}

VisualProbing::~VisualProbing()
{
    Table.clear();
    if (Sys)
        delete Sys;
    Sys = nullptr;
    std::cerr << "Call destructor for VisualProbing" << '\n';
};

void VisualProbing::clear()
{
    Table.clear();
    if (Sys)
        Sys->clear();
    for (int i = 0; i < 5; i++)
        f[i].erase();
}

LinearProbing::LinearProbing()
{
    setType(Backend::Probing::Type::Linear);
}

QuadraticProbing::QuadraticProbing()
{
    setType(Backend::Probing::Type::Quadratic);
}

DoubleHashing::DoubleHashing()
{
    setType(Backend::Probing::Type::Double);
}

LinearProbing::~LinearProbing()
{
    std::cerr << "Call destructor for LinearProbingVisual" << '\n';
}

QuadraticProbing::~QuadraticProbing()
{
    std::cerr << "Call destructor for QuadraticProbingVisual" << '\n';
}

DoubleHashing::~DoubleHashing()
{
    std::cerr << "Call destructor for DoubleHashingVisual" << '\n';
}
