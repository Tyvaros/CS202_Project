#include "project.h"

std::string playerStat(std::stringstream & s, Actor & a) {
	s << a.getHealth();
	return s.str();
}

int main()
{
	
	Actor player;
    sf::RenderWindow window(sf::VideoMode(800, 600), "Project Window");
    
    sf::RectangleShape rectangle(sf::Vector2f(1000, 50));//top wall
    sf::RectangleShape rectangle2(sf::Vector2f(100, 1000));//side wall

	sf::Sprite sprite;
	sf::Texture texture;
	
	sf::Font font;
	if(!font.loadFromFile("LiberationMono-Bold.ttf")) {
		return -1;
	}
	
	sf::Text health;
	health.setFont(font);
	std::stringstream s;
	std::string healthDisplay=playerStat(s,player);
	health.setString(healthDisplay);
	
	health.setPosition(0,0);
	health.setCharacterSize(24);
	health.setColor(sf::Color::Red);	
	
	texture.setRepeated(false);//load the sprite for the player
	if (!texture.loadFromFile("sprite.png")) {
			return -1;// error...
		}
	sprite.setTexture(texture);
	sprite.setPosition(100,200);
	//main loop
    while (window.isOpen()) {
        sf::Event event;
        //event loop
        while (window.pollEvent(event)) {
            switch (event.type) {
				case sf::Event::Closed:
					window.close();
					break;
				//case sf::Event::KeyPressed:
					
				default:
					break;
			}
        }
        //movement must be done outside of the event loop for smooth movement
        //note:making velocity and acceleration functions would be nice
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {					
			sprite.move(-.11,0);
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			sprite.move(.11,0);
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			sprite.move(0,-.11);
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			sprite.move(0,.11);
		}
		std::cout<< "Health: "<<player.getHealth()<<std::endl;	
		
		
		
        window.clear();
        
		
        window.draw(rectangle);
        window.draw(rectangle2);
        window.draw(sprite);
        window.draw(health);
        window.display();
        //stuff needs to be drawn in the right order.
        //VERY IMPORTANT: collision detection is done after drawing
        //	if it's done before the bounds are not defined
        sf::FloatRect boundingBox = sprite.getGlobalBounds();
		sf::FloatRect whiteBox = rectangle.getGlobalBounds();
		sf::FloatRect whiteBox2 = rectangle2.getGlobalBounds();
		//very simple collision detection. THIS WALL CAN ONLY BE A TOP WALL etc
		//need to figure out a way to set sprite move behavior based on direction
		if(boundingBox.intersects(whiteBox))//upper wall
		{
			sprite.move(0,1);
			
			//std::cout << "collision detected"<< std::endl;
		}	

		if(boundingBox.intersects(whiteBox2))//west wall
		{
			sprite.move(1,0);
			player.damage(.01);
			//std::cout << "collision detected"<< std::endl;
		}
		if(player.getHealth()<=0) {
			std::cout << "You died" <<std::endl;
			return 0;
		}
		
    }

    return 0;
}
