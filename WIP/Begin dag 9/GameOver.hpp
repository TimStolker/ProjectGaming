#ifndef _GAMEOVER_HPP
#define _GAMEOVER_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include "Objects.hpp" 

class GameOverClass{
private:
	sf::RenderWindow & window;
	std::string return_statement="";
	
	std::map<std::string, rectangle> borderList = {
        {"wall_top",    rectangle( sf::Vector2f( 394.0, 0.0 ),   sf::Color(0,0,0), sf::Vector2f( 1142.0, 1.0 ) )},
        {"wall_bottom", rectangle( sf::Vector2f( 384.0, 865.0 ), sf::Color(0,0,0), sf::Vector2f( 1152.0, 1.0 ) )},
        {"wall_right",  rectangle( sf::Vector2f( 1536.0, 0.0 ),  sf::Color(255,255,255), sf::Vector2f( 10.0, 1080.0 ) )},
        {"wall_left",   rectangle( sf::Vector2f( 384.0, 0.0 ),   sf::Color(255,255,255), sf::Vector2f( 10.0, 1080.0 ) )}
    };
    std::map<std::string, picture> GameOverList = {
        {"Background", picture(sf::Vector2f( 394.0, 0.0 ), "images/space.jpg", sf::Vector2f( 1142.0, 865.0 ))},
		{"ReturnMenu_GameButton", picture(sf::Vector2f( 700.0, 400.0), "images/Return.png", sf::Vector2f( 500.0, 70.0))}
    };
	
	action ButtonClick[1] = {
		action( sf::Mouse::Left,  [&](){
			for(auto & picture: GameOverList){
				if(select_object( sf::Mouse::getPosition( window ), picture.second )){
					if(picture.first=="ReturnMenu_GameButton"){
						return_statement = "MENU";
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
	GameOverClass(auto& window):
        window( window )
    {};

	std::string GameOverLoop(){
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
		}
		for( auto & action : ButtonClick ){
			action();
		}
	}
	
	void render(){
        window.clear();

        for(auto & picture: GameOverList){
            picture.second.draw( window );
        }

        for(auto & border: borderList){
            border.second.draw( window );
        }

        window.display();
	}
};

#endif