#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>

class Player : public sf::Sprite
{
private:
	// Animation
	static const std::vector<sf::IntRect> idleFrames;
	static const std::vector<sf::IntRect> walkingFrames;

	int currentFrame = 0;
	int fps = 7;

	sf::Clock animationClock;

	bool moving = false;
	
	// Physics
	// COULD BE DONE BETTER
	static const float gravity;

	bool onGround = false;
	bool jumped = false;

	float acceleration = 1;
	float movingSpeed = 25;
	float jumpStrength = 15;

	float startX, startY;
	
public:
	Player(sf::Texture& texture, float x, float y, float scale=1);

	void draw(sf::RenderTarget& target);

	void update();

	void respawn();
	void resetOnGround();
	void checkCollision(sf::FloatRect colliderBounds);
	void checkCollisionWithWindow(sf::FloatRect colliderBounds);

	void animatedMove(float x);
	void jump();

	static const sf::IntRect frameSize;

};
