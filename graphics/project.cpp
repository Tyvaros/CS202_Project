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

//std::string playerStat(std::stringstream & s, Actor a) {
	//s << a.getHealth();
	//return s.str();
//}

