#ifndef _OBJECTS_HPP
#define _OBJECTS_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <functional>

//Class for a sfml rectangle object
class rectangle{
private:
    sf::Vector2f position;
    sf::Color color;
	sf::Vector2f size;
	sf::RectangleShape shape;
    
public:
	rectangle( sf::Vector2f position, sf::Color color, sf::Vector2f size):
    	position( position ),
        color( color ),
		size( size )
   	{}

	rectangle(){}

	void draw( sf::RenderWindow & window ) {
		shape.setFillColor( color );
		shape.setSize( size );
		shape.setPosition( position );
		window.draw(shape);
	}

	sf::RectangleShape getShape(){
		return shape;
	}
};

//Class for a sfml picture object
class picture {
private:
	sf::Vector2f position;
    sf::Vector2f size;
    std::string image;
    sf::Texture pic;
    sf::RectangleShape shape;
	
public:
    picture( sf::Vector2f position, std::string image, sf::Vector2f shape):
        position( position ),
		image( image ),
		shape( shape )
    {}

	picture(){}

    void draw( sf::RenderWindow & window ){   
        shape.setPosition(position);
        pic.loadFromFile(image);
        shape.setTexture(&pic);
        window.draw(shape);
    }

	bool collision( auto & object ){
		return getShape().getGlobalBounds().intersects( object.getShape().getGlobalBounds());
	}

    void jump( sf::Vector2f delta ){
		position = delta;
	}

    void move( sf::Vector2f delta ){
		position += delta;
	}

	sf::RectangleShape getShape(){
		return shape;
	}
};

#endif
