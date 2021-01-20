#ifndef _GAMECONTROL_HPP
#define _GAMECONTROL_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <functional>
#include "Objects.hpp"
#include "Enemy.hpp"

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
class gameControl{
private:
	sf::RenderWindow & window;
    sf::Vector2f direction = sf::Vector2f(0.0, -2.0);
    playerStats stats;
    sf::Time updateTime = sf::milliseconds(20);
    sf::Clock clock;
    sf::Time elapsedTime;
	bool playerdead;
    int elapsed =0;
    displayText boardText = displayText(stats);
    int waveStrength = 10;
    bool crateSpawn = false;
    int waveCount = 1;
	bool resetcrate =true;
	std::string return_statement="";

    std::map<std::string, rectangle> borderList = {
        {"wall_top",    rectangle( sf::Vector2f( 394.0, 0.0 ),   sf::Color(0,0,0), sf::Vector2f( 1142.0, 1.0 ) )},
        {"wall_bottom", rectangle( sf::Vector2f( 384.0, 865.0 ), sf::Color(0,0,0), sf::Vector2f( 1152.0, 1.0 ) )},
        {"wall_right",  rectangle( sf::Vector2f( 1536.0, 0.0 ),  sf::Color(255,255,255), sf::Vector2f( 10.0, 1080.0 ) )},
        {"wall_left",   rectangle( sf::Vector2f( 384.0, 0.0 ),   sf::Color(255,255,255), sf::Vector2f( 10.0, 1080.0 ) )}
    };
    std::map<std::string, picture> objectList = {
        {"Ship", picture(sf::Vector2f( 945.0, 750.0 ), stats.ship, stats.size)},
        {"Background1", picture(sf::Vector2f( 394.0, 0.0 ), "images/space.jpg", sf::Vector2f( 1142.0, 866.0 ))},
		{"Background2", picture(sf::Vector2f( 394.0, -865.0 ), "images/space.jpg", sf::Vector2f( 1142.0, 866.0 ))},
        {"Crate", picture(sf::Vector2f( 3000.0, 300.0 ), "images/Crate.jpg", sf::Vector2f( 40.0, 40.0 ))} 
    };

    std::vector<enemy*> enemyList = {
        new enemy0() //extra enemy in list
    };

    std::vector<picture> enemyBulletList = {};

