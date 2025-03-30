//this file contains Doxygen lines
///file LeaderBoard.hpp
/// \brief LeaderBoardClass
/// \details Contains all the necessary information about the LeaderBoardClass class
#ifndef _LEADERBOARD_HPP
#define _LEADERBOARD_HPP

#include <fstream>
#include "Objects.hpp" 
#include <cstring>
	
class LeaderBoardClass{
private:
	std::vector<std::string> scoreList, nameList, readList;
	std::string score_string="",tmp_score_string="";
	std::string read_string="",name_string="";
	bool return_statement, score_bool;
	float y_value, x_value, x2_value;
	sf::RenderWindow & window;
	sf::Text leaderboard;
	sf::Font MyFont;
	
	std::map<std::string, picture> BoardList = {
        {"Background",picture(sf::Vector2f{ 0.0, 0.0 }, "images/Background.png", sf::Vector2f( 1920, 900 ))},
		{"Logo",picture(sf::Vector2f( 600.0, 5.0 ), "images/Logo.png", sf::Vector2f( 600.0, 300.0 ))},
		{"Quit_GameButton",picture(sf::Vector2f{0.0,800.0}, "images/Return.png", sf::Vector2f( 500.0, 70.0 ))}
	};

	std::map<std::string, rectangle> BackList = {
		{"Leaderboard background", rectangle( sf::Vector2f( 560.0, 330.0 ),   sf::Color(22,29,47,200), sf::Vector2f( 700.0, 525.0 ) )}
	};
	
	action ButtonClick[1] = {
		action( sf::Mouse::Left, [&](){
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
                if(event.type == sf::Event::MouseButtonReleased) {
					sf::sleep( sf::milliseconds(150));
                    break;
                }
            }
		})
	};

public:
	LeaderBoardClass(sf::RenderWindow& window):
        window( window )
    {}
	/// \brief Reads the leaderboard.txt file.
	/// \details Puts every line in readList and is used by leaderboardcalc() and CheckInTop().
	void readFile(){
		std::ifstream myfile;
		read_string = "";
		readList.clear();
		myfile.open ("leaderboard.txt");
		if (!myfile) {
			std::cout << "File not created! \n";
		}
		
		while(std::getline(myfile, read_string)){
			readList.push_back(read_string);
		}
		myfile.close();
	}
	/// \brief The main loop for the leaderboard.
	/// \details This shows the leaderboard on the screen with everything updated.

	bool LeaderBoardLoop(){
		nameList.clear();
		scoreList.clear();
		return_statement = 0;
		makeListScoreName();
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
	/// \brief updates nameList and scoreList.
	/// \details Used by leaderboardcalc() and CheckInTop().
	void makeListScoreName(){
		readFile();
		nameList.clear();
		scoreList.clear();
		score_string="";
		score_bool = false;
		for(auto&& tmp_score_string : readList){
			for(unsigned int i=0; i<=tmp_score_string.size()-1;i++){
				if (tmp_score_string[i]=='|'){
					score_bool = true;
				}
				if(score_bool){
					if(!((tmp_score_string[i]==' ')||(tmp_score_string[i]=='|'))){
						score_string = score_string +tmp_score_string[i];
					
					}
				}
				else{
					if(!(tmp_score_string[i]=='|')){
						name_string = name_string +tmp_score_string[i];
						
					}
				}
			}
			score_bool = false;
			nameList.push_back(name_string);
			scoreList.push_back(score_string);
			score_string="";
			name_string="";
		}
	}
	/// \brief Writes score_name and score to the leaderboard file.
    /// \details Used by GameOver.hpp.
//===========================================================================================
	void leaderboardcalc(std::string score_name,int score){
		nameList.clear();
		scoreList.clear();
		makeListScoreName();
		int index = getIndexWithScore(score);
		writeFile(score_name,score,index);
	}
	/// \brief Returns an index with the score.
	/// \details Used by leaderboardcalc() and CheckInTop().
//===========================================================================================
	int getIndexWithScore(int score){
		int index=0;
		if(scoreList.size()>0){
			for(unsigned int i=0; i<=scoreList.size()-1;i++){
				if(score>=std::stoi(scoreList[i])){
					index=i;
					return index;
				}
				
			}
			index=scoreList.size();
			return index;
			
		}
		else{
			return index;
		}
	}
	/// \brief Processes all input from user.
	/// \details Makes you go back to the menu.
//===========================================================================================
	void writeFile(std::string score_name,int score,int index){
		std::ofstream myfile;
		std::string stringToFile = score_name+" | "+std::to_string(score);
		std::vector<std::string>::iterator iter = readList.begin() + index;
		readList.insert(iter, stringToFile);
		myfile.open ("leaderboard.txt");
		for(const auto &e : readList) myfile << e << "\n";
		myfile.close();
	}
/// \brief Draws all stats to the screen.
/// \details Makes use of namelist for the names and scorelist for the scores.
//===========================================================================================
	void drawLeaderBoard(){
		y_value=50;
		x_value=500;
		x2_value=40;
		int length = 0;
		MyFont.loadFromFile("images/OstrichSans-Medium.otf");
		leaderboard.setFont(MyFont);
		leaderboard.setCharacterSize(55);
		leaderboard.setFillColor(sf::Color::White);
		leaderboard.setStyle(sf::Text::Bold);
		leaderboard.setPosition(575,325);
		if (nameList.size()>10){
			length=9;
		}else{
			length=nameList.size()-1;
		}
		for(int i=0; i<=length; i++){
			leaderboard.setString(std::to_string(i+1)+". ");
			window.draw(leaderboard);
			leaderboard.move(x2_value,0);
			leaderboard.setString(nameList[i]);
			window.draw(leaderboard);
			leaderboard.setString(scoreList[i]);
			leaderboard.move(x_value,0);
			window.draw(leaderboard);
			leaderboard.move(0,y_value);
			leaderboard.move(-x_value,0);
			leaderboard.move(-x2_value,0);
		}
	}
	/// \brief Processes all input from user.
	/// \details Makes you go back to the menu.
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
/// \brief Renders everything to the screen.
/// \details Renders all thats in BoardList and BackList to display and uses drawleaderboard for the score data.
	
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
		drawLeaderBoard();
        window.display();
    }
//===========================================================================================
	/// \brief Gets playerNmr and power and write them in a pool.
	/// \details Requires an int playerNmr and int power.
int checkInTop(int score){
        makeListScoreName();
        return getIndexWithScore(score);
    }
};
#endif