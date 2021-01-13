#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameControl.hpp"
#include "Objects.hpp"

class MainMenu{
private:
	std::string return_statement="";
	sf::RenderWindow & window;
	std::map<std::string, picture> MenuList = {
        {"Background",picture(sf::Vector2f{ 0.0, 0.0 }, "images/Background.png", sf::Vector2f( 1920, 900 ))},
		{"Logo",picture(sf::Vector2f( 600.0, 5.0 ), "images/Logo.png", sf::Vector2f( 600.0, 300.0 ))},
		{"Start_GameButton",picture(sf::Vector2f{ 710.0, 400.0 }, "images/Play.png", sf::Vector2f( 500.0, 70.0 ))},
		{"Leaderbord_GameButton",picture(sf::Vector2f{ 710.0, 500.0 }, "images/Leaderboard.png", sf::Vector2f( 500.0, 70.0 ))},
		{"Quit_GameButton",picture(sf::Vector2f{ 710.0, 600.0 }, "images/Quit.png", sf::Vector2f( 500.0, 70.0 ))}
    };
	
	action ButtonClick[1] = {
		action( sf::Mouse::Left,  [&](){
			for(auto & picture: MenuList){
				if(select_object( sf::Mouse::getPosition( window ), picture.second )){
					if(picture.first=="Start_GameButton"){
						return_statement = "GAME";
					}
				}
			}
			for(;;){
				sf::Event event;
				sf::sleep( sf::milliseconds(5));
                window.pollEvent(event);
                if (event.type == sf::Event::MouseButtonReleased) {
					sf::sleep( sf::milliseconds(150));
                    break;
                }
            }
		})
	};
	
public:
	 MainMenu(auto& window):
        window( window )
    {}

	std::string MainMenuLoop(){
		for(;;){
			sf::sleep( sf::milliseconds(20));
			
			render();
			processInput();
			if(return_statement!=""){
				return "GAME";
			}
		}
	}
	
    void processInput(){
        sf::Event event;
        while( window.pollEvent(event) ){
            if( event.type == sf::Event::Closed ){
                window.close();
            }
        }
		for( auto & action : ButtonClick ){
			action();
		}
	}

    void render(){
        window.clear(sf::Color::White);
		for(auto & picture: MenuList){
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
