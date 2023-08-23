#include <Execute.hpp>
#include <FrontendGlobal.hpp>
#include <iostream>
#include <thread>

void SingleExecute::clear()
{
    if (List.size())
    {
        for (int i = step; i < List.size(); i++)
        {
            if (List[i].pos_c)
                List[i].Cur->setPosition(List[i].x, List[i].y);
            if (List[i].val_c)
                List[i].Cur->setStr(List[i].val);
        }
        for (int i = 0; i < List.size(); i++)
        {
            List[i].Cur->setOutline(TextColor);
            List[i].Cur->setTextColor(TextColor);
            List[i].Cur->setFillColor(BackgroundColor);
        }
    }

    // if (RevList.size())
    //     for (int i = step; i >= 0; i--)
    //         RevList[i].Cur->setOutline(TextColor);
    Visual.drawTexture();
    step = 0;
    order = 0;
    List.clear();
    RevList.clear();
}

void SingleExecute::push_back(Process Tmp)
{
    List.push_back(Tmp);
}

int SingleExecute::size()
{
    return List.size();
}

const Process &SingleExecute::operator[](int id)
{
    return List[id];
}

void SingleExecute::stepforw(const sf::Event &event)
{
    if (step == List.size())
    {
        run1step = 0;
        return;
    }
    // std::cerr << "Forw step: " << step << '\n';
    // current = &Cur;
    // std::cerr << &Cur << "step stage\n";
    sf::Color Tmp_color = List[step].Cur->getOutlineColor();
    sf::Color Tmp_fill = List[step].Cur->getFillColor();
    sf::Color delta_color = List[step].color - Tmp_color;
    sf::Vector2f Tmp_pos = List[step].Cur->getPosition();
    sf::Text Tmp_text = List[step].Cur->getText();
    float x = List[step].x - Tmp_pos.x, y = List[step].y - Tmp_pos.y;
    if (step == order && step + 1 < List.size())
    {
        Process a;
        a.color = Tmp_color;
        a.color_c = List[step].color_c;
        a.pos_c = List[step].pos_c;
        a.x = Tmp_pos.x;
        a.y = Tmp_pos.y;
        a.val_c = List[step].val_c;
        a.val = Tmp_text.getString();
        a.Cur = List[step].Cur;
        if (step + 2 == List.size())
            a.val_c = List[step + 1].val_c;
        if (step == 0)
        {
            a.emph = 0;
            RevList.push_back(a);
        }
        a.emph = 1;
        RevList.push_back(a);
        order++;
    }
    clock.restart();
    while (clock.getElapsedTime().asMilliseconds() <= interval)
    {
        float i = clock.getElapsedTime().asMilliseconds();
        // std::cerr << i << " " << '\n';
        if (((int)i % 20) == 0)
        {
            if (List[step].color_c)
            {
                sf::Color temp = sf::Color(Tmp_color.r + 1.0f * (i * (List[step].color.r - Tmp_color.r)) / (1.0f * interval),
                                           Tmp_color.g + 1.0f * (i * (List[step].color.g - Tmp_color.g)) / (1.0f * interval),
                                           Tmp_color.b + 1.0f * (i * (List[step].color.b - Tmp_color.b)) / (1.0f * interval));
                sf::Color temp_fill = sf::Color(Tmp_fill.r + 1.0f * (i * (List[step].color.r - Tmp_fill.r)) / (1.0f * interval),
                                                Tmp_fill.g + 1.0f * (i * (List[step].color.g - Tmp_fill.g)) / (1.0f * interval),
                                                Tmp_fill.b + 1.0f * (i * (List[step].color.b - Tmp_fill.b)) / (1.0f * interval));
                sf::Color tmp_text_color = sf::Color(TextColor.r + 1.0f * (i * (BackgroundColor.r - TextColor.r)) / (1.0f * interval),
                                                     TextColor.g + 1.0f * (i * (BackgroundColor.g - TextColor.g)) / (1.0f * interval),
                                                     TextColor.b + 1.0f * (i * (BackgroundColor.b - TextColor.b)) / (1.0f * interval));
                List[step].Cur->setOutline(temp);
                if (List[step].emph)
                {
                    List[step].Cur->setFillColor(temp_fill);
                    List[step].Cur->setTextColor(tmp_text_color);
                }
                if (step > 0)
                {
                    sf::Color tmp_fill_revcolor = sf::Color(List[step - 1].color.r + 1.0f * (i * (BackgroundColor.r - List[step - 1].color.r)) / (1.0f * interval),
                                                            List[step - 1].color.g + 1.0f * (i * (BackgroundColor.g - List[step - 1].color.g)) / (1.0f * interval),
                                                            List[step - 1].color.b + 1.0f * (i * (BackgroundColor.b - List[step - 1].color.b)) / (1.0f * interval));
                    sf::Color tmp_text_revcolor = sf::Color(BackgroundColor.r + 1.0f * (i * (List[step - 1].color.r - BackgroundColor.r)) / (1.0f * interval),
                                                            BackgroundColor.g + 1.0f * (i * (List[step - 1].color.g - BackgroundColor.g)) / (1.0f * interval),
                                                            BackgroundColor.b + 1.0f * (i * (List[step - 1].color.b - BackgroundColor.b)) / (1.0f * interval));
                    List[step - 1].Cur->setFillColor(tmp_fill_revcolor);
                    List[step - 1].Cur->setTextColor(tmp_text_revcolor);
                }
                // std::cerr << (int)temp.r << " " << (int)temp.g << " " << (int)temp.b << '\n';
                // Rec100.setFillColor(temp);
            }
            if (List[step].pos_c)
                List[step].Cur->setPosition(Tmp_pos.x + 1.0f * (i * x) / (1.0f * interval),
                                            Tmp_pos.y + 1.0f * (i * y) / (1.0f * interval));
            if (List[step].val_c)
            {
                if (i >= interval / 2)
                {
                    Tmp_text.setString(List[step].val);
                    Tmp_text.setFillColor(List[step].Cur->getTextColor());
                    // sf::Color temp_cor = TextColor;
                    // temp_cor.a = (2.0f * i - (1.0f * interval)) * 255 / (1.0f * interval);
                    // // Tmp_text.setFillColor(sf::Color((2.0f * i - (1.0f * interval)) * TextColor.r / (1.0f * interval),
                    // //                                 (2.0f * i - (1.0f * interval)) * TextColor.g / (1.0f * interval),
                    // //                                 (2.0f * i - (1.0f * interval)) * TextColor.b / (1.0f * interval)));
                    // Tmp_text.setFillColor(temp_cor);
                    List[step].Cur->setText(Tmp_text);
                }
                // else
                // {
                //     sf::Color temp_cor = TextColor;
                //     temp_cor.a = ((1.0f * interval) - 2.0f * i) * 255 / (1.0f * interval);
                //     // Tmp_text.setFillColor(sf::Color(((1.0f * interval) - 2.0f * i) * TextColor.r / (1.0f * interval),
                //     //                                 ((1.0f * interval) - 2.0f * i) * TextColor.g / (1.0f * interval),
                //     //                                 ((1.0f * interval) - 2.0f * i) * TextColor.b / (1.0f * interval)));
                //     Tmp_text.setFillColor(temp_cor);
                // }
            }
            // List[step].Cur->drawTexture();
            // std::cerr << step << '\n';
            // current->drawTexture();
        }
    }
    if (List[step].color_c)
    {
        List[step].Cur->setOutline(List[step].color);
        if (step > 0)
        {
            List[step - 1].Cur->setFillColor(BackgroundColor);
            List[step - 1].Cur->setTextColor(List[step - 1].color);
        }
        if (List[step].emph)
        {
            List[step].Cur->setFillColor(List[step].color);
            List[step].Cur->setTextColor(BackgroundColor);
        }
    }
    if (List[step].pos_c)
        List[step].Cur->setPosition(x, y);
    if (List[step].val_c)
        List[step].Cur->setStr(List[step].val);
    // current->drawTexture();
    step++;
    run1step = 0;
}

