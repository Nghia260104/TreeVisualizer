#include <GraphVisual.hpp>
#include <FrontendGlobal.hpp>
#include <thread>
#include <iostream>
using namespace Frontend;

GraphVisual::GraphVisual()
{
    Table = nullptr;
    Arc = nullptr;
    for (int i = 0; i < 20; i++)
        dragging[i] = 0;
}

void GraphVisual::create()
{
    Pattern::create();

    // ToolBar
    ToolBar.setSize(sf::Vector2f(150, 300));
    ToolBar.setFillColor(ToolBarColor);
    ToolBar.setPosition(0, window.getSize().y - 200);
    std::string S[] = {"Randomize Data", "Add vertex", "Delete vertex", "Add edge", "Delete Edge", "Shortest path", "MST"};

    for (int i = 0; i < 7; i++)
    {
        Start[i].create(0, window.getSize().y - 350 + 50 * i, 150, 50, Segoe, 16, S[i]);
        Start[i].setFillColor(ToolBarColor);
        Start[i].setCoverColor(sf::Color(__max((ToolBarColor.r - 50) % 255, (ToolBarColor.r + 50) % 255),
                                         __max((ToolBarColor.g - 50) % 255, (ToolBarColor.g + 50) % 255),
                                         __max((ToolBarColor.b - 50) % 255, (ToolBarColor.b + 50) % 255), 50));
        Start[i].setTextColor(SpecialTextColor);
        Start[i].setOutline(SpecialTextColor);
        Start[i].drawTexture();
    }
    for (int i = 0; i < 9; i++)
    {
        f[i].create(0, 0, 50, 50, textsize, sf::Vector2f(8, 25));
        f[i].setFillColor(BackgroundColor);
        f[i].setTextColor(TextColor);
        f[i].setOutlineColor(TextColor, TextColor);
        f[i].setCaret();
        f[i].setOpacity();
        f[i].setTyping();
        f[i].setFont(Consola);
        f[i].setNumber();
        if (i != 0)
            f[i].setLimit(2);
        else
            f[i].setLimit(1);
        f[i].drawTexture();
        if (i == 0)
            f[i].setPosition(150, window.getSize().y - 350);
        else if (i == 1)
            f[i].setPosition(150, window.getSize().y - 300);
        else if (i == 2)
            f[i].setPosition(150, window.getSize().y - 250);
        else if (i == 3)
            f[i].setPosition(150, window.getSize().y - 200);
        else if (i == 4)
            f[i].setPosition(200, window.getSize().y - 200);
        else if (i == 5)
            f[i].setPosition(250, window.getSize().y - 200);
        else if (i == 6)
            f[i].setPosition(150, window.getSize().y - 150);
        else if (i == 7)
            f[i].setPosition(200, window.getSize().y - 150);
        else if (i == 8)
            f[i].setPosition(150, window.getSize().y - 100);
    }
    Overload.setCharacterSize(20);
    Overload.setFont(Segoe);
    Overload.setFillColor(sf::Color::Red);
    Overload.setString("Number of nodes can not be over 20!");
    Overload.setPosition(5, window.getSize().y - 375);

    Exist.setCharacterSize(20);
    Exist.setFont(Segoe);
    Exist.setFillColor(sf::Color::Red);
    Exist.setString("Existed!");
    Exist.setPosition(5, window.getSize().y - 375);

    NonExist.setCharacterSize(20);
    NonExist.setFont(Segoe);
    NonExist.setFillColor(sf::Color::Red);
    NonExist.setString("Node does not exist!");
    NonExist.setPosition(5, window.getSize().y - 375);

    RandomErr.setCharacterSize(20);
    RandomErr.setFont(Segoe);
    RandomErr.setFillColor(sf::Color::Red);
    RandomErr.setString("Number of randomize can not be over 8!");
    RandomErr.setPosition(5, window.getSize().y - 375);

    Table = new Frontend::CircleNode[20];
    Arc = new Frontend::Arrow[190];
    Sys.link(Table, Arc);
    for (int i = 0; i < 20; i++)
        Table[i].hide();
    for (int i = 0; i < 190; i++)
    {
        Arc[i].hide();
        Arc[i].setThickness(0.1f * g_radius);
    }

    fail = 0;
    drawTexture();
}

