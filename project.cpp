#include "project.h"

Actor::Actor() {
	health_=10;
	movespeed_=.1;
}
	
void Actor::setHealth(double &x) {
	health_=x;
}
void Actor::damage(double x) {
	health_-=x;
}
	
double Actor::getHealth() {
	return health_;
}
Tile::Tile() {
	height_=1;
	width_=1;
}
Tile::Tile(double h, double w) {
	height_=h;
	width_=w;
}
//std::string playerStat(std::stringstream & s, Actor a) {
	//s << a.getHealth();
	//return s.str();
//}

