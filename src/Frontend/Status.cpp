#include <Status.hpp>
#include <FrontendGlobal.hpp>
#include <iostream>

Status::Status()
{
    Node = nullptr;
    OutlineColor = NodeTextColor = ArcColor = TextColor;
    NodeFillColor = BackgroundColor;
    Arc = nullptr;
    thickness = 1;
    NodePosition = ArcFirstPosition = ArcSecondPosition = sf::Vector2f(0, 0);
    nodeVal = "";
    hideNode = hideArc = 0;
}

void Status::highlightNode()
{
    NodeFillColor = Highlight;
    NodeTextColor = BackgroundColor;
    OutlineColor = Highlight;
}

void Status::NodeOnPath()
{
    NodeFillColor = BackgroundColor;
    NodeTextColor = Highlight;
}

void Status::NormalNode()
{
    NodeFillColor = BackgroundColor;
    NodeTextColor = TextColor;
    OutlineColor = TextColor;
}

void Status::highlightArc()
{
    ArcColor = Highlight;
    thickness = 0.15f * g_radius;
}

void Status::ArcOnPath()
{
    // ArcColor = Highlight;
    thickness = 0.1f * g_radius;
}

void Status::NormalArc()
{
    ArcColor = TextColor;
    thickness = 0.1f * g_radius;
}

Handle::Handle()
{
    step = 0;
}

void Handle::push_back(std::vector<Status> Tmp)
{
    list.push_back(Tmp);
}

int Handle::size()
{
    return list.size();
}

std::vector<Status> &Handle::back()
{
    return list.back();
}

std::vector<Status> &Handle::operator[](int id)
{
    return list[id];
}

void Handle::clear()
{
    if (list.size())
    {
        std::cerr << "Num steps: " << list.size() << "\n";
        for (int i = 0; i < list.back().size(); i++)
        {
            if (list.back()[i].Node)
            {
                list.back()[i].Node->setFillColor(BackgroundColor);
                list.back()[i].Node->setOutline(TextColor);
                list.back()[i].Node->setText(list.back()[i].nodeVal);
                list.back()[i].Node->setTextColor(TextColor);
                list.back()[i].Node->setPosition(list.back()[i].NodePosition.x, list.back()[i].NodePosition.y);
                list.back()[i].Node->toPar = list.back()[i].Node->toPar;
                if (list.back()[i].hideNode)
                    list.back()[i].Node->hide();
                else
                    list.back()[i].Node->show();
            }
            if (list.back()[i].Arc)
            {
                list.back()[i].Arc->setFillColor(TextColor);
                list.back()[i].Arc->setFirstPosition(list.back()[i].ArcFirstPosition);
                list.back()[i].Arc->setSecondPosition(list.back()[i].ArcSecondPosition);
                list.back()[i].Arc->setThickness(0.1f * g_radius);
                if (list.back()[i].hideArc)
                    list.back()[i].Arc->hide();
                else
                    list.back()[i].Arc->show();
            }
        }
    }
    Visual.drawTexture();
    list.clear();
    step = 0;
}

