#ifndef _LEADERBOARD_HPP
#define _LEADERBOARD_HPP
#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <vector>
#include "Objects.hpp" 
#include <cstring>

	
class LeaderBoardClass{
private:
	bool return_statement;
	sf::RenderWindow & window;
	sf::Font MyFont;
	sf::Text leaderboard;
	bool scorebool;
	float y_value;
	float x_value;
	float x2_value;
	int index=0;
	std::string scorestring="";
	std::string tmpscorestring="";
	std::string readstring="";
	std::string namestring="";
	std::vector<std::string> scorelist;
	std::vector<std::string> namelist;
	std::vector<std::string> readlist;
	std::map<std::string, picture> BoardList = {
        {"Background",picture(sf::Vector2f{ 0.0, 0.0 }, "images/Background.png", sf::Vector2f( 1920, 900 ))},
		{"Logo",picture(sf::Vector2f( 600.0, 5.0 ), "images/Logo.png", sf::Vector2f( 600.0, 300.0 ))},
		{"Quit_GameButton",picture(sf::Vector2f{0.0,800.0}, "images/Return.png", sf::Vector2f( 500.0, 70.0 ))}
	};
	std::map<std::string, rectangle> BackList = {
		{"Leaderboard background",    rectangle( sf::Vector2f( 560.0, 330.0 ),   sf::Color(22,29,47,200), sf::Vector2f( 700.0, 525.0 ) )}
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

//___________________________________________________________________________________________
	void readfile(){
		std::ifstream myfile;
		readstring = "";
		readlist.clear();
		myfile.open ("leaderboard.txt");
		if (!myfile) {
			std::cout << "File not created! \n";
		}
		
		while(std::getline(myfile, readstring)){
			readlist.push_back(readstring);
		}
		myfile.close();
	}

//___________________________________________________________________________________________
	bool LeaderBoardLoop(){
		return_statement = 0;
		makelistscore_name();
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
//___________________________________________________________________________________________
	void makelistscore_name(){
		readfile();
		scorestring="";
		scorebool = false;
		for(auto&& tmpscorestring : readlist){
			for(unsigned int i=0; i<=tmpscorestring.size()-1;i++){
				if (tmpscorestring[i]=='|'){
					scorebool = true;
				}
				if(scorebool){
					if(!((tmpscorestring[i]==' ')||(tmpscorestring[i]=='|'))){
						scorestring = scorestring +tmpscorestring[i];
					
					}
				}
				else{
					if(!(tmpscorestring[i]=='|')){
						namestring = namestring +tmpscorestring[i];
						
					}
				}
			}
			scorebool = false;
			namelist.push_back(namestring);
			scorelist.push_back(scorestring);
			scorestring="";
			namestring="";
		}
	}
	
//===========================================================================================
	void leaderboardcalc(std::string score_name, int score){
		makelistscore_name();
		getindexwithscore(score);
		writefile(score_name,score);
	}
//===========================================================================================
	void getindexwithscore(int score){
		index=0;
		for(unsigned int i=0; i<=scorelist.size()-1;i++){
			std::cout << scorelist[i] << std::endl;
			if(score>=std::stoi(scorelist[i])){
				index=i;
			}
		}
		index=scorelist.size();
	}
//===========================================================================================
	void writefile(std::string score_name,int score){
		std::ofstream myfile;
		std::string stringtofile = score_name+" | "+std::to_string(score);
		std::cout << index << std::endl;
		std::vector<std::string>::iterator iter = readlist.begin() + index;
		readlist.insert(iter, stringtofile);
		myfile.open ("leaderboard.txt");
		for (const auto &e : readlist) myfile << e << "\n";
		myfile.close();
	}
	
//===========================================================================================
	void drawleaderboard(){
		y_value=50;
		x_value=500;
		x2_value=40;
		MyFont.loadFromFile("images/OstrichSans-Medium.otf");
		leaderboard.setFont(MyFont);
		leaderboard.setCharacterSize(55);
		leaderboard.setFillColor(sf::Color::White);
		leaderboard.setStyle(sf::Text::Bold);
		leaderboard.setPosition(575,325);
		for(unsigned int i=0;i<=9;i++){
			leaderboard.setString(std::to_string(i+1)+". ");
			window.draw(leaderboard);
			leaderboard.move(x2_value,0);
			leaderboard.setString(namelist[i]);
			window.draw(leaderboard);
			leaderboard.setString(scorelist[i]);
			leaderboard.move(x_value,0);
			window.draw(leaderboard);
			leaderboard.move(0,y_value);
			leaderboard.move(-x_value,0);
			leaderboard.move(-x2_value,0);
		}
	}
	
//===========================================================================================
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
	
//===========================================================================================
    void render(){
        window.clear(sf::Color::White);
		for(auto & picture: BoardList){
            picture.second.draw( window );
        }
		for(auto & picture: BackList){
			picture.second.setBorder(10 , sf::Color(0,0,0));
			picture.second.draw( window );
        }
		drawleaderboard();
        window.display();
    }
	
//===========================================================================================
	bool select_object( sf::Vector2i MousePosition, picture object ){
		auto posFloat = static_cast<sf::Vector2f>(MousePosition);
		if(object.clicked( posFloat )){
			return true;
		}
		return false;
	}
};
#endif