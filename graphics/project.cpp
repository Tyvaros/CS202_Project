#include "project.h"

Actor::Actor() {	
	health_=10;
	movespeed_=.1;
}
	
	
void Actor::setHealth(int &x) {
	health_=x;
}
void Actor::damage(int x) {
	health_-=x;
}
	
int Actor::getHealth() {
	return health_;
}
void Enemy::updatePosition(sf::Sprite &s,const int* level) {
	int xCoor=(int) (s.getPosition().x / 32);
	int yCoor = (int) (s.getPosition().y / 32);
	int index = xCoor+yCoor*16;
						
	if (index >= 16 && level[index-16] != 0 && (rand()%4 ==2)) //check window bounds and water 
		s.move(0,-32);	
						
	if (index % 16 != 0 && level[index-1] != 0 && (rand()%4 ==4))
		s.move(-32,0);								
					
	if (index <=112 && level[index+16] != 0 && (rand()%4 ==1))
		s.move(0,32);						
						
	if (index % 16 != 15 && level[index+1] != 0 && (rand()%4 ==3))
		s.move(32,0);
	
	
}

//std::string playerStat(std::stringstream & s, Actor a) {
	//s << a.getHealth();
	//return s.str();
//}

