#ifndef _GAMECONTROL_HPP
#define _GAMECONTROL_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <functional>
#include "Objects.hpp"
#include "Enemy.hpp"
#include "Upgrade.hpp"

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
    int elapsed =0;
    displayText boardText = displayText(stats);
    int waveStrength = 55;
    bool crateSpawn = false;
    int waveCount = 10;
    int invincibilityCooldown = 1000;
    int shipDamagedCooldown = 0;
    bool resetcrate =true;
    std::string return_statement="";
    bool playerdead = false;
    bool spawnWave = true;
    int traderTimer = 5000;
    bool crateSpawned = false;
    int upgradeListIndex = 0;
    int crates = 3;
    sf::SoundBuffer PlayerShootBuffer;
	sf::SoundBuffer AlienShootBuffer;
	sf::SoundBuffer AlienHitBuffer;
	sf::SoundBuffer PlayerHitBuffer;
	sf::Sound PlayerShootSound;
	sf::Sound AlienShootSound;
	sf::Sound AlienHitSound;
	sf::Sound PlayerHitSound;
	sf::SoundBuffer BossScytheBuffer;
	sf::SoundBuffer BossScytheBigBuffer;
	sf::Sound BossScytheBigSound;
	sf::Sound BossScytheSound;
	sf::SoundBuffer ShieldBuffer;
	sf::Sound ShieldSound;
	bool first_time = true;
		
		

    std::map<std::string, rectangle> borderList = {
        {"wall_top",    rectangle( sf::Vector2f( 394.0, 0.0 ),   sf::Color(0,0,0), sf::Vector2f( 1142.0, 1.0 ) )},
        {"wall_bottom", rectangle( sf::Vector2f( 384.0, 875.0 ), sf::Color(0,0,0), sf::Vector2f( 1152.0, 1.0 ) )},
        {"wall_right",  rectangle( sf::Vector2f( 1536.0, 0.0 ),  sf::Color(255,255,255), sf::Vector2f( 10.0, 1080.0 ) )},
        {"wall_left",   rectangle( sf::Vector2f( 384.0, 0.0 ),   sf::Color(255,255,255), sf::Vector2f( 10.0, 1080.0 ) )}
    };
    std::map<std::string, picture> objectList = {
        {"Ship", picture(sf::Vector2f( 945.0, 750.0 ), stats.ship, stats.size)},
        {"Background1", picture(sf::Vector2f( 394.0, 0.0 ), "images/space.jpg", sf::Vector2f( 1142.0, 866.0 ))},
        {"Background2", picture(sf::Vector2f( 394.0, -866.0 ), "images/space.jpg", sf::Vector2f( 1142.0, 866.0 ))}
        //{"Crate", picture(sf::Vector2f( 3000.0, 300.0 ), "images/Crate.jpg", sf::Vector2f( 40.0, 40.0 ))} 
    };

    std::vector<enemy*> enemyList = {
        new enemy0() //extra enemy in list
    };

    std::vector<std::pair<picture, sf::Vector2f>> enemyBulletList = {};

    std::vector<upgrade*> upgradeList = {};

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
                PlayerShootSound.play();
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
        bufferloader();
		first_time = true;
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
				return return_statement;
			}
			if(playerdead){
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

    void bufferloader(){
		PlayerShootBuffer.loadFromFile("sounds/player_laser.wav");
		PlayerShootSound.setBuffer(PlayerShootBuffer);
		AlienShootBuffer.loadFromFile("sounds/enemy_shoot.wav");
		AlienShootSound.setBuffer(AlienShootBuffer);
		PlayerHitBuffer.loadFromFile("sounds/player_hit.wav");
		PlayerHitSound.setBuffer(PlayerHitBuffer);
		AlienHitBuffer.loadFromFile("sounds/enemy_hit.wav");
		AlienHitSound.setBuffer(AlienHitBuffer);
		BossScytheBuffer.loadFromFile("sounds/scythe.wav");
		BossScytheSound.setBuffer(BossScytheBuffer);
		BossScytheBigBuffer.loadFromFile("sounds/big_scythe.wav");
		BossScytheBigSound.setBuffer(BossScytheBigBuffer);
		ShieldBuffer.loadFromFile("sounds/scythe.wav");
		ShieldSound.setBuffer(ShieldBuffer);
	}
    void resetall(){
        std::vector<std::string> toDelete = {};
		objectList.erase("pause");
		objectList.erase("quit_GameButton");
        objectList.erase("trader");
		stats.ResetStats();
        upgradeList.clear();
        spawnWave = true;
        crateSpawned = false;
		waveCount=1;
		waveStrength=45;
		enemyList.clear();
		enemyList.push_back(new enemy0());
		enemyBulletList.clear();
		resetcrate = false;
        for(auto & picture: objectList){
            if(picture.second.getType() == "bullet"){
                toDelete.push_back(picture.first);
            }
        }
        for(auto & picture: toDelete){
            objectList.erase(picture);
        }
        
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
    void BackGroundPicker(int mapcount){
		if(1){
			objectList["Background1"].move( sf::Vector2f( 0.0, 1.0 ));
			objectList["Background2"].move( sf::Vector2f( 0.0, 1.0 ));
		}
		else if (2){
			if (first_time){
				objectList["Background1"].jump( sf::Vector2f( 394, 0.0));
				objectList["Background2"].jump( sf::Vector2f(  394, -865.0));
				first_time = false;
			}
			objectList["Background1"].move( sf::Vector2f( 0.0, 0.001 ));
			objectList["Background2"].move( sf::Vector2f( 0.0, 0.001 ));
		
		}
		if(objectList["Background1"].getPosition().y>=866){
			objectList["Background1"].jump( sf::Vector2f( 394, -866.0));
			}
		if(objectList["Background2"].getPosition().y>=866){
			objectList["Background2"].jump( sf::Vector2f(  394, -866.0));
		}
			
			
	}

    void update(){
        srand(time(0));
        std::vector<std::string> toDelete = {};
        std::vector<int> bulletDelete = {};
        std::vector<int> upgradeDelete = {};
        int bulletIndex = 0;
        if(waveStrength>55){
			objectList["Background2"].change_image("images/space_icy_planet.jpg");
			objectList["Background1"].change_image("images/space_icy.png");
			BackGroundPicker(2);
		}
		else{
			BackGroundPicker(1);
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
        bool spawnMinions = false;
        for(auto & enemy: enemyList){
            enemy->move();
            if(enemy->shoot()){
                sf::Vector2f position = enemy->getTexture().getPosition();
                position.x += 25;
                position.y += 37;
                picture tmp = picture(position, "images/lazer_green.png", sf::Vector2f(10.0, 25.0), "enemyBullet1" );
				if(enemy->getStrength() == 1){
					AlienShootSound.play();
				}
                else if(enemy->getStrength() == 2){
					AlienShootSound.play();
                    tmp = picture(position, "images/Lazer_red.png", sf::Vector2f(5.0, 15.0), "enemyBullet1" );
                }
                else if(enemy->getStrength() == 3){
					AlienShootSound.play();
                    tmp = picture(position, "images/Lazer_orange.png", sf::Vector2f(25.0, 10.0), "enemyBullet1" );
                }
                else if(enemy->getStrength() == 5 || enemy->getStrength() == 15){
					AlienShootSound.play();
                    tmp = picture(position, "images/Bullet_blue.png", sf::Vector2f(15.0, 15.0), "enemyBullet1" );
                }
                else if(enemy->getStrength() == 20){
					AlienShootSound.play();
                    tmp = picture(position, "images/Lazer_purple.png", sf::Vector2f(5.0, 15.0), "enemyBullet1" );
                }
                else if(enemy->getStrength() == 10){
					AlienShootSound.play();
                    tmp = picture(position, "images/Lazer_orange.png", sf::Vector2f(25.0, 10.0), "diagonalOrange" );
                    if(enemy->getTrajectory().x > 0){
                        tmp.rotate(45.0);
                    }
                    else if(enemy->getTrajectory().x < 0){
                        tmp.rotate(315.0);
                    }
                }
                else if(enemy->getStrength() == 30){
					AlienShootSound.play();
                    tmp = picture(position, "images/Lazer_purple.png", sf::Vector2f(5.0, 15.0), "enemyBullet1" );
                    if(enemy->getTrajectory().x < 0){
                        tmp.rotate(45.0);
                    }
                    else if(enemy->getTrajectory().x > 0){
                        tmp.rotate(315.0);
                    }
                }
                else if(enemy->getStrength() == 200){
                    std::vector<int> randomNumber = {1,1,1,1,1,1,2,2,2,2,2,2,3,4,4,4};
                    int attack = randomNumber[rand()%16]; 
                    position.y += 30;
                    position.x += 60;
                    if(attack == 1){
						BossScytheSound.play();
                        tmp = picture(position, "images/Scythe_left.png", sf::Vector2f(80.0, 80.0), "enemyBullet1" );
                    }
                    else if(attack == 2){
						BossScytheSound.play();
                        position.x += 156;
                        tmp = picture(position, "images/Scythe_right.png", sf::Vector2f(80.0, 80.0), "enemyBullet1" );
                    }
                    else if(attack == 3){
                        spawnMinions = true;
                    }
                    else if(attack == 4){
						BossScytheBigSound.play();
                        position.x += 100;
                        tmp = picture(position, "images/Scythe_right.png", sf::Vector2f(120.0, 120.0), "BossScythe" );
                    }
                }
                if(!spawnMinions){
                    enemyBulletList.push_back(std::pair<picture, sf::Vector2f>(tmp, enemy->getTrajectory()));
                }
            }
            if(enemy->getStrength() == 20 || enemy->getStrength() == 30 ){
                enemy20spawned = true;
                sf::Vector2f position = enemy->getTexture().getPosition();
                position.x += -10;
                position.y += -10;
                std::string name = "portal"+std::to_string(position.y+position.x);


                if(enemy->summon_Portal()){
                    picture tmp = picture(position, "images/Portal.png", sf::Vector2f(70.0, 70.0), "portal");
                    if(enemy->getStrength() ==  30){
                        tmp.move({7.5, 0.0});
                    }
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
        if(spawnMinions){
            spawnMinions = false;
            enemyList.push_back(new enemy2());
            enemyList.push_back(new enemy2());
        }

        if(stats.waveCount %3 == 0.0 && stats.waveCount > 1 && enemyList.size() <= 1){
            auto crate1 = spawnUpgrade({760.0 ,350.0}, stats, rand()); 
            auto crate2 = spawnUpgrade({960.0 ,350.0}, stats, rand()); 
            auto crate3 = spawnUpgrade({1160.0 ,350.0}, stats, rand());
            

            spawnWave = false;
            bool up = false;
            objectList.insert({"trader", picture(sf::Vector2f( 400.0 , 180.0) , "images/Trader.png", sf::Vector2f(200.0, 100.0))});
            
            
            if(objectList["trader"].getPosition().x < 860){
                enemyBulletList.clear();
                for(auto bullet : objectList){
                    if(bullet.second.getType() == "bullet"){
                        toDelete.push_back(bullet.first);
                    }
                }
                for(auto & picture: toDelete){
                    objectList.erase(picture);
                }
                if(stats.ship == "images/Small_Ship.png"){
                    sf::Vector2f portalPosition = objectList["Ship"].getPosition();
                    portalPosition.x -= 5;
                    objectList.insert({"Portal" ,picture(portalPosition, "images/Portal.png", sf::Vector2f(50.0, 70.0))});

                }
                else if(stats.ship == "images/Big_Ship.png"){
                    objectList.insert({"Portal" ,picture(objectList["Ship"].getPosition(), "images/Portal.png", sf::Vector2f(70.0, 80.0))});
                }
                else{
                    objectList.insert({"Portal" ,picture(objectList["Ship"].getPosition(), "images/Portal.png", sf::Vector2f(70.0, 80.0))});
                }
                
                while(objectList["trader"].getPosition().x < 860){
                    if(objectList["trader"].getPosition().x == 610){
                        objectList["Ship"].jump({ 945.0, 750.0 });
                        objectList["Portal"].jump({ 940.0, 750.0 });
                    }
                    objectList["trader"].move({3.0, 0.0});
                    if(up){
                        objectList["trader"].move({0.0, 1.0});
                        up = false;
                    }
                    else{
                        objectList["trader"].move({0.0, -1.0});
                        up = true;
                    }
                    render();
                }
                toDelete.push_back("Portal");
            }
            
            if(!crateSpawned){               
                upgradeList.push_back(crate1);                
                upgradeList.push_back(crate2);               
                upgradeList.push_back(crate3);
                crateSpawned = true;
            }
        
            if(traderTimer <= 0){
                upgradeList.clear();
                while(objectList["trader"].getPosition().x < 1336){
                    objectList["trader"].move({3.0, 0.0});
                    if(up){
                        objectList["trader"].move({0.0, 1.0});
                        up = false;
                    }
                    else{
                        objectList["trader"].move({0.0, -1.0});
                        up = true;
                    }
                    render();
                }
                toDelete.push_back("trader");
                
                traderTimer = 2000;
                spawnWave = true;
                crates = 3;
                crateSpawned = false;

            }
            traderTimer -= 10;
        }

        if(enemyList.size() <= 1 && spawnWave){
            generateWave(waveStrength, enemyList);
            stats.waveCount = waveCount;
			waveCount++;
			waveStrength += 5;
        }

        for(unsigned int i = 0; i<= enemyList.size()-1; i++){
            auto tmpTexture = enemyList[i]->getTexture();
            invincibilityCooldown -= 5;
            shipDamagedCooldown += 1;
            if(tmpTexture.collision(objectList["Ship"])){
                if(invincibilityCooldown < 0){
                    if(stats.ship == "images/Medium_Ship.png"){
                        objectList["Ship"].change_image("images/Medium_Ship_Damaged.png");
                    }
                    else if(stats.ship == "images/Small_Ship.png"){
                        objectList["Ship"].change_image("images/Small_Ship_Damaged.png");
                    }
                    else if(stats.ship == "images/Big_Ship.png"){
                        objectList["Ship"].change_image("images/Big_Ship_Damaged.png");
                    }

                    stats.health -=1;
                    shipDamagedCooldown = 0;
                    invincibilityCooldown = 1000;
                }

            }

            if(shipDamagedCooldown > 50){
                if(stats.ship == "images/Medium_Ship.png"){
                    objectList["Ship"].change_image("images/Medium_Ship.png");
                }
                else if(stats.ship == "images/Small_Ship.png"){
                    objectList["Ship"].change_image("images/Small_Ship.png");
                }
                else if(stats.ship == "images/Big_Ship.png"){
                    objectList["Ship"].change_image("images/Big_Ship.png");
                }
            }
        
            
            for(auto & picture: objectList){
                if(picture.second.getType() == "bullet"){
                    if(picture.second.collision( tmpTexture)){
                        enemyList[i]->setHealth(stats.bulletDamage);
                        toDelete.push_back(picture.first);
                        if(enemyList[i]->getHealth() <= 0){
                            AlienHitSound.play();
                            stats.credits += (rand()%3 + 1);
                            stats.playerScore+= enemyList[i]->getStrength();
                            enemyList.erase(enemyList.begin() +i);
                            stats.enemyKilled+=1;
                        }
                    }
                }
            }
        }

        for(auto & bullet: enemyBulletList){
            bullet.first.move(bullet.second); //trajectory
            if(bullet.first.getType()=="BossScythe"){
                bullet.first.rotate(10.0);
            }
            if(bullet.first.collision( objectList["Ship"])){
                if(stats.ship == "images/Medium_Ship.png"){
                    objectList["Ship"].change_image("images/Medium_Ship_Damaged.png");
                }
                else if(stats.ship == "images/Small_Ship.png"){
                    objectList["Ship"].change_image("images/Small_Ship_Damaged.png");
                }
                else if(stats.ship == "images/Big_Ship.png"){
                    objectList["Ship"].change_image("images/Big_Ship_Damaged.png");
                }
                PlayerHitSound.play();
                shipDamagedCooldown = 0;
                stats.health -= 1;
                bulletDelete.push_back(bulletIndex); 
            }
            if(bullet.first.getPosition().y > 900){
                bulletDelete.push_back(bulletIndex); 
            }
            else if(bullet.first.getPosition().x < 394){
                bulletDelete.push_back(bulletIndex); 
            }
            else if(bullet.first.getPosition().x > 1506){
                bulletDelete.push_back(bulletIndex); 
            }
            bulletIndex++;
        }

        for(auto & upgrade: upgradeList){
            auto tmpTexture = upgrade->getTexture();
            if(objectList["Ship"].collision(tmpTexture)){
                if(stats.credits >= upgrade->getPrice()){
                    stats.credits -= upgrade->getPrice();
                    upgrade->applyUpgrade(stats);
                    upgradeDelete.push_back(upgradeListIndex);
                    crates -= 1;
                }
            }
            upgradeListIndex++;
        }
        upgradeListIndex = 0;
            
        
        for(auto & picture: toDelete){
            objectList.erase(picture);
        }
        

        for(auto i: bulletDelete){
            enemyBulletList.erase(enemyBulletList.begin() + i); //delete the bullet
        }
        for(auto i: upgradeDelete){
            upgradeList.erase(upgradeList.begin() + i); //delete the upgrade crate
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
            bullet.first.draw( window );
        }
        for(auto & upgrade: upgradeList){
            upgrade->draw( window );
        }

        boardText.drawAll(window);

        window.display();
    }

    void updateStats( playerStats newStats ){
        stats = newStats;
        objectList["Ship"] = picture(sf::Vector2f( 945.0, 750.0 ), stats.ship, stats.size);
    }
    int get_score(){
		return stats.playerScore;
	}
};


#endif