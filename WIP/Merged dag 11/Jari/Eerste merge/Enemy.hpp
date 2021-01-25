#ifndef _ENEMY_HPP
#define _ENEMY_HPP

#include "Objects.hpp"
#include "GameControl.hpp"

class enemy{
protected:
    picture texture;
    int health;
    int strength;
    sf::Vector2f bulletTrajectory;

public:
    enemy(picture texture, int health, int strength, sf::Vector2f bulletTrajectory):
        texture(texture), 
        health(health),
        strength(strength),
        bulletTrajectory(bulletTrajectory)
    {}

    virtual void move() = 0;
    virtual bool shoot() = 0;
    virtual bool summon_Portal() = 0;
    virtual sf::Vector2f getTrajectory() = 0;

    void draw( sf::RenderWindow & window ){  
        texture.draw(window);
    }

    picture getTexture(){
        return texture;
    }

    int getHealth(){
        return health;
    }

    void setHealth(int bulletDamage){
        health -= bulletDamage;
    }

    int getStrength(){
        return strength;
    }

    


};

class enemy0 : public enemy {
private:

public:
    enemy0():
        enemy(picture(sf::Vector2f( 3000, 3000.0 ), "images/Enemy1.png", sf::Vector2f( 50.0f, 50.0f )), 2, 1, sf::Vector2f(0.0, 0.0))
    {}
    void move(){
        return;
    }
    bool shoot(){
        return false;
    }
    bool summon_Portal(){
        return false;
    }
    sf::Vector2f getTrajectory(){
        return bulletTrajectory;
    }
};

class enemy1 : public enemy { //basic enemy
private:
    std::vector<std::string> randomX = {"right","left"};
    std::string direction = randomX[rand()%2];
    int target = 40;
    int gunCooldown = rand()%3000 + 100;

public:
    enemy1():
        enemy(picture(sf::Vector2f( rand()%1000 + 400, -50.0 ), "images/Enemy1.png", sf::Vector2f( 50.0f, 50.0f )), 2, 1, sf::Vector2f(0.0, 10.0))
    {}

    void move(){
        sf::Vector2f position = texture.getPosition();

        if(texture.getPosition().y < 50){
            texture.move(sf::Vector2f(0.0, 2.0));
        }
        if(position.y < target && target < 500){
            texture.move(sf::Vector2f(0.0, 2.0));
        }
        else{
            if(direction == "left"){
                texture.move(sf::Vector2f(-2.0, 0.0));
                if(position.x < 404){
                    target = position.y + 50;
                    direction = "right";

                }
            }
            else if(direction == "right"){
                texture.move(sf::Vector2f(2.0, 0.0));
                if(position.x > 1480){
                    target = position.y + 50;
                    direction = "left";

                }
            }
        }
        
    }
    bool shoot(){
        gunCooldown -= rand()%10 + 1;
        if(gunCooldown < 0){
            gunCooldown = rand()%3000 + 100;
            return true;
        }
        return false;
    }
    bool summon_Portal(){
        return false;
    }
    sf::Vector2f getTrajectory(){
        return bulletTrajectory;
    }
};

class enemy2 : public enemy { //basic enemy
private:
    std::vector<std::string> randomX = {"right","left"};
    std::string directionX = randomX[rand()%2];
    std::string directionY = "down";
    int target = 40;
    int gunCooldown = rand()%1000 + 100;

public:
    enemy2():
        enemy(picture(sf::Vector2f( rand()%1000 + 400, -50.0 ), "images/Enemy2.png", sf::Vector2f( 30.0f, 30.0f )), 1, 2, sf::Vector2f(0.0, 10.0))
    {}

