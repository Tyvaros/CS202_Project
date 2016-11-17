#ifndef _PROJECT_
#define _PROJECT_


#include <SFML/Graphics.hpp>
#include <math.h>
#include <string>
#include <iostream>
#include <sstream>
#include <ctime>
#include <vector>

class Actor 
{
public:
	Actor(); 
	void setHealth(int & x); 
	void damage(int x);
	int getHealth();
	
private:
	int health_;
	int movespeed_;
};
class Player: public Actor
{
public:
	
};
class Enemy : public Actor
{
public:
	void updatePosition(sf::Sprite &s,std::vector<int> level);
};
#endif