// void SingleExecute::checking(const sf::Event &event)
// {
//     while (keepRunning)
//         for (int i = 0; i < 3; i++)
//             if (current->Navigate[i].isPressed(event))
//                 keepRunning = 0;
// }

void SingleExecute::stepback(const sf::Event &event)
{
    if (step == 0)
    {
        run1step = 0;
        return;
    }
    step--;
    // std::cerr << "Back step: " << step << '\n';
    sf::Color Tmp_color = RevList[step].Cur->getOutlineColor();
    sf::Color Tmp_fill = RevList[step].Cur->getFillColor();
    // sf::Color delta_color = RevList[step].color - Tmp_color;
    sf::Vector2f Tmp_pos = RevList[step].Cur->getPosition();
    sf::Text Tmp_text = RevList[step].Cur->getText();
    float x = RevList[step].x - Tmp_pos.x, y = RevList[step].y - Tmp_pos.y;
    clock.restart();
    while (clock.getElapsedTime().asMilliseconds() <= interval)
    {
        float i = clock.getElapsedTime().asMilliseconds();
        // std::cerr << i << " " << '\n';
        if (((int)i % 20) == 0)
        {
            if (RevList[step].color_c)
            {
                sf::Color temp = sf::Color(Tmp_color.r + 1.0f * (i * (RevList[step].color.r - Tmp_color.r)) / (1.0f * interval),
                                           Tmp_color.g + 1.0f * (i * (RevList[step].color.g - Tmp_color.g)) / (1.0f * interval),
                                           Tmp_color.b + 1.0f * (i * (RevList[step].color.b - Tmp_color.b)) / (1.0f * interval));
                sf::Color temp_fill = sf::Color(Tmp_fill.r + 1.0f * (i * (Highlight.r - Tmp_fill.r)) / (1.0f * interval),
                                                Tmp_fill.g + 1.0f * (i * (Highlight.g - Tmp_fill.g)) / (1.0f * interval),
                                                Tmp_fill.b + 1.0f * (i * (Highlight.b - Tmp_fill.b)) / (1.0f * interval));
                sf::Color tmp_text_color = sf::Color(Highlight.r + 1.0f * (i * (BackgroundColor.r - Highlight.r)) / (1.0f * interval),
                                                     Highlight.g + 1.0f * (i * (BackgroundColor.g - Highlight.g)) / (1.0f * interval),
                                                     Highlight.b + 1.0f * (i * (BackgroundColor.b - Highlight.b)) / (1.0f * interval));
                sf::Color tmp_fill_revcolor = sf::Color(Highlight.r + 1.0f * (i * (BackgroundColor.r - Highlight.r)) / (1.0f * interval),
                                                        Highlight.g + 1.0f * (i * (BackgroundColor.g - Highlight.g)) / (1.0f * interval),
                                                        Highlight.b + 1.0f * (i * (BackgroundColor.b - Highlight.b)) / (1.0f * interval));
                sf::Color tmp_text_revcolor = sf::Color(BackgroundColor.r + 1.0f * (i * (TextColor.r - BackgroundColor.r)) / (1.0f * interval),
                                                        BackgroundColor.g + 1.0f * (i * (TextColor.g - BackgroundColor.g)) / (1.0f * interval),
                                                        BackgroundColor.b + 1.0f * (i * (TextColor.b - BackgroundColor.b)) / (1.0f * interval));
                if (RevList[step].emph)
                {
                    RevList[step].Cur->setOutline(temp_fill);
                    RevList[step].Cur->setFillColor(temp_fill);
                    RevList[step].Cur->setTextColor(tmp_text_color);
                }
                else
                {
                    RevList[step].Cur->setOutline(temp);
                    RevList[step].Cur->setFillColor(tmp_fill_revcolor);
                    RevList[step].Cur->setTextColor(tmp_text_revcolor);
                }
                if (step < List.size() - 1)
                {
                    RevList[step + 1].Cur->setOutline(temp);
                    RevList[step + 1].Cur->setFillColor(tmp_fill_revcolor);
                    RevList[step + 1].Cur->setTextColor(tmp_text_revcolor);
                }
            }
            if (RevList[step].pos_c)
                RevList[step].Cur->setPosition(Tmp_pos.x + 1.0f * (i * x) / (1.0f * interval),
                                               Tmp_pos.y + 1.0f * (i * y) / (1.0f * interval));
            if (RevList[step].val_c)
            {
                if (i >= interval / 2)
                {
                    Tmp_text.setString(RevList[step].val);
                    Tmp_text.setFillColor(RevList[step].Cur->getTextColor());
                    RevList[step].Cur->setText(Tmp_text);
                }
            }
        }
    }
    if (RevList[step].color_c)
    {
        if (RevList[step].emph)
        {
            RevList[step].Cur->setOutline(Highlight);
            RevList[step].Cur->setFillColor(Highlight);
            RevList[step].Cur->setTextColor(BackgroundColor);
        }
        else
        {
            RevList[step].Cur->setOutline(Highlight);
            RevList[step].Cur->setFillColor(BackgroundColor);
            RevList[step].Cur->setTextColor(TextColor);
        }
        if (step < List.size() - 1)
        {
            RevList[step + 1].Cur->setOutline(TextColor);
            RevList[step + 1].Cur->setFillColor(BackgroundColor);
            RevList[step + 1].Cur->setTextColor(TextColor);
        }
    }
    if (RevList[step].pos_c)
        RevList[step].Cur->setPosition(x, y);
    if (RevList[step].val_c)
        RevList[step].Cur->setStr(RevList[step].val);
    // current->drawTexture();
    // step--;
    run1step = 0;
}

