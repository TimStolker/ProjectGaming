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
	int waveCount = 1;
	int enemyKilled = 0;
	int playerScore = 0;
	int health = 3;
	int bulletDamage = 2;
	sf::Vector2f size = {100.0, 100.0};
    std::string ship = "images/Medium_Ship.png";
	sf::Vector2f bulletAlignment;


	void upgrade(){
		srand(time(0)); //gebruik de huidige tijd als seed
		int randomNumber = rand() % 100+1; //random getal 0 - 100
		if(randomNumber <= 5){  //Legendary loot (5%)
			srand(time(0));
			int randomUpgrade = rand() % 1+1;
			if(randomUpgrade == 1){
				health += 2;
			}
		}
		else if(randomNumber <= 15){ //Rare loot (15%)
			srand(time(0));
			int randomUpgrade = rand() % 4+1;  
			if(randomUpgrade == 1){
				health += 1;
			}
			else if(randomUpgrade == 2){
				bulletSpeed += 10;
			}
			else if(randomUpgrade == 3){
				if(reloadTime > 50){
					reloadTime -= 50;
				}
			}
			else{
				shipSpeed += 5;
			}
		}

		else if(randomNumber <= 50){ //uncommen loot (30%)
			srand(time(0));
			int randomUpgrade = rand() % 3+1;
			if(randomUpgrade == 1){
				bulletSpeed += 5;
			}
			else if(randomUpgrade == 2){
				if(reloadTime > 25){
					reloadTime -= 25;
				}
			}
			else{
				shipSpeed += 3;
			}
		}
		else{ //common loot (50%)
			srand(time(0));
			int randomUpgrade = rand() % 3+1;  
			if(randomUpgrade == 1){
				bulletSpeed += 3;
			}
			else if(randomUpgrade == 2){
				if(reloadTime > 10){
					reloadTime -= 10;
				}
			}
			else{
				shipSpeed += 1;
			}
		}
	}
};

//Class for a sfml rectangle object
class rectangle{
private:
    sf::Vector2f position;
    sf::Color color;
	sf::Vector2f size;
	sf::RectangleShape shape;
	int thickness=1;
    
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
	void setBorder(int thickness,sf::Color bordercolor){
        shape.setOutlineThickness(thickness);
        shape.setOutlineColor(bordercolor);
    }
	bool clicked( sf::Vector2f MousePosition ){
        return shape.getGlobalBounds().contains(MousePosition);
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
	
	void rotate( float rotation ){
        shape.rotate( rotation );
    }

	void scale( const sf::Vector2f & new_size ){    
        shape.scale(new_size);
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
	sf::Text waveCount;
	sf::Text enemyKilled;
	sf::Text playerScore;
	sf::Text health;
	
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
		draw("Wave: ", stats.waveCount, waveCount, sf::Vector2f(1550.0, 10.0), window);
		draw("Enemies killed: ", stats.enemyKilled, enemyKilled, sf::Vector2f(1550.0, 40.0), window);
		draw("Score: ", stats.playerScore, playerScore, sf::Vector2f(1550.0, 70.0), window);
		draw("Player health: ", stats.health, health, sf::Vector2f(1550.0, 100.0), window);
	}

	void update(playerStats newStats){
		stats = newStats;
	}

};

bool select_object( sf::Vector2i MousePosition, auto object ){
    auto posFloat = static_cast<sf::Vector2f>(MousePosition);
    if(object.clicked( posFloat )){
        return true;
    }
    return false;
}



#endif