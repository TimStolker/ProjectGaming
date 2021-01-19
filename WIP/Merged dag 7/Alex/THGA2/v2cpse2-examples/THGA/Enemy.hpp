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
};

class enemy1 : public enemy {
private:
    std::string direction = "right";
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
};



void generateWave(int waveStrength, std::vector<enemy*> & enemyList){
    enemyList.clear();
    std::vector<int> randomNumber = {1,3,5};
    srand(time(NULL));
    while(waveStrength > 0){
        int strength = randomNumber[rand()%3]; 
        if(strength == 1){
            enemyList.push_back(new enemy1());
            waveStrength -= 1;
        }
        /*
        else if (strength == 3 && waveStrength > 3){
            enemyList.push_back(enemy(picture(sf::Vector2f( rand()%1000 + 400, 100.0 ), "images/Enemy1.png", sf::Vector2f( 80.0f, 80.0f )), 6,  3));
            waveStrength -= 3;
        }
        else if (strength == 5 && waveStrength > 5){
            enemyList.push_back(enemy(picture(sf::Vector2f( rand()%1000 + 400, 200.0 ), "images/Enemy1.png", sf::Vector2f( 100.0f, 100.0f )), 10,  5));
            waveStrength -= 5;
        }
        */
    }
    enemyList.push_back(new enemy0()); //extra enemy in list
    
    
}

#endif