void SingleExecute::run(const sf::Event &event)
{
    // std::cerr << "Running\n";
    // std::cerr << "run stage\n";
    // std::thread check(&SingleExecute::checking, this, std::ref(event));
    // check.detach();
    // buildRev();
    while (keepRunning && step < List.size())
    {
        run1step = 1;
        stepforw(event);
    }
    keepRunning = false;
    // std::cerr << "Stop\n";
    // std::cerr << "Step: " << step << "\n\n";
    // display();
    // displayRev();
}

void SingleExecute::displayRev()
{
    std::cerr << "RevList: ";
    // for (int i = RevList.size() - 1; i >= 0; i--)
    // {
    //     std::cerr << RevList[i].Cur << "\n"
    //               << "Val" << RevList[i].val_c << " " << std::string(RevList[i].val) << "\n"
    //               << RevList[i].color_c << " " << (int)RevList[i].color.r << " " << (int)RevList[i].color.g << " " << (int)RevList[i].color.b << "\n\n";
    // }
    for (int i = 0; i < RevList.size(); i++)
    {
        std::cerr << RevList[i].Cur << " ";
    }
    std::cerr << '\n';
}

void SingleExecute::display()
{
    std::cerr << "List: ";
    for (int i = 0; i < List.size(); i++)
    {
        std::cerr << List[i].Cur << " ";
    }
    std::cerr << '\n';
}

// void SingleExecute::buildRev()
// {
//     for (int i = 0; i + 1 < List.size(); i++)
//     {
//     }
// }