    action actions[6] = {
        action( sf::Keyboard::Left,  [&](){ 
            objectList["Ship"].move( sf::Vector2f( -stats.shipSpeed, 0.0 )); 
            if(objectList["Ship"].collision( borderList["wall_left"] )){
                objectList["Ship"].move( sf::Vector2f( stats.shipSpeed, 0.0 )); 
            }
        }),
        action( sf::Keyboard::Right, [&](){ 
            objectList["Ship"].move( sf::Vector2f( stats.shipSpeed, 0.0 ));
            if(objectList["Ship"].collision( borderList["wall_right"] )){
                objectList["Ship"].move( sf::Vector2f( -stats.shipSpeed,  0.0 )); 
            } 
        }),
        action( sf::Keyboard::Up,    [&](){ 
            objectList["Ship"].move( sf::Vector2f( 0.0, -stats.shipSpeed )); 
            if(objectList["Ship"].collision( borderList["wall_top"] )){
                objectList["Ship"].move( sf::Vector2f( 0.0, stats.shipSpeed )); 
            }
        }),
        action( sf::Keyboard::Down,  [&](){ 
            objectList["Ship"].move( sf::Vector2f( 0.0, stats.shipSpeed )); 
            if(objectList["Ship"].collision( borderList["wall_bottom"] )){
                objectList["Ship"].move( sf::Vector2f( 0.0, -stats.shipSpeed )); 
            }
        }),
        action( sf::Keyboard::Space,  [&](){ 
            elapsedTime = clock.getElapsedTime();
            elapsed = elapsedTime.asMilliseconds();  //int
            if(elapsed > stats.reloadTime){
                std::string bullet = "bullet"+std::to_string(stats.bulletCount);
                picture tmp = picture(objectList["Ship"].getPosition(), stats.lazerColor, sf::Vector2f(10.0, 25.0), "bullet" );
                objectList.insert({bullet,tmp});
                objectList[bullet].move(stats.bulletAlignment);
                stats.bulletCount +=1;

                clock.restart();
            }


        }),
        action( sf::Keyboard::Escape, [&](){
            sf::Event event;
            picture tmp_pause = picture(sf::Vector2f( 0.0, 0.0 ), "images/paused.png", sf::Vector2f( 1920.0, 875.0 ));
			picture tmp_Quit_Button = picture(sf::Vector2f( 710.0, 700.0 ), "images/Quit.png", sf::Vector2f( 500.0, 70.0 ));
            objectList.insert({"pause",tmp_pause});
			objectList.insert({"quit_GameButton",tmp_Quit_Button});
            for(;;){
				sf::sleep( sf::milliseconds(10));
				render();
                window.pollEvent(event);
				for( auto & action : ButtonClick ){
					action();
				}
				if(event.type == sf::Event::MouseMoved){
					if(select_object(sf::Mouse::getPosition( window ), objectList["quit_GameButton"])){
						objectList["quit_GameButton"].change_image("images/Quit_hover.png");
					}
					else{
						objectList["quit_GameButton"].change_image("images/Quit.png");
					}
				}
                if (event.type == sf::Event::KeyPressed && !(sf::Mouse::Left)) {
					objectList.erase("pause");
					objectList.erase("quit_GameButton");
                    break;
                }
				if(!(return_statement=="")){
					break;
				}
            }
            
        })
	};
	action ButtonClick[1] = {
		action( sf::Mouse::Left,  [&](){
			for(auto & picture: objectList){
				if(select_object( sf::Mouse::getPosition( window ), picture.second )){
					if(picture.first=="quit_GameButton"){
						return_statement = "MENU";
					}
				}
			}
			for(;;){
				sf::Event event;
                window.pollEvent(event);
                if (event.type == sf::Event::MouseButtonReleased) {
                    break;
                }
            }
		})
    };

public:
	gameControl(auto& window):
        window( window )
    {};
    std::string loop(){
        picture tmp = picture(sf::Vector2f( 0.0, 0.0 ), "images/getReady.png", sf::Vector2f( 1920.0, 875.0 ));
        objectList.insert({"pause",tmp});
        render();
        sf::sleep( sf::milliseconds(2000));
        objectList.erase("pause");
        sf::Time lag = sf::milliseconds(0);
        sf::Clock clock;
		clock.restart();
		return_statement="";
        while (true){
            sf::sleep( sf::milliseconds(20));

            sf::Time elapsed = clock.getElapsedTime();
            lag += elapsed;
            processInput();
			if(return_statement=="MENU"){
				resetall();
				return return_statement;
			}
			if(playerdead){
				resetall();
				playerdead=false;
				return "GAMEOVER";
			}
            while (lag >= updateTime){
				update();
				lag -= updateTime;
            }
			resetcrate = true;
            render();
            clock.restart();
        }
    }
	void resetall(){
		objectList.erase("pause");
		objectList.erase("quit_GameButton");
		stats.ResetStats();
		waveCount=0;
		waveStrength=10;
		enemyList.clear();
		enemyList.push_back(new enemy0());
		enemyBulletList.clear();
		resetcrate = false;
		window.clear();
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
        std::vector<int> bulletDelete = {};
        int bulletIndex = 0;
		objectList["Background1"].move( sf::Vector2f( 0.0, 1.0 ));
		objectList["Background2"].move( sf::Vector2f( 0.0, 1.0 ));
		if(objectList["Background1"].getYPosition()==368){
			objectList["Background1"].jump( sf::Vector2f( 0.0, 394.0));
		}
		if(objectList["Background2"].getYPosition()==368){
			objectList["Background2"].jump( sf::Vector2f(  0.0, 394.0));
		}
		if(stats.getPlayerHealth()<=0){
			playerdead = true;
			return;
		}
        for(auto & picture: objectList){
            if(picture.second.getType() == "bullet"){
                picture.second.move(sf::Vector2f{0.0, -float(stats.bulletSpeed)});
                if(picture.second.collision( borderList["wall_top"] )){ 
                    toDelete.push_back(picture.first);
                }
            }

        }
        bool enemy20spawned = false;
        for(auto & enemy: enemyList){
            enemy->move();
            if(enemy->shoot()){
                sf::Vector2f position = enemy->getTexture().getPosition();
                position.x += 25;
                position.y += 40;
                picture tmp = picture(position, "images/lazer_green.png", sf::Vector2f(10.0, 25.0), "enemyBullet1" );
                if(enemy->getStrength() == 20){
                    tmp = picture(position, "images/Lazer_purple.png", sf::Vector2f(5.0, 15.0), "enemyBullet1" );
                }
                if(enemy->getStrength() == 5){
                    tmp = picture(position, "images/Bullet_blue.png", sf::Vector2f(15.0, 15.0), "enemyBullet1" );
                }
                enemyBulletList.push_back(tmp);
            }
            if(enemy->getStrength() == 20){
                enemy20spawned = true;
                sf::Vector2f position = enemy->getTexture().getPosition();
                position.x += -10;
                position.y += -10;
                std::string name = "portal"+std::to_string(position.y+position.x);

                if(enemy->summon_Portal()){
                    picture tmp = picture(position, "images/Portal.png", sf::Vector2f(70.0, 70.0), "portal");
                    objectList.insert({name,tmp});
                }

                else{
                    for(auto & picture: objectList){
                        if(picture.second.getType() == "portal"){
                            toDelete.push_back(picture.first);
                        }
                    }
                }
            } 
        }
        if(!enemy20spawned){
            for(auto & picture: objectList){
                if(picture.second.getType() == "portal"){
                    toDelete.push_back(picture.first);
                }
            }
        }
        if(enemyList.size() <= 1){
            generateWave(waveStrength, enemyList);
			if(resetcrate){
				if(crateSpawn){
					objectList["Crate"].move(sf::Vector2f(-2000.0 , 0.0));
					crateSpawn = false;
					waveCount++;
					stats.waveCount = waveCount;
				}
				waveStrength += 5;
				crateSpawn = true;
			}
        }
        if(objectList["Ship"].collision( objectList["Crate"] )){  //Crate test
            stats.upgrade();   //Crate test
            objectList["Crate"].move(sf::Vector2f(2000.0 , 0.0));
            
        }

        for(unsigned int i = 0; i<= enemyList.size()-1; i++){
            auto tmpTexture = enemyList[i]->getTexture();
            for(auto & picture: objectList){
                if(picture.second.getType() == "bullet"){
                    if(picture.second.collision( tmpTexture)){
                        enemyList[i]->setHealth(stats.bulletDamage);
                        toDelete.push_back(picture.first);
                        if(enemyList[i]->getHealth() <= 0){
                            stats.playerScore+= enemyList[i]->getStrength();
                            enemyList.erase(enemyList.begin() +i);
                            stats.enemyKilled+=1;
                        }
                    }
                }
            }
        }

        for(auto & bullet: enemyBulletList){
            bullet.move(sf::Vector2f{ 0.0, 10.0 });
            if(bullet.collision( objectList["Ship"])){
                stats.health -= 1;
                bulletDelete.push_back(bulletIndex); 
                
            }
            if(bullet.getPosition().y > 900){
                bulletDelete.push_back(bulletIndex); 
            }
            bulletIndex++;
        }
        
        for(auto & picture: toDelete){
            objectList.erase(picture);
        }

        for(auto i: bulletDelete){
            enemyBulletList.erase(enemyBulletList.begin() + i); //kijk later na
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
        for(auto & enemy: enemyList){
            enemy->draw( window );
        }

        for(auto & bullet: enemyBulletList){
            bullet.draw( window );
        }

        boardText.drawAll(window);

        window.display();
    }

    void updateStats( playerStats newStats ){
        stats = newStats;
        objectList["Ship"] = picture(sf::Vector2f( 945.0, 750.0 ), stats.ship, stats.size);
    }
};


#endif