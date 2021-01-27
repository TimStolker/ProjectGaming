#ifndef _UPGRADE_HPP
#define _UPGRADE_HPP

class upgrade{
private:
    picture image;
    sf::Font MyFont;
    std::string text;
    sf::Vector2f position;
    int price;

public:
    upgrade(picture image, std::string text, sf::Vector2f position, int price):
        image(image),
        text(text),
        position(position),
        price(price)
    {}

    void draw( sf::RenderWindow & window ){
        image.draw(window);
        sf::Text itemName, itemCost;
        MyFont.loadFromFile("images/OstrichSans-Medium.otf");
        itemName.setFont(MyFont);
		itemName.setString(text);
		itemName.setCharacterSize(30);
		itemName.setFillColor(sf::Color::White);
		itemName.setStyle(sf::Text::Bold);
		itemName.move(position);

        MyFont.loadFromFile("images/OstrichSans-Medium.otf");
        itemCost.setFont(MyFont);
		itemCost.setString(" " + std::to_string(price) + "$");
		itemCost.setCharacterSize(30);
		itemCost.setFillColor(sf::Color::White);
		itemCost.setStyle(sf::Text::Bold);
		itemCost.move({position.x + 40, position.y + 100});

        window.draw(itemName);
		window.draw(itemCost);
    }

    int getPrice(){
        return price;
    }

    picture getTexture(){
        return image;
    }

    virtual void applyUpgrade(playerStats & stats) = 0;


};

//Legendary
class upg_damage2 : public upgrade{
public:
    upg_damage2(sf::Vector2f position):
        upgrade(picture(position, "images/Damage.png", sf::Vector2f( 40.0, 40.0 )), "Damage +2", {position.x - 40,position.y - 50}, 80)
    {}

    void applyUpgrade(playerStats & stats){
        stats.bulletDamage += 2;
    }
};

class upg_tripleFire : public upgrade{
public:
    upg_tripleFire(sf::Vector2f position):
        upgrade(picture(position, "images/tripleFire.png", sf::Vector2f( 40.0, 40.0 )), "Triple fire", {position.x - 40,position.y - 50}, 250)
    {}

    void applyUpgrade(playerStats & stats){
        stats.tripleFire = true;
        stats.reloadTime += 500;
    }
};

//Rare
class upg_reload50 : public upgrade{
public:
    upg_reload50(sf::Vector2f position):
        upgrade(picture(position, "images/reload.png", sf::Vector2f( 40.0, 40.0 )), "Reload Time -50", {position.x - 40,position.y - 50}, 45)
    {}

    void applyUpgrade(playerStats & stats){
        if(stats.tripleFire && stats.reloadTime > 400){
            stats.reloadTime -= 50;
        }
        else if(stats.reloadTime > 50){
            stats.reloadTime -= 50;
        }
    }
};

class upg_damage1 : public upgrade{
public:
    upg_damage1(sf::Vector2f position):
        upgrade(picture(position, "images/Damage.png", sf::Vector2f( 40.0, 40.0 )), "Damage +1", {position.x - 40,position.y - 50}, 50)
    {}

    void applyUpgrade(playerStats & stats){
        stats.bulletDamage += 1;
    }
};

class upg_shield : public upgrade{
public:
    upg_shield(sf::Vector2f position):
        upgrade(picture(position, "images/Shield.png", sf::Vector2f( 40.0, 40.0 )), "     Shield", {position.x - 40,position.y - 50}, 40)
    {}

    void applyUpgrade(playerStats & stats){
        stats.spawnShields = true;
    }
};

//Uncommen
class upg_health1 : public upgrade{
public:
    upg_health1(sf::Vector2f position):
        upgrade(picture(position, "images/Health.png", sf::Vector2f( 40.0, 40.0 )), "   Health +1", {position.x - 40,position.y - 50}, 40)
    {}

    void applyUpgrade(playerStats & stats){
        stats.health += 1;
    }
};

class upg_reload30 : public upgrade{
public:
    upg_reload30(sf::Vector2f position):
        upgrade(picture(position, "images/reload.png", sf::Vector2f( 40.0, 40.0 )), "Reload Time -30", {position.x - 40,position.y - 50}, 30)
    {}

    void applyUpgrade(playerStats & stats){
        if(stats.tripleFire && stats.reloadTime > 400){
            stats.reloadTime -= 30;
        }
        else if(stats.reloadTime > 30){
            stats.reloadTime -= 30;
        }
    }
};

//Common
class upg_shipSpeed1 : public upgrade{
public:
    upg_shipSpeed1(sf::Vector2f position):
        upgrade(picture(position, "images/Speed.png", sf::Vector2f( 40.0, 40.0 )), "Ship Speed +1", {position.x - 40,position.y - 50}, 15)
    {}

    void applyUpgrade(playerStats & stats){
        stats.shipSpeed += 1;
    }
};

class upg_reload20 : public upgrade{
public:
    upg_reload20(sf::Vector2f position):
        upgrade(picture(position, "images/reload.png", sf::Vector2f( 40.0, 40.0 )), "Reload Time -20", {position.x - 40,position.y - 50}, 20)
    {}

    void applyUpgrade(playerStats & stats){
        if(stats.tripleFire && stats.reloadTime > 400){
            stats.reloadTime -= 20;
        }
        else if(stats.reloadTime > 20){
            stats.reloadTime -= 20;
        }
    }
};

upgrade *spawnUpgrade(sf::Vector2f position, playerStats stats, int seed){
    upgrade *upg;

    srand(seed); 
    int randomNumber = rand() % 100+1; //random getal 0 - 100
    if(randomNumber <= 5){  //Legendary loot (5%)
        int randomUpgrade = rand() % 2+1;
        if(randomUpgrade == 1){
            upg = new upg_damage2(position);
        }
        else{
            upg = new upg_tripleFire(position);
        }
    }

    else if(randomNumber <= 20){ //Rare loot (15%)
        int randomUpgrade = rand() % 3+1;
        if(randomUpgrade == 1){
            upg = new upg_reload50(position);
        }
        else if(randomUpgrade == 2){
            upg = new upg_damage1(position);
        }
        else{
            upg = new upg_shield(position);
        }

    }

    else if(randomNumber <= 50){ //uncommen loot (30%)
        int randomUpgrade = rand() % 2+1;
        if(randomUpgrade == 1){
            upg = new upg_health1(position);
        }
        else{
            upg = new upg_reload30(position);
        }
    }
    else{ //common loot (50%)
        int randomUpgrade = rand() % 2+1;
        if(randomUpgrade == 1){
            upg = new upg_shipSpeed1(position);
        }
        else{
            upg = new upg_reload20(position);
        }
    }
    return upg;
}

#endif