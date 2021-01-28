//this file contains Doxygen lines
///file CharacterMenu.hpp
/// \brief CharacterMenu
/// \details Contains all the necessary information about the CharacterMenu class

#include "GameControl.hpp"
#include "Objects.hpp"

/// \brief CharacterMenu Class
/// \details Handels everything that is needed for the character selection screen
//===========================================================================================
class CharacterMenu{
private:
	sf::RenderWindow & window;
	std::string return_statement="";
	bool standard_hoverd = false, small_hoverd = false, big_hoverd = false;
	picture background = picture(sf::Vector2f{ 0.0, 0.0 }, "images/Background.png", sf::Vector2f( 1920, 900 ));

	std::map<std::string, rectangle> borderList = {
        {"border_ship1",    rectangle( sf::Vector2f{ 330.0, 350.0 },   sf::Color(15,67,116,100), sf::Vector2f( 205.0, 200.0 ) )},
		{"char_ship1",      rectangle( sf::Vector2f{ 230.0, 200.0 },   sf::Color(22,29,47,200), sf::Vector2f( 405.0, 145.0 ) )},
		{"border_ship2",    rectangle( sf::Vector2f{ 860.0, 350.0 },   sf::Color(15,67,116,100), sf::Vector2f( 205.0, 200.0 ) )},
		{"char_ship2",      rectangle( sf::Vector2f{ 760.0, 200.0 },   sf::Color(22,29,47,200), sf::Vector2f( 405.0, 145.0 ) )},
		{"border_ship3",    rectangle( sf::Vector2f{ 1390.0, 350.0 },  sf::Color(15,67,116,100), sf::Vector2f( 205.0, 200.0 ) )},
		{"char_ship3",      rectangle( sf::Vector2f{ 1290.0, 200.0 },  sf::Color(22,29,47,200), sf::Vector2f( 405.0, 145.0 ) )}
    };
	std::map<std::string, picture> CharacterList = {
		{"Return_GameButton",  picture(sf::Vector2f{ 710.0, 750.0 },  "images/Return.png", sf::Vector2f( 500.0, 70.0 ))},
		{"Small_SpaceShip",    picture(sf::Vector2f{ 910.0, 400.0 },  "images/Small_Ship.png", sf::Vector2f( 100.0, 100.0 ))},
		{"Medium_SpaceShip",   picture(sf::Vector2f{ 380.0, 400.0 },  "images/Medium_Ship.png", sf::Vector2f( 100.0, 100.0 ))},
		{"Big_SpaceShip",      picture(sf::Vector2f{ 1440.0, 400.0 }, "images/Big_Ship.png", sf::Vector2f( 100.0, 100.0 ))},
		{"Kurt",      		   picture(sf::Vector2f{ 760.0, 200.0 },  "images/Kurt.png", sf::Vector2f( 405.0, 145.0 ))},
		{"Ian",      		   picture(sf::Vector2f{ 230.0, 200.0 },  "images/Ian.png", sf::Vector2f( 405.0, 145.0 ))},
		{"Xavier",      	   picture(sf::Vector2f{ 1290.0, 200.0 }, "images/Xavier.png", sf::Vector2f( 405.0, 145.0 ))}
	};
	

	action ButtonClick[1] = {
		action( sf::Mouse::Left, [&](){
			if(select_object( sf::Mouse::getPosition( window ), CharacterList["Return_GameButton"] )){
				return_statement = "RETURN";
			}

			for(auto & border: borderList){
				if(select_object( sf::Mouse::getPosition( window ), border.second )){
					if(border.first=="border_ship1"){
						return_statement = "START_standard";
						break;
					}
					else if(border.first=="border_ship2"){
						return_statement = "START_small";
						break;
					}
					else if(border.first=="border_ship3"){
						return_statement = "START_big";
						break;
					}
				}
			}
			
			for(;;){
				sf::Event event;
                window.pollEvent(event);
                if (event.type == sf::Event::MouseButtonReleased) {
                    break;
                }
            }
		})
	};	

public:
	/// \brief CharacterMenu Constructor
	/// \details Constructor of CharacterMenu, only needs a window
	//===========================================================================================
	CharacterMenu(auto & window):
		window( window )
    {}

	/// \brief Central CharacterMenu loop
	/// \details Handels processInput() and render()
	//===========================================================================================
	std::string CharacterMenuLoop(){
		for(auto & picture: borderList){
            picture.second.setBorder( 5, sf::Color(0,0,0) );
        }

		return_statement="";
		for(;;){
			sf::sleep( sf::milliseconds(25));
			processInput();
			render();
			if(return_statement!=""){
				return return_statement;
			}
		}
	}
	
	/// \brief Processes user input
    /// \details Checks if the user triggered any events, calls action and checks if the user hoverd over anything
    //===========================================================================================
	void processInput(){
		sf::Event event;
		while( window.pollEvent(event) ){
			if( event.type == sf::Event::Closed ){
				window.close();
			}
			else if(event.type == sf::Event::MouseMoved){
				if(select_object( sf::Mouse::getPosition( window ), CharacterList["Return_GameButton"] )){
					CharacterList["Return_GameButton"].change_image("images/Return_hover.png");
				}
				else{
					CharacterList["Return_GameButton"].change_image("images/Return.png");
				}

				for(auto & border: borderList){
					if(select_object( sf::Mouse::getPosition( window ), border.second )){
						if(border.first=="border_ship1"){
							if(!standard_hoverd){
								CharacterList["Medium_SpaceShip"].move({-20, -20});
								CharacterList["Medium_SpaceShip"].scale({1.5, 1.5});
								standard_hoverd = true;
							}
							break;
						}
						else if(border.first=="border_ship2"){
							if(!small_hoverd){
								CharacterList["Small_SpaceShip"].move({-20, -20});
								CharacterList["Small_SpaceShip"].scale({1.5, 1.5});
								small_hoverd = true;
							}
							break;
						}
						else if(border.first=="border_ship3"){
							if(!big_hoverd){
								CharacterList["Big_SpaceShip"].move({-20, -20});
								CharacterList["Big_SpaceShip"].scale({1.5, 1.5});
								big_hoverd = true;
							}
							break;
						}
					}
					else{
						if(standard_hoverd){
							CharacterList["Medium_SpaceShip"].move({20, 20});
							CharacterList["Medium_SpaceShip"].scale({0.66666666, 0.66666666});
							standard_hoverd = false;
						}
						if(small_hoverd){
							CharacterList["Small_SpaceShip"].move({20, 20});
							CharacterList["Small_SpaceShip"].scale({0.66666666, 0.66666666});
							small_hoverd = false;
						}
						if(big_hoverd){
							CharacterList["Big_SpaceShip"].move({20, 20});
							CharacterList["Big_SpaceShip"].scale({0.66666666, 0.66666666});
							big_hoverd = false;
						}
					}
						
				}
				break;
			}
		}
		for( auto & action : ButtonClick ){
			action();
		}	
	}

	/// \brief Renders
    /// \details Renders all object in the game
    //===========================================================================================
	void render(){
		window.clear();
		background.draw( window );

		for(auto & picture: borderList){
            picture.second.draw( window );
        }
		
		for(auto & picture: CharacterList){
            picture.second.draw( window );
		}	
		
        window.display();
    }
};