    void move(){
        sf::Vector2f position = texture.getPosition();

        if(texture.getPosition().y < 50){
            texture.move(sf::Vector2f(0.0, 2.0));
        }
        else{
            if(position.y >= 500){
                directionY = "up";
            }
            if(directionX == "left" && directionY == "down"){ 
                texture.move(sf::Vector2f(-6.0, 1));
                if(position.x < 404){
                    directionX = "right";

                }
            }
            else if(directionX == "right" && directionY == "down"){

                texture.move(sf::Vector2f(6.0, 1));
                if(position.x > 1450){
                    directionX = "left";
                }
            }


            else if(directionX == "left" && directionY == "up"){
                texture.move(sf::Vector2f(-6.0, -1));
                if(position.x < 404){
                    directionX = "right";
                    directionY = "down";

                }
            }
            else if(directionX == "right" && directionY == "up"){
                texture.move(sf::Vector2f(6.0, -1));
                if(position.x > 1450){
                    directionX = "left";
                    directionY = "down";

                }
            }
        }
        
    }
    bool shoot(){
        gunCooldown -= rand()%10 + 1;
        if(gunCooldown < 0){
            gunCooldown = rand()%1000 + 100;
            return true;
        }
        return false;
    }
    bool summon_Portal(){
        return false;
    }
    sf::Vector2f getTrajectory(){
        return bulletTrajectory;
    }
};


class enemy3 : public enemy { //medium enemy
private:
    std::vector<std::string> randomX = {"right","left"};
    std::string directionX = randomX[rand()%2];
    std::string directionY = "down";
    int gunCooldown = rand()%800 + 100;

public:
    enemy3():
        enemy(picture(sf::Vector2f( rand()%1000 + 400, -50.0 ), "images/Enemy3.png", sf::Vector2f( 80.0f, 80.0f )), 6, 3 ,sf::Vector2f(-10.0, 0.0))
    {}

    void move(){
        sf::Vector2f position = texture.getPosition();

        if(texture.getPosition().y < 50){
            texture.move(sf::Vector2f(0.0, 2.0));
        }
        else{
            if(position.y >= 500){
                directionY = "up";
            }
            if(position.y <= 55){
                directionY = "down";
            }
            if(directionX == "left" && directionY == "down"){ 
                texture.move(sf::Vector2f(-6.0, 2));
                if(position.x < 404){
                    directionX = "right";

                }
            }
            else if(directionX == "right" && directionY == "down"){

                texture.move(sf::Vector2f(6.0, 2));
                if(position.x > 1450){
                    directionX = "left";
                }
            }


            else if(directionX == "left" && directionY == "up"){
                texture.move(sf::Vector2f(-6.0, -2));
                if(position.x < 404){
                    directionX = "right";

                }
            }
            else if(directionX == "right" && directionY == "up"){
                texture.move(sf::Vector2f(6.0, -2));
                if(position.x > 1450){
                    directionX = "left";

                }
            }
        }
        
    }
    bool shoot(){
        gunCooldown -= rand()%10 + 1;
        if(gunCooldown < 0){
            bulletTrajectory.x *= -1;
            gunCooldown = rand()%800 + 100;

            return true;
        }
        return false;
    }
    bool summon_Portal(){
        return false;
    }
    sf::Vector2f getTrajectory(){
        return bulletTrajectory;
    }

};

class enemy5 : public enemy { //medium enemy
private:
    std::vector<std::string> randomX = {"right","left"};
    std::string direction = randomX[rand()%2];
    int target = 40;
    int gunCooldown = rand()%400 + 1;

public:
    enemy5():
        enemy(picture(sf::Vector2f( rand()%1000 + 400, -50.0 ), "images/Enemy5.png", sf::Vector2f( 100.0f, 60.0f )), 10, 5 ,sf::Vector2f(0.0, 10.0))
    {}

    void move(){
        sf::Vector2f position = texture.getPosition();

        if(texture.getPosition().y < 50){
            texture.move(sf::Vector2f(0.0, 2.0));
        }
        else{
            if(direction == "left"){
                texture.move(sf::Vector2f(-5.0, 0.0));
                if(position.x < 404){
                    direction = "right";

                }
            }
            else if(direction == "right"){
                texture.move(sf::Vector2f(5.0, 0.0));
                if(position.x > 1425){
                    direction = "left";

                }
            }
        }
        
    }
    bool shoot(){
        gunCooldown -= rand()%10 + 1;
        if(gunCooldown < 0){
            gunCooldown = rand()%400 + 1;
            return true;
        }
        return false;
    }
    bool summon_Portal(){
        return false;
    }
    sf::Vector2f getTrajectory(){
        return bulletTrajectory;
    }
};

