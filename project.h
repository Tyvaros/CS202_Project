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
	void setHealth(double & x); 
	void damage(double x);
	double getHealth();
	
private:
	double health_;
	double movespeed_;
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
	Tile(double h, double w);
private:
	double height_;
	double width_;
};
#endif