void Execute::clear()
{
    if (List.size())
    {
        for (int i = step; i < List.size(); i++)
        {
            for (auto &j : List[i])
            {
                if (j.Cur)
                {
                    if (j.pos_c)
                        j.Cur->setPosition(j.x, j.y);
                    if (j.val_c)
                        j.Cur->setStr(j.val);
                    if (j.show)
                        if (j.Cur->isHidden())
                            j.Cur->show();
                        else
                            j.Cur->hide();
                }
                if (j.Arc)
                {
                    if (j.arc_pos_c)
                    {
                        j.Arc->setFirstPosition(j.arc_pos1);
                        j.Arc->setSecondPosition(j.arc_pos2);
                    }
                }
            }
        }
        for (int i = 0; i < List.size(); i++)
        {
            for (Process &j : List[i])
            {
                if (j.Cur)
                {
                    j.Cur->setOutline(TextColor);
                    j.Cur->setTextColor(TextColor);
                    j.Cur->setFillColor(BackgroundColor);
                }
                if (j.Arc)
                {
                    j.Arc->setFillColor(TextColor);
                    j.Arc->setThickness(0.1f * g_radius);
                }
            }
        }
    }

    // if (RevList.size())
    //     for (int i = step; i >= 0; i--)
    //         RevList[i].Cur->setOutline(TextColor);
    Visual.drawTexture();
    step = 0;
    order = 0;
    List.clear();
    RevList.clear();
}

void Execute::push_back(const std::vector<Process> &Tmp)
{
    List.push_back(Tmp);
}

int Execute::size()
{
    return List.size();
}

const std::vector<Process> &Execute::operator[](int id)
{
    return List[id];
}

