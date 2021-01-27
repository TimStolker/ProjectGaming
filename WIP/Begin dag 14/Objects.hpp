#ifndef _OBJECTS_HPP
#define _OBJECTS_HPP

//Class where the player's information is stored
class playerStats{
public:
    int reloadTime = 500, shipSpeed = 10, bulletCount=0;
	int waveCount = 1, enemyKilled = 0, playerScore = 0;
	sf::Vector2f bulletAlignment, size = {100.0, 100.0};
	int health = 3, bulletDamage = 2, credits = 0;
	bool tripleFire = false, spawnShields = false;
    std::string ship = "images/Medium_Ship.png";
	std::string lazerColor = "";

	int getPlayerHealth(){
		return health;
	}

	void ResetStats(){
		playerScore=0;
		enemyKilled=0;
		waveCount=1;
		bulletCount=0;
	}
};

//Action class which provides usefull functions
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
	sf::Text waveCount, enemyKilled, playerScore;
    sf::Text reloadTime, shipSpeed, bulletCount;
	sf::Text health, credits, bulletDamage;
	playerStats stats;
	sf::Font MyFont;
	
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
		draw("Bullet damage: ", stats.bulletDamage, bulletDamage, sf::Vector2f(10.0, 70.0), window);
		draw("Bullet count: ", stats.bulletCount, bulletCount, sf::Vector2f(10.0, 100.0), window);
		draw("Wave: ", stats.waveCount, waveCount, sf::Vector2f(1550.0, 10.0), window);
		draw("Enemies killed: ", stats.enemyKilled, enemyKilled, sf::Vector2f(1550.0, 40.0), window);
		draw("Score: ", stats.playerScore, playerScore, sf::Vector2f(1550.0, 70.0), window);
		draw("Player health: ", stats.health, health, sf::Vector2f(1550.0, 100.0), window);
		draw("Credits: ", stats.credits, credits, sf::Vector2f(1550.0, 130.0), window);
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