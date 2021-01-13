#ifndef _LEADERBOARD_HPP
#define _LEADERBOARD_HPP
#include <iostream>
#include <SFML/Graphics.hpp>
class LeaderBoardClass{
private:
	bool return_statement;
	sf::RenderWindow & window;
	std::map<std::string, picture> BoardList = {
        {"Background",picture(sf::Vector2f{ 0.0, 0.0 }, "images/Background.png", sf::Vector2f( 1920, 900 ))},
		{"Logo",picture(sf::Vector2f( 600.0, 5.0 ), "images/Logo.png", sf::Vector2f( 600.0, 300.0 ))},
		{"Quit_GameButton",picture(sf::Vector2f{0.0,600.0}, "images/Quit.png", sf::Vector2f( 500.0, 70.0 ))}
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
				sf::sleep( sf::milliseconds(5));
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
	
	bool LeaderBoardLoop(){
		return_statement = 0;
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
	void processInput(){
        sf::Event event;
        while( window.pollEvent(event) ){
            if( event.type == sf::Event::Closed ){
                window.close();
            }
        }
		for( auto & action : ButtonClick ){
			action();
		}
	}

    void render(){
        window.clear(sf::Color::White);
		for(auto & picture: BoardList){
            picture.second.draw( window );
        }
        window.display();
    }
	bool select_object( sf::Vector2i MousePosition, picture object ){
		auto posFloat = static_cast<sf::Vector2f>(MousePosition);
		if(object.clicked( posFloat )){
			return true;
		}
		return false;
	}
};
#endif