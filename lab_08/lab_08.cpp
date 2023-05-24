#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <math.h>
#include <time.h>

#include <iostream>
#include <vector>
#include <random>

#include "CustomRectangleShape.h"

sf::Color CustomRectangleShape::inactive_color = sf::Color(192, 192, 192);

int main() {
    srand(time(NULL));

    // create the window
    int win_width = 800;
    int win_height = 600;
    sf::RenderWindow window(sf::VideoMode(win_width, win_height), "Cool rectangles");
    window.setFramerateLimit(60);
    sf::Clock clock;

    std::vector<CustomRectangleShape> rectangles;
    for (int i = 0; i < 10; i++) {
        sf::Vector2f size(120.0, 60.0);
        sf::Vector2f position(std::rand() % (window.getSize().x - 120), std::rand() % (window.getSize().y - 60));
        CustomRectangleShape rec(size, position);

        rec.setFillColor(CustomRectangleShape::inactive_color);
        rec.setBounds(0, window.getSize().x, 0, window.getSize().y);
        rec.setSpeed(std::rand() % 10 * 10 + 50, std::rand() % 10 * 10 + 50, std::rand() % 5 * 5 + 5);

        rectangles.emplace_back(rec);
    }

    // run the program as long as the window is open
    while (window.isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed) window.close();

            int x = 0, y = 0, step = 5;
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) window.close();
                
                switch (event.key.code) {
                    case sf::Keyboard::Up:    y = -step; break;
                    case sf::Keyboard::Down:  y =  step; break;
                    case sf::Keyboard::Left:  x = -step; break;
                    case sf::Keyboard::Right: x =  step; break;
                }

                //if (event.key.code == sf::Keyboard::Up
                // || event.key.code == sf::Keyboard::Down
                // || event.key.code == sf::Keyboard::Left
                // || event.key.code == sf::Keyboard::Right) {
                    for (auto& rec : rectangles) {
                        if (rec.selected()) rec.moveLockedToBounds(x, y);
                    }
                //}
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f mouse_pos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                for (auto& rec : rectangles) {
                    if (!rec.collides(mouse_pos)) continue;
                    if (event.mouseButton.button == sf::Mouse::Left)  rec.select();
                    if (event.mouseButton.button == sf::Mouse::Right) rec.unselect();
                }
            }
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        // animate and draw
        sf::Time elapsed = clock.restart();
        for (auto & rec : rectangles) {
            rec.animate(elapsed);
            window.draw(rec);
        }

        // end the current frame
        window.display();
    }

    return 0;
}
