//this file contains Doxygen lines
///file Enemy.hpp
/// \brief enemy
/// \details Contains all the necessary information about the enemy class

#ifndef _ENEMY_HPP
#define _ENEMY_HPP

#include "Objects.hpp"
#include "GameControl.hpp"

/// \brief enemy Class
/// \details This is a superclass which allows the smaller classes to inherit from this one
//===========================================================================================
class enemy{
protected:
    picture texture;
    int health, strength;
    sf::Vector2f bulletTrajectory;

public:
    /// \brief Costructor of enemy
    /// \details This costructor needs a picture, 2 ints for health and strength and an sf::Vector2f
    enemy(picture texture, int health, int strength, sf::Vector2f bulletTrajectory):
        texture(texture), 
        health(health),
        strength(strength),
        bulletTrajectory(bulletTrajectory)
    {}

    /// \brief Virtual function move
    /// \details Virtual so that the classes that inherit this can change it
    virtual void move() = 0;

    /// \brief Virtual function shoot
    /// \details Virtual so that the classes that inherit this can change it
    virtual bool shoot() = 0;

    /// \brief Virtual function summon_Portal
    /// \details Virtual so that the classes that inherit this can change it
    virtual bool summon_Portal() = 0;

    /// \brief Virtual function getTrajectory
    /// \details Virtual so that the classes that inherit this can change it
    virtual sf::Vector2f getTrajectory() = 0;

    /// \brief Draw function
    /// \details This function calls upon the texure and draws it, a window needs to be provided
    void draw( sf::RenderWindow & window ){  
        texture.draw(window);
    }

    /// \brief Returns the picture
    /// \details Returns the picture of the enemy
    picture getTexture(){
        return texture;
    }

    /// \brief returns the health
    /// \details returns the health of the enemy
    int getHealth(){
        return health;
    }

    /// \brief returns the strength
    /// \details returns the strength of the enemey
    int getStrength(){
        return strength;
    }

    /// \brief Changes the health
    /// \details Changes enemy's health, taken damage needs to be provided
    void setHealth(int bulletDamage){
        health -= bulletDamage;
    }
};

/// \brief enemy0 Class
/// \details This class is for the 'useless' enemy which is only used as a list filler, it inherits enemy
//===========================================================================================
class enemy0 : public enemy {
public:

    /// \brief Constructor for the class
    /// \details The constructor calls on enemy which needs a picture, int health, int strength and an sf:vector bulletTrajectory
    enemy0():
        enemy(picture(sf::Vector2f( 3000, 3000.0 ), "images/Enemy1.png", sf::Vector2f( 50.0f, 50.0f )), 2, 1, sf::Vector2f(0.0, 0.0))
    {}

    /// \brief Moves the enemy
    /// \details This function does nothing for enemy0 because it is stationary
    void move(){
        return;
    }

    /// \brief Allows enemy to shoot
    /// \details This function does nothing for enemy0 because it can't shoot
    bool shoot(){
        return false;
    }

    /// \brief Allows enemy to summon portals
    /// \details This function does nothing for enemy0 because it can't summon portals 
    bool summon_Portal(){
        return false;
    }

    /// \brief Returns Trajectory
    /// \details Returns the bulletTrajectory of the enemys
    sf::Vector2f getTrajectory(){
        return bulletTrajectory;
    }
};

/// \brief enemy1 Class
/// \details This class is for the weakest enemy, it inherits enemy
//===========================================================================================
class enemy1 : public enemy {
private:
    std::vector<std::string> randomX = {"right", "left"};
    std::string direction = randomX[rand()%2];
    int target = 40;
    int gunCooldown = rand()%3000 + 100;

public:

    /// \brief Constructor for the class
    /// \details The constructor calls on enemy which needs a picture, int health, int strength and an sf:vector bulletTrajectory
    enemy1():
        enemy(picture(sf::Vector2f( rand()%1000 + 400, -50.0 ), "images/Enemy1.png", sf::Vector2f( 50.0f, 50.0f )), 2, 1, sf::Vector2f(0.0, 10.0))
    {}

    /// \brief Moves the enemy
    /// \details Enemy1 moves side to side on the screen, uppon hitting a border it moves down 50 pixels. This repeats until it is about 3/5 of the way down
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

    /// \brief Allows enemy to shoot
    /// \details This enemy shoots rarely
    bool shoot(){
        gunCooldown -= rand()%10 + 1;
        if(gunCooldown < 0){
            gunCooldown = rand()%3000 + 100;
            return true;
        }
        return false;
    }

