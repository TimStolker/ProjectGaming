#ifndef _GAMEOVER_HPP
#define _GAMEOVER_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <fstream>
#include "Objects.hpp"
#include "GameControl.hpp"
#include "LeaderBoard.hpp"

class GameOverClass{
private:
	sf::RenderWindow & window;
	std::string return_statement="";	
	std::string playerInput;
	sf::Text playerName;
	sf::Font font;
	
	LeaderBoardClass leaderboard = LeaderBoardClass(window);
	playerStats playerstats;
	
	bool UploadedName;
	
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
		UploadedName = false;
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
		if (event.type == sf::Event::TextEntered){
			if(event.text.unicode < 128){
				std::cout << "ASCII character typed: " << static_cast<char>(event.text.unicode) << std::endl;
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)){
					playerInput.pop_back();
					std::cout << "BACKSLASH: " << playerInput << std::endl;
				}
				else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)){
					//playerName.setString(playerInput);
					//leaderboard.leaderboardcalc(playerInput, playerstats.GetScore());
					std::cout << playerInput << std::endl;
				}
				else{
					playerInput += static_cast<char>(event.text.unicode);
				}				
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