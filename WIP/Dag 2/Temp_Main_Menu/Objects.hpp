#ifndef _OBJECTS_HPP
#define _OBJECTS_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <functional>

class rectangle{
private:
    sf::Vector2f position;
    sf::Color color;
	sf::Vector2f size;
	sf::RectangleShape rec;
    

public:
	rectangle( sf::Vector2f position, sf::Color color, sf::Vector2f size):
    	position( position ),
        color( color ),
		size( size )
   	{}

	void draw( sf::RenderWindow & window ) {
		rec.setFillColor( color );
		rec.setSize( size );
		rec.setPosition( position );
		window.draw(rec);
	}
};

class picture {
protected:

	sf::Vector2f position;
    sf::Vector2f size;
    std::string image;
    sf::Texture pic;
    sf::RectangleShape shape;
	
public:
    picture( sf::Vector2f position, std::string image, sf::Vector2f shape):
        position(position),
		image(image),
		shape(shape)
    {}

	picture(){}

    void draw( sf::RenderWindow & window ){   
        shape.setPosition(position);
        pic.loadFromFile(image);
        shape.setTexture(&pic);
        window.draw(shape);
    }

	bool clicked( sf::Vector2f MousePosition ){
		return shape.getGlobalBounds().contains(MousePosition);
	}

    void jump( sf::Vector2f delta ){
		position = delta;
	}

    void move( sf::Vector2f delta ){
		position += delta;
	}
};

#endif