class enemy20 : public enemy {
private:
    int gunCooldown = rand()%500 + 100;
    int teleportCooldown = 200;
    int switchCooldown = rand()%150 + 100;;
    std::string direction = "right";
    bool summonPortal = false;

public:
    enemy20():
        enemy(picture(sf::Vector2f( rand()%1000 + 400, -100.0 ), "images/Enemy20.png", sf::Vector2f( 50.0f, 50.0f )), 5, 20,  sf::Vector2f(0.0, 10.0))
    {}
    void move(){
        teleportCooldown -= 10;
        switchCooldown -= 10;
        if(switchCooldown <= 0){
            switchCooldown = rand()%350 + 100;
            if(direction == "right"){
                direction = "left";
            }
            else{
                direction = "right";
            }
        }
        if(teleportCooldown <= 0){
            teleportCooldown = 1500;
            texture.jump(sf::Vector2f(rand()%1000 + 400, rand()%500));
        }
        else if(teleportCooldown >= 400){
            summonPortal = false;
            if(direction == "right"){
                if(texture.getPosition().x < 1480){
                    texture.move(sf::Vector2f(3.0, 0.0));
                }
                else{
                   direction = "left"; 
                }
            }
            else{
                if(texture.getPosition().x > 404){
                    texture.move(sf::Vector2f(-3.0, 0.0));
                }
                else{
                   direction = "right"; 
                }
            }
        }
        else{
            summonPortal = true;
        }
    }
    bool shoot(){
        if(!summonPortal){
            gunCooldown -= rand()%10 + 1;
            if(gunCooldown < 0){
                gunCooldown = rand()%500 + 100;
                return true;
            }
        }
        return false;
    }

    bool summon_Portal(){
        return summonPortal;
    }
    sf::Vector2f getTrajectory(){
        return bulletTrajectory;
    }
    
};

class boss1 : public enemy {
private:
    int gunCooldown = 300;
    std::string direction = "right";
    int target = 60;

public:
    boss1():
        enemy(picture(sf::Vector2f( 750, -200.0 ), "images/Boss1.png", sf::Vector2f( 400.0f, 150.0f )), 120, 200, sf::Vector2f(0.0, 10.0))
    {}
    void move(){
        sf::Vector2f position = texture.getPosition();
        if(position.y < 60){
            texture.move(sf::Vector2f(0.0, 4.0));
        }
        else{
            if(direction == "right"){
                texture.move(sf::Vector2f(4.0, 0.0));
                if(position.x > 1036){
                    direction = "down";
                }
            }
            else if(direction == "down"){
                texture.move(sf::Vector2f(0.0, 4.0));
                if(position.y > 110){
                    direction = "left";
                }
            }
            else if(direction == "left"){
                texture.move(sf::Vector2f(-4.0, 0.0));
                if(position.x < 408){
                    direction = "up";
                }
            }
            else if(direction == "up"){
                texture.move(sf::Vector2f(0.0 , -4.0));
                if(position.y < 64){
                    direction = "right";
                }
            }
        }
    }
    bool shoot(){
        gunCooldown -= 10;
        if(gunCooldown < 0){
            gunCooldown = 300;
            return true;
        }
        return false;
    }
    bool summon_Portal(){
        return false;
    }
    sf::Vector2f getTrajectory(){
        return bulletTrajectory;
    }
};

class enemy6 : public enemy {
private:
    std::vector<std::string> randomX = {"right","left"};
    std::string direction = randomX[rand()%2];
    int target = 40;
    int gunCooldown = rand()%2000 + 100;
    int shots = 0;

public:
    enemy6():
        enemy(picture(sf::Vector2f( rand()%1000 + 400, -50.0 ), "images/Enemy6.png", sf::Vector2f( 55.0f, 55.0f )), 6, 6, sf::Vector2f(0.0, 12.0))
    {}

