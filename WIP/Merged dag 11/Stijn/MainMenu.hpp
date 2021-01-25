#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "GameControl.hpp"
#include "Objects.hpp"

class MainMenu{
private:
	sf::Vector2i cursorPos;
	std::string return_statement="";
	sf::RenderWindow & window;

	std::map<std::string, picture> MenuList = {
        {"Background",picture(sf::Vector2f{ 0.0, 0.0 }, "images/Background.png", sf::Vector2f( 1920, 900 ))},
		{"Logo",picture(sf::Vector2f( 600.0, 5.0 ), "images/Logo.png", sf::Vector2f( 600.0, 300.0 ))},
		{"Play_GameButton",picture(sf::Vector2f{ 710.0, 400.0 }, "images/Play.png", sf::Vector2f( 500.0, 70.0 ))},
		{"Leaderbord_GameButton",picture(sf::Vector2f{ 710.0, 500.0 }, "images/Leaderboard.png", sf::Vector2f( 500.0, 70.0 ))},
		{"Quit_GameButton",picture(sf::Vector2f{ 710.0, 600.0 }, "images/Quit.png", sf::Vector2f( 500.0, 70.0 ))}
    };
	
	action ButtonClick[1] = {
		action( sf::Mouse::Left,  [&](){
			for(auto & picture: MenuList){
				if(select_object( sf::Mouse::getPosition( window ), picture.second )){
					if(picture.first=="Play_GameButton"){
						return_statement = "GAME";
					}
					else if(picture.first=="Leaderbord_GameButton"){
						return_statement = "LEADERBOARD";
					}
					else if(picture.first=="Quit_GameButton"){
						window.close();
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
	 MainMenu(auto& window):
        window( window )
    {}

	std::string MainMenuLoop(){
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
				for(auto & picture: MenuList){
					if(select_object( sf::Mouse::getPosition( window ), picture.second )){
						if(!(picture.first=="Play_GameButton" || picture.first=="Leaderbord_GameButton" || picture.first=="Quit_GameButton")){
							MenuList["Play_GameButton"].change_image("images/Play.png");
							MenuList["Leaderbord_GameButton"].change_image("images/Leaderboard.png");
							MenuList["Quit_GameButton"].change_image("images/Quit.png");
						}
						if(picture.first=="Play_GameButton"){
							picture.second.change_image("images/Play_hover.png");
							break;
						}
						else if(picture.first=="Leaderbord_GameButton"){
							picture.second.change_image("images/Leaderboard_hover.png");
							break;
						}
						else if(picture.first=="Quit_GameButton"){
							picture.second.change_image("images/Quit_hover.png");
							break;
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
		for(auto & picture: MenuList){
            picture.second.draw( window );
        }
        window.display();
    }

};