    /// \brief Allows enemy to summon portals
    /// \details This function does nothing for enemy1 because it can't summon portals 
    bool summon_Portal(){
        return false;
    }

    /// \brief Returns Trajectory
    /// \details Returns the bulletTrajectory of the enemys
    sf::Vector2f getTrajectory(){
        return bulletTrajectory;
    }
};

/// \brief enemy2 Class
/// \details This class is for the minion summoned by the boss, it inherits enemy
//===========================================================================================
class enemy2 : public enemy {
private:
    std::vector<std::string> randomX = {"right","left"};
    std::string directionX = randomX[rand()%2], directionY = "down";
    int target = 40, gunCooldown = rand()%1000 + 100;

public:

    /// \brief Constructor for the class
    /// \details The constructor calls on enemy which needs a picture, int health, int strength and an sf:vector bulletTrajectory
    enemy2():
        enemy(picture(sf::Vector2f( rand()%1000 + 400, -50.0 ), "images/Enemy2.png", sf::Vector2f( 30.0f, 30.0f )), 1, 2, sf::Vector2f(0.0, 10.0))
    {}

    /// \brief Moves the enemy
    /// \details Enemy2 moves across the screen untill it hits about 3/5 where it goes up again and repeats the process
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

    /// \brief Allows enemy to shoot
    /// \details This enemy shoots every so often
    bool shoot(){
        gunCooldown -= rand()%10 + 1;
        if(gunCooldown < 0){
            gunCooldown = rand()%1000 + 100;
            return true;
        }
        return false;
    }

    /// \brief Allows enemy to summon portals
    /// \details This function does nothing for enemy1 because it can't summon portals 
    bool summon_Portal(){
        return false;
    }

    /// \brief Returns Trajectory
    /// \details Returns the bulletTrajectory of the enemys
    sf::Vector2f getTrajectory(){
        return bulletTrajectory;
    }
};

/// \brief enemy3 Class
/// \details This class is for the medium enemy, it inherits from enemy
//===========================================================================================
class enemy3 : public enemy { 
private:
    std::vector<std::string> randomX = {"right","left"};
    std::string directionX = randomX[rand()%2], directionY = "down";
    int gunCooldown = rand()%800 + 100;

public:

    /// \brief Constructor for the class
    /// \details The constructor calls on enemy which needs a picture, int health, int strength and an sf:vector bulletTrajectory
    enemy3():
        enemy(picture(sf::Vector2f( rand()%1000 + 400, -50.0 ), "images/Enemy3.png", sf::Vector2f( 80.0f, 80.0f )), 6, 3 ,sf::Vector2f(-10.0, 0.0))
    {}

    /// \brief Moves the enemy
    /// \details Enemy3 moves diagonally across the screen untill it hits about 3/5 where it goes up again and repeats the process
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

    /// \brief Allows enemy to shoot
    /// \details This enemy shoots every so often and switches firing direction
    bool shoot(){
        gunCooldown -= rand()%10 + 1;
        if(gunCooldown < 0){
            bulletTrajectory.x *= -1;
            gunCooldown = rand()%800 + 100;
            return true;
        }
        return false;
    }

    /// \brief Allows enemy to summon portals
    /// \details This function does nothing for enemy1 because it can't summon portals 
    bool summon_Portal(){
        return false;
    }

    /// \brief Returns Trajectory
    /// \details Returns the bulletTrajectory of the enemys
    sf::Vector2f getTrajectory(){
        return bulletTrajectory;
    }
};

/// \brief enemy5 Class
/// \details This class is for the long medium enemy, it inherits from enemy
//===========================================================================================
class enemy5 : public enemy {
private:
    std::vector<std::string> randomX = {"right","left"};
    std::string direction = randomX[rand()%2];
    int target = 40, gunCooldown = rand()%400 + 100;

public:

    /// \brief Constructor for the class
    /// \details The constructor calls on enemy which needs a picture, int health, int strength and an sf:vector bulletTrajectory
    enemy5():
        enemy(picture(sf::Vector2f( rand()%1000 + 400, -50.0 ), "images/Enemy5.png", sf::Vector2f( 100.0f, 60.0f )), 10, 5 ,sf::Vector2f(0.0, 10.0))
    {}

    /// \brief Moves the enemy
    /// \details Enemy5 stays at the top of the screen and moves side to side
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

    /// \brief Allows enemy to shoot
    /// \details This enemy shoots fairly often
    bool shoot(){
        gunCooldown -= 10;
        if(gunCooldown < 0){
            gunCooldown = rand()%400 + 100;
            return true;
        }
        return false;
    }