void GraphVisual::drawTexture()
{
    Texture.clear(BackgroundColor);
    Texture.draw(Artwork);
    Texture.draw(ToolBar);
    for (int i = 0; i < 190; i++)
        if (!Arc[i].isHidden())
            Texture.draw(Arc[i]);
    for (int i = 0; i < 20; i++)
    {
        Table[i].drawTexture();
        if (!Table[i].isHidden())
            Texture.draw(Table[i]);
    }
    for (int i = 0; i < 7; i++)
    {
        Start[i].drawTexture();
        Texture.draw(Start[i]);
    }
    for (int i = 0; i < 9; i++)
    {
        f[i].drawTexture();
        Texture.draw(f[i]);
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
    else if (fail == existed)
        Texture.draw(Exist);
    else if (fail == rand_size)
        Texture.draw(RandomErr);
    else if (fail == notExisted)
        Texture.draw(NonExist);
    // std::cerr << "Called\n";
    Texture.display();
}

void GraphVisual::processEvent(const sf::Event &event)
{
    changeSpd(event);
    Navigating(event);
    sf::Mouse mouse;
    sf::Vector2i MousePos = mouse.getPosition(window);
    for (int i = 0; i < 20; i++)
    {
        if (!Table[i].isHidden() && Table[i].mouseOn(MousePos) &&
            event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            std::cerr << "Choosing vertex " << i << '\n';
            dragging[i] = 1;
            Sys.setChoosing(i);
        }
        if (dragging[i])
        {
            Table[i].setPosition(__min(1560, __max(360, MousePos.x)), __min(800, __max(100, MousePos.y)));
            Sys.setVertexPosition(i);
            if (!run1step)
            {
                std::cerr << "Force-directed\n";
                std::thread th(&Backend::Graph::arrangePosition, &Sys);
                th.detach();
                drawTexture();
            }
        }
        // else
        //     delta = sf::Vector2f(MousePos.x - Table[i].getPosition().x, MousePos.y - Table[i].getPosition().y);
        if (event.type == sf::Event::MouseButtonReleased)
        {
            for (int i = 0; i < 20; i++)
                dragging[i] = 0;
            Sys.setChoosing();
        }
    }
    for (int i = 0; i < 9; i++)
        if (f[i].checkEvent(event))
            Texture.draw(f[i]);
    for (int i = 0; i < 7; i++)
    {
        if (!keepRunning)
            Texture.draw(Start[i]);
        if (Start[i].isPressed(event) && !keepRunning)
        {
            if (i == 0 && !run1step)
            {
                if (f[i].getText() == "")
                    return;
                int val = std::stoi(std::string(f[i].getText()));
                if (val > 8 || val == 0)
                {
                    fail = rand_size;
                    drawTexture();
                    return;
                }
                fail = 0;
                windowHandle.clear();
                clearGpx();
                Sys.clear();
                std::cerr << "Add vertices\n";
                for (int i = 0; i < val; i++)
                {
                    Sys.addVertex(i);
                }
                std::cerr << "Add edges\n";
                srand(time(NULL));
                for (int i = 0; i < (val) * (val - 1) / 4; i++)
                {
                    int u = rand() % val;
                    int v = rand() % val;
                    int w = rand() % 9 + 1;
                    while (!Sys.addEdge(u, v, w))
                    {
                        u = rand() % val;
                        v = rand() % val;
                    }
                }
                // for (int i = 0; i < val; i++)
                //     Sys.addEdge(i, (i + 1) % val, 1);
                // for (int i = 2; i < val; i++)
                //     Sys.addEdge(i - 1, i, 1);
                std::cerr << "Force-directed\n";
                std::thread th(&Backend::Graph::setup, &Sys);
                th.detach();
                drawTexture();
            }
            if (i == 1 && !run1step)
            {
                if (f[i].getText() == "")
                    return;
                int val = std::stoi(std::string(f[i].getText()));
                if (val >= 20)
                {
                    fail = oversize;
                    drawTexture();
                    return;
                }
                windowHandle.clear();
                Sys.reset();
                resetColor();
                if (!Sys.addVertex(val))
                {
                    fail = existed;
                    drawTexture();
                    return;
                }
                std::cerr << "Force-directed\n";
                std::thread th(&Backend::Graph::arrangePosition, &Sys);
                th.detach();
                drawTexture();
            }
            if (i == 2 && !run1step)
            {
                if (f[i].getText() == "")
                    return;
                int val = std::stoi(std::string(f[i].getText()));
                if (val >= 20)
                {
                    fail = oversize;
                    drawTexture();
                    return;
                }
                windowHandle.clear();
                Sys.reset();
                resetColor();
                if (Sys.removeVertex(val))
                {
                    std::cerr << "Force-directed\n";
                    std::thread th(&Backend::Graph::arrangePosition, &Sys);
                    th.detach();
                    drawTexture();
                }
            }
            if (i == 3 && !run1step)
            {
                if (f[i].getText() == "" || f[i + 1].getText() == "" || f[i + 2].getText() == "")
                    return;
                int u = std::stoi(std::string(f[i].getText())),
                    v = std::stoi(std::string(f[i + 1].getText())),
                    w = std::stoi(std::string(f[i + 2].getText()));
                windowHandle.clear();
                Sys.reset();
                resetColor();
                if (!Sys.addEdge(u, v, w))
                {
                    fail = existed;
                    drawTexture();
                    return;
                }
                else
                {
                    std::cerr << "Force-directed\n";
                    std::thread th(&Backend::Graph::arrangePosition, &Sys);
                    th.detach();
                    drawTexture();
                }
            }
            if (i == 4 && !run1step)
            {
                if (f[6].getText() == "" || f[7].getText() == "")
                    return;
                int u = std::stoi(std::string(f[6].getText())),
                    v = std::stoi(std::string(f[7].getText()));
                windowHandle.clear();
                Sys.reset();
                resetColor();
                if (Sys.removeEdge(u, v))
                {
                    std::cerr << "Force-directed\n";
                    std::thread th(&Backend::Graph::arrangePosition, &Sys);
                    th.detach();
                    drawTexture();
                }
            }
            if (i == 5 && !run1step)
            {
                if (f[8].getText() == "")
                    return;
                int s = std::stoi(std::string(f[8].getText()));
                windowHandle.clear();
                Sys.reset();
                resetColor();
                std::cerr << "Dijkstra\n";
                if (!Sys.Dijkstra(s))
                {
                    fail = notExisted;
                    drawTexture();
                    return;
                }
                keepRunning = 1;
                std::thread Run(&Handle::run, &windowHandle);
                Run.detach();
            }
            if (i == 6 && !run1step)
            {
                windowHandle.clear();
                Sys.reset();
                resetColor();
                if (Sys.MST())
                {
                    keepRunning = 1;
                    std::thread Run(&Handle::run, &windowHandle);
                    Run.detach();
                }
            }
        }
    }
}

void GraphVisual::clear()
{
    windowHandle.clear();
    Sys.clear();
    clearGpx();
    for (int i = 0; i < 6; i++)
        f[i].erase();
    interval = 1200;
}

void GraphVisual::clearGpx()
{
    for (int i = 0; i < 20; i++)
    {
        sf::String Tmp("");
        Table[i].setFillColor(BackgroundColor);
        Table[i].setTextColor(TextColor);
        Table[i].setOutline(TextColor);
        Table[i].setText(Tmp);
        Table[i].setPosition(0, 0);
        Table[i].drawTexture();
        Table[i].hide();
    }
    for (int i = 0; i < 190; i++)
    {
        sf::String Tmp("");
        Arc[i].setFillColor(TextColor);
        Arc[i].setFirstPosition(sf::Vector2f(0, 0));
        Arc[i].setSecondPosition(sf::Vector2f(0, 0));
        Arc[i].setThickness(0.1f * g_radius);
        Arc[i].setWeight(Tmp);
        Arc[i].hide();
    }
}

void GraphVisual::Navigating(const sf::Event &event)
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

void GraphVisual::resetColor()
{
    for (int i = 0; i < 20; i++)
    {
        Table[i].setFillColor(BackgroundColor);
        Table[i].setOutline(TextColor);
        Table[i].setTextColor(TextColor);
    }
    for (int i = 0; i < 190; i++)
    {
        Arc[i].setFillColor(TextColor);
        Arc[i].setThickness(0.1f * g_radius);
    }
}

void GraphVisual::ReSetting()
{
    Pattern::ReSetting();
    ToolBar.setFillColor(ToolBarColor);
    for (int i = 0; i < 9; i++)
    {
        f[i].setFillColor(BackgroundColor);
        f[i].setTextColor(TextColor);
    }
    for (int i = 0; i < 7; i++)
    {
        Start[i].setFillColor(ToolBarColor);
        Start[i].setTextColor(SpecialTextColor);
        Start[i].setCoverColor(sf::Color(__max((ToolBarColor.r - 50) % 255, (ToolBarColor.r + 50) % 255),
                                         __max((ToolBarColor.g - 50) % 255, (ToolBarColor.g + 50) % 255),
                                         __max((ToolBarColor.b - 50) % 255, (ToolBarColor.b + 50) % 255), 50));
    }
    Overload.setFillColor(TextColor);
    RandomErr.setFillColor(TextColor);
    Exist.setFillColor(TextColor);
    NonExist.setFillColor(TextColor);
    if (Table)
        for (int i = 0; i < 20; i++)
        {
            Table[i].setRadius(g_radius);
            Table[i].setFillColor(BackgroundColor);
            Table[i].setTextColor(TextColor);
            Table[i].setOutline(TextColor);
        }
    if (Arc)
        for (int i = 0; i < 190; i++)
        {
            Arc[i].setThickness(0.1f * g_radius);
            Arc[i].setFillColor(TextColor);
        }
}

GraphVisual::~GraphVisual()
{
    delete[] Table;
    delete[] Arc;
    Table = nullptr;
    Arc = nullptr;
}