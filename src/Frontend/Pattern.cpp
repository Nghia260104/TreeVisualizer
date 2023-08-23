#include <Pattern.hpp>
#include <thread>
#include <FrontendGlobal.hpp>
using namespace Frontend;

Pattern::Pattern()
{
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