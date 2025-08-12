#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    // create fullscreen window
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Heart", sf::Style::Fullscreen);
    window.setMouseCursorVisible(false);

    sf::Event event;

    // create heart shape with 10 points
    sf::ConvexShape heart(10);
    heart.setPoint(0, sf::Vector2f(100, 0));
    heart.setPoint(1, sf::Vector2f(200, 0));
    heart.setPoint(2, sf::Vector2f(275, 100));
    heart.setPoint(3, sf::Vector2f(350, 0));
    heart.setPoint(4, sf::Vector2f(450, 0));
    heart.setPoint(5, sf::Vector2f(550, 100));
    heart.setPoint(6, sf::Vector2f(550, 300));
    heart.setPoint(7, sf::Vector2f(275, 500));
    heart.setPoint(8, sf::Vector2f(0, 300));
    heart.setPoint(9, sf::Vector2f(0, 100));

    // set heart colors and outline
    heart.setFillColor(sf::Color::Red);
    heart.setOutlineThickness(-10);
    heart.setOutlineColor(sf::Color::White);

    sf::Clock clock; // clock for delta time
    int moveX = 150; // horizontal speed in pixels/sec
    int moveY = 50;  // vertical speed in pixels/sec

    while (window.isOpen())
    {
        // handle events
        while (window.pollEvent(event))
        {
            if (event.key.code == sf::Keyboard::Escape)
            {
                window.close(); // close window on escape
            }
        }

        // calculate delta time
        float deltatime = clock.restart().asSeconds();

        // move heart
        heart.move(moveX * deltatime, moveY * deltatime);

        // bounce horizontally when hitting right wall
        if (heart.getPosition().x + heart.getLocalBounds().width >= sf::VideoMode::getDesktopMode().width)
        {
            moveX = -150;
        }
        // bounce vertically when hitting bottom wall
        else if (heart.getPosition().y + heart.getLocalBounds().height >= sf::VideoMode::getDesktopMode().height)
        {
            moveY = -50;
        }
        // bounce horizontally when hitting left wall
        else if (heart.getPosition().x <= 0)
        {
            moveX = 150;
        }
        // bounce vertically when hitting top wall
        else if (heart.getPosition().y <= 0)
        {
            moveY = 50;
        }

        // draw frame
        window.clear();
        window.draw(heart);
        window.display();
    }
    return 0;
}