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
	std::string playerName = "";
	int score;
	int IndexScore;
	
	LeaderBoardClass leaderboard = LeaderBoardClass(window);
	playerStats playerstats;
	
	picture Background = picture(sf::Vector2f{ 0.0, 0.0 }, "images/Background.png", sf::Vector2f( 1920, 900 ));

    std::map<std::string, picture> GameOverList = {
		{"gameOver",picture(sf::Vector2f{ 600.0, 225.0 }, "images/Game_over.png", sf::Vector2f( 750, 150 ))},
    };
	
	std::map<std::string, rectangle> BackList = {
		{"Leaderboard background",    rectangle( sf::Vector2f( 510.0, 100.0 ),   sf::Color(22,29,47,200), sf::Vector2f( 900.0, 650.0 ) )},
		{"playerNameBar", rectangle( sf::Vector2f( 560.0, 600.0 ),   sf::Color(15,67,116,100), sf::Vector2f( 800.0, 70.0 ))}
	};
	
public:
	GameOverClass(auto& window):
        window( window )
    {};

	std::string GameOverLoop(int new_score){
		return_statement="";
		score = new_score;
		playerName="";
		IndexScore = leaderboard.CheckinTop(score);
		if( IndexScore >= 10){
			return "MENU";
		}
		while(true){
			sf::sleep( sf::milliseconds(10));
			processInput();
			render();
			if(!(return_statement=="")){
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
			if(event.text.unicode < 128 && event.text.unicode != 124 && event.text.unicode != 9){
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)){
					if(!(playerName=="")){
						playerName.pop_back();
					}
				}
				else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)){
					if(playerName!=""){
						leaderboard.leaderboardcalc(playerName, score);
						playerName = "";
						return_statement = "LEADERBOARD";
					}
				}
				else{
					playerName += static_cast<char>(event.text.unicode);
				}
			}
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

		DisplayScore();
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
		Name.setFillColor(sf::Color::White);
		Name.setStyle(sf::Text::Bold);
		Name.setPosition({570.0, 600.0});
		window.draw(Name);
	}
	
	void DisplayText(){
		sf::Text Name;
		sf::Font MyFont;
		MyFont.loadFromFile("images/OstrichSans-Medium.otf");
		Name.setFont(MyFont);
		Name.setString("Enter your Name: ");
		Name.setCharacterSize(60);
		Name.setFillColor(sf::Color::White);
		Name.setStyle(sf::Text::Bold);
		Name.setPosition({640.0, 510.0});
		window.draw(Name);
	}
	
	void DisplayScore(){
		sf::Text Name;
		sf::Font MyFont;
		MyFont.loadFromFile("images/OstrichSans-Medium.otf");
		Name.setFont(MyFont);
		Name.setString("Score: " + std::to_string(score));
		Name.setCharacterSize(60);
		Name.setFillColor(sf::Color::White);
		Name.setStyle(sf::Text::Bold);
		Name.setPosition({640.0, 440.0});
		window.draw(Name);
	}
};

#endif