void Execute::stepforw(const sf::Event &event)
{
    if (step == List.size())
    {
        run1step = 0;
        return;
    }
    // std::cerr << "Forw step: " << step << '\n';
    // current = &Cur;
    // std::cerr << &Cur << "step stage\n";
    std::vector<sf::Color> Tmp_color;
    std::vector<sf::Color> Tmp_fill;
    std::vector<sf::Vector2f> Tmp_pos, Tmp_arc_pos1, Tmp_arc_pos2;
    std::vector<sf::Text> Tmp_text;
    std::vector<float> x, y;
    for (int j = 0; j < List[step].size(); j++)
    {
        if (List[step][j].Cur)
        {
            Tmp_color.push_back(List[step][j].Cur->getOutlineColor());
            Tmp_fill.push_back(List[step][j].Cur->getFillColor());
            Tmp_pos.push_back(List[step][j].Cur->getPosition());
            Tmp_text.push_back(List[step][j].Cur->getText());
        }
        else
        {
            Tmp_color.push_back(TextColor);
            Tmp_fill.push_back(BackgroundColor);
            Tmp_pos.push_back(sf::Vector2f(0, 0));
            Tmp_text.push_back(sf::Text());
        }
        x.push_back(List[step][j].x - Tmp_pos[j].x);
        y.push_back(List[step][j].y - Tmp_pos[j].y);
        if (List[step][j].Arc)
        {
            Tmp_arc_pos1.push_back(List[step][j].Arc->getFirstPosition());
            Tmp_arc_pos2.push_back(List[step][j].Arc->getSecondPosition());
        }
        else
        {
            Tmp_arc_pos1.push_back(sf::Vector2f(0, 0));
            Tmp_arc_pos2.push_back(sf::Vector2f(0, 0));
        }
    }
    if (step == order && step + 1 < List.size())
    {
        std::vector<Process> Preprocess;
        for (int j = 0; j < List[step].size(); j++)
        {
            Process a;
            a.color = Tmp_color[j];
            a.color_c = List[step][j].color_c;
            a.pos_c = List[step][j].pos_c;
            a.x = Tmp_pos[j].x;
            a.y = Tmp_pos[j].y;
            a.val_c = List[step][j].val_c;
            a.val = Tmp_text[j].getString();
            a.Cur = List[step][j].Cur;
            a.Arc = List[step][j].Arc;
            a.arc_pos1 = Tmp_arc_pos1[j];
            a.arc_pos2 = Tmp_arc_pos2[j];
            a.arc_pos_c = List[step][j].arc_pos_c;
            if (step + 2 == List.size())
                a.val_c = List[step + 1][j].val_c;
            a.emph = List[step][j].emph;
            a.show = List[step][j].show;
            a.reset_c = List[step][j].reset_c;
            Preprocess.push_back(a);
        }
        if (step == 0)
        {
            std::vector<Process> Reset = Preprocess;
            for (int j = 0; j < Reset.size(); j++)
                Reset[j].emph = 0;
            RevList.push_back(Reset);
        }
        RevList.push_back(Preprocess);
        order++;
    }
    clock.restart();
    while (clock.getElapsedTime().asMilliseconds() <= interval)
    {
        float i = clock.getElapsedTime().asMilliseconds();
        // std::cerr << i << " " << '\n';
        if (((int)i % 20) == 0)
        {
            if (step > 0)
            {
                for (int a = 0; a < List[step - 1].size(); a++)
                {
                    if (List[step - 1][a].Cur)
                    {
                        sf::Color tmp_fill_revcolor = sf::Color(List[step - 1][a].color.r + 1.0f * (i * (BackgroundColor.r - List[step - 1][a].color.r)) / (1.0f * interval),
                                                                List[step - 1][a].color.g + 1.0f * (i * (BackgroundColor.g - List[step - 1][a].color.g)) / (1.0f * interval),
                                                                List[step - 1][a].color.b + 1.0f * (i * (BackgroundColor.b - List[step - 1][a].color.b)) / (1.0f * interval));
                        sf::Color tmp_text_revcolor = sf::Color(BackgroundColor.r + 1.0f * (i * (List[step - 1][a].color.r - BackgroundColor.r)) / (1.0f * interval),
                                                                BackgroundColor.g + 1.0f * (i * (List[step - 1][a].color.g - BackgroundColor.g)) / (1.0f * interval),
                                                                BackgroundColor.b + 1.0f * (i * (List[step - 1][a].color.b - BackgroundColor.b)) / (1.0f * interval));
                        List[step - 1][a].Cur->setFillColor(tmp_fill_revcolor);
                        List[step - 1][a].Cur->setTextColor(tmp_text_revcolor);
                    }
                    if (List[step - 1][a].Arc)
                    {
                        float tmp_thick = 0.15f * g_radius - 1.0f * i * 0.05f * g_radius / (1.0f * interval);
                        List[step - 1][a].Arc->setThickness(tmp_thick);
                    }
                }
            }
            for (int j = 0; j < List[step].size(); j++)
            {
                if (List[step][j].reset_c)
                {
                    for (int a = 0; a < step; a++)
                        for (int z = 0; z < List[a].size(); z++)
                        {
                            if (List[a][z].Cur)
                            {
                                List[a][z].Cur->setFillColor(BackgroundColor);
                                List[a][z].Cur->setOutline(TextColor);
                                List[a][z].Cur->setTextColor(TextColor);
                            }
                            if (List[a][z].Arc)
                                List[a][z].Arc->setFillColor(TextColor);
                        }
                    continue;
                }
                if (List[step][j].Cur)
                {
                    if (List[step][j].color_c)
                    {
                        sf::Color temp = sf::Color(Tmp_color[j].r + 1.0f * (i * (List[step][j].color.r - Tmp_color[j].r)) / (1.0f * interval),
                                                   Tmp_color[j].g + 1.0f * (i * (List[step][j].color.g - Tmp_color[j].g)) / (1.0f * interval),
                                                   Tmp_color[j].b + 1.0f * (i * (List[step][j].color.b - Tmp_color[j].b)) / (1.0f * interval));
                        sf::Color temp_fill = sf::Color(Tmp_fill[j].r + 1.0f * (i * (List[step][j].color.r - Tmp_fill[j].r)) / (1.0f * interval),
                                                        Tmp_fill[j].g + 1.0f * (i * (List[step][j].color.g - Tmp_fill[j].g)) / (1.0f * interval),
                                                        Tmp_fill[j].b + 1.0f * (i * (List[step][j].color.b - Tmp_fill[j].b)) / (1.0f * interval));
                        sf::Color tmp_text_color = sf::Color(TextColor.r + 1.0f * (i * (BackgroundColor.r - TextColor.r)) / (1.0f * interval),
                                                             TextColor.g + 1.0f * (i * (BackgroundColor.g - TextColor.g)) / (1.0f * interval),
                                                             TextColor.b + 1.0f * (i * (BackgroundColor.b - TextColor.b)) / (1.0f * interval));
                        List[step][j].Cur->setOutline(temp);
                        if (List[step][j].emph)
                        {
                            List[step][j].Cur->setFillColor(temp_fill);
                            List[step][j].Cur->setTextColor(tmp_text_color);
                        }
                    }
                    if (List[step][j].pos_c)
                        List[step][j].Cur->setPosition(Tmp_pos[j].x + 1.0f * (i * x[j]) / (1.0f * interval),
                                                       Tmp_pos[j].y + 1.0f * (i * y[j]) / (1.0f * interval));
                    if (List[step][j].val_c)
                    {
                        if (i >= interval / 2)
                        {
                            Tmp_text[j].setString(List[step][j].val);
                            Tmp_text[j].setFillColor(List[step][j].Cur->getTextColor());
                            List[step][j].Cur->setText(Tmp_text[j]);
                        }
                    }
                    if (List[step][j].show)
                    {
                        if (List[step][j].Cur->isHidden())
                            List[step][j].Cur->show();
                        else
                            List[step][j].Cur->hide();
                    }
                }
                if (List[step][j].Arc)
                {
                    sf::Color tmp_high_color = sf::Color(TextColor.r + 1.0f * (i * (Highlight.r - TextColor.r)) / (1.0f * interval),
                                                         TextColor.g + 1.0f * (i * (Highlight.g - TextColor.g)) / (1.0f * interval),
                                                         TextColor.b + 1.0f * (i * (Highlight.b - TextColor.b)) / (1.0f * interval));
                    List[step][j].Arc->setFillColor(tmp_high_color);
                    if (List[step][j].arc_pos_c)
                    {
                        sf::Vector2f fi = Tmp_arc_pos1[j] + (1.0f * i * (List[step][j].arc_pos1 - Tmp_arc_pos1[j])) / (1.0f * interval),
                                     sc = Tmp_arc_pos2[j] + (1.0f * i * (List[step][j].arc_pos2 - Tmp_arc_pos2[j])) / (1.0f * interval);
                        List[step][j].Arc->setFirstPosition(fi);
                        List[step][j].Arc->setSecondPosition(sc);
                    }
                    if (List[step][j].emph)
                    {
                        float tmp_thick = 0.1f * g_radius + 1.0f * i * 0.05f * g_radius / (1.0f * interval);
                        List[step][j].Arc->setThickness(tmp_thick);
                    }
                }
            }
        }
    }
    for (int j = 0; j < List[step].size(); j++)
    {
        if (List[step][j].Cur)
        {
            if (List[step][j].color_c)
            {
                List[step][j].Cur->setOutline(List[step][j].color);
                if (step > 0)
                {
                    List[step - 1][j].Cur->setFillColor(BackgroundColor);
                    List[step - 1][j].Cur->setTextColor(List[step - 1][j].color);
                }
                if (List[step][j].emph)
                {
                    List[step][j].Cur->setFillColor(List[step][j].color);
                    List[step][j].Cur->setTextColor(BackgroundColor);
                }
            }
            if (List[step][j].pos_c)
                List[step][j].Cur->setPosition(x[j], y[j]);
            if (List[step][j].val_c)
                List[step][j].Cur->setStr(List[step][j].val);
        }
        if (List[step][j].Arc)
        {
            if (List[step][j].emph)
                List[step][j].Arc->setThickness(0.15f * g_radius);
            if (List[step][j].arc_pos_c)
            {
                List[step][j].Arc->setFirstPosition(List[step][j].arc_pos1);
                List[step][j].Arc->setSecondPosition(List[step][j].arc_pos2);
            }
        }
    }
    step++;
    run1step = 0;
}

