#include "project.h"
#include <SFML/Graphics.hpp>
#include "AnimatedSprite.hpp"
#include <iostream>

std::string playerStat(std::stringstream & s, Actor & a) {
    s <<"HP: "<< a.getHealth();
    return s.str();
}
class TileMap : public sf::Drawable, public sf::Transformable
{
    
public:
    
    bool load(const std::string& tileset, sf::Vector2u tileSize, std::vector<int> tiles, unsigned int width, unsigned int height)
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
std::vector<int> levelGen() {//generates a random map
    std::vector<int> level(128);
    int sum=0;
    while(sum<140) {
        sum=0;
        for(int i=1;i<128;i++) {
            level[i]=(rand()%3);
        }
        for(int i=0;i<128;i++) {
            sum+=level[i];
        }
    }
    level[0]=1;
    level[1]=1;
    level[2]=1;
    level[17]=1;
    return level;
}
TileMap mapInit(std::vector<int> level) {//loads a new map
    
    TileMap map;
    if(!map.load("tilese_cave.png",sf::Vector2u(32,32), level,16,8)) {
        return map;
    }
    return map;
}
void randPos(sf::Transformable &s,std::vector<int> level) {
    int xCoor;
    int yCoor;
    
    while(true) {//This prevents the new position to be on an impassible space
        xCoor=(rand()%15)*32;
        yCoor = (rand()%7)*32;
        if(level[(xCoor/32)+(yCoor/32)*16] !=0) {
            s.setPosition(xCoor,yCoor);
            break;
        }
    }
    
}
//Important note, to make everything much easier,
//we should store all of the entities into a vector
//and then pass into the transform functions to
//draw,move,set everything at once
int main()
{
    srand(time(0));
    Player player;
    Enemy zombie1;
    sf::Vector2i screenDimensions(512,288);
    sf::RenderWindow window(sf::VideoMode(screenDimensions.x,screenDimensions.y), "Project Window");
    window.setFramerateLimit(60);
    
    sf::RectangleShape rectangle(sf::Vector2f(512,32));//healthbox
    rectangle.setPosition(0,256);
    
    //the tiles for the map, see picture for details
    //0=water,1=tree,2=grass/bottom bridge, 3= grass/bottom water, 4=grass/top bridge, 5=grass,6=bridge,7=flowers,8=grass/top bridge
    std::vector<int> level ={
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
    
    sf::Font font;
    if(!font.loadFromFile("LiberationMono-Bold.ttf")) {
        return -1;
    }
    
    sf::Text health;
    health.setFont(font);
    std::stringstream s;
    std::string healthDisplay=playerStat(s,player);
    health.setString(healthDisplay);
    health.setPosition(0,256);
    health.setCharacterSize(24);
    health.setColor(sf::Color::Red);
    
    sf::Sprite sprite;
    sf::Texture texture;
    
    texture.setRepeated(false);//load the sprite for the player
    if (!texture.loadFromFile("sprite.png")) {
        return -1;// error...
    }
    sprite.setTexture(texture);
    sprite.setPosition(448,64);
    sprite.setScale(.5,.5);
    
    sf::Sprite zombie;
    sf::Texture zombieTexture;
    if(!zombieTexture.loadFromFile("zombie.png")) {
        return -1;
    }
    zombie.setTexture(zombieTexture);
    zombie.setPosition(32,32);
    
    sf::Sprite stairs;
    stairs.setPosition(32,32);
    sf::Texture stairsTexture;
    if(!stairsTexture.loadFromFile("stairs.png")) {
        return -1;
    }
    stairs.setTexture(stairsTexture);
    
    sf::Sprite mist;
    sf::Texture mistTexture;
    if(!mistTexture.loadFromFile("mist.png")) {
        return -1;
    }
    const sf::Texture *mistPtr= &mistTexture;
    mistTexture.setRepeated(true);
    mist.setTexture(mistTexture);
    mist.setScale(2,2);
    mist.setPosition(0,-32);
    
    
    
    int xCoor=(sprite.getPosition().x / 32);
    int yCoor = (int) (sprite.getPosition().y / 32);
    int index = xCoor+yCoor*16;
    //main loop
    sf::Clock clock;
    while (window.isOpen()) {
        sf::Event event;
        //event loop
        sf::Time elapsed = clock.restart();
        
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
                    
                    zombie1.updatePosition(zombie,level);
                    health.setString(playerStat(s,player));
                    mist.move(0,.1);
                default:
                    break;
            }
        }
        
        window.clear();
        
        sf::FloatRect boundingBox = sprite.getGlobalBounds();
        sf::FloatRect zombieBox = zombie.getGlobalBounds();
        sf::FloatRect stairBox =stairs.getGlobalBounds();
        
        //window.draw(map2);
        window.draw(map);
        window.draw(stairs);
        window.draw(rectangle);
        window.draw(zombie);
        window.draw(sprite);
        window.draw(mist);
        window.draw(health);
        window.display();
        //stuff needs to be drawn in the right order.
        //VERY IMPORTANT: collision detection is done after drawing
        //	if it's done before the bounds are not defined
        if(boundingBox.intersects(stairBox)) {
            level=levelGen();
            map=mapInit(level);
            //mapLoad(map,level);
            std::cout << "changed map" << std::endl;
            randPos(zombie,level);
            randPos(sprite,level);
            randPos(stairs,level);
            mist.setPosition(0,-32);
            //stairs.setRotation((rand()%4)*90);
        }
        
        if(boundingBox.intersects(zombieBox)) {
            sprite.move(32,32);
            player.damage(1);
        }	
        
        if(player.getHealth()<=0) {
            std::cout << "You died" <<std::endl;
            return 0;
        }
        s.str(""); //clear the health string
    }
    
    return 0;
}
