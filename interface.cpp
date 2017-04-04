#include <SFML/Graphics.hpp>
#include <iostream> 
#define Size Vector2f(500,80)
#define HEIGHT 400
#define LENGTH 1270

int button_pressed (Vector2i p,RectangleShape button)
{
	Vector2f p1=button.getPosition();
	if((p.x>p1.x)&&(p.y>p1.y)&&(p.x<p1.x+Size.x)&&(p.y<p1.y+Size.y)) return 1;
	else return 0;
}
	
ConvexShape* mouse_create()
{
	ConvexShape (*shape) = new ConvexShape;
	shape->setPointCount(4);
	shape->setPoint(0, sf::Vector2f(0, 0));
	shape->setPoint(1, sf::Vector2f(10, 20));
	shape->setPoint(2, sf::Vector2f(10, 10));
	shape->setPoint(3, sf::Vector2f(20, 10));
	shape->setOutlineThickness(1);
	shape->setOutlineColor(Color::Black);
	return shape;
}

