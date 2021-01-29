//this file contains Doxygen lines
///file GameOver.hpp
/// \brief gameover
/// \details Contains all the necessary information about the GameOverClass class

#ifndef _GAMEOVER_HPP
#define _GAMEOVER_HPP

#include <fstream>
#include "Objects.hpp"
#include "GameControl.hpp"
#include "LeaderBoard.hpp"

/// \brief GameOver Class
/// \details This class handels everything that is needed for the gameover screen
//===========================================================================================
class GameOverClass{
private:
	int score, indexScore;
	playerStats playerstats;
	sf::RenderWindow & window;
	std::string return_statement="", playerName = "";
	LeaderBoardClass leaderboard = LeaderBoardClass(window);
	picture Background = picture(sf::Vector2f{ 0.0, 0.0 }, "images/Background.png", sf::Vector2f( 1920, 900 ));

    std::map<std::string, picture> GameOverList = {
		{"gameOver",picture(sf::Vector2f{ 600.0, 225.0 }, "images/Game_over.png", sf::Vector2f( 750, 150 ))},
    };
	
	std::map<std::string, rectangle> BackList = {
		{"Leaderboard background",    rectangle( sf::Vector2f( 510.0, 100.0 ),   sf::Color(22,29,47,200), sf::Vector2f( 900.0, 650.0 ) )},
		{"playerNameBar", rectangle( sf::Vector2f( 560.0, 600.0 ),   sf::Color(15,67,116,100), sf::Vector2f( 800.0, 70.0 ))}
	};
	
public:
	/// \brief Costructor of the GameOverClass
    /// \details This costructor only needs a window
	GameOverClass(auto& window):
        window( window )
    {};

	/// \brief Central gameover loop
    /// \details This loop activiated processInput() and render(), it needs an int score
    //===========================================================================================
	std::string GameOverLoop(int new_score){
		return_statement="";
		score = new_score;
		playerName="";
		indexScore = leaderboard.checkInTop(score);
		if( indexScore >= 10){
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
	
	/// \brief Processes user input
    /// \details Checks if the user triggered any events
    //===========================================================================================
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
	
	/// \brief Renders
    /// \details Renders all object in the game
    //===========================================================================================
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

		DisplayText(("Score: " + std::to_string(score)), {640.0, 440.0});
		DisplayText("Enter your Name: ", {640.0, 510.0});
		DisplayText(playerName, {570.0, 600.0});
		window.display();
	}

	/// \brief Displays text
    /// \details Displays a given text at a given position
    //===========================================================================================
	void DisplayText(std::string Text, sf::Vector2f position){
		sf::Text Name;
		sf::Font MyFont;
		MyFont.loadFromFile("images/OstrichSans-Medium.otf");
		Name.setFont(MyFont);
		Name.setString(Text);
		Name.setCharacterSize(60);
		Name.setFillColor(sf::Color::White);
		Name.setStyle(sf::Text::Bold);
		Name.setPosition(position);
		window.draw(Name);
	}
};

#endif