    /// \brief Allows enemy to summon portals
    /// \details This function does nothing for enemy1 because it can't summon portals 
    bool summon_Portal(){
        return false;
    }

    /// \brief Returns Trajectory
    /// \details Returns the bulletTrajectory of the enemys
    sf::Vector2f getTrajectory(){
        return bulletTrajectory;
    }
};

/// \brief enemy20 Class
/// \details This class is for the warper enemy, it inherits from enemy
//===========================================================================================
class enemy20 : public enemy {
private:
    int gunCooldown = rand()%500 + 100, teleportCooldown = 200, switchCooldown = rand()%150 + 100;;
    std::string direction = "right";
    bool summonPortal = false;

public:

    /// \brief Constructor for the class
    /// \details The constructor calls on enemy which needs a picture, int health, int strength and an sf:vector bulletTrajectory
    enemy20():
        enemy(picture(sf::Vector2f( rand()%1000 + 400, -100.0 ), "images/Enemy20.png", sf::Vector2f( 50.0f, 50.0f )), 5, 20,  sf::Vector2f(0.0, 10.0))
    {}

    /// \brief Moves the enemy
    /// \details Enemy20 moves side to side and switches direction randomly, it periodically teleports
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

    /// \brief Allows enemy to shoot
    /// \details This enemy shoots fairly often, if its not teleporting
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

    /// \brief Allows enemy to summon portals
    /// \details This function returns the summonPortal bool
    bool summon_Portal(){
        return summonPortal;
    }

    /// \brief Returns Trajectory
    /// \details Returns the bulletTrajectory of the enemys
    sf::Vector2f getTrajectory(){
        return bulletTrajectory;
    }
};

/// \brief Boss Class
/// \details This class is for the boss, it inherits from enemy
//===========================================================================================
class boss1 : public enemy {
private:
    int gunCooldown = 300, target = 60;
    std::string direction = "right";

public:

    /// \brief Constructor for the class
    /// \details The constructor calls on enemy which needs a picture, int health, int strength and an sf:vector bulletTrajectory
    boss1():
        enemy(picture(sf::Vector2f( 750, -200.0 ), "images/Boss1.png", sf::Vector2f( 400.0f, 150.0f )), 120, 200, sf::Vector2f(0.0, 10.0))
    {}

    /// \brief Moves the boss
    /// \details The boss move is rectangle shaped
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

    /// \brief Allows the boss to shoot
    /// \details The boss shoots very quick
    bool shoot(){
        gunCooldown -= 10;
        if(gunCooldown < 0){
            gunCooldown = 300;
            return true;
        }
        return false;
    }

    /// \brief Allows enemy to summon portals
    /// \details This function does nothing for enemy1 because it can't summon portals 
    bool summon_Portal(){
        return false;
    }

    /// \brief Returns Trajectory
    /// \details Returns the bulletTrajectory of the boss
    sf::Vector2f getTrajectory(){
        return bulletTrajectory;
    }
};

/// \brief enemy6 Class
/// \details This class is for the the upgraded version of enemy1, it inherits from enemy
//===========================================================================================
class enemy6 : public enemy {
private:
    std::vector<std::string> randomX = {"right", "left"};
    std::string direction = randomX[rand()%2];
    int gunCooldown = rand()%2000 + 100, shots = 0, target = 40;

public:

    /// \brief Constructor for the class
    /// \details The constructor calls on enemy which needs a picture, int health, int strength and an sf:vector bulletTrajectory
    enemy6():
        enemy(picture(sf::Vector2f( rand()%1000 + 400, -50.0 ), "images/Enemy6.png", sf::Vector2f( 55.0f, 55.0f )), 10, 6, sf::Vector2f(0.0, 12.0))
    {}

    /// \brief Moves the enemy
    /// \details Enemy1 moves side to side on the screen, uppon hitting a border it moves down 50 pixels. This repeats until it is about 3/5 of the way down
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

    /// \brief Allows enemy to shoot
    /// \details This enemy shoots rarely
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

    /// \brief Allows enemy to summon portals
    /// \details This function does nothing for enemy1 because it can't summon portals 
    bool summon_Portal(){
        return false;
    }

    /// \brief Returns Trajectory
    /// \details Returns the bulletTrajectory of the enemys
    sf::Vector2f getTrajectory(){
        return bulletTrajectory;
    }
};

