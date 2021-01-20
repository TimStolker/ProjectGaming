#ifndef _STATEMACHINE_HPP
#define _STATEMACHINE_HPP
#include "GameControl.hpp"
#include "SplashScreen.hpp"
#include "MainMenu.hpp"
#include "LeaderBoard.hpp"
#include "CharacterMenu.hpp"
#include "GameOver.hpp"

#include <iostream>

class Statemachine{
	
	enum state_t {SPLASH, MENU,	LEADERBOARD, CHARACTER, GAME, GAMEOVER};
	state_t state = SPLASH;
public:

	void machine(){	
		sf::RenderWindow window{ sf::VideoMode{ 1920, 875 },"Totally Original Space Shooter " };
		std::string outcome = "";
		playerStats stats;
		gameControl loop               = gameControl(window);
		SplashClass splash 			= SplashClass(window);
		MainMenu menu  				= MainMenu(window);
		LeaderBoardClass board 		= LeaderBoardClass(window);
		CharacterMenu charactermenu = CharacterMenu(window);
		GameOverClass gameover		= GameOverClass(window);
		
		for(;;){
			sf::sleep( sf::milliseconds(20));
			switch(state){
				case SPLASH:
					splash.SplashShow();
					state = MENU;
					break;
				case MENU:
					outcome = menu.MainMenuLoop();
					if(outcome=="GAME"){
						state=CHARACTER;
					}
					else if(outcome=="LEADERBOARD"){
						state=LEADERBOARD;
					}
					break;
				case LEADERBOARD:
					if(board.LeaderBoardLoop()==1){
						state=MENU;
					}
					break;
				case CHARACTER:
					outcome=charactermenu.CharacterMenuLoop();
					if(outcome=="START_small"){
						stats.shipSpeed = 10;
						stats.health = 2;
						stats.size = {40,60};
						stats.reloadTime = 1000;
                        stats.lazerColor = "images/Lazer_red.png";
                        stats.bulletAlignment = {15.0, -8.0};
						stats.ship = "images/Small_Ship.png";
						state = GAME;
					}
					else if(outcome=="START_standard"){
						stats.shipSpeed = 8;
						stats.health = 3;
						stats.size = {70,80};
                        stats.lazerColor = "images/Lazer_blue.png";
                        stats.bulletAlignment = {30.0, -8.0};
						stats.ship = "images/Medium_Ship.png";
						state = GAME;
					}
					else if(outcome=="START_big"){
						stats.shipSpeed = 6;
						stats.health = 4;
						stats.bulletDamage = 3;
						stats.size = {70,90};
                        stats.lazerColor = "images/Lazer_yellow.png";
                        stats.bulletAlignment = {30.0, -15.0};
						stats.ship = "images/Big_Ship.png";
						state = GAME;
					}
					else if(outcome=="RETURN"){
						state = MENU;
					}
					loop.updateStats(stats);
					break;
				case GAME:
					outcome = loop.loop();
					if (outcome=="GAMEOVER"){
						state = GAMEOVER;
					}
					else if(outcome=="MENU"){
						state = MENU;
					}
					break;
				case GAMEOVER:
					outcome = gameover.GameOverLoop();
					state = MENU;
					break;
			}
		}
	}
};
#endif
