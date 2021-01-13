#ifndef _SPLASHSCREEN_HPP
#define _SPLASHSCREEN_HPP
#include <iostream>
#include <SFML/Graphics.hpp>

class SplashClass{
private:
	sf::RenderWindow & window;

	 std::map<std::string, rectangle> borderList = {
        {"Background",  rectangle{ sf::Vector2f{ 1536.0, 0.0 }, sf::Color(255,255,255), sf::Vector2f{ 10.0, 1080.0  } }},

    };
	std::map<std::string, picture> objectList = {
        {"Logo",picture(sf::Vector2f{ 500.0, 500.0 }, "images/ship1.png", sf::Vector2f( 80.0f, 80.0f ))}
    };
	
	//sf::RenderWindow window{ sf::VideoMode{ 1920, 900 },"SFML window" };
   
public:
	SplashClass(auto& window):
        window( window )
    {}
	bool SplashShow(){
		
		return true;
	}
};
#endif
