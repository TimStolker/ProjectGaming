//this file contains Doxygen lines
///file Objects.hpp
/// \brief Class playerStats
/// \details Contains all the necessary information about the playerStats Class
#ifndef _OBJECTS_HPP
#define _OBJECTS_HPP
class playerStats{
public:
    int reloadTime = 500, shipSpeed = 10, bulletCount=0;
	int waveCount = 1, enemyKilled = 0, playerScore = 0;
	sf::Vector2f bulletAlignment, size = {100.0, 100.0};
	int health = 3, bulletDamage = 2, credits = 0;
	bool tripleFire = false, spawnShields = false;
    std::string ship = "images/Medium_Ship.png";
	std::string lazerColor = "";
	
	/// \brief Resets all the stats to start again.
	/// \details It reseting all integer stats to its base values and is used by GameControl.hpp and Statemachine.hpp
	//===========================================================================================
	void ResetStats(){
		playerScore=0;
		enemyKilled=0;
		waveCount=1;
		bulletCount=0;
	}
};

/// \brief Class action
/// \details Contains all the necessary information about the action Class
class action {
private:
	std::function< bool() > condition;
	std::function< void() > work;

public:
	action(
	   std::function< bool() > condition, 
	   std::function< void() > work
	) : condition( condition ), 
		work( work ) 
	{}
	/// \brief If the key is pressed it returns the key.
	/// \details It returns the key as a char.
	//===========================================================================================
	action(
		sf::Keyboard::Key key,
		std::function< void() > work
	) :
		condition(
			[ key ]()->bool { return sf::Keyboard::isKeyPressed( key ); }
		),
		work(work)
	{}
	action(
		std::function< void() > work
	) :
		condition(
			[]()->bool { return true; }
		),
		work(work)
	{}
	/// \brief It constructs the mouse button.
	/// \details If thee mouse button is pressed return true
	//===========================================================================================
	action(
        sf::Mouse::Button button,
        std::function< void() > work
    ) :
        condition(
            [ button ]()->bool { return sf::Mouse::isButtonPressed( button ); }
        ),
        work(work)
    {}
	void operator()(){
		if( condition() ){
			work();
		}
	}
};

