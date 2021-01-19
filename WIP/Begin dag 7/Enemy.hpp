#ifndef _ENEMY_HPP
#define _ENEMY_HPP

#include "Objects.hpp"
#include "GameControl.hpp"

class enemy{
private:
    picture texture;
    int health;
    int strength;

public:
    enemy(picture texture, int health, int strength):
        texture(texture), 
        health(health),
        strength(strength)
    {}

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

void generateWave(int waveStrength, std::vector<enemy> & enemyList){
    enemyList.clear();
    std::vector<int> randomNumber = {1,3,5};
    srand(time(NULL));
    while(waveStrength > 0){
        int strength = randomNumber[rand()%3]; 
        if(strength == 1){
            enemyList.push_back(enemy(picture(sf::Vector2f( rand()%1000 + 400, 100.0 ), "images/Enemy1.png", sf::Vector2f( 50.0f, 50.0f )), 2,  1));
            waveStrength -= 1;
        }
        else if (strength == 3 && waveStrength > 3){
            enemyList.push_back(enemy(picture(sf::Vector2f( rand()%1000 + 400, 100.0 ), "images/Enemy1.png", sf::Vector2f( 80.0f, 80.0f )), 6,  3));
            waveStrength -= 3;
        }
        else if (strength == 5 && waveStrength > 5){
            enemyList.push_back(enemy(picture(sf::Vector2f( rand()%1000 + 400, 200.0 ), "images/Enemy1.png", sf::Vector2f( 100.0f, 100.0f )), 10,  5));
            waveStrength -= 5;
        }
    }
    enemyList.push_back(enemy(picture(sf::Vector2f( 3000, 3000.0 ), "images/Enemy1.png", sf::Vector2f( 100.0f, 100.0f )), 10,  0)); //extra enemy in list
    
    
}

/*
        enemy(picture(sf::Vector2f( 950.0, 200.0 ), "images/enemy1.png", sf::Vector2f( 50.0f, 50.0f )), 2),
        enemy(picture(sf::Vector2f( 850.0, 300.0 ), "images/enemy1.png", sf::Vector2f( 50.0f, 50.0f )), 2),
        enemy(picture(sf::Vector2f( 750.0, 200.0 ), "images/enemy1.png", sf::Vector2f( 50.0f, 50.0f )), 2),
        enemy(picture(sf::Vector2f( 1050.0, 300.0 ), "images/enemy1.png", sf::Vector2f( 50.0f, 50.0f )), 2)
*/

#endif