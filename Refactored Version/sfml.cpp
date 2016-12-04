#include "project.h"

std::string playerStat(std::stringstream & s, Actor & a) {
	s << "HP: " << a.getHealth();
	return s.str();
}

//std::vector<int> levelGen() {//generates a random map for 16 by 8 maps
//	std::vector<int> level(128);
//	int sum = 0;
//	while (sum<140) {
//		sum = 0;
//		for (int i = 1; i<128; i++) {
//			level[i] = (rand() % 3);
//		}
//		for (int i = 0; i<128; i++) {
//			sum += level[i];
//		}
//	}
//	level[0] = 1;
//	level[1] = 1;
//	level[2] = 1;
//	level[17] = 1;
//	return level;
//}
//
//void mapInit(Level map, std::vector<int> level) {//loads a new map	
//	
//	if (!map.load("tilese_cave.png", sf::Vector2u(32, 32), level, 16, 8)) {
//		std::cout << "Unable to load tilese_cave.png" << std::endl;
//		return;
//	}
//	// HI
//	map.randPos(map.getPlayer());
//	for (auto it = map.getEnemies().begin(); it != map.getEnemies().end(); ++it)
//	{
//		map.randPos(*it);
//	}
//}


/**********************************************************************************************/


//Important note, to make everything much easier, 
//we should store all of the entities into a vector 
//and then pass into the transform functions to 
//draw,move,set everything at once
int main()
{
	srand(time(NULL));
	sf::RenderWindow window(sf::VideoMode(512, 288), "Project Window");

	//sf::RectangleShape doorBox(sf::Vector2f(32, 32));
	//doorBox.setPosition(0, 0);
	sf::RectangleShape rectangle(sf::Vector2f(512, 32));//healthbox
	rectangle.setPosition(0, 256);

	//the tiles for the map, see picture for details
	//0=water,1=tree,2=grass/bottom bridge, 3= grass/bottom water, 4=grass/top bridge, 5=grass,6=bridge,7=flowers,8=grass/top bridge
	std::vector<int> level = {
		3, 5, 5, 1, 5, 1, 2, 3, 3, 3, 3, 5, 3, 3, 3, 3,
		0, 5, 3, 3, 3, 3, 6, 0, 0, 0, 0, 2, 0, 0, 0, 0,
		8, 5, 0, 0, 8, 0, 4, 8, 8, 8, 8, 6, 8, 8, 8, 8,
		3, 5, 8, 0, 1, 8, 5, 3, 3, 3, 1, 4, 1, 5, 3, 3,
		0, 3, 1, 0, 5, 3, 3, 0, 0, 0, 1, 7, 1, 1, 8, 0,
		8, 0, 5, 0, 5, 0, 8, 8, 0, 0, 1, 7, 5, 1, 1, 8,
		3, 0, 5, 0, 3, 0, 5, 5, 8, 0, 3, 3, 7, 5, 1, 1,
		0, 0, 5, 0, 0, 8, 5, 5, 3, 0, 0, 0, 1, 1, 1, 1, };

	Level map; //TileMap map;

	if (!map.load("tileset.png", sf::Vector2u(32, 32), level, 16, 8)) {
		std::cout << "Unable to load tileset.png" << std::endl;
		return EXIT_FAILURE;
	}

	sf::Font font;
	if (!font.loadFromFile("LiberationMono-Bold.ttf")) {
		std::cout << "Unable to load LiberationMono-Bold.ttf" << std::endl;
		return EXIT_FAILURE;
	}

	sf::Text health;
	health.setFont(font);
	std::stringstream s;
	std::string healthDisplay = playerStat(s, map.getPlayer());
	health.setString(healthDisplay);
	health.setPosition(0, 256);
	health.setCharacterSize(24);
	health.setFillColor(sf::Color::Red);

	sf::Sprite sprite;
	sf::Texture texture;

	texture.setRepeated(false);//load the sprite for the player
	if (!texture.loadFromFile("player.png")) {
		std::cout << "Unable to load player.png" << std::endl;
		return EXIT_FAILURE;
	}

//	texture.loadFromFile("player.png");  // TODO no need to repeat it :/

	//TODO TODONOW NOW

	sf::IntRect walkingRight(0, 64, 32, 32);
	sf::IntRect walkingUp(0, 96, 32, 32);
	sf::IntRect walkingLeft(0, 32, 32, 32);
	sf::IntRect walkingDown(0, 0, 32, 32);

	sprite.setTextureRect(walkingDown);
	sprite.setTexture(texture);
	//sprite.setPosition(0, 0);//sprite.setPosition(448,64);
	sprite.setScale(1, 1);

	sf::Vector2i spriteGameCoordinates{ 0, 0 };
	PlayerObject user;
	user.setObject(sprite);
	user.setDirectionFacing(DIRECTION::DOWN);
	//user.setDirectionFacing(DIRECTION::DOWN); // Cuz first sprite is walking down
	user.setGameCoordinates(spriteGameCoordinates);

	// Important put them in the same order as the enum DIRECTION
	user.getRects().push_back(walkingRight);
	user.getRects().push_back(walkingUp);
	user.getRects().push_back(walkingLeft);
	user.getRects().push_back(walkingDown);

	map.setPlayer(user);

	/********************************/

	sf::Sprite zombie;
	sf::Texture zombieTexture;
	if (!zombieTexture.loadFromFile("zombie.png")) {
		std::cout << "Unable to load zombie.png" << std::endl;
		return EXIT_FAILURE;
	}
	zombie.setTexture(zombieTexture);
	zombie.setPosition(32, 32);

	sf::Sprite stairs;
	stairs.setPosition(32, 32);
	sf::Texture stairsTexture;
	if (!stairsTexture.loadFromFile("stairs.png")) {
		std::cout << "Unable to load stairs.png" << std::endl;
		return EXIT_FAILURE;
	}
	stairs.setTexture(stairsTexture);

	sf::Sprite mist;
	sf::Texture mistTexture;
	if (!mistTexture.loadFromFile("mist.png")) {
		std::cout << "Unable to load mist.png" << std::endl;
		return EXIT_FAILURE;
	}
	const sf::Texture *mistPtr = &mistTexture;
	mistTexture.setRepeated(true);
	mist.setTexture(mistTexture);
	mist.setScale(2, 2);
	mist.setPosition(0, -32);

	/**********************************/
	EnemyObject enemyObj_zombie;
	enemyObj_zombie.setObject(zombie);
	enemyObj_zombie.setGameCoordinates(sf::Vector2i{ 1, 1 });
	map.addEnemy(enemyObj_zombie);

	GameObject gameObj_stairs;
	gameObj_stairs.setObject(stairs);
	gameObj_stairs.setGameCoordinates(sf::Vector2i{ 1, 1 });
	map.setStairs(gameObj_stairs);

	//main loop
	sf::Clock clock;
	unsigned int millisecondsSleep = 100000;
	while (window.isOpen())
	{
		sf::Event event;
		//event loop
		DIRECTION lastDirectionFrom = DIRECTION::RIGHT; // Just so some reasonable DIRECTION is here

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::KeyPressed:
					if (event.key.code == sf::Keyboard::W) {
						if (!map.canMove_Player(DIRECTION::UP))
							break;
						map.move_Player(DIRECTION::UP);
						lastDirectionFrom = DIRECTION::DOWN;
						std::cout << "UP: " << map.getPlayer().getGameCoordinates().x << ", " << map.getPlayer().getGameCoordinates().y << std::endl;
					}
					if (event.key.code == sf::Keyboard::A) {
						if (!map.canMove_Player(DIRECTION::LEFT))
							break;
						map.move_Player(DIRECTION::LEFT);
						lastDirectionFrom = DIRECTION::RIGHT;
						std::cout << "LEFT: " << map.getPlayer().getGameCoordinates().x << ", " << map.getPlayer().getGameCoordinates().y << std::endl;
					}
					if (event.key.code == sf::Keyboard::S) {
						if (!map.canMove_Player(DIRECTION::DOWN))
							break;
						map.move_Player(DIRECTION::DOWN);
						lastDirectionFrom = DIRECTION::UP;
						std::cout << "DOWN: " << map.getPlayer().getGameCoordinates().x << ", " << map.getPlayer().getGameCoordinates().y << std::endl;
					}
					if (event.key.code == sf::Keyboard::D) {
						if (!map.canMove_Player(DIRECTION::RIGHT))
							break;
						map.move_Player(DIRECTION::RIGHT);
						lastDirectionFrom = DIRECTION::LEFT;
						std::cout << "RIGHT: " << map.getPlayer().getGameCoordinates().x << ", " << map.getPlayer().getGameCoordinates().y << std::endl;
					}
					if (event.key.code == sf::Keyboard::Up) {
						map.getPlayer().setDirectionFacing(DIRECTION::UP);
						break;
					}
					if (event.key.code == sf::Keyboard::Left)
					{
						map.getPlayer().setDirectionFacing(DIRECTION::LEFT);
						break;
					}
					if (event.key.code == sf::Keyboard::Down)
					{
						map.getPlayer().setDirectionFacing(DIRECTION::DOWN);
						break;
					}
					if (event.key.code == sf::Keyboard::Right)
					{
						map.getPlayer().setDirectionFacing(DIRECTION::RIGHT);
						break;
					}
					if (event.key.code == sf::Keyboard::P)
					{
						std::cout << map.toString();
						break;
					}
					//if (event.key.code == sf::Keyboard::LControl)
					//{
					//	// TODO player attack in that direction
					//	map.playerAttack();
					//}

					map.enemy_AI_Movement();
					mist.move(0, .1); // I didn't touch this

				default:
					break;
			}
		}
	
		health.setString(playerStat(s, map.getPlayer()));
		window.clear();

		window.draw(map);
		window.draw(rectangle);
		//	window.draw(zombie);
		//	window.draw(sprite);
        window.draw(health);
		window.display();
        
        Level::saveGame(map); 
        
		//stuff needs to be drawn in the right order.
		//VERY IMPORTANT: collision detection is done after drawing
		//	if it's done before the bounds are not defined
		//  if(boundingBox.intersects(door)) {
//		//	level=levelGen();
		//	map=mapInit(level);
		//	//mapLoad(map,level);
		//	std::cout << "changed map" << std::endl;
		//	sprite.setPosition(448,64); // Game Coordinates are (14,2)
		//}

		if (map.isPlayerWhereEnemiesAre())
		{
			map.getPlayer().getDirectionFacing();
			map.ifCanThenMove_Player(lastDirectionFrom);

			DIRECTION temp = lastDirectionFrom;
			map.getPlayer().setDirectionFacing(-temp); // opposite of lastDirectionFrom so torwards enemy
			map.getPlayer().damage(1);
			std::cout << "1 damage" << std::endl;
		}

		//if (map.isPlayerWhereDoorIs())
		//{
		//	/*level = levelGen();
		//	mapInit(map, level);*/
		//	std::cout << "changed map" << std::endl;
		//	//map.randPos(map.getPlayer());
		//	map.moveToCoordinates(map.getPlayer(), sf::Vector2i{ 3, 0 });
		//}

		if (map.getPlayer().getHealth() <= 0) {
			std::cout << "You died" << std::endl;
			return 0;
		}

		s.str(""); //clear the health string
	}

	return 0;
}
