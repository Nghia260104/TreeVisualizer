#include <AVLVisual.hpp>
#include <FrontendGlobal.hpp>
#include <stdlib.h>
#include <thread>
#include <iostream>
using namespace Frontend;

AVLVisual::AVLVisual()
{
}

void AVLVisual::create()
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
        f[i].setNumber();
        f[i].setLimit((i == 0 ? 2 : 3));
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
    Overload.setString("Number of nodes can not be over 63!");
    Overload.setPosition(5, window.getSize().y - 225);

    heightError.setCharacterSize(20);
    heightError.setFont(Segoe);
    heightError.setFillColor(sf::Color::Red);
    heightError.setString("Tree's height can not be over 6!");
    heightError.setPosition(5, window.getSize().y - 225);

    RandomErr.setCharacterSize(20);
    RandomErr.setFont(Segoe);
    RandomErr.setFillColor(sf::Color::Red);
    RandomErr.setString("Number of randomize can not be over 31!");
    RandomErr.setPosition(5, window.getSize().y - 225);

    // Prepare
    Root = nullptr;
    Table = new Frontend::CircleNode[limit];
    Arc = new Frontend::Arrow[limit];
    for (int i = 0; i < 63; i++)
    {
        Table[i].toPar = &Arc[i];
        Table[i].hide();
        Arc[i].hide();
    }
    for (int i = 0; i < 63; i++)
        Table[i].Child.resize(2, nullptr);

    Sys.link(Table, window.getSize().x / 2 - 800, Arc);

    fail = 0;
    drawTexture();
}

void AVLVisual::drawTexture()
{
    Texture.clear(BackgroundColor);
    Texture.draw(Artwork);
    Texture.draw(ToolBar);
    for (int i = 0; i < 63; i++)
        if (!Arc[i].isHidden())
            Texture.draw(Arc[i]);
    for (int i = 0; i < 63; i++)
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
    if (fail == oversize)
        Texture.draw(Overload);
    else if (fail == h_err)
        Texture.draw(heightError);
    else if (fail == rand_size)
        Texture.draw(RandomErr);
    // std::cerr << "Called\n";
    Texture.display();
}

void AVLVisual::processEvent(const sf::Event &event)
{
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
            int val = std::stoi(std::string(f[i].getText()));
            if (i == 0)
            {
                if (val > limit / 2)
                {
                    fail = rand_size;
                    drawTexture();
                    return;
                }
                fail = 0;
                windowHandle.clear();
                clearGpx();
                Root = nullptr;
                Sys.clear();
                std::vector<int> Tmp, Input;
                for (int j = 0; j < val; j++)
                {
                    int random = rand() % 1000;
                    Tmp.push_back(random);
                }
                std::sort(Tmp.begin(), Tmp.end());
                PreparedArray(Tmp, 0, val - 1, Input);
                std::cerr << "Random vector: ";
                for (int j = 0; j < val; j++)
                    std::cerr << Tmp[j] << " ";
                std::cerr << "\nSorted vector: ";
                for (int j = 0; j < val; j++)
                    std::cerr << Input[j] << " ";
                std::cerr << '\n';
                for (int j = 0; j < val; j++)
                {
                    Sys.insertWithOrder(Input[j]);
                    // Sys.insert(Input[j]);
                    windowHandle.clear();
                }
                for (int j = 0; j < val; j++)
                    std::cerr << (!Table[j].isHidden() ? "Show " : "Hide ");
                std::cerr << "\n";
                for (int j = 0; j < val; j++)
                {
                    std::cerr << (!Arc[j].isHidden() ? "Show-" : "Hide-");
                    std::cerr << (Arc[j].getThickness()) << " ";
                }
                drawTexture();
            }
            else if (i == 1)
            {
                windowHandle.clear();
                Backend::BST::Limit t = Sys.insert(val);
                if (t == Backend::BST::Limit::Overheight)
                {
                    fail = h_err;
                    drawTexture();
                }
                else if (t == Backend::BST::Limit::Overload)
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
                fail = 0;
                windowHandle.clear();
                Sys.remove(val);
                keepRunning = 1;
                std::thread Run(&Handle::run, &windowHandle);
                Run.detach();
            }
            else if (i == 3)
            {
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

void AVLVisual::clear()
{
    windowHandle.clear();
    clearGpx();
    Sys.clear();
    for (int i = 0; i < 4; i++)
        f[i].erase();
}

void AVLVisual::clearGpx()
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

void AVLVisual::PreparedArray(std::vector<int> &Given, int l, int r, std::vector<int> &Res)
{
    if (l > r)
        return;
    int mid = (l + r) / 2;
    Res.push_back(Given[mid]);
    PreparedArray(Given, l, mid - 1, Res);
    PreparedArray(Given, mid + 1, r, Res);
    return;
}

void AVLVisual::Navigating(const sf::Event &event)
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

AVLVisual::~AVLVisual()
{
    delete[] Table;
    delete[] Arc;
    Table = nullptr;
    Arc = nullptr;
}