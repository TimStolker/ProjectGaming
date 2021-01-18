#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameControl.hpp"
#include "Objects.hpp"

class CharacterMenu{
private:
	sf::RenderWindow & window;
	std::string return_statement="";
	bool standard_hoverd = false, small_hoverd = false, big_hoverd = false;
	
	std::map<std::string, picture> CharacterList = {
		{"Return_GameButton",  picture(sf::Vector2f{ 710.0, 750.0 },  "images/Return.png", sf::Vector2f( 500.0, 70.0 ))},
		{"Standard_SpaceShip", picture(sf::Vector2f{ 910.0, 400.0 },  "images/Standard_Ship.png", sf::Vector2f( 100.0, 100.0 ))},
		{"Small_SpaceShip",    picture(sf::Vector2f{ 380.0, 400.0 },  "images/Small_Ship.png", sf::Vector2f( 100.0, 100.0 ))},
		{"Big_SpaceShip",      picture(sf::Vector2f{ 1440.0, 400.0 }, "images/Big_Ship.png", sf::Vector2f( 100.0, 100.0 ))},
		{"Background",         picture(sf::Vector2f{ 0.0, 0.0 },      "images/Background.png", sf::Vector2f( 1920, 900 ))}
	};

	action ButtonClick[1] = {
		action( sf::Mouse::Left,  [&](){
			for(auto & picture: CharacterList){
				if(select_object( sf::Mouse::getPosition( window ), picture.second )){
					if(picture.first=="Standard_SpaceShip"){
						return_statement = "START";
					}
					else if(picture.first=="Small_SpaceShip"){
						return_statement = "START";
					}
					else if(picture.first=="Big_SpaceShip"){
						return_statement = "START";
					}
					else if(picture.first=="Return_GameButton"){
						return_statement = "RETURN";
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
	CharacterMenu(auto& window):
		window( window )
    {}

	std::string CharacterMenuLoop(){
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
	
	void processInput(){
		sf::Event event;
		while( window.pollEvent(event) ){
			if( event.type == sf::Event::Closed ){
				window.close();
			}
			else if(event.type == sf::Event::MouseMoved){
				for(auto & picture: CharacterList){
					if(select_object( sf::Mouse::getPosition( window ), picture.second )){
						if(picture.first != "Background"){
							if(picture.first=="Return_GameButton"){
								picture.second.change_image("images/Return_hover.png");
								break;
							}
							else if(picture.first=="Standard_SpaceShip"){
								if(!standard_hoverd){
									picture.second.move({-20, 0});
									picture.second.scale({1.5, 1.5});
									standard_hoverd = true;
								}
								break;
							}
							else if(picture.first=="Big_SpaceShip"){
								if(!big_hoverd){
									picture.second.move({-20, 0});
									picture.second.scale({1.5, 1.5});
									big_hoverd = true;
								}
								break;
							}
							else if(picture.first=="Small_SpaceShip"){
								if(!small_hoverd){
									picture.second.move({-20, 0});
									picture.second.scale({1.5, 1.5});
									small_hoverd = true;
								}
								break;
							}
						}
						else{
							CharacterList["Return_GameButton"].change_image("images/Return.png");
							if(small_hoverd){
								CharacterList["Small_SpaceShip"].move({20, 0});
								CharacterList["Small_SpaceShip"].scale({0.66666666, 0.66666666});
								small_hoverd = false;
							}
							if(standard_hoverd){
								CharacterList["Standard_SpaceShip"].move({20, 0});
								CharacterList["Standard_SpaceShip"].scale({0.66666666, 0.66666666});
								standard_hoverd = false;
							}
							if(big_hoverd){
								CharacterList["Big_SpaceShip"].move({20, 0});
								CharacterList["Big_SpaceShip"].scale({0.66666666, 0.66666666});
								big_hoverd = false;
							}
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

	void render(){
		window.clear();
		for(auto & picture: CharacterList){
            picture.second.draw( window );
        }
        window.display();
    }
	bool select_object( sf::Vector2i MousePosition, picture object ){
		auto posFloat = static_cast<sf::Vector2f>(MousePosition);
		if(object.clicked( posFloat )){
			return true;
		}
		return false;
	}
};