/// \brief Class rectangle
/// \details Contains all the necessary information about the rectangle class
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
	/// \brief Draws the rectangle object on to the window.
	/// \details Needs the window where it is going to draw to.
	//===========================================================================================
	void draw( sf::RenderWindow & window ) {
		shape.setFillColor( color );
		shape.setSize( size );
		shape.setPosition( position );
		window.draw(shape);
	}
	/// \brief Gets the shape of the rectangle object.
	/// \details Returns the shape in type sf::RectangleShape.
	//===========================================================================================
	sf::RectangleShape getShape(){
		return shape;
	}
	/// \brief Moves the rectangle object to a diffrent place from where it is.
	/// \details Needs the offset in an sf::Vector2f where the first number is x and the second y.
	//===========================================================================================
	void move( sf::Vector2f delta ){
		position += delta;
	}
	/// \brief Sets the border color and thickness of the rectangle object
	/// \details Needs the thickness of the border in int and the color in sf::Color.
	//===========================================================================================
	void setBorder(int thickness,sf::Color bordercolor){
        shape.setOutlineThickness(thickness);
        shape.setOutlineColor(bordercolor);
    }
	/// \brief Checks if the mouse position is inside of the rectangle object.
	/// \details Needs the position from mouse in sf::Vector2f and returns a bool true or false.
	//===========================================================================================
	bool clicked( sf::Vector2f MousePosition ){
        return shape.getGlobalBounds().contains(MousePosition);
    }
};
/// \brief Class picture
/// \details Contains all the necessary information about the picture class
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
	/// \brief Draws the picture object on to the window.
	/// \details Needs the window where it is going to draw to.
	//===========================================================================================
    void draw( sf::RenderWindow & window ){   
        shape.setPosition(position);
        pic.loadFromFile(image);
        shape.setTexture(&pic);
        window.draw(shape);
    }
	/// \brief Checks if a object is intersecting with the picture object.
	/// \details Needs the object and returns a bool true or false if its intersecting.
	//===========================================================================================
	bool collision( rectangle & object ){
		return getShape().getGlobalBounds().intersects( object.getShape().getGlobalBounds());
	}
	bool collision( picture & object ){
		return getShape().getGlobalBounds().intersects( object.getShape().getGlobalBounds());
	}
	/// \brief Checks if the mouse position is inside of the picture object.
	/// \details Needs the position from mouse in sf::Vector2f and returns a bool true or false.
	//===========================================================================================
	bool clicked( sf::Vector2f MousePosition ){
		return shape.getGlobalBounds().contains(MousePosition);
	}
	/// \brief Jumps the picture object to a place in xy.
	/// \details Needs the position to jump to in an sf::Vector2f where the first number is x and the second y.
	//===========================================================================================
    void jump( sf::Vector2f delta ){
		position = delta;
	}
	/// \brief Moves the picture object to a diffrent place from where it is.
	/// \details Needs the offset in an sf::Vector2f where the first number is x and the second y.
	//===========================================================================================
    void move( sf::Vector2f delta ){
		position += delta;
	}
	/// \brief Gets the shape of the picture object.
	/// \details Returns the shape in type sf::RectangleShape.
	//===========================================================================================
	sf::RectangleShape getShape(){
		return shape;
	}
	/// \brief Gets the position of the picture object.
	/// \details Returns the position in type sf::Vector2f.
	//===========================================================================================
	sf::Vector2f getPosition(){
		return position;
	}
	
	/// \brief Rotates the picture object to a diffrent rotation.
	/// \details Needs the float of the rotation offset.
	//===========================================================================================
	std::string getType(){
		return type; 
	}
	
	/// \brief Changes the picture object to a diffrent image.
	/// \details Needs the new image in type std::string.
	//===========================================================================================
	void change_image( std::string new_image ){
    	image = new_image;
	}
	
	/// \brief Roates the picture object to a diffrent rotation.
	/// \details Needs the float of the rotation offset.
	//===========================================================================================
	void rotate( float rotation ){
        shape.rotate( rotation );
    }
	/// \brief Scales the picture object to its new size.
	/// \details Needs in a vector2f its new size.
	//===========================================================================================
	void scale( const sf::Vector2f & new_size ){    
        shape.scale(new_size);
    }
};
/// \brief Class displayText
/// \details Contains all the necessary information about the displayText class
class displayText{
private:
	sf::Text waveCount, enemyKilled, playerScore;
    sf::Text reloadTime, shipSpeed, bulletCount;
	sf::Text health, credits, bulletDamage;
	playerStats stats;
	sf::Font MyFont;
	
public:
	displayText(playerStats stats):
	stats(stats)
	{}
	/// \brief Draws a stat to an specific location on the screen.
	/// \details Needs the text its going to write, the stat itself, the name of the stat, the plac its going to be rendered and the window.
	//===========================================================================================
	void draw( std::string text, float stat, sf::Text statName, sf::Vector2f place, sf::RenderWindow & window){  
		MyFont.loadFromFile("images/OstrichSans-Medium.otf");
		statName.setFont(MyFont);
		statName.setString(text + std::to_string(stat) );
		statName.setCharacterSize(30);
		statName.setFillColor(sf::Color::White);
		statName.setStyle(sf::Text::Bold);
		statName.move(place);
		window.draw(statName);
    }
	/// \brief Draws all of the stats on to the screen using the stats
	/// \details Used by GameControl.hpp
	//===========================================================================================
	void drawAll(sf::RenderWindow & window){
		draw("Reload time: ", stats.reloadTime, reloadTime, sf::Vector2f(10.0, 10.0), window);
		draw("Ship speed: ", stats.shipSpeed, shipSpeed, sf::Vector2f(10.0, 40.0), window);
		draw("Bullet damage: ", stats.bulletDamage, bulletDamage, sf::Vector2f(10.0, 70.0), window);
		draw("Bullet count: ", stats.bulletCount, bulletCount, sf::Vector2f(10.0, 100.0), window);
		draw("Wave: ", stats.waveCount, waveCount, sf::Vector2f(1550.0, 10.0), window);
		draw("Enemies killed: ", stats.enemyKilled, enemyKilled, sf::Vector2f(1550.0, 40.0), window);
		draw("Score: ", stats.playerScore, playerScore, sf::Vector2f(1550.0, 70.0), window);
		draw("Player health: ", stats.health, health, sf::Vector2f(1550.0, 100.0), window);
		draw("Credits: ", stats.credits, credits, sf::Vector2f(1550.0, 130.0), window);
	}
	/// \brief Updates the stat with a new stat you put in.
	/// \details Needs the newStat and changes the stat.
	//===========================================================================================
	void update(playerStats newStats){
		stats = newStats;
	}

};
	/// \brief Checks if the mouse clicks something.
	/// \details Needs MousePosition and the object its going to click then return true or false.
	//===========================================================================================
bool select_object( sf::Vector2i MousePosition, rectangle object ){
    auto posFloat = static_cast<sf::Vector2f>(MousePosition);
    if(object.clicked( posFloat )){
        return true;
    }
    return false;
}
bool select_object( sf::Vector2i MousePosition, picture object ){
    auto posFloat = static_cast<sf::Vector2f>(MousePosition);
    if(object.clicked( posFloat )){
        return true;
    }
    return false;
}



#endif