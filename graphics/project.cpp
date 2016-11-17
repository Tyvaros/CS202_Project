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
void Enemy::updatePosition(sf::Sprite &s,std::vector<int> level) {
	int xCoor=(int) (s.getPosition().x / 32);
	int yCoor = (int) (s.getPosition().y / 32);
	int index = xCoor+yCoor*16;
	int direction= rand()%6;					
	if ((direction ==2) && index >= 16 && level[index-16] != 0) //check window bounds and water 
		s.move(0,-32);	
						
	if (direction==4 && index % 16 != 0 && level[index-1] != 0)
		s.move(-32,0);								
					
	if (direction ==1 && index <=112 && level[index+16] != 0)
		s.move(0,32);						
						
	if (direction ==3 && index % 16 != 15 && level[index+1] != 0)
		s.move(32,0);
		
	if (direction==5)
		s.move(0,0);
}

//std::string playerStat(std::stringstream & s, Actor a) {
	//s << a.getHealth();
	//return s.str();
//}