void Handle::stepforw()
{
    if (step + 1 >= list.size())
    {
        run1step = 0;
        return;
    }

    step++;
    std::cerr << "Stepforw step: " << step << '\n';
    clock.restart();
    while (clock.getElapsedTime().asMilliseconds() <= interval)
    {
        float i = clock.getElapsedTime().asMilliseconds();
        if (((int)i % 20) == 0)
        {
            for (int j = 0; j < list[step].size(); j++)
            {
                if (list[step][j].Node)
                {
                    sf::Color change_Fill(list[step - 1][j].NodeFillColor.r + 1.0f * i * (list[step][j].NodeFillColor.r - list[step - 1][j].NodeFillColor.r) / (1.0f * interval),
                                          list[step - 1][j].NodeFillColor.g + 1.0f * i * (list[step][j].NodeFillColor.g - list[step - 1][j].NodeFillColor.g) / (1.0f * interval),
                                          list[step - 1][j].NodeFillColor.b + 1.0f * i * (list[step][j].NodeFillColor.b - list[step - 1][j].NodeFillColor.b) / (1.0f * interval)),
                        change_out(list[step - 1][j].OutlineColor.r + 1.0f * i * (list[step][j].OutlineColor.r - list[step - 1][j].OutlineColor.r) / (1.0f * interval),
                                   list[step - 1][j].OutlineColor.g + 1.0f * i * (list[step][j].OutlineColor.g - list[step - 1][j].OutlineColor.g) / (1.0f * interval),
                                   list[step - 1][j].OutlineColor.b + 1.0f * i * (list[step][j].OutlineColor.b - list[step - 1][j].OutlineColor.b) / (1.0f * interval)),
                        change_text(list[step - 1][j].NodeTextColor.r + 1.0f * i * (list[step][j].NodeTextColor.r - list[step - 1][j].NodeTextColor.r) / (1.0f * interval),
                                    list[step - 1][j].NodeTextColor.g + 1.0f * i * (list[step][j].NodeTextColor.g - list[step - 1][j].NodeTextColor.g) / (1.0f * interval),
                                    list[step - 1][j].NodeTextColor.b + 1.0f * i * (list[step][j].NodeTextColor.b - list[step - 1][j].NodeTextColor.b) / (1.0f * interval));
                    list[step][j].Node->setFillColor(change_Fill);
                    list[step][j].Node->setOutline(change_out);
                    list[step][j].Node->setTextColor(change_text);
                    float x = list[step - 1][j].NodePosition.x + 1.0f * i * (list[step][j].NodePosition.x - list[step - 1][j].NodePosition.x) / (1.0f * interval),
                          y = list[step - 1][j].NodePosition.y + 1.0f * i * (list[step][j].NodePosition.y - list[step - 1][j].NodePosition.y) / (1.0f * interval);
                    list[step][j].Node->setPosition(x, y);
                    if (i >= interval / 2)
                        list[step][j].Node->setText(list[step][j].nodeVal);
                    if (!list[step][j].hideNode)
                        list[step][j].Node->show();
                    else
                        list[step][j].Node->hide();
                }
                if (list[step][j].Arc)
                {
                    sf::Color change_arc(list[step - 1][j].ArcColor.r + 1.0f * i * (list[step][j].ArcColor.r - list[step - 1][j].ArcColor.r) / (1.0f * interval),
                                         list[step - 1][j].ArcColor.g + 1.0f * i * (list[step][j].ArcColor.g - list[step - 1][j].ArcColor.g) / (1.0f * interval),
                                         list[step - 1][j].ArcColor.b + 1.0f * i * (list[step][j].ArcColor.b - list[step - 1][j].ArcColor.b) / (1.0f * interval));
                    list[step][j].Arc->setFillColor(change_arc);
                    list[step][j].Arc->setThickness(list[step - 1][j].thickness + 1.0f * i * (list[step][j].thickness - list[step - 1][j].thickness) / (1.0f * interval));
                    float x1 = list[step - 1][j].ArcFirstPosition.x + 1.0f * i * (list[step][j].ArcFirstPosition.x - list[step - 1][j].ArcFirstPosition.x) / (1.0f * interval),
                          y1 = list[step - 1][j].ArcFirstPosition.y + 1.0f * i * (list[step][j].ArcFirstPosition.y - list[step - 1][j].ArcFirstPosition.y) / (1.0f * interval);
                    float x2 = list[step - 1][j].ArcSecondPosition.x + 1.0f * i * (list[step][j].ArcSecondPosition.x - list[step - 1][j].ArcSecondPosition.x) / (1.0f * interval),
                          y2 = list[step - 1][j].ArcSecondPosition.y + 1.0f * i * (list[step][j].ArcSecondPosition.y - list[step - 1][j].ArcSecondPosition.y) / (1.0f * interval);
                    if (!list[step][j].hideArc)
                        list[step][j].Arc->show();
                    else
                        list[step][j].Arc->hide();
                    list[step][j].Arc->setFirstPosition(sf::Vector2f(x1, y1));
                    list[step][j].Arc->setSecondPosition(sf::Vector2f(x2, y2));
                }
            }
        }
    }
    run1step = 0;
}

