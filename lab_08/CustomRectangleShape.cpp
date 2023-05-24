#include "CustomRectangleShape.h"

CustomRectangleShape::CustomRectangleShape(sf::Vector2f size, sf::Vector2f pos) : sf::RectangleShape(size) {
	setPosition(pos);
}

void CustomRectangleShape::setSpeed(int speed_x, int speed_y, int speed_rotate)
{
	speed_x_ = speed_x;
	speed_y_ = speed_y;
	speed_rotate_ = speed_rotate;
}

void CustomRectangleShape::setBounds(int left, int right, int top, int bottom) {
    move_bounds_ = sf::IntRect(left, top, right - left, bottom - top);
}

void CustomRectangleShape::setBounds(sf::IntRect bounds) {
    move_bounds_ = bounds;
}

void CustomRectangleShape::bounce() {
    int lbe = move_bounds_.left;                      // left boundry edge
    int rbe = move_bounds_.left + move_bounds_.width; // right boundry edge
    int tbe = move_bounds_.top;                       // top boundry edge
    int bbe = move_bounds_.top + move_bounds_.height; // bottom boundry edge
    sf::FloatRect bounds = getGlobalBounds();
    if (bounds.left <= lbe) {
        speed_x_ = abs(speed_x_);
    }
    else if (bounds.left + bounds.width >= rbe) {
        speed_x_ = -abs(speed_x_);
    }
    if (bounds.top <= tbe) {
        speed_y_ = abs(speed_y_);
    }
    else if (bounds.top + bounds.height >= bbe) {
        speed_y_ = -abs(speed_y_);
    }
}

void CustomRectangleShape::animate(const sf::Time& elapsed) {
    if (is_selected) return;
    float secondsElapsed = elapsed.asSeconds();
    move(speed_x_ * secondsElapsed, speed_y_ * secondsElapsed);
    rotate(speed_rotate_ * secondsElapsed);
    bounce();
}

bool CustomRectangleShape::collides(const sf::Vector2f& pos)
{
    sf::FloatRect bounds = getGlobalBounds();
    if (pos.x > bounds.left && pos.x < bounds.left + bounds.width
        && pos.y > bounds.top && pos.y < bounds.top + bounds.height) return true;
    return false;
}

void CustomRectangleShape::select()
{
    is_selected = true;
    setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
}

void CustomRectangleShape::unselect()
{
    is_selected = false;
    setFillColor(inactive_color);
}

void CustomRectangleShape::moveLockedToBounds(float x, float y)
{
    int lbe = move_bounds_.left;                      // left boundry edge
    int rbe = move_bounds_.left + move_bounds_.width; // right boundry edge
    int tbe = move_bounds_.top;                       // top boundry edge
    int bbe = move_bounds_.top + move_bounds_.height; // bottom boundry edge

    sf::FloatRect bounds = getGlobalBounds();

    float sl2lbe = bounds.left - lbe;                // space left to left boundry edge
    float sl2rbe = rbe - bounds.left - bounds.width; // space left to right boundry edge
    float sl2tbe = bounds.top - tbe;                 // space left to top boundry edge
    float sl2bbe = bbe - bounds.top - bounds.height; // space left to bottom boundry edge

    float step_x;
    if (x < 0) step_x = -std::min(std::abs(x), std::abs(sl2lbe));
    else       step_x =  std::min(std::abs(x), std::abs(sl2rbe));

    float step_y;
    if (y < 0) step_y = -std::min(std::abs(y), std::abs(sl2tbe));
    else       step_y =  std::min(std::abs(y), std::abs(sl2bbe));

    move(step_x, step_y);
}
