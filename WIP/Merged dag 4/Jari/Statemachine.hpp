#ifndef _STATEMACHINE_HPP
#define _STATEMACHINE_HPP
#include "GameControl.hpp"
#include "SplashScreen.hpp"
#include "MainMenu.hpp"
#include "LeaderBoard.hpp"
#include "CharacterMenu.hpp"

#include <iostream>

class Statemachine{
	
	enum state_t {SPLASH, MENU,	LEADERBOARD, CHARACTER, GAME, GAMEOVER};
	state_t state = SPLASH;
public:

	void machine(){	
		sf::RenderWindow window{ sf::VideoMode{ 1920, 875 },"Totally Original Space Shooter " };
		std::string outcome = "";
		gameLoop loop     			= gameLoop(window);
		SplashClass splash 			= SplashClass(window);
		MainMenu menu  				= MainMenu(window);
		LeaderBoardClass board 		= LeaderBoardClass(window);
		CharacterMenu charactermenu = CharacterMenu(window);
		
		for(;;){
			sf::sleep( sf::milliseconds(20));
			switch(state){
				case SPLASH:
					if(splash.SplashShow()){
						state = MENU;
					}
					break;
				case MENU:
					outcome=menu.MainMenuLoop();
					if(outcome=="PLAY"){
						state=CHARACTER;
					}
					if(outcome=="LEADERBOARD"){
						state=LEADERBOARD;
					}
					break;
				case LEADERBOARD:
					if(board.LeaderBoardLoop()==1){
						std::cout<<"menu";
						state=MENU;
					}
					break;
				case CHARACTER:
					outcome=charactermenu.CharacterMenuLoop();
					if(outcome=="START"){
						state=GAME;
					}
					else if(outcome=="RETURN"){
						state=MENU;
					}
					break;
				case GAME:
					loop.loop();
					break;
				case GAMEOVER:
					state = MENU;
					break;
			}
		}
	}
};
#endif
