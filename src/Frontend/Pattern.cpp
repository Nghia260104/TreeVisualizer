#include <Pattern.hpp>
#include <thread>
#include <FrontendGlobal.hpp>
using namespace Frontend;

Pattern::Pattern()
{
    speed = 0;
}

void Pattern::create()
{
    // Background
    Texture.create(window.getSize().x, window.getSize().y);
    Texture.clear(BackgroundColor);

    // Artwork
    Artwork.setSize(sf::Vector2f(1680, 800));
    Artwork.setOrigin(Artwork.getSize().x / 2, 0);
    Artwork.setPosition(window.getSize().x / 2, 100);
    Artwork.setFillColor(BackgroundColor);

    // Navigate Box
    NavigateBox.setSize(sf::Vector2f(130, 50));
    NavigateBox.setFillColor(ToolBarColor);
    NavigateBox.setPosition(window.getSize().x / 2 - 65, window.getSize().y - 50);

    // Speed Button
    Spd.create(window.getSize().x / 2 + 200, window.getSize().y - 50, 50, 50, Segoe, fontsize, "1x");
    Spd.setFillColor(ToolBarColor);
    Spd.setTextColor(SpecialTextColor);
    Spd.setCoverColor(sf::Color(__max((ToolBarColor.r - 50) % 255, (ToolBarColor.r + 50) % 255),
                                __max((ToolBarColor.g - 50) % 255, (ToolBarColor.g + 50) % 255),
                                __max((ToolBarColor.b - 50) % 255, (ToolBarColor.b + 50) % 255), 50));
    Spd.drawTexture();

    // Navigate Button
    std::string Tmp[3] = {"stepback.png", "start.png", "stepforw.png"};
    for (int i = 0; i < 3; i++)
    {
        Navigate[i].create(window.getSize().x / 2 - 55 + i * 40, window.getSize().y - 40, 30, 30, Segoe, 1, "");
        Navigate[i].setFillColor(BackgroundColor);
        Navigate[i].setCoverColor(sf::Color(__max((BackgroundColor.r - 50) % 255, (BackgroundColor.r + 50) % 255),
                                            __max((BackgroundColor.g - 50) % 255, (BackgroundColor.g + 50) % 255),
                                            __max((BackgroundColor.b - 50) % 255, (BackgroundColor.b + 50) % 255), 50));
        Navigate[i].setImage(UTILS_PATH + Tmp[i]);
        Navigate[i].setImageColor(ToolBarColor);
        Navigate[i].drawTexture();
    }
}

void Pattern::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    sf::Sprite sprite(Texture.getTexture());
    target.draw(sprite);
}

void Pattern::drawTexture()
{
}

void Pattern::ReSetting()
{
    Texture.clear(BackgroundColor);
    Artwork.setFillColor(BackgroundColor);
    NavigateBox.setFillColor(ToolBarColor);
    for (int i = 0; i < 3; i++)
    {
        Navigate[i].setFillColor(BackgroundColor);
        Navigate[i].setImageColor(ToolBarColor);
        Navigate[i].setCoverColor(sf::Color(__max((ToolBarColor.r - 50) % 255, (ToolBarColor.r + 50) % 255),
                                __max((ToolBarColor.g - 50) % 255, (ToolBarColor.g + 50) % 255),
                                __max((ToolBarColor.b - 50) % 255, (ToolBarColor.b + 50) % 255), 50));
    }
    Spd.setFillColor(ToolBarColor);
    Spd.setTextColor(SpecialTextColor);
    Spd.setCoverColor(sf::Color(__max((ToolBarColor.r - 50) % 255, (ToolBarColor.r + 50) % 255),
                                __max((ToolBarColor.g - 50) % 255, (ToolBarColor.g + 50) % 255),
                                __max((ToolBarColor.b - 50) % 255, (ToolBarColor.b + 50) % 255), 50));
}

void Pattern::Navigating(const sf::Event &event)
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
                    std::thread th(&SingleExecute::stepback, &List, std::ref(event));
                    th.detach();
                }
                else if (i == 1)
                {
                    keepRunning = 1;
                    run1step = 1;
                    std::thread th(&SingleExecute::run, &List, std::ref(event));
                    th.detach();
                }
                else if (i == 2)
                {
                    run1step = 1;
                    std::thread th(&SingleExecute::stepforw, &List, std::ref(event));
                    th.detach();
                }
            }
            return;
        }
    }
}

void Pattern::changeSpd(const sf::Event &event)
{
    Texture.draw(Spd);
    if (Spd.isPressed(event))
    {
        speed = (speed + 1) % 4;
        Spd.setText(S[speed]);
        interval = timeInterval[speed];
        Spd.drawTexture();
        return;
    }
}