#ifndef _GAMECONTROL_HPP
#define _GAMECONTROL_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <functional>
#include "Objects.hpp"

class action {
private:
	std::function< bool() > condition;
	std::function< void() > work;
public:
	action(
	   std::function< bool() > condition, 
	   std::function< void() > work
	) : condition( condition ), 
		work( work ) 
	{}

	action(
		sf::Keyboard::Key key,
		std::function< void() > work
	) :
		condition(
			[ key ]()->bool { return sf::Keyboard::isKeyPressed( key ); }
		),
		work(work)
	{}

	action(
		std::function< void() > work
	) :
		condition(
			[]()->bool { return true; }
		),
		work(work)
	{}

	void operator()(){
		if( condition() ){
			work();
		}
	}
	action(
        sf::Mouse::Button button,
        std::function< void() > work
    ) :
        condition(
            [ button ]()->bool { return sf::Mouse::isButtonPressed( button ); }
        ),
        work(work)
    {}
};

class gameLoop{
private:

    sf::Time updateTime = sf::milliseconds(20);
    std::map<std::string, picture> objectList = {
        {"ship",picture(sf::Vector2f{ 500.0, 500.0 }, "images/ship1.png", sf::Vector2f( 80.0f, 80.0f ))}
    };
    std::map<std::string, rectangle> borderList = {
        {"wall_right",  rectangle{ sf::Vector2f{ 1536.0, 0.0 }, sf::Color(255,255,255), sf::Vector2f{ 10.0, 1080.0  } }},
        {"wall_left",   rectangle{ sf::Vector2f{ 384.0, 0.0 }, sf::Color(255,255,255), sf::Vector2f{ 10.0, 1080.0 } }},
        {"wall_top",    rectangle{ sf::Vector2f{ 384.0, 0.0 }, sf::Color(255,255,255), sf::Vector2f{ 1152.0, 10.0 } }},
        {"wall_bottom", rectangle{ sf::Vector2f{ 384.0, 865.0 }, sf::Color(255,255,255), sf::Vector2f{ 1152.0, 10.0 } }}
    };
    
    sf::RenderWindow window{ sf::VideoMode{ 1920, 900 },"SFML window" };

    action actions[4] = {
        action( sf::Keyboard::Left,  [&](){ objectList["ship"].move( sf::Vector2f( -10.0,  0.0 )); }),
        action( sf::Keyboard::Right, [&](){ objectList["ship"].move( sf::Vector2f( +10.0,  0.0 )); }),
        action( sf::Keyboard::Up,    [&](){ objectList["ship"].move( sf::Vector2f(  0.0, -10.0 )); }),
        action( sf::Keyboard::Down,  [&](){ objectList["ship"].move( sf::Vector2f(  0.0, +10.0 )); })
    };

public:
    sf::Time lag = sf::milliseconds(0);
    sf::Clock clock;

    void loop(){
        while (true){
            sf::sleep( sf::milliseconds(20));

            sf::Time elapsed = clock.getElapsedTime();
            lag += elapsed;

            processInput();
            while (lag >= updateTime){
                update();
                lag -= updateTime;
            }

            render();
            clock.restart();
        }
    }

    void processInput(){
        sf::Event event;
        while( window.pollEvent(event) ){
            if( event.type == sf::Event::Closed ){
                window.close();
            }
        }
        for( auto & action : actions ){
            action();
        }
    }

    void update(){
        return;
    }

    void render(){
        window.clear();

        for(auto & picture: objectList){
            picture.second.draw( window );
        }
        for(auto & border: borderList){
            border.second.draw( window );
        }

        window.display();
    }
};


#endif