void Execute::stepback(const sf::Event &event)
{
    if (step == 0)
    {
        run1step = 0;
        return;
    }
    step--;
    // std::cerr << "Back step: " << step << '\n';
    std::vector<sf::Color> Tmp_color;
    std::vector<sf::Color> Tmp_fill;
    std::vector<sf::Vector2f> Tmp_pos, Tmp_arc_pos1, Tmp_arc_pos2;
    std::vector<sf::Text> Tmp_text;
    std::vector<float> x, y;
    for (int j = 0; j < RevList[step].size(); j++)
    {
        if (RevList[step][j].Cur)
        {
            Tmp_color.push_back(RevList[step][j].Cur->getOutlineColor());
            Tmp_fill.push_back(RevList[step][j].Cur->getFillColor());
            Tmp_pos.push_back(RevList[step][j].Cur->getPosition());
            Tmp_text.push_back(RevList[step][j].Cur->getText());
        }
        else
        {
            Tmp_color.push_back(TextColor);
            Tmp_fill.push_back(BackgroundColor);
            Tmp_pos.push_back(sf::Vector2f(0, 0));
            Tmp_text.push_back(sf::Text());
        }
        x.push_back(RevList[step][j].x - Tmp_pos[j].x);
        y.push_back(RevList[step][j].y - Tmp_pos[j].y);
        if (RevList[step][j].Arc)
        {
            Tmp_arc_pos1.push_back(RevList[step][j].Arc->getFirstPosition());
            Tmp_arc_pos2.push_back(RevList[step][j].Arc->getSecondPosition());
        }
        else
        {
            Tmp_arc_pos1.push_back(sf::Vector2f(0, 0));
            Tmp_arc_pos2.push_back(sf::Vector2f(0, 0));
        }
    }
    clock.restart();
    while (clock.getElapsedTime().asMilliseconds() <= interval)
    {
        float i = clock.getElapsedTime().asMilliseconds();
        // std::cerr << i << " " << '\n';
        if (((int)i % 20) == 0)
        {
            if (step < List.size() - 1)
            {
                for (int j = 0; j < RevList[step + 1].size(); j++)
                {
                    if (RevList[step + 1][j].Cur)
                    {
                        sf::Color temp = sf::Color(RevList[step + 1][j].color.r + 1.0f * (i * (TextColor.r - RevList[step + 1][j].color.r)) / (1.0f * interval),
                                                   RevList[step + 1][j].color.g + 1.0f * (i * (TextColor.g - RevList[step + 1][j].color.g)) / (1.0f * interval),
                                                   RevList[step + 1][j].color.b + 1.0f * (i * (TextColor.b - RevList[step + 1][j].color.b)) / (1.0f * interval));
                        sf::Color tmp_fill_revcolor = sf::Color(Highlight.r + 1.0f * (i * (BackgroundColor.r - Highlight.r)) / (1.0f * interval),
                                                                Highlight.g + 1.0f * (i * (BackgroundColor.g - Highlight.g)) / (1.0f * interval),
                                                                Highlight.b + 1.0f * (i * (BackgroundColor.b - Highlight.b)) / (1.0f * interval));
                        sf::Color tmp_text_revcolor = sf::Color(BackgroundColor.r + 1.0f * (i * (TextColor.r - BackgroundColor.r)) / (1.0f * interval),
                                                                BackgroundColor.g + 1.0f * (i * (TextColor.g - BackgroundColor.g)) / (1.0f * interval),
                                                                BackgroundColor.b + 1.0f * (i * (TextColor.b - BackgroundColor.b)) / (1.0f * interval));
                        RevList[step + 1][j].Cur->setOutline(temp);
                        RevList[step + 1][j].Cur->setFillColor(tmp_fill_revcolor);
                        RevList[step + 1][j].Cur->setTextColor(tmp_text_revcolor);
                    }
                    if (RevList[step + 1][j].Arc)
                    {
                        sf::Color tmp_high_revcolor = sf::Color(Highlight.r + 1.0f * (i * (TextColor.r - Highlight.r)) / (1.0f * interval),
                                                                Highlight.g + 1.0f * (i * (TextColor.g - Highlight.g)) / (1.0f * interval),
                                                                Highlight.b + 1.0f * (i * (TextColor.b - Highlight.b)) / (1.0f * interval));
                        RevList[step + 1][j].Arc->setFillColor(tmp_high_revcolor);
                        RevList[step + 1][j].Arc->setThickness(0.15f * g_radius - (1.0f * i * 0.05f * g_radius / (1.0f * interval)));
                    }
                }
            }
            for (int j = 0; j < RevList[step].size(); j++)
            {
                if (RevList[step][j].reset_c)
                {
                    for (int a = 0; a < step; a++)
                        for (int z = 0; z < List[a].size(); z++)
                        {
                            if (List[a][z].Cur)
                            {
                                List[a][z].Cur->setFillColor(BackgroundColor);
                                List[a][z].Cur->setOutline(TextColor);
                                List[a][z].Cur->setTextColor(TextColor);
                            }
                            if (List[a][z].Arc)
                                List[a][z].Arc->setFillColor(TextColor);
                        }
                    continue;
                }
                sf::Color temp = sf::Color(Tmp_color[j].r + 1.0f * (i * (RevList[step][j].color.r - Tmp_color[j].r)) / (1.0f * interval),
                                           Tmp_color[j].g + 1.0f * (i * (RevList[step][j].color.g - Tmp_color[j].g)) / (1.0f * interval),
                                           Tmp_color[j].b + 1.0f * (i * (RevList[step][j].color.b - Tmp_color[j].b)) / (1.0f * interval));
                sf::Color temp_fill = sf::Color(Tmp_fill[j].r + 1.0f * (i * (Highlight.r - Tmp_fill[j].r)) / (1.0f * interval),
                                                Tmp_fill[j].g + 1.0f * (i * (Highlight.g - Tmp_fill[j].g)) / (1.0f * interval),
                                                Tmp_fill[j].b + 1.0f * (i * (Highlight.b - Tmp_fill[j].b)) / (1.0f * interval));
                sf::Color tmp_text_color = sf::Color(Highlight.r + 1.0f * (i * (BackgroundColor.r - Highlight.r)) / (1.0f * interval),
                                                     Highlight.g + 1.0f * (i * (BackgroundColor.g - Highlight.g)) / (1.0f * interval),
                                                     Highlight.b + 1.0f * (i * (BackgroundColor.b - Highlight.b)) / (1.0f * interval));
                sf::Color tmp_fill_revcolor = sf::Color(Highlight.r + 1.0f * (i * (BackgroundColor.r - Highlight.r)) / (1.0f * interval),
                                                        Highlight.g + 1.0f * (i * (BackgroundColor.g - Highlight.g)) / (1.0f * interval),
                                                        Highlight.b + 1.0f * (i * (BackgroundColor.b - Highlight.b)) / (1.0f * interval));
                sf::Color tmp_high_revcolor = sf::Color(Highlight.r + 1.0f * (i * (TextColor.r - Highlight.r)) / (1.0f * interval),
                                                        Highlight.g + 1.0f * (i * (TextColor.g - Highlight.g)) / (1.0f * interval),
                                                        Highlight.b + 1.0f * (i * (TextColor.b - Highlight.b)) / (1.0f * interval));
                sf::Color tmp_text_revcolor = sf::Color(BackgroundColor.r + 1.0f * (i * (TextColor.r - BackgroundColor.r)) / (1.0f * interval),
                                                        BackgroundColor.g + 1.0f * (i * (TextColor.g - BackgroundColor.g)) / (1.0f * interval),
                                                        BackgroundColor.b + 1.0f * (i * (TextColor.b - BackgroundColor.b)) / (1.0f * interval));
                if (RevList[step][j].Cur)
                {
                    if (RevList[step][j].color_c)
                    {
                        if (RevList[step][j].emph)
                        {
                            RevList[step][j].Cur->setOutline(temp_fill);
                            RevList[step][j].Cur->setFillColor(temp_fill);
                            RevList[step][j].Cur->setTextColor(tmp_text_color);
                        }
                        else
                        {
                            RevList[step][j].Cur->setOutline(temp);
                            RevList[step][j].Cur->setFillColor(tmp_fill_revcolor);
                            RevList[step][j].Cur->setTextColor(tmp_text_revcolor);
                        }
                    }
                    if (RevList[step][j].pos_c)
                        RevList[step][j].Cur->setPosition(Tmp_pos[j].x + 1.0f * (i * x[j]) / (1.0f * interval),
                                                          Tmp_pos[j].y + 1.0f * (i * y[j]) / (1.0f * interval));
                    if (RevList[step][j].val_c)
                    {
                        if (i >= interval / 2)
                        {
                            Tmp_text[j].setString(RevList[step][j].val);
                            Tmp_text[j].setFillColor(RevList[step][j].Cur->getTextColor());
                            RevList[step][j].Cur->setText(Tmp_text[j]);
                        }
                    }
                    if (RevList[step][j].show)
                    {
                        if (RevList[step][j].Cur->isHidden())
                            RevList[step][j].Cur->show();
                        else
                            RevList[step][j].Cur->hide();
                    }
                }
                if (RevList[step][j].Arc)
                {
                    RevList[step][j].Arc->setThickness(0.1f * g_radius + (1.0f * i * 0.05f * g_radius / (1.0f * interval)));
                    if (RevList[step][j].arc_pos_c)
                    {
                        sf::Vector2f fi = Tmp_arc_pos1[j] + (1.0f * i * (RevList[step][j].arc_pos1 - Tmp_arc_pos1[j])) / (1.0f * interval),
                                     sc = Tmp_arc_pos2[j] + (1.0f * i * (RevList[step][j].arc_pos2 - Tmp_arc_pos2[j])) / (1.0f * interval);
                        RevList[step][j].Arc->setFirstPosition(fi);
                        RevList[step][j].Arc->setSecondPosition(sc);
                    }
                }
            }
        }
    }

    if (step < List.size() - 1)
    {
        for (int j = 0; j < RevList[step + 1].size(); j++)
        {
            if (RevList[step + 1][j].Cur)
            {
                RevList[step + 1][j].Cur->setOutline(TextColor);
                RevList[step + 1][j].Cur->setFillColor(BackgroundColor);
                RevList[step + 1][j].Cur->setTextColor(TextColor);
            }
            if (RevList[step + 1][j].Arc)
            {
                RevList[step + 1][j].Arc->setFillColor(TextColor);
                RevList[step + 1][j].Arc->setThickness(0.1f * g_radius);
            }
        }
    }
    for (int j = 0; j < RevList[step].size(); j++)
    {
        if (RevList[step][j].Cur)
        {
            if (RevList[step][j].color_c)
            {
                if (RevList[step][j].emph)
                {
                    RevList[step][j].Cur->setOutline(Highlight);
                    RevList[step][j].Cur->setFillColor(Highlight);
                    RevList[step][j].Cur->setTextColor(BackgroundColor);
                }
                else
                {
                    RevList[step][j].Cur->setOutline(Highlight);
                    RevList[step][j].Cur->setFillColor(BackgroundColor);
                    RevList[step][j].Cur->setTextColor(TextColor);
                }
            }
            if (RevList[step][j].pos_c)
                RevList[step][j].Cur->setPosition(x[j], y[j]);
            if (RevList[step][j].val_c)
                RevList[step][j].Cur->setStr(RevList[step][j].val);
        }
        if (RevList[step][j].Arc)
        {
            RevList[step][j].Arc->setThickness(0.15f * g_radius);
            if (RevList[step][j].arc_pos_c)
            {
                RevList[step][j].Arc->setFirstPosition(RevList[step][j].arc_pos1);
                RevList[step][j].Arc->setSecondPosition(RevList[step][j].arc_pos2);
            }
        }
    }
    // current->drawTexture();
    // step--;
    run1step = 0;
}

