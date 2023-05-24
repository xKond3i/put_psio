#include "Player.h"

Player::Player(sf::Texture& texture, float x, float y, float scale)
{
	setTexture(texture);
	setTextureRect(idleFrames[0]);
	setScale(scale, scale);
	setOrigin(Player::frameSize.width / 2, Player::frameSize.height);
	setPosition(x, y);

	startX = x;
	startY = y;
}

void Player::draw(sf::RenderTarget& target)
{
	target.draw(*this);
}

void Player::update()
{
	double time = animationClock.getElapsedTime().asMilliseconds();

	if (!onGround) {
		move(0, Player::gravity * time / 1000 * acceleration);
		acceleration += acceleration < 10 ? std::abs(acceleration) / 100 + 0.5 : 0;
	}

	if (moving) move((jumped ? 2 * movingSpeed : movingSpeed) * time / 1000, 0);

	if (time <= 1000 / fps) return;

	animationClock.restart();
	currentFrame += 1;
	if (!moving) {
		currentFrame = currentFrame % idleFrames.size();
		setTextureRect(idleFrames[currentFrame]);
	}
	else {
		currentFrame = currentFrame % walkingFrames.size();
		setTextureRect(walkingFrames[currentFrame]);
	}
}

void Player::respawn()
{
	setPosition(startX, startY);
}

void Player::resetOnGround()
{
	onGround = false;
}

void Player::checkCollision(sf::FloatRect colliderBounds)
{
	float colliderBottomEdge = colliderBounds.top + colliderBounds.height;
	float colliderRightEdge  = colliderBounds.left + colliderBounds.width;
	sf::FloatRect playerBounds = getGlobalBounds();
	float playerBottomEdge = playerBounds.top + playerBounds.height;
	float playerRightEdge  = playerBounds.left + playerBounds.width;
	float playerCenterX	   = playerBounds.left + playerBounds.width / 2;
	// BOTTOM-TOP collision with some kind of ground
	if (playerBottomEdge >= colliderBounds.top && playerBottomEdge <= colliderBottomEdge
	 && playerCenterX >= colliderBounds.left && playerCenterX <= colliderRightEdge) {
		setPosition(getPosition().x, getPosition().y - std::abs(playerBottomEdge - colliderBounds.top));
		onGround = true;
		jumped = false;
		acceleration = 1;
	}
}

void Player::checkCollisionWithWindow(sf::FloatRect colliderBounds)
{
	float colliderBottomEdge = colliderBounds.top + colliderBounds.height;
	float colliderRightEdge = colliderBounds.left + colliderBounds.width;
	sf::FloatRect playerBounds = getGlobalBounds();
	float playerBottomEdge = playerBounds.top + playerBounds.height;
	float playerRightEdge = playerBounds.left + playerBounds.width;
	
	if (playerBounds.left <= colliderBounds.left)
		setPosition(getPosition().x + std::abs(playerBounds.left - colliderBounds.left), getPosition().y);
	else if (playerRightEdge >= colliderRightEdge)
		setPosition(getPosition().x - std::abs(playerRightEdge - colliderRightEdge), getPosition().y);
}

void Player::animatedMove(float x)
{
	if (x == 0) {
		moving = false;
		return;
	}
	moving = true;
	float scale = std::abs(getScale().x);
	float speed = std::abs(movingSpeed);
	if (x < 0) {
		setScale(-scale, scale);
		movingSpeed = -speed;
	}
	else {
		setScale(scale, scale);
		movingSpeed = speed;
	}
}

void Player::jump()
{
	if (jumped || !onGround) return;
	jumped = true;
	onGround = false;
	acceleration = -jumpStrength;
}

const std::vector<sf::IntRect> Player::idleFrames = {sf::IntRect(13, 0, 24, 36), sf::IntRect(63, 0, 24, 36), sf::IntRect(113, 0, 24, 36)};
const std::vector<sf::IntRect> Player::walkingFrames = {sf::IntRect(163, 0, 24, 36), sf::IntRect(213, 0, 24, 36), sf::IntRect(263, 0, 24, 36), sf::IntRect(313, 0, 24, 36), sf::IntRect(363, 0, 24, 36), sf::IntRect(413, 0, 24, 36)};

const sf::IntRect Player::frameSize = sf::IntRect(0, 0, 36, 50);
