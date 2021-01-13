#ifndef _GAMECONTROL_HPP
#define _GAMECONTROL_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <functional>
#include "Objects.hpp"






//Action class which provides usefull functions
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
	action(
        sf::Mouse::Button button,
        std::function< void() > work
    ) :
        condition(
            [ button ]()->bool { return sf::Mouse::isButtonPressed( button ); }
        ),
        work(work)
    {}
	
	void operator()(){
		if( condition() ){
			work();
		}
	}
	
};

//Class which provides the central game loop
class gameLoop{
private:
	sf::RenderWindow & window;
    sf::Vector2f direction = sf::Vector2f(0.0, -2.0);
    playerStats stats;
    sf::Time updateTime = sf::milliseconds(20);
    sf::Clock clock;
    sf::Time elapsedTime;
    int elapsed =0;
    displayText boardText = displayText(stats);

    std::map<std::string, rectangle> borderList = {
        {"wall_top",    rectangle( sf::Vector2f( 394.0, 0.0 ),   sf::Color(0,0,0), sf::Vector2f( 1142.0, 1.0 ) )},
        {"wall_bottom", rectangle( sf::Vector2f( 384.0, 865.0 ), sf::Color(0,0,0), sf::Vector2f( 1152.0, 1.0 ) )},
        {"wall_right",  rectangle( sf::Vector2f( 1536.0, 0.0 ),  sf::Color(255,255,255), sf::Vector2f( 10.0, 1080.0 ) )},
        {"wall_left",   rectangle( sf::Vector2f( 384.0, 0.0 ),   sf::Color(255,255,255), sf::Vector2f( 10.0, 1080.0 ) )}
    };
    std::map<std::string, picture> objectList = {
        {"ship", picture(sf::Vector2f( 945.0, 750.0 ), "images/Ship1.png", sf::Vector2f( 50.0f, 70.0f ))},
        {"background", picture(sf::Vector2f( 394.0, 0.0 ), "images/space.jpg", sf::Vector2f( 1142.0, 865.0 ))}
    };

    action actions[6] = {
        action( sf::Keyboard::Left,  [&](){ 
            objectList["ship"].move( sf::Vector2f( -stats.shipSpeed, 0.0 )); 
            if(objectList["ship"].collision( borderList["wall_left"] )){
                objectList["ship"].move( sf::Vector2f( stats.shipSpeed, 0.0 )); 
            }
        }),
        action( sf::Keyboard::Right, [&](){ 
            objectList["ship"].move( sf::Vector2f( stats.shipSpeed, 0.0 ));
            if(objectList["ship"].collision( borderList["wall_right"] )){
                objectList["ship"].move( sf::Vector2f( -stats.shipSpeed,  0.0 )); 
            } 
        }),
        action( sf::Keyboard::Up,    [&](){ 
            objectList["ship"].move( sf::Vector2f( 0.0, -stats.shipSpeed )); 
            if(objectList["ship"].collision( borderList["wall_top"] )){
                objectList["ship"].move( sf::Vector2f( 0.0, stats.shipSpeed )); 
            }
        }),
        action( sf::Keyboard::Down,  [&](){ 
            objectList["ship"].move( sf::Vector2f( 0.0, stats.shipSpeed )); 
            if(objectList["ship"].collision( borderList["wall_bottom"] )){
                objectList["ship"].move( sf::Vector2f( 0.0, -stats.shipSpeed )); 
            }
        }),
        action( sf::Keyboard::Space,  [&](){ 
            elapsedTime = clock.getElapsedTime();
            elapsed = elapsedTime.asMilliseconds();  //int

            if(elapsed > stats.reloadTime){
                std::string bullet = "bullet"+std::to_string(stats.bulletCount);
                picture tmp = picture(objectList["ship"].getPosition(), "images/lazer.png", sf::Vector2f( 30.0, 30.0 ), "bullet" );
                objectList.insert({bullet,tmp});
                objectList[bullet].move(sf::Vector2f{11.0, -8.0});
                stats.bulletCount +=1;

                clock.restart();
            }
        }),
        action( sf::Keyboard::Escape, [&](){
            sf::Event event;
            picture tmp = picture(sf::Vector2f( 0.0, 0.0 ), "images/paused.png", sf::Vector2f( 1920.0, 875.0 ));
            objectList.insert({"pause",tmp});
            render();
            for(;;){
                window.pollEvent(event);
                if (event.type == sf::Event::KeyPressed) {
                    break;
                }
            }
            objectList.erase("pause");

            
        })
    };

public:
	gameLoop(auto& window):
        window( window )
    {};
    void loop(){
        sf::Time lag = sf::milliseconds(0);
        sf::Clock clock;

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
        std::vector<std::string> toDelete = {};
        for(auto & picture: objectList){
            if(picture.second.getType() == "bullet"){
                picture.second.move(sf::Vector2f{0.0, -float(stats.bulletSpeed)});
                if(picture.second.collision( borderList["wall_top"] )){ 
                    toDelete.push_back(picture.first);
                }
            }
        }
        for(auto & picture: toDelete){
            objectList.erase(picture);
        }
        boardText.update(stats);
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
        
        boardText.drawAll(window);

        window.display();
    }
};


#endif