void Execute::run(const sf::Event &event)
{
    // std::cerr << "Running\n";
    // std::cerr << "run stage\n";
    // std::thread check(&SingleExecute::checking, this, std::ref(event));
    // check.detach();
    // buildRev();
    while (keepRunning && step < List.size())
        stepforw(event);
    keepRunning = false;
    // std::cerr << "Stop\n";
    // std::cerr << "Step: " << step << "\n\n";
    // display();
    // displayRev();
}

void Execute::displayRev()
{
    std::cerr << "RevList:\n";
    // for (int i = RevList.size() - 1; i >= 0; i--)
    // {
    //     std::cerr << RevList[i].Cur << "\n"
    //               << "Val" << RevList[i].val_c << " " << std::string(RevList[i].val) << "\n"
    //               << RevList[i].color_c << " " << (int)RevList[i].color.r << " " << (int)RevList[i].color.g << " " << (int)RevList[i].color.b << "\n\n";
    // }
    for (int i = 0; i < RevList.size(); i++)
    {
        for (auto &j : RevList[i])
            std::cerr << j.Cur << " ";
        std::cerr << '\n';
    }
    std::cerr << '\n';
}

void Execute::display()
{
    std::cerr << "List:\n";
    for (int i = 0; i < List.size(); i++)
    {
        for (auto &j : List[i])
            std::cerr << j.Cur << " ";
        std::cerr << '\n';
    }
    std::cerr << '\n';
}