    void move(){
        sf::Vector2f position = texture.getPosition();

        if(texture.getPosition().y < 50){
            texture.move(sf::Vector2f(0.0, 3.0));
        }
        if(position.y < target && target < 500){
            texture.move(sf::Vector2f(0.0, 3.0));
        }
        else{
            if(direction == "left"){
                texture.move(sf::Vector2f(-3.0, 0.0));
                if(position.x < 404){
                    target = position.y + 50;
                    direction = "right";
                }
            }
            else if(direction == "right"){
                texture.move(sf::Vector2f(3.0, 0.0));
                if(position.x > 1480){
                    target = position.y + 50;
                    direction = "left";

                }
            }
        }
    }

    bool shoot(){
        gunCooldown -= 10;
        if(gunCooldown < 0){
            if(shots < 2){
                gunCooldown = 20;
                shots++;
            }
            else{
                shots = 0;
                gunCooldown = rand()%2000 + 100;
            }
            return true;

        }
        return false;
    }

    bool summon_Portal(){
        return false;
    }
    sf::Vector2f getTrajectory(){
        return bulletTrajectory;
    }
};

class enemy10 : public enemy { //medium enemy
private:
    std::vector<std::string> randomX = {"right","left"};
    std::string directionX = randomX[rand()%2];
    std::string directionY = "down";
    int gunCooldown = rand()%500 + 100;

public:
    enemy10():
        enemy(picture(sf::Vector2f( rand()%1000 + 400, rand()%40 - 100), "images/Enemy10.png", sf::Vector2f( 80.0f, 80.0f )), 6, 10 ,sf::Vector2f(-10.0, 10.0))
    {}

    void move(){
        sf::Vector2f position = texture.getPosition();

        if(texture.getPosition().y < 50){
            texture.move(sf::Vector2f(0.0, 2.0));
        }
        else{
            if(position.y >= 500){
                directionY = "up";
            }
            if(position.y <= 55){
                directionY = "down";
            }
            if(directionX == "left" && directionY == "down"){ 
                texture.move(sf::Vector2f(-8.0, 3));
                if(position.x < 404){
                    directionX = "right";

                }
            }
            else if(directionX == "right" && directionY == "down"){

                texture.move(sf::Vector2f(8.0, 3));
                if(position.x > 1450){
                    directionX = "left";
                }
            }


            else if(directionX == "left" && directionY == "up"){
                texture.move(sf::Vector2f(-8.0, -3));
                if(position.x < 404){
                    directionX = "right";

                }
            }
            else if(directionX == "right" && directionY == "up"){
                texture.move(sf::Vector2f(8.0, -3));
                if(position.x > 1450){
                    directionX = "left";

                }
            }
        }
        
    }
    bool shoot(){
        gunCooldown -= rand()%10 + 1;
        if(gunCooldown < 0){
            bulletTrajectory.x *= -1;
            gunCooldown = rand()%500 + 100;

            return true;
        }
        return false;
    }
    bool summon_Portal(){
        return false;
    }
    sf::Vector2f getTrajectory(){
        return bulletTrajectory;
    }

};

class enemy15 : public enemy { //medium enemy
private:
    std::vector<std::string> randomX = {"right","left"};
    std::string direction = randomX[rand()%2];
    int gunCooldown = rand()%200 + 1;

public:
    enemy15():
        enemy(picture(sf::Vector2f( rand()%1000 + 400, -50.0 ), "images/Enemy15.png", sf::Vector2f( 100.0f, 60.0f )), 10, 15 ,sf::Vector2f(0.0, 10.0))
    {}

    void move(){
        sf::Vector2f position = texture.getPosition();

        if(texture.getPosition().y < 50){
            texture.move(sf::Vector2f(0.0, 2.0));
        }
        else{
            if(direction == "left"){
                texture.move(sf::Vector2f(-8.0, 0.0));
                if(position.x < 404){
                    direction = "right";

                }
            }
            else if(direction == "right"){
                texture.move(sf::Vector2f(8.0, 0.0));
                if(position.x > 1425){
                    direction = "left";

                }
            }
        }
        
    }
    bool shoot(){
        gunCooldown -= rand()%10 + 1;
        if(gunCooldown < 0){
            gunCooldown = rand()%200 + 1;
            return true;
        }
        return false;
    }
    bool summon_Portal(){
        return false;
    }
    sf::Vector2f getTrajectory(){
        return bulletTrajectory;
    }
};

