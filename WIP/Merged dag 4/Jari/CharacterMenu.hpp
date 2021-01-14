#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameControl.hpp"
#include "Objects.hpp"

class CharacterMenu{
private:
	sf::RenderWindow & window;
	std::string return_statement="";
	
	std::map<std::string, picture> BackgroundObject = {
		{"Background",picture(sf::Vector2f{ 0.0, 0.0 }, "images/Background.png", sf::Vector2f( 1920, 900 ))},
	};
	
	std::map<std::string, picture> CharacterList = {
		{"Return_GameButton",picture(sf::Vector2f{ 710.0, 750.0 }, "images/Return.png", sf::Vector2f( 500.0, 70.0 ))},
		{"Standard_SpaceShip",picture(sf::Vector2f{ 910.0, 400.0 }, "images/Standard_Ship.png", sf::Vector2f( 100.0, 100.0 ))},
		{"Small_SpaceShip",picture(sf::Vector2f{ 380.0, 400.0 }, "images/Small_Ship.png", sf::Vector2f( 100.0, 100.0 ))},
		{"Big_SpaceShip",picture(sf::Vector2f{ 1440.0, 400.0 }, "images/Big_Ship.png", sf::Vector2f( 100.0, 100.0 ))}
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
			if(event.type == sf::Event::MouseMoved){
				for(auto & picture: CharacterList){
					std::cout << picture.first << std::endl;
					if(select_object( sf::Mouse::getPosition( window ), picture.second )){
						if(picture.first=="Return_GameButton"){
							std::cout << " kat " << std::endl;
							picture.second.change_image("images/Return_hover.png");
							break;
						}
						else if(picture.first=="Standard_SpaceShip"){
							std::cout << " hond_standard " << std::endl;
							picture.second.new_image_size( sf::Vector2f( 150, 150 ));
							break;
						}
						else if(picture.first=="Big_SpaceShip"){
							std::cout << " hond_Big " << std::endl;
							picture.second.new_image_size( sf::Vector2f( 150, 150));
							break;
						}
						else if(picture.first=="Small_SpaceShip"){
							std::cout << " hond_Small " << std::endl;
							picture.second.new_image_size( sf::Vector2f( 150, 150));
							break;
						}
					}
					else{
						std::cout << " RETURN VALUES " << std::endl;
						CharacterList["Return_GameButton"].change_image("images/Return.png");
						CharacterList["Standard_SpaceShip"].new_image_size( sf::Vector2f( 100.0, 100.0 ));
						CharacterList["Small_SpaceShip"].new_image_size( sf::Vector2f( 100.0, 100.0 ));
						CharacterList["Big_SpaceShip"].new_image_size( sf::Vector2f( 100.0, 100.0 ));
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
		for(auto & picture: BackgroundObject){
			picture.second.draw( window );
		}
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