/// \brief enemy10 Class
/// \details This class is for the the upgraded version of enemy3, it inherits from enemy
//===========================================================================================
class enemy10 : public enemy {
private:
    std::vector<std::string> randomX = {"right","left"};
    std::string directionX = randomX[rand()%2];
    std::string directionY = "down";
    int gunCooldown = rand()%500 + 100;

public:

    /// \brief Constructor for the class
    /// \details The constructor calls on enemy which needs a picture, int health, int strength and an sf:vector bulletTrajectory
    enemy10():
        enemy(picture(sf::Vector2f( rand()%1000 + 400, rand()%40 - 100), "images/Enemy10.png", sf::Vector2f( 80.0f, 80.0f )), 12, 10 ,sf::Vector2f(-10.0, 10.0))
    {}

    /// \brief Moves the enemy
    /// \details Enemy10 moves diagonally across the screen untill it hits about 3/5 where it goes up again and repeats the process
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

    /// \brief Allows enemy to shoot
    /// \details This enemy shoots every so often
    bool shoot(){
        gunCooldown -= rand()%10 + 1;
        if(gunCooldown < 0){
            bulletTrajectory.x *= -1;
            gunCooldown = rand()%500 + 100;

            return true;
        }
        return false;
    }

    /// \brief Allows enemy to summon portals
    /// \details This function does nothing for enemy1 because it can't summon portals 
    bool summon_Portal(){
        return false;
    }

    /// \brief Returns Trajectory
    /// \details Returns the bulletTrajectory of the enemys
    sf::Vector2f getTrajectory(){
        return bulletTrajectory;
    }
};

/// \brief enemy15 Class
/// \details This class is for the the upgraded version of enemy5, it inherits from enemy
//===========================================================================================
class enemy15 : public enemy { //medium enemy
private:
    std::vector<std::string> randomX = {"right","left"};
    std::string direction = randomX[rand()%2];
    int gunCooldown = rand()%200 + 20;

public:

    /// \brief Constructor for the class
    /// \details The constructor calls on enemy which needs a picture, int health, int strength and an sf:vector bulletTrajectory
    enemy15():
        enemy(picture(sf::Vector2f( rand()%1000 + 400, -50.0 ), "images/Enemy15.png", sf::Vector2f( 100.0f, 60.0f )), 15, 15 ,sf::Vector2f(0.0, 10.0))
    {}

    /// \brief Moves the enemy
    /// \details Enemy15 stays at the top of the screen and moves side to side
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

    /// \brief Allows enemy to shoot
    /// \details This enemy shoots fairly quick
    bool shoot(){
        gunCooldown -= rand()%10 + 1;
        if(gunCooldown < 0){
            gunCooldown = rand()%200 + 20;
            return true;
        }
        return false;
    }

    /// \brief Allows enemy to summon portals
    /// \details This function does nothing for enemy1 because it can't summon portals 
    bool summon_Portal(){
        return false;
    }

    /// \brief Returns Trajectory
    /// \details Returns the bulletTrajectory of the enemys
    sf::Vector2f getTrajectory(){
        return bulletTrajectory;
    }
};

/// \brief enemy30 Class
/// \details This class is for the the upgraded version of enemy20, it inherits from enemy
//===========================================================================================
class enemy30 : public enemy {
private:
    std::string direction = "right", bulletDirection = "left";
    int gunCooldown = rand()%500 + 100, teleportCooldown = 200;
    int switchCooldown = rand()%150 + 100, shots = 0;
    bool summonPortal = false;

public:

    /// \brief Constructor for the class
    /// \details The constructor calls on enemy which needs a picture, int health, int strength and an sf:vector bulletTrajectory
    enemy30():
        enemy(picture(sf::Vector2f( rand()%1000 + 400, -100.0 ), "images/Enemy30.png", sf::Vector2f( 65.0f, 50.0f )), 14, 30,  sf::Vector2f(-10.0, 10.0))
    {}

    /// \brief Moves the enemy
    /// \details Enemy30 moves side to side and switches direction randomly, it periodically teleports
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

    /// \brief Allows enemy to shoot
    /// \details This enemy shoots fairly often, if its not teleporting
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

    /// \brief Allows enemy to summon portals
    /// \details This function returns the summonPortal bool
    bool summon_Portal(){
        return summonPortal;
    }

    /// \brief Returns Trajectory
    /// \details Returns the bulletTrajectory of the enemys
    sf::Vector2f getTrajectory(){
        return bulletTrajectory;
    }
};

/// \brief Generate Wave
/// \details This functions fills a provided vector with enemies acording to the given strength
//===========================================================================================
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