#ifndef _STATEMACHINE_HPP
#define _STATEMACHINE_HPP
#include "GameControl.hpp"
#include "SplashScreen.hpp"
#include "MainMenu.hpp"

#include <iostream>

class Statemachine{
	
	enum state_t {SPLASH, MENU,	LEADERBOARD, CHARACTER, GAME, GAMEOVER};
	state_t state = SPLASH;
public:

	void machine(){	
		sf::RenderWindow window{ sf::VideoMode{ 1920, 875 },"Totally Original game" };
		
		gameLoop loop     = gameLoop(window);
		SplashClass splash = SplashClass(window);
		MainMenu menu  = MainMenu(window);
		for(;;){
			sf::sleep( sf::milliseconds(20));
			switch(state){
				case SPLASH:
					//if(splash.SplashShow()){
					state = MENU;
					//}
					break;
				case MENU:
					menu.MainMenuLoop();
					
					break;
				case LEADERBOARD:
					std::cout<<"hi";
					break;
				case CHARACTER:
					std::cout<<"hi";
					break;
				case GAME:
					loop.loop();
					break;
				case GAMEOVER:
					std::cout<<"hi";
					break;
			}
		}
	}
};
#endif
