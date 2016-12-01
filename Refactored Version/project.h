#ifndef _PROJECT_
#define _PROJECT_


#include <SFML/Graphics.hpp>
#include <math.h>
#include <string>
#include <iostream>
#include <sstream>
#include <ctime>
#include <vector>
#include <iterator>

class Actor 
{
public:
	Actor(); 
	void setHealth(int & x); 
	void damage(int x);
	int getHealth();
	void heal(int);
	
private:
	int health_;
	//int movespeed_;
};

//class Player: public Actor
//{
//public:
//	
//};
//class Enemy : public Actor
//{
//public:
//	void updatePosition(sf::Sprite &s,std::vector<int> level);
//};



/**************************************************************/

// Direction enum
// Needs to correspond to the order put into the array for different direction sprites
enum class DIRECTION { RIGHT, UP, LEFT, DOWN };

class TileMap : public sf::Drawable, public sf::Transformable
{
public:
	bool load(const std::string& tileset, sf::Vector2u tileSize, std::vector<int> tiles, unsigned int width, unsigned int height);

	std::vector<int>& getTiles();

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	std::vector<int> m_tiles;
	sf::VertexArray m_vertices;
	sf::Texture m_tileset;
};

class GameObject : public sf::Drawable, public sf::Transformable
{
public:
	virtual sf::Vector2i& getGameCoordinates();
	virtual sf::Sprite& getObject();

	virtual void setGameCoordinates(sf::Vector2i);
	virtual void setObject(sf::Sprite&);

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
private:
	sf::Vector2i m_gameCoordinates;
	sf::Sprite m_obj; // Error if unique
};

class EnemyObject : public GameObject, public Actor
{
	//TODO nothing?
};

class PlayerObject : public GameObject, public Actor
{
public:
	DIRECTION getDirectionFacing();
	void setDirectionFacing(DIRECTION);

	std::vector<sf::IntRect>& getRects();

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
private:
	std::vector<sf::IntRect> m_rects; // list of rectangular vertices of sprites in texture
	DIRECTION m_directionFacing;
	// Needs to have a texture to read correct sprite image from
};


class Level : public sf::Drawable, public sf::Transformable
{
public:
	bool load(const std::string& tileset, sf::Vector2u tileSize, std::vector<int> tiles, unsigned int width, unsigned int height);

	std::vector<GameObject>& getItems();
	std::vector<EnemyObject>& getEnemies();
	GameObject& getStairs();
	PlayerObject& getPlayer();
	int getTileNum(int x, int y);
	bool tileIsWalkable(sf::Vector2i);
	bool tileIsWalkable(int x, int y);
	void addItem(GameObject&);
	void addEnemy(EnemyObject&);
	void setPlayer(PlayerObject&);
	void setStairs(GameObject&);
	void enemy_AI_Movement();
	bool canMove_Enemy(int index, DIRECTION);
	bool canMove_Player(DIRECTION);
	bool canMove(GameObject&, DIRECTION);
	void move_Enemy(int index, DIRECTION);
	void move_Player(DIRECTION);
	void move(GameObject&, DIRECTION);
	//void moveToCoordinates(GameObject&, sf::Vector2i);
	//void moveToCoordinates(GameObject&, int x, int y);
	bool ifCanThenMove_Enemy(int index, DIRECTION);
	bool ifCanThenMove_Player(DIRECTION);
	bool ifCanThenMove(GameObject&, DIRECTION);
	bool isPlayerWhereEnemiesAre();
	bool isPlayerWhereDoorIs();
	TileMap& getTileMap();
	void setTileMap(TileMap&);
	sf::Vector2u getTileSize();
	//void Level::randPos(GameObject& obj);

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

private:
	std::vector<GameObject> m_Items;
	std::vector<EnemyObject> m_Enemies;
	PlayerObject m_Player;
	GameObject m_stairs;
	TileMap m_map;
	sf::Vector2u m_tileSize;
	sf::Vector2i m_sizeOfTileMap;
};

// Special Operators for directions
DIRECTION& operator-(DIRECTION&); //reverse DIRECTION
DIRECTION& operator++(DIRECTION&); // increment (counterclockwise)
DIRECTION operator++(DIRECTION&, int); // Postfix increment (counterclockwise)
DIRECTION& operator--(DIRECTION&); // decrement (clockwise)
DIRECTION operator--(DIRECTION&, int); //Postfix decrement (clockwise)

/**************************************************************/

#endif