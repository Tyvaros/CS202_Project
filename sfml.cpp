#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
#include <string>

int main()
{
	//std::string title;
	//std::cin >> title; 
    sf::RenderWindow window(sf::VideoMode(800, 600), "Sample Text");
    //sf::CircleShape shape(100);
    //shape.setFillColor(sf::Color::Green);
	sf::Sprite sprite;
	sf::Texture texture;
	texture.setRepeated(true);
	if (!texture.loadFromFile("sprite.png")) {
			return -1;// error...
		}
	sprite.setTexture(texture);
    while (window.isOpen()) {
        sf::Event event;
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
        window.clear();
        //window.draw(shape);
        window.draw(sprite);
        window.display();
    }

    return 0;
}