void Handle::stepback()
{
    if (step <= 0)
    {
        run1step = 0;
        return;
    }

    step--;
    std::cerr << "Stepback step: " << step << '\n';
    clock.restart();
    while (clock.getElapsedTime().asMilliseconds() <= interval)
    {
        float i = clock.getElapsedTime().asMilliseconds();
        if (((int)i % 20) == 0)
        {
            for (int j = 0; j < list[step].size(); j++)
            {
                if (list[step][j].Node)
                {
                    sf::Color change_Fill(list[step + 1][j].NodeFillColor.r + 1.0f * i * (list[step][j].NodeFillColor.r - list[step + 1][j].NodeFillColor.r) / (1.0f * interval),
                                          list[step + 1][j].NodeFillColor.g + 1.0f * i * (list[step][j].NodeFillColor.g - list[step + 1][j].NodeFillColor.g) / (1.0f * interval),
                                          list[step + 1][j].NodeFillColor.b + 1.0f * i * (list[step][j].NodeFillColor.b - list[step + 1][j].NodeFillColor.b) / (1.0f * interval)),
                        change_out(list[step + 1][j].OutlineColor.r + 1.0f * i * (list[step][j].OutlineColor.r - list[step + 1][j].OutlineColor.r) / (1.0f * interval),
                                   list[step + 1][j].OutlineColor.g + 1.0f * i * (list[step][j].OutlineColor.g - list[step + 1][j].OutlineColor.g) / (1.0f * interval),
                                   list[step + 1][j].OutlineColor.b + 1.0f * i * (list[step][j].OutlineColor.b - list[step + 1][j].OutlineColor.b) / (1.0f * interval)),
                        change_text(list[step + 1][j].NodeTextColor.r + 1.0f * i * (list[step][j].NodeTextColor.r - list[step + 1][j].NodeTextColor.r) / (1.0f * interval),
                                    list[step + 1][j].NodeTextColor.g + 1.0f * i * (list[step][j].NodeTextColor.g - list[step + 1][j].NodeTextColor.g) / (1.0f * interval),
                                    list[step + 1][j].NodeTextColor.b + 1.0f * i * (list[step][j].NodeTextColor.b - list[step + 1][j].NodeTextColor.b) / (1.0f * interval));
                    list[step][j].Node->setFillColor(change_Fill);
                    list[step][j].Node->setOutline(change_out);
                    list[step][j].Node->setTextColor(change_text);
                    float x = list[step + 1][j].NodePosition.x + 1.0f * i * (list[step][j].NodePosition.x - list[step + 1][j].NodePosition.x) / (1.0f * interval),
                          y = list[step + 1][j].NodePosition.y + 1.0f * i * (list[step][j].NodePosition.y - list[step + 1][j].NodePosition.y) / (1.0f * interval);
                    list[step][j].Node->setPosition(x, y);
                    if (i >= interval / 2)
                        list[step][j].Node->setText(list[step][j].nodeVal);
                    if (!list[step][j].hideNode)
                        list[step][j].Node->show();
                    else
                        list[step][j].Node->hide();
                }
                if (list[step][j].Arc)
                {
                    sf::Color change_arc(list[step + 1][j].ArcColor.r + 1.0f * i * (list[step][j].ArcColor.r - list[step + 1][j].ArcColor.r) / (1.0f * interval),
                                         list[step + 1][j].ArcColor.g + 1.0f * i * (list[step][j].ArcColor.g - list[step + 1][j].ArcColor.g) / (1.0f * interval),
                                         list[step + 1][j].ArcColor.b + 1.0f * i * (list[step][j].ArcColor.b - list[step + 1][j].ArcColor.b) / (1.0f * interval));
                    list[step][j].Arc->setFillColor(change_arc);
                    list[step][j].Arc->setThickness(list[step + 1][j].thickness + 1.0f * i * (list[step][j].thickness - list[step + 1][j].thickness) / (1.0f * interval));
                    float x1 = list[step + 1][j].ArcFirstPosition.x + 1.0f * i * (list[step][j].ArcFirstPosition.x - list[step + 1][j].ArcFirstPosition.x) / (1.0f * interval),
                          y1 = list[step + 1][j].ArcFirstPosition.y + 1.0f * i * (list[step][j].ArcFirstPosition.y - list[step + 1][j].ArcFirstPosition.y) / (1.0f * interval);
                    float x2 = list[step + 1][j].ArcSecondPosition.x + 1.0f * i * (list[step][j].ArcSecondPosition.x - list[step + 1][j].ArcSecondPosition.x) / (1.0f * interval),
                          y2 = list[step + 1][j].ArcSecondPosition.y + 1.0f * i * (list[step][j].ArcSecondPosition.y - list[step + 1][j].ArcSecondPosition.y) / (1.0f * interval);
                    list[step][j].Arc->setFirstPosition(sf::Vector2f(x1, y1));
                    list[step][j].Arc->setSecondPosition(sf::Vector2f(x2, y2));
                    if (!list[step][j].hideArc)
                        list[step][j].Arc->show();
                    else
                        list[step][j].Arc->hide();
                }
            }
        }
    }
    run1step = 0;
}

void Handle::run()
{
    while (keepRunning && step + 1 < list.size())
    {
        run1step = 1;
        stepforw();
    }
    keepRunning = false;
}
