#pragma once

#include <SFML/Graphics.hpp>

#include <random>

class CustomRectangleShape : public sf::RectangleShape
{
private:
	int speed_x_ = 10;
	int speed_y_ = 10;
	int speed_rotate_ = 10;

	bool is_selected = false;

	sf::IntRect move_bounds_;

	void bounce();

public:
	CustomRectangleShape(sf::Vector2f size = { 10., 10. }, sf::Vector2f pos = { 0., 0. });

	void setSpeed(int speed_x, int speed_y, int speed_rotate);

	void setBounds(int left, int right, int top, int bottom);
	void setBounds(sf::IntRect bounds);

	void animate(const sf::Time & elapsed);

	bool collides(const sf::Vector2f & pos);

	void select();
	void unselect();
	bool selected() { return is_selected; };

	void moveLockedToBounds(float x, float y);

	static sf::Color inactive_color;
};
