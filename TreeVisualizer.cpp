#include <FrontendGlobal.hpp>
#include <TextBox.hpp>
#include <Initialize.hpp>
#include <math.h>
#include <numbers>
#include <iostream>
#include <CircleNode.hpp>

Frontend::LinearProbing Test;
// sf::RectangleShape Rec100;

signed main()
{
    // Initialize Window
    window.create(sf::VideoMode(sf::VideoMode::getDesktopMode().width,
                                sf::VideoMode::getDesktopMode().height * 93 / 100),
                  "Tree Visualization",
                  sf::Style::Default ^ sf::Style::Resize);
    window.setPosition(sf::Vector2i(0, 0));
    window.setFramerateLimit(60);
    window.requestFocus();

    // Initialize
    Frontend::Initialize();
    // Test.create();
    
    // Rec100.setSize(sf::Vector2f(50, 50));
    // Rec100.setPosition(500, 20);

    // Execute

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            default:
                break;
            }
            // Test.processEvent(event);
            Visual.processEvent(event);
            // if (Visual.mouseOnButton(mouse.getPosition(window)))
            //     window.setMouseCursor(HandCursor);
            // else
            //     window.setMouseCursor(DefaultCursor);
        }
        window.clear(BackgroundColor);
        if (keepRunning || run1step)
            Visual.drawTexture();
        // window.draw(Test);
        // window.draw(Rec100);
        // window.draw(Tmp);
        // window.draw(Tmp1);
        window.draw(Visual);
        window.display();
    }
}