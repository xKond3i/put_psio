// Libraries
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <vector>
#include <string>
#include <random>

#include <time.h>

#include <iostream>

// --- Variables --- //
// Window
int win_width = 1280;
int win_height = 720;

sf::View view;

// Background
sf::Sprite sky;
sf::Texture skyTexture;
sf::Sprite sea;
sf::Texture seaTexture;
sf::Sprite clouds;
sf::Texture cloudsTexture;
sf::Sprite farGrounds;
sf::Texture farGroundsTexture;

float backgroundAnimationSpeed = 1.0;

// Tiles
sf::Texture tilesTexture; // tileset 16x16
std::vector<sf::IntRect> tiles;
std::vector<sf::IntRect> hitboxes;
enum tileIDs;

float scale = 2.0;
float unit = 16.0;

// Obstacles
std::vector<sf::RectangleShape> obstacles;
std::vector<sf::Sprite> decorations;

// Player
sf::Texture playerTexture;

// Components
#include "Background.h"
#include "Tiles.h"
#include "Player.h"

const float Player::gravity = 9.8;

bool showHitboxes = false;

int main() {
    srand(time(NULL));

    // Create the window
    sf::RenderWindow window(sf::VideoMode(win_width, win_height), "Platformer");
    window.setFramerateLimit(60);

    // View
    view.setSize(sf::Vector2f(win_width*3/4, win_height*3/4));

    // Background
    setupBackground();

    // Tiles
    setupTiles();

    // Player
    if (!playerTexture.loadFromFile("resources/character/character.png")) { return -1; }
    Player player(playerTexture, Player::frameSize.width * scale, win_height / 2, scale);

    while (window.isOpen()) {
        // Check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event)) {
            // "Close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape)
                    window.close();

                switch (event.key.code) {
                    case sf::Keyboard::Left:
                    case sf::Keyboard::A:
                        player.animatedMove(-3);
                        break;
                    case sf::Keyboard::Right:
                    case sf::Keyboard::D:
                        player.animatedMove(3);
                        break;
                    case sf::Keyboard::Space:
                        player.jump();
                        break;
                }
            }

            if (event.type == sf::Event::KeyReleased) {
                switch (event.key.code) {
                    case sf::Keyboard::Left:
                    case sf::Keyboard::A:
                    case sf::Keyboard::Right:
                    case sf::Keyboard::D:
                        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
                            && !sf::Keyboard::isKeyPressed(sf::Keyboard::A)
                            && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
                            && !sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                            player.animatedMove(0);
                        }
                        break;
                    case sf::Keyboard::H:
                        showHitboxes = !showHitboxes;
                        break;
                }
            }
        }

        // Update Loop
        animateBackground();
        
        player.update();
        updateView(window, player);

        // Collision with window frames
        player.checkCollisionWithWindow(sf::FloatRect(0, 0, win_width, win_height));

        // Collides with obstacles
        player.resetOnGround();
        for (const auto& obstacle : obstacles) {
            player.checkCollision(obstacle.getGlobalBounds());
        }

        // Player out of the map
        if (player.getGlobalBounds().top > win_height) {
            player.respawn();
        }

        // clear the window with black color
        window.clear(sf::Color(161, 242, 236));
        
        // Draw Loop
        renderBackground(window);
        for (const auto& decoration : decorations) {
            window.draw(decoration);
        }

        // Draw colliders
        if (showHitboxes) {
            for (const auto& obstacle : obstacles) {
                window.draw(obstacle);
            }
        }

        window.draw(player);

        // end the current frame
        window.display();
    }

    return 0;
}
