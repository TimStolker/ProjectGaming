#ifndef _SPLASHSCREEN_HPP
#define _SPLASHSCREEN_HPP
#include <iostream>
#include <SFML/Graphics.hpp>

class SplashClass{
private:
	sf::RenderWindow & window;
	bool done;

	std::map<std::string, picture> SplashList = {
        {"Background", picture(sf::Vector2f( 0.0, 0.0 ),      "images/Background.png",    sf::Vector2f( 1920, 900 ))},
		{"Logo1",      picture(sf::Vector2f( -600.0, 5.0 ),   "images/Logo_shooter.png",  sf::Vector2f( 600.0, 300.0 ))},
		{"Logo2",	   picture(sf::Vector2f( 1800.0, 5.0 ),   "images/Logo_original.png", sf::Vector2f( 600.0, 300.0 ))},
		{"Logo3",	   picture(sf::Vector2f( -600.0, 5.0 ),   "images/Logo_totally.png",  sf::Vector2f( 600.0, 300.0 ))},
		{"Play",       picture(sf::Vector2f( 710.0, 1000.0 ), "images/Play.png",          sf::Vector2f( 500.0, 70.0 ))},
		{"Leaderbord", picture(sf::Vector2f( 710.0, 1200.0 ), "images/Leaderboard.png",   sf::Vector2f( 500.0, 70.0 ))},
		{"Quit",       picture(sf::Vector2f( 710.0, 1400.0 ), "images/Quit.png",          sf::Vector2f( 500.0, 70.0 ))},
		{"ship",       picture(sf::Vector2f( 0.0, 660.0 ),    "images/Ship1.png",         sf::Vector2f( 60.0f, 70.0f ))}
    };
   
public:
	SplashClass(auto& window):
        window( window )
    {}
	
    void SplashShow(){
		SplashList["ship"].rotate(70);
        for(;;){
            sf::sleep( sf::milliseconds(20));
			done = updateLogo();
            render();

			if(done){ break; }
			if(processInput()){ return; }
        }
		for(;;){
            sf::sleep( sf::milliseconds(20));
			done = updateButtons();
            render();

			if(done){ break; }
			if(processInput()){ return; }
        }
		
		for(int i = 0; i <= 10; i++){
            sf::sleep( sf::milliseconds(20));
			SplashList["ship"].move({80,-40});
            render();

			if(processInput()){ return; }
        }
		

    }

	bool processInput(){
        sf::Event event;
        while( window.pollEvent(event) ){
            if( event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::KeyPressed  ){
                return true;
            }
        }
		return false;
    }

	bool updateLogo(){
		int finished = 0;

		if(!(SplashList["Logo1"].getPosition()==sf::Vector2f( 600.0, 5.0 ))){
			SplashList["Logo1"].move(sf::Vector2f( 20.0, 0.0 ));
		}
		else{ finished++; }

		if(!(SplashList["Logo2"].getPosition()==sf::Vector2f( 600.0, 5.0 ))){
			SplashList["Logo2"].move(sf::Vector2f( -20.0, 0.0 ));
		}
		else{ finished++; }

		if(!(SplashList["Logo3"].getPosition()==sf::Vector2f( 600.0, 5.0 ))){
			SplashList["Logo3"].move(sf::Vector2f( 20.0, 0.0 ));
		}
		else{ finished++; }

		if(finished==3){
			return true;
		}
		return false;
	}
	bool updateButtons(){
		int finished = 0;

		if(!(SplashList["Play"].getPosition()==sf::Vector2f( 710.0, 400.0 ))){
			SplashList["Play"].move(sf::Vector2f( 0.0, -50.0 ));
		}
		else{ finished++; }

		if(!(SplashList["Leaderbord"].getPosition()==sf::Vector2f( 710.0, 500.0 ))){
			SplashList["Leaderbord"].move(sf::Vector2f( 0.0, -50.0 ));
		}
		else{ finished++; }

		if(!(SplashList["Quit"].getPosition()==sf::Vector2f( 710.0, 600.0 ))){
			SplashList["Quit"].move(sf::Vector2f( 0.0, -50.0 ));
		}
		else{ finished++; }
		
		if(finished==3){
			return true;
		}
		return false;
	}
	
	void render(){
        window.clear();
		for(auto & picture: SplashList){
			picture.second.draw( window );
        }
        window.display();
    }

};
#endif