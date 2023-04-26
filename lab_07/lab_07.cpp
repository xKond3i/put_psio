// PSiO at Poznan University Of Technology
// Laboratory 07
// Source: https://jug.dpieczynski.pl/lab-psio/Lab%2007%20-%20Wprowadzenie%20do%20SFML.html
// Executed by Konrad Ceglarski
// 20/04/2023

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <math.h>
#include <time.h>

void change_color(sf::RectangleShape & shape, bool random_shift = true) {
    const int max_shift = 32;
    int shift = 16;
    sf::Color color = shape.getFillColor();
    if (random_shift) shift = std::floor(rand() * 32);
    color.r = (color.r + shift) % 256;
    if (random_shift) shift = std::floor(rand() * 32);
    color.g = (color.g + shift) % 256;
    if (random_shift) shift = std::floor(rand() * 32);
    color.b = (color.b + shift) % 256;
    shape.setFillColor(color);
}

void fix_pos_to_win_bounds(sf::RectangleShape & shape, sf::RenderWindow & window) {
    const float w = window.getSize().x;
    const float h = window.getSize().y;
    sf::FloatRect bounds = shape.getGlobalBounds();
    float xo = 0; // x overflow
    if      (bounds.left <= 0)                  xo = bounds.left;
    else if ((bounds.left + bounds.width) >= w) xo = bounds.left + bounds.width - w;
    float yo = 0; // y overflow
    if      (bounds.top <= 0)                   yo = bounds.top;
    else if ((bounds.top + bounds.height) >= h) yo = bounds.top + bounds.height - h;
    const sf::Vector2f pos = shape.getPosition();
    shape.setPosition(sf::Vector2f(pos.x - xo, pos.y - yo));
}

int main() {
    srand(time(NULL));

    // create the window
    int win_width = 800;
    int win_height = 600;
    sf::RenderWindow window(sf::VideoMode(win_width, win_height), "My window");

    // create some shapes
    sf::CircleShape circle(100.0);
    circle.setPosition(100.0, 300.0);
    circle.setFillColor(sf::Color(100, 250, 50));

    sf::RectangleShape rectangle(sf::Vector2f(120.0, 60.0));
    rectangle.setPosition(500.0, 400.0);
    rectangle.setFillColor(sf::Color(100, 50, 250));

    sf::ConvexShape triangle;
    triangle.setPointCount(3);
    triangle.setPoint(0, sf::Vector2f(0.0, 0.0));
    triangle.setPoint(1, sf::Vector2f(0.0, 100.0));
    triangle.setPoint(2, sf::Vector2f(140.0, 40.0));
    triangle.setOutlineColor(sf::Color::Red);
    triangle.setOutlineThickness(5);
    triangle.setPosition(600.0, 100.0);

    // clock to keep frames consistant!
    sf::Clock clock;

    // rectangle velocities
    int rectangle_velocity_x = 5;
    int rectangle_velocity_y = 15;
    float rectangle_angular_velocity = 10;

    rectangle.setScale(sf::Vector2f(2.0, 2.0));

    // run the program as long as the window is open
    while (window.isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::Time elapsed = clock.getElapsedTime();
        if (elapsed.asMilliseconds() > 50) {
            rectangle.move(rectangle_velocity_x, rectangle_velocity_y);
            rectangle.rotate(rectangle_angular_velocity / 20);
            sf::FloatRect bounds = rectangle.getGlobalBounds();
            if (bounds.left <= 0 || bounds.left + bounds.width >= win_width) {
                rectangle_velocity_x *= -1;
                fix_pos_to_win_bounds(rectangle, window);
                change_color(rectangle);
            }
            if (bounds.top <= 0 || bounds.top + bounds.height >= win_height) {
                rectangle_velocity_y *= -1;
                fix_pos_to_win_bounds(rectangle, window);
                change_color(rectangle);
            }
            clock.restart();
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...
        window.draw(circle);
        window.draw(rectangle);
        window.draw(triangle);

        // end the current frame
        window.display();
    }

    return 0;
}
