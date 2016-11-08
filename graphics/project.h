#ifndef _PROJECT_
#define _PROJECT_


#include <SFML/Graphics.hpp>
#include <math.h>
#include <string>
#include <iostream>
#include <sstream>

class Actor 
{
public:
	Actor(); 
	void setHealth(float & x); 
	void damage(float x);
	float getHealth();
	
private:
	float health_;
	float movespeed_;
};

class Player : public Actor
{
public:
	
private:
};
class Tile
{
public:
	Tile();
	Tile(float h, float w);
private:
	float height_;
	float width_;
};
#endif
