#ifndef _SPLASHSCREEN_HPP
#define _SPLASHSCREEN_HPP
#include <iostream>
#include <SFML/Graphics.hpp>

class SplashClass{
private:
	sf::RenderWindow & window;
	sf::Clock clock;
	sf::Time timer;
	float elapsed;
	int displaytime = 5;
	std::map<std::string, picture> SplashList = {
        {"Background",picture(sf::Vector2f{ 0.0, 0.0 }, "images/Background.png", sf::Vector2f( 1920, 900 ))},
		{"Splash",picture(sf::Vector2f( 600.0, 300.0 ), "images/Logo.png", sf::Vector2f( 600.0, 300.0 ))}
    };
   
public:
	SplashClass(auto& window):
        window( window )
    {}
	bool SplashShow(){
		
		clock.restart();
		while(displaytime>elapsed){
			timer = clock.getElapsedTime();
			elapsed= timer.asSeconds();
			render();
			sf::sleep( sf::milliseconds(20));
		}
		return true;
		
	}
	
	void render(){
        window.clear(sf::Color::White);
		for(auto & picture: SplashList){
			picture.second.draw( window );
        }
        window.display();
    }
};
#endif
