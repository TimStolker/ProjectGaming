#ifndef _OBJECTS_HPP
#define _OBJECTS_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <functional>
#include "GameControl.hpp"

//Class where the player's information is stored
class playerStats{
public:
    int reloadTime = 500;
    int shipSpeed = 10;
    int bulletSpeed = 15;
    int bulletCount=0;
};

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

	void move( sf::Vector2f delta ){
		position += delta;
	}
};

//Class for a sfml picture object
class picture {
private:
	sf::Vector2f position;
    std::string image;
    sf::Texture pic;
    sf::RectangleShape shape;
	std::string type;
	
public:
    picture( sf::Vector2f position, std::string image, sf::Vector2f shape, std::string type=""):
        position( position ),
		image( image ),
		shape( shape ),
		type (type)
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
	
	bool clicked( sf::Vector2f MousePosition ){
		return shape.getGlobalBounds().contains(MousePosition);
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

	sf::Vector2f getPosition(){
		return position;
	}

	std::string getType(){
		return type; 
	}

	void change_image( std::string new_image ){
    	image = new_image;
	}
	
    void new_image_size( const sf::Vector2f & new_size ){    
		sf::RectangleShape new_shape( new_size );        
		shape = new_shape;
    }
};

class displayText{
private:
	playerStats stats;
	sf::Font MyFont;
    sf::Text reloadTime;
	sf::Text shipSpeed;
	sf::Text bulletSpeed;
	sf::Text bulletCount;
	
	
public:
	displayText(playerStats stats):
	stats(stats)
	{}

	void draw( std::string text, auto stat, sf::Text statName, sf::Vector2f place, sf::RenderWindow & window){  
		MyFont.loadFromFile("images/OstrichSans-Medium.otf");
		statName.setFont(MyFont);
		statName.setString(text + std::to_string(stat) );
		statName.setCharacterSize(30);
		statName.setFillColor(sf::Color::White);
		statName.setStyle(sf::Text::Bold);
		statName.move(place);
		window.draw(statName);

    }

	void drawAll(sf::RenderWindow & window){
		draw("Reload time: ", stats.reloadTime, reloadTime, sf::Vector2f(10.0, 10.0), window);
		draw("Ship speed: ", stats.shipSpeed, shipSpeed, sf::Vector2f(10.0, 40.0), window);
		draw("Bullet speed: ", stats.bulletSpeed, bulletSpeed, sf::Vector2f(10.0, 70.0), window);
		draw("Bullet count: ", stats.bulletCount, bulletCount, sf::Vector2f(10.0, 100.0), window);
	}

	void update(playerStats newStats){
		stats = newStats;
	}

};

#endif
