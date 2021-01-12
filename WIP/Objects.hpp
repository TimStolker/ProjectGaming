#ifndef _OBJECTS_HPP
#define _OBJECTS_HPP

#include <SFML/Graphics.hpp>

//================================================================

class objects {
protected:
	sf::Vector2f position;
	sf::Color color;
public:
	objects(sf::Vector2f position,sf::Color color):
		position(position), color(color)
	{}

	virtual void draw(sf::RenderWindow & window) = 0;

	virtual void move( sf::Vector2f delta ) = 0;
};

//================================================================

class ball : public objects {
protected:
	float size;
	sf::CircleShape circle;
public:
	ball( sf::Vector2f position, sf::Color color, float size = 30.0):
    	objects(position,color),size(size)
	{}

	void draw( sf::RenderWindow & window ){
		
		circle.setRadius(size);
		circle.setPosition(position);
		circle.setFillColor(color);
		window.draw(circle);
	}
	void move( sf::Vector2f delta ){
    	position += delta;
	}
	auto getCircle(){
		return circle;
	}
};

//================================================================

class wall : public objects {
protected:
	sf::Vector2f size;
	sf::RectangleShape rectangle;
public:
    wall( sf::Vector2f position, sf::Color color, sf::Vector2f size):
		objects(position,color),size(size)
	{}

	void draw( sf::RenderWindow & window ){
		rectangle.setSize(size);
		rectangle.setPosition(position);
		rectangle.setFillColor(color);
		window.draw(rectangle);
	}

    void move( sf::Vector2f delta ){
    	position += delta;
	}

	auto getRectangle(){
		return rectangle;
	}
};

//================================================================
#endif

