#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <memory>
#include <vector>

#include <math.h>

#include <iostream>

sf::Vector2f calculateOutsideOffset(sf::Vector2f coords, sf::FloatRect playerBounds, sf::FloatRect wallBounds) {
    int lbe = wallBounds.left;                    // left boundry edge
    int rbe = wallBounds.left + wallBounds.width; // right boundry edge
    int tbe = wallBounds.top;                     // top boundry edge
    int bbe = wallBounds.top + wallBounds.height; // bottom boundry edge

    float sl2lbe = lbe - playerBounds.left - playerBounds.width; // space left to left boundry edge
    float sl2rbe = playerBounds.left - rbe;                      // space left to right boundry edge
    float sl2tbe = tbe - playerBounds.top - playerBounds.height; // space left to top boundry edge
    float sl2bbe = playerBounds.top - bbe;                       // space left to bottom boundry edge

    float xo;
    if (coords.x > 0) xo =  std::min(std::abs(coords.x), std::abs(sl2lbe));
    else              xo = -std::min(std::abs(coords.x), std::abs(sl2rbe));

    float yo;
    if (coords.y > 0) yo =  std::min(std::abs(coords.y), std::abs(sl2tbe));
    else              yo = -std::min(std::abs(coords.y), std::abs(sl2bbe));

    return sf::Vector2f(xo, yo);
}

sf::Vector2f calculateInsideOffset(sf::Vector2f coords, sf::FloatRect playerBounds, sf::FloatRect wallBounds) {
    int lbe = wallBounds.left;                    // left boundry edge
    int rbe = wallBounds.left + wallBounds.width; // right boundry edge
    int tbe = wallBounds.top;                     // top boundry edge
    int bbe = wallBounds.top + wallBounds.height; // bottom boundry edge

    float sl2lbe = playerBounds.left - lbe;                      // space left to left boundry edge
    float sl2rbe = rbe - playerBounds.left - playerBounds.width; // space left to right boundry edge
    float sl2tbe = playerBounds.top - tbe;                       // space left to top boundry edge
    float sl2bbe = bbe - playerBounds.top - playerBounds.height; // space left to bottom boundry edge

    float step_x;
    if (coords.x < 0) step_x = -std::min(std::abs(coords.x), std::abs(sl2lbe));
    else              step_x =  std::min(std::abs(coords.x), std::abs(sl2rbe));

    float step_y;
    if (coords.y < 0) step_y = -std::min(std::abs(coords.y), std::abs(sl2tbe));
    else              step_y =  std::min(std::abs(coords.y), std::abs(sl2bbe));

    return sf::Vector2f(step_x, step_y);
}

int main() {
    // create the window
    int win_width = 1280;
    int win_height = 720;
    sf::RenderWindow window(sf::VideoMode(win_width, win_height), "Labirynth");

    // Background
    sf::Sprite bg;
    sf::Texture grass;
    if (!grass.loadFromFile("resources/grass.png")) { return 1; }
    grass.setRepeated(true);
    bg.setTexture(grass);
    bg.setTextureRect(sf::IntRect(0, 0, win_width, win_height));

    // Player
    sf::Texture playerTexture;
    sf::Sprite player;
    if (!playerTexture.loadFromFile("resources/guy.png")) { return 1; }
    player.setTexture(playerTexture);

    std::vector<std::unique_ptr<sf::Drawable>> walls;
    sf::Texture texture_wall;
    if (!texture_wall.loadFromFile("resources/wall.png")) { return 1; }
    texture_wall.setRepeated(true);

    std::vector<sf::FloatRect> wall_coords = { {250,                         (float)win_height/2-150, 50,  400},
                                               {(float)(win_width-200)/2-75, (float)win_height/2-200, 200, 50 },
                                               {(float)win_width-450,        (float)win_height/2-250, 50,  400},
                                               {(float)win_width-400,        (float)win_height/2-50,  150, 50 } };
    for (const auto& coord : wall_coords) {
        std::unique_ptr<sf::Sprite> wall = std::make_unique<sf::Sprite>();
        wall -> setPosition(coord.left, coord.top);
        wall -> setTexture(texture_wall);
        wall -> setTextureRect({0, 0, (int)coord.width, (int)coord.height});

        auto bounds = wall -> getGlobalBounds();
        // std::cout << "WALL AT: x: " << bounds.left << ", " << "y: " << bounds.top << ", " << "w: " << bounds.width << ", " << "h: " << bounds.height << "\n";
        
        walls.push_back(std::move(wall));
    }

    // event moving values
    float x = 0, y = 0, step = 5.0/25;

    // run the program as long as the window is open
    while (window.isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) window.close();
                
                switch (event.key.code) {
                    case sf::Keyboard::Up:
                    case sf::Keyboard::W:
                        y = -step;
                        break;
                    case sf::Keyboard::Down:
                    case sf::Keyboard::S:
                        y = step;
                        break;
                    case sf::Keyboard::Left:
                    case sf::Keyboard::A:
                        x = -step;
                        break;
                    case sf::Keyboard::Right:
                    case sf::Keyboard::D:
                        x = step;
                        break;
                }
            }

            if (event.type == sf::Event::KeyReleased) {
                switch (event.key.code) {
                case sf::Keyboard::Up:
                case sf::Keyboard::W:
                case sf::Keyboard::Down:
                case sf::Keyboard::S:
                    y = 0;
                    break;
                case sf::Keyboard::Left:
                case sf::Keyboard::A:
                case sf::Keyboard::Right:
                case sf::Keyboard::D:
                    x = 0;
                    break;
                }
            }
        }

        // collision
        sf::Vector2f posBeforeCollision = player.getPosition();
        sf::FloatRect playerBounds = player.getGlobalBounds();
        sf::Vector2f windowOffset = calculateInsideOffset(sf::Vector2f(x, y), playerBounds, sf::FloatRect(0, 0, win_width, win_height));
        player.move(windowOffset.x, windowOffset.y);
        for (const auto& wall : walls) {
            sf::FloatRect wallBounds = dynamic_cast<sf::Sprite*>(wall.get())->getGlobalBounds();
            if (!wallBounds.intersects(player.getGlobalBounds())) continue;

            // std::cout << "COLLISION AT: " << player.getPosition().x << ", " << player.getPosition().y << "\n";
            sf::Vector2f offset = calculateOutsideOffset(sf::Vector2f(x, y), playerBounds, wallBounds);
            player.setPosition(sf::Vector2f(posBeforeCollision.x + offset.x, posBeforeCollision.y + offset.y));
            break;
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...
        window.draw(bg);
        for (const auto& wall : walls) {
            window.draw(*wall);
        }
        window.draw(player);

        // end the current frame
        window.display();
    }

    return 0;
}
