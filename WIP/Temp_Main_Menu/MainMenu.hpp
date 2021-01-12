#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameControl.hpp"
#include "Objects.hpp"

class MainMenu{
private:
	
	sf::RenderWindow MainWindow{ sf::VideoMode{ 1920, 900 },"Totaly Original Space Shooter" };
	
	std::map<std::string, picture> MenuList = {
        {"Background",picture(sf::Vector2f{ 0.0, 0.0 }, "images/Background.png", sf::Vector2f( 1920, 900 ))},
		{"Logo",picture(sf::Vector2f( 600.0, 5.0 ), "images/Logo.png", sf::Vector2f( 600.0, 300.0 ))},
		{"Start_GameButton",picture(sf::Vector2f{ 710.0, 400.0 }, "images/Play.png", sf::Vector2f( 500.0, 70.0 ))},
		{"Leaderbord_GameButton",picture(sf::Vector2f{ 710.0, 500.0 }, "images/Leaderboard.png", sf::Vector2f( 500.0, 70.0 ))},
		{"Quit_GameButton",picture(sf::Vector2f{ 710.0, 600.0 }, "images/Quit.png", sf::Vector2f( 500.0, 70.0 ))}
    };
	
	action ButtonClick[1] = {
		action( sf::Mouse::Left,  [&](){
			for(auto & picture: MenuList){
				if(select_object( sf::Mouse::getPosition( MainWindow ), picture.second )){
					std::cout<< "anker" << std::endl;
				}
			}
			for(;;){
				sf::Event event;
				sf::sleep( sf::milliseconds(5));
                MainWindow.pollEvent(event);
                if (event.type == sf::Event::MouseButtonReleased) {
					sf::sleep( sf::milliseconds(150));
                    break;
                }
            }
		})
	};
	
public:
	void MainMenuLoop(){
		for(;;){
			sf::sleep( sf::milliseconds(20));
			processInput();
			render();
		}
	}
	
    void processInput(){
        sf::Event event;
        while( MainWindow.pollEvent(event) ){
            if( event.type == sf::Event::Closed ){
                MainWindow.close();
            }
        }
		for( auto & action : ButtonClick ){
			action();
		}
	}

    void render(){
        MainWindow.clear(sf::Color::White);
		for(auto & picture: MenuList){
            picture.second.draw( MainWindow );
        }
        MainWindow.display();
    }
	bool select_object( sf::Vector2i MousePosition, picture object ){
		auto posFloat = static_cast<sf::Vector2f>(MousePosition);
		if(object.clicked( posFloat )){
			return true;
		}
		return false;
	}
};