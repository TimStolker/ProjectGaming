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
	std::string playerName;
	int score;
	
	LeaderBoardClass leaderboard = LeaderBoardClass(window);
	playerStats playerstats;
	
	picture Background = picture(sf::Vector2f{ 0.0, 0.0 }, "images/Background.png", sf::Vector2f( 1920, 900 ));

    std::map<std::string, picture> GameOverList = {
		{"gameOver",picture(sf::Vector2f{ 600.0, 150.0 }, "images/Game_over.png", sf::Vector2f( 750, 350 ))},
		{"ReturnMenu_GameButton", picture(sf::Vector2f( 400.0, 800.0 ), "images/Return.png", sf::Vector2f( 500.0, 70.0))},
		{"LeaderBoard_GameButton", picture(sf::Vector2f( 1100.0, 800.0 ), "images/Leaderboard.png", sf::Vector2f( 500.0, 70.0))}
    };
	
	std::map<std::string, rectangle> BackList = {
		{"Leaderboard background",    rectangle( sf::Vector2f( 550.0, 100.0 ),   sf::Color(22,29,47,200), sf::Vector2f( 900.0, 650.0 ) )},
		{"playerNameBar", rectangle( sf::Vector2f( 600.0, 600.0 ),   sf::Color(255,255,255), sf::Vector2f( 800.0, 70.0 ))}
	};

	action ButtonClick[1] = {
		action( sf::Mouse::Left,  [&](){
			for(auto & picture: GameOverList){
				if(select_object( sf::Mouse::getPosition( window ), picture.second )){
					if(picture.first=="ReturnMenu_GameButton"){
						return_statement = "MENU";
					}
					if(picture.first=="LeaderBoard_GameButton"){
						return_statement = "LEADERBOARD";
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
			sf::sleep( sf::milliseconds(10));
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
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)){
					playerName.pop_back();
				}
				else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)){
					leaderboard.leaderboardcalc(playerName, score);
					playerName = "";
				}
				else{
					playerName += static_cast<char>(event.text.unicode);
				}				
			}
		}
		if(event.type == sf::Event::MouseMoved){
			for(auto & picture: GameOverList){
				if(select_object( sf::Mouse::getPosition( window ), picture.second )){
					if(!(picture.first=="ReturnMenu_GameButton" || picture.first=="LeaderBoard_GameButton" )){
						GameOverList["ReturnMenu_GameButton"].change_image("images/Return.png");
						GameOverList["LeaderBoard_GameButton"].change_image("images/Leaderboard.png");
					}
					if(picture.first=="ReturnMenu_GameButton"){
						picture.second.change_image("images/Return_hover.png");
						break;
					}
					else if(picture.first=="LeaderBoard_GameButton"){
						picture.second.change_image("images/Leaderboard_hover.png");
						break;
					}
				}
			}
		}
		for( auto & action : ButtonClick ){
			action();
		}
		
	}
	
	void render(){
        window.clear();
		Background.draw( window );

		for(auto & picture: BackList){
			picture.second.setBorder(10 , sf::Color(0,0,0));
			picture.second.draw( window );
        }
		
        for(auto & picture: GameOverList){
            picture.second.draw( window );
        }

		
		DisplayText();
		DisplayName(playerName);
		window.display();
	}
	
	void DisplayName(std::string Text){
		sf::Text Name;
		sf::Font MyFont;
		MyFont.loadFromFile("images/OstrichSans-Medium.otf");
		Name.setFont(MyFont);
		Name.setString(Text);
		Name.setCharacterSize(60);
		Name.setFillColor(sf::Color::Black);
		Name.setStyle(sf::Text::Bold);
		Name.setPosition({610.0, 600.0});
		window.draw(Name);
	}
	
	void DisplayText(){
		sf::Text Name;
		sf::Font MyFont;
		MyFont.loadFromFile("images/OstrichSans-Medium.otf");
		Name.setFont(MyFont);
		Name.setString("Type a name for the leaderbord: ");
		Name.setCharacterSize(60);
		Name.setFillColor(sf::Color::White);
		Name.setStyle(sf::Text::Bold);
		Name.setPosition({610.0, 510.0});
		window.draw(Name);
	}
};

#endif