class enemy30 : public enemy {
private:
    int gunCooldown = rand()%500 + 100;
    int teleportCooldown = 200;
    int switchCooldown = rand()%150 + 100;;
    std::string direction = "right";
    std::string bulletDirection = "left";
    bool summonPortal = false;
    int shots = 0;

public:
    enemy30():
        enemy(picture(sf::Vector2f( rand()%1000 + 400, -100.0 ), "images/Enemy30.png", sf::Vector2f( 65.0f, 50.0f )), 8, 30,  sf::Vector2f(-10.0, 10.0))
    {}
    void move(){
        teleportCooldown -= 10;
        switchCooldown -= 10;
        if(switchCooldown <= 0){
            switchCooldown = rand()%350 + 100;
            if(direction == "right"){
                direction = "left";
            }
            else{
                direction = "right";
            }
        }
        if(teleportCooldown <= 0){
            teleportCooldown = 1500;
            texture.jump(sf::Vector2f(rand()%1000 + 400, rand()%500));
        }
        else if(teleportCooldown >= 400){
            summonPortal = false;
            if(direction == "right"){
                if(texture.getPosition().x < 1480){
                    texture.move(sf::Vector2f(3.0, 0.0));
                }
                else{
                   direction = "left"; 
                }
            }
            else{
                if(texture.getPosition().x > 404){
                    texture.move(sf::Vector2f(-3.0, 0.0));
                }
                else{
                   direction = "right"; 
                }
            }
        }
        else{
            summonPortal = true;
        }
    }
    bool shoot(){
        if(!summonPortal){
            gunCooldown -= rand()%10 + 1;
            if(bulletDirection == "left"){
                bulletTrajectory.x = -10;
                bulletDirection = "down";
            }
            else if(bulletDirection == "down"){
                bulletTrajectory.x = 0;
                bulletDirection = "right";
            }
            else if(bulletDirection == "right"){
                bulletTrajectory.x = 10;
                bulletDirection = "left";
            }
            if(gunCooldown < 0){
                if(shots < 2){
                    gunCooldown = 20;
                    shots++;
                }
                else{
                    shots = 0;
                    gunCooldown = rand()%500 + 100;
                }
                return true;
            }
        }
        return false;
    }

    bool summon_Portal(){
        return summonPortal;
    }
    sf::Vector2f getTrajectory(){
        return bulletTrajectory;
    }
    
};



void generateWave(int waveStrength, std::vector<enemy*> & enemyList){
    enemyList.clear();
    std::vector<int> enemySelect = {1,2,3,4};
    srand(time(NULL));
    if(waveStrength < 50){
        while(waveStrength > 0){
            int enemy = enemySelect[rand()%4]; 
            if(enemy == 1){
                enemyList.push_back(new enemy1());
                waveStrength -= 1;
            }
            
            else if (enemy == 2 && waveStrength > 3){
                enemyList.push_back(new enemy3());
                waveStrength -= 3;
            }
            
            else if (enemy == 3 && waveStrength > 5){
                enemyList.push_back(new enemy5());
                waveStrength -= 5;
            }

            else if (enemy == 4 && waveStrength > 20){
                enemyList.push_back(new enemy20());
                waveStrength -= 20;
            }
        }
    } 
    else if(waveStrength == 50){
        enemyList.push_back(new boss1());
    }
    else{
        while(waveStrength > 0){
            int enemy = enemySelect[rand()%4]; 
            if(enemy == 1){
                enemyList.push_back(new enemy6());
                waveStrength -= 5;
            }
            else if(enemy == 2){
                enemyList.push_back(new enemy10());
                waveStrength -= 10;
            }
            else if(enemy == 3){
                enemyList.push_back(new enemy15());
                waveStrength -= 15;
            }            
            else if(enemy == 4){
                enemyList.push_back(new enemy30());
                waveStrength -= 30;
            }
        }
    }

    enemyList.push_back(new enemy0()); //extra enemy in list
}

#endif