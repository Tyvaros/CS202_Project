#include "project.h"

Actor::Actor() {
	health_=10;
	movespeed_=.1;
}
	
void Actor::setHealth(float &x) {
	health_=x;
}
void Actor::damage(float x) {
	health_-=x;
}
	
float Actor::getHealth() {
	return health_;
}
Tile::Tile() {
	height_=1;
	width_=1;
}
Tile::Tile(float h, float w) {
	height_=h;
	width_=w;
}
//std::string playerStat(std::stringstream & s, Actor a) {
	//s << a.getHealth();
	//return s.str();
//}

