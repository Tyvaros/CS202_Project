#include "project.h"

std::string playerStat(std::stringstream & s, Actor & a) {
	s << a.getHealth();
	return s.str();
}
class TileMap : public sf::Drawable, public sf::Transformable
{
public:

    bool load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height)
    {
        // load the tileset texture
        if (!m_tileset.loadFromFile(tileset))
            return false;

        // resize the vertex array to fit the level size
        m_vertices.setPrimitiveType(sf::Quads);
        m_vertices.resize(width * height * 4);

        // populate the vertex array, with one quad per tile
        for (unsigned int i = 0; i < width; ++i)
            for (unsigned int j = 0; j < height; ++j)
            {
                // get the current tile number
                int tileNumber = tiles[i + j * width];

                // find its position in the tileset texture
                int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
                int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

                // get a pointer to the current tile's quad
                sf::Vertex* quad = &m_vertices[(i + j * width) * 4];

                // define its 4 corners
                quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
                quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
                quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
                quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

                // define its 4 texture coordinates
                quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
                quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
                quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
                quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
            }

        return true;
    }

private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // apply the transform
        states.transform *= getTransform();

        // apply the tileset texture
        states.texture = &m_tileset;

        // draw the vertex array
        target.draw(m_vertices, states);
    }

    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
};
int main()
{
	Actor player;
    sf::RenderWindow window(sf::VideoMode(512,256), "Project Window");
    
    sf::RectangleShape rectangle(sf::Vector2f(32,32));//top wall

	sf::Font font;
	if(!font.loadFromFile("LiberationMono-Bold.ttf")) {
		return -1;
	}
	//the tiles for the map, see picture for details
	//0=water,1=tree,2=grass/bottom bridge, 3= grass/bottom water, 4=grass/top bridge, 5=grass,6=bridge,7=flowers,8=grass/top bridge
	const int level[] {
		3, 5, 5, 1, 5, 1, 2, 3, 3, 3, 3, 5, 3, 3, 3, 3,
        0, 5, 3, 3, 3, 3, 6, 0, 0, 0, 0, 2, 0, 0, 0, 0,
        8, 5, 0, 0, 8, 0, 4, 8, 8, 8, 8, 6, 8, 8, 8, 8,
        3, 5, 8, 0, 1, 8, 5, 3, 3, 3, 1, 4, 1, 5, 3, 3,
        0, 3, 1, 0, 5, 3, 3, 0, 0, 0, 1, 7, 1, 1, 8, 0,
        8, 0, 5, 0, 5, 0, 8, 8, 0, 0, 1, 7, 5, 1, 1, 8,
        3, 0, 5, 0, 3, 0, 5, 5, 8, 0, 3, 3, 7, 5, 1, 1,
        0, 0, 5, 0, 0, 8, 5, 5, 3, 0, 0, 0, 1, 1, 1, 1,};
		
		
	TileMap map;
	if(!map.load("tileset.png",sf::Vector2u(32,32), level,16,8)) {
		return 1;
	}
	sf::Text health;
	health.setFont(font);
	std::stringstream s;
	std::string healthDisplay=playerStat(s,player);
	health.setString(healthDisplay);
	
	health.setPosition(0,0);
	health.setCharacterSize(24);
	health.setColor(sf::Color::Red);
	
	sf::Sprite sprite;
	sf::Texture texture;	
	
	texture.setRepeated(false);//load the sprite for the player
	if (!texture.loadFromFile("sprite.png")) {
			return -1;// error...
		}
	sprite.setTexture(texture);
	sprite.setPosition(0,0);
	sprite.setScale(1,.5);
	
	sf::Sprite zombie;
	sf::Texture zombie_texture;
	if(!zombie_texture.loadFromFile("zombie.png")) {
		return -1;
	}
	zombie.setTexture(zombie_texture);
	zombie.setPosition(64,156);
	
	int xCoor=(sprite.getPosition().x / 32);
	int yCoor = (int) (sprite.getPosition().y / 32);
	int index = xCoor+yCoor*16;
	//main loop
    while (window.isOpen()) {
        sf::Event event;
        //event loop
        while (window.pollEvent(event)) {
            switch (event.type) {
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::KeyPressed:
					xCoor=(int) (sprite.getPosition().x / 32);
					yCoor = (int) (sprite.getPosition().y / 32);
					index = xCoor+yCoor*16;
					if(event.key.code == sf::Keyboard::W) {
						if (index >= 16 && level[index-16] != 0) //check window bounds and water 
						sprite.move(0,-32);
					}
					if(event.key.code == sf::Keyboard::A) {
						if (index % 16 != 0 && level[index-1] != 0)
						sprite.move(-32,0);
					}
					if(event.key.code == sf::Keyboard::S) {
						if (index <=112 && level[index+16] != 0)
						sprite.move(0,32);
					}
					if(event.key.code == sf::Keyboard::D) {
						if (index % 16 != 15 && level[index+1] != 0)
						sprite.move(32,0);
						
					}
					
				default:
					break;
			}
        }
        
		std::cout<< "Health: "<<player.getHealth()<<std::endl;	
		
        window.clear();
        window.draw(map);
        window.draw(rectangle);
        window.draw(zombie);
        window.draw(sprite);
        window.draw(health);
        window.display();
        //stuff needs to be drawn in the right order.
        //VERY IMPORTANT: collision detection is done after drawing
        //	if it's done before the bounds are not defined
        sf::FloatRect boundingBox = sprite.getGlobalBounds();
		sf::FloatRect zombieBox = zombie.getGlobalBounds();
		
		if(boundingBox.intersects(zombieBox))
		{
			sprite.move(0,-32);
			player.damage(.1);
			
			//std::cout << "collision detected"<< std::endl;
		}	

		if(player.getHealth()<=0) {
			std::cout << "You died" <<std::endl;
			return 0;
		}
		
    }

    return 0;
}
