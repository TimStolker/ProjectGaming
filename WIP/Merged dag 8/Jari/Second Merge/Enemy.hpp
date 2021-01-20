#ifndef _ENEMY_HPP
#define _ENEMY_HPP

#include "Objects.hpp"
#include "GameControl.hpp"

class enemy{
protected:
    picture texture;
    int health;
    int strength;

public:
    enemy(picture texture, int health, int strength):
        texture(texture), 
        health(health),
        strength(strength)
    {}

    virtual void move() = 0;
    virtual bool shoot() = 0;
    virtual bool summon_Portal() = 0;

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
        enemy(picture(sf::Vector2f( 3000, 3000.0 ), "images/Enemy1.png", sf::Vector2f( 50.0f, 50.0f )), 2, 1)
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
};

class enemy1 : public enemy { //basic enemy
private:
    std::vector<std::string> randomX = {"right","left"};
    std::string direction = randomX[rand()%2];
    int target = 40;
    int gunCooldown = rand()%3000 + 100;

public:
    enemy1():
        enemy(picture(sf::Vector2f( rand()%1000 + 400, -50.0 ), "images/Enemy1.png", sf::Vector2f( 50.0f, 50.0f )), 2, 1)
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
};


class enemy3 : public enemy { //medium enemy
private:
    std::vector<std::string> randomX = {"right","left"};
    std::string directionX = randomX[rand()%2];
    std::string directionY = "down";
    int gunCooldown = rand()%3000 + 100;

public:
    enemy3():
        enemy(picture(sf::Vector2f( rand()%1000 + 400, -50.0 ), "images/Enemy3.png", sf::Vector2f( 80.0f, 80.0f )), 6, 3)
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
            gunCooldown = rand()%3000 + 100;
            return true;
        }
        return false;
    }
    bool summon_Portal(){
        return false;
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
        enemy(picture(sf::Vector2f( rand()%1000 + 400, -50.0 ), "images/Enemy5.png", sf::Vector2f( 100.0f, 60.0f )), 10, 5)
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
        enemy(picture(sf::Vector2f( rand()%1000 + 400, -100.0 ), "images/Enemy20.png", sf::Vector2f( 50.0f, 50.0f )), 5, 20)
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
    
};



void generateWave(int waveStrength, std::vector<enemy*> & enemyList){
    enemyList.clear();
    std::vector<int> randomNumber = {1,3,5,20};
    srand(time(NULL));
    while(waveStrength > 0){
        int strength = randomNumber[rand()%4]; 
        if(strength == 1){
            enemyList.push_back(new enemy1());
            waveStrength -= 1;
        }
        
        else if (strength == 3 && waveStrength > 3){
            enemyList.push_back(new enemy3());
            waveStrength -= 3;
        }
        
        else if (strength == 5 && waveStrength > 5){
            enemyList.push_back(new enemy5());
            waveStrength -= 5;
        }

        else if (strength == 20 && waveStrength > 20){
            enemyList.push_back(new enemy20());
            waveStrength -= 20;
        }
        
    }
    enemyList.push_back(new enemy0()); //extra enemy in list
    
    
}

#endif