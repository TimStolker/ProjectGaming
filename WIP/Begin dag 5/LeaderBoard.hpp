#ifndef _LEADERBOARD_HPP
#define _LEADERBOARD_HPP
#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include "Objects.hpp" 

class LeaderBoardClass{
private:
	bool return_statement;
	sf::RenderWindow & window;
	sf::Font MyFont;
	sf::Text leaderboard;
	
	float y_value;
	std::string readstring="";
	std::vector<std::string> readlist;
	std::map<std::string, picture> BoardList = {
        {"Background",picture(sf::Vector2f{ 0.0, 0.0 }, "images/Background.png", sf::Vector2f( 1920, 900 ))},
		{"Logo",picture(sf::Vector2f( 600.0, 5.0 ), "images/Logo.png", sf::Vector2f( 600.0, 300.0 ))},
		{"Quit_GameButton",picture(sf::Vector2f{0.0,800.0}, "images/Return.png", sf::Vector2f( 500.0, 70.0 ))}
	};
	std::map<std::string, rectangle> BackList = {
        {"Leaderboard background",    rectangle( sf::Vector2f( 560.0, 330.0 ),   sf::Color(128,128,128), sf::Vector2f( 700.0, 525.0 ) )}
    };
	
	action ButtonClick[1] = {
		action( sf::Mouse::Left,  [&](){
			for(auto & picture: BoardList){
				if(select_object( sf::Mouse::getPosition( window ), picture.second )){
                    if(picture.first=="Quit_GameButton"){
						return_statement=1;
                    }
				}
			}
			for(;;){
				sf::Event event;
                window.pollEvent(event);
                if (event.type == sf::Event::MouseButtonReleased) {
					sf::sleep( sf::milliseconds(150));
                    break;
                }
            }
		})
	};
public:
	LeaderBoardClass(auto& window):
        window( window )
    {}
	
	bool LeaderBoardLoop(){
		return_statement = 0;
		readfile();
		for(;;){
			sf::sleep( sf::milliseconds(20));
			render();
			processInput();
			if(return_statement==1){
				window.clear(sf::Color::White);
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
				for(auto & picture: BoardList){
					if(select_object( sf::Mouse::getPosition( window ), picture.second )){
						if(!(picture.first=="Quit_GameButton")){
							BoardList["Quit_GameButton"].change_image("images/Return.png");
						}
						if(picture.first=="Quit_GameButton"){
							picture.second.change_image("images/Return_hover.png");
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
	void readfile(){
		std::ifstream myfile;
		readstring = "";
		readlist.clear();
		myfile.open ("leaderboard.txt");
		if (!myfile) {
			std::cout << "File not created! \n";
		}
		
		for(int i=0; i<=8;i++){
			getline (myfile, readstring);
			readlist.push_back(readstring);
		}
		myfile.close();
	}
	void drawleaderboard(){
		y_value=10;
		MyFont.loadFromFile("images/OstrichSans-Medium.otf");
		leaderboard.setFont(MyFont);
		leaderboard.setCharacterSize(60);
		leaderboard.setFillColor(sf::Color::White);
		leaderboard.setStyle(sf::Text::Bold);
		leaderboard.setPosition(600,325);
		for(unsigned int i=0;i<=(readlist.size())-1;i++){
			leaderboard.setString(readlist[i]);
			leaderboard.move(0,y_value);
			window.draw(leaderboard);
			y_value=+55;
		}
	}
    void render(){
        window.clear(sf::Color::White);
		for(auto & picture: BoardList){
            picture.second.draw( window );
        }
		for(auto & picture: BackList){
			picture.second.setBorder(10 , sf::Color(68,68,68));
			picture.second.draw( window );
        }
		drawleaderboard();
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
#endif
