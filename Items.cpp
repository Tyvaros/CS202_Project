//
//  Items.cpp
//  Group Project
//
//  Created by Thatcher Lane on 11/5/16.
//  Copyright © 2016 Thatcher Lane. All rights reserved.
//

#include "Items.h"

weapon::weapon(){}

weapon::~weapon(){
    delete this;
}

rangedWeapon::rangedWeapon(){}

rangedWeapon::~rangedWeapon(){
    delete this;
}

meleWeapon::meleWeapon(){}

meleWeapon::~meleWeapon(){
    delete this;
}

longBlade::longBlade(string name, int damage, int speed, int mass, int reach, int attackSpeed){
    name_=name;
    damage_=damage;
    speed_=speed;
    mass_=mass;
    reach_=reach;
    attackSpeed_= attackSpeed;
}

longBlade::~longBlade(){
    delete this;
}

shortBlade::shortBlade(string name, int damage, int speed, int mass, int reach, int attackSpeed){
    name_=name;
    damage_=damage;
    speed_=speed;
    mass_=mass;
    reach_=reach;
    attackSpeed_= attackSpeed;
}

shortBlade::~shortBlade(){
    delete this;
}

axe::axe(string name, int damage, int speed, int mass, int reach, int attackSpeed, int cleave){
    name_=name;
    damage_=damage;
    speed_=speed;
    mass_=mass;
    reach_=reach;
    attackSpeed_= attackSpeed;
    cleave_=cleave;
}

axe::~axe(){
    delete this;
}

impactWeapon::impactWeapon(string name, int damage, int speed, int mass, int reach, int attackSpeed){
    name_=name;
    damage_=damage;
    speed_=speed;
    mass_=mass;
    reach_=reach;
    attackSpeed_= attackSpeed;
}

impactWeapon::~impactWeapon(){
    delete this;
}

modifier::modifier(){}

modifier::~modifier(){
    delete this;
}

armor::armor(){}

armor::~armor(){
    delete this;
}

bodyArmor::bodyArmor(string name, int armorValue){
    name_=name;
    armorValue_ = armorValue;
}

bodyArmor::~bodyArmor(){
    delete this;
}

gloves::gloves(string name, int armorValue){
    name_=name;
    armorValue_=armorValue;
}

gloves::~gloves(){
    delete this;
}

boots::boots(string name, int armorValue){
    name_=name;
    armorValue_=armorValue;
}

boots::~boots(){
    delete this;
}

headGear::headGear(string name, int armorValue){
    name_=name;
    armorValue_=armorValue;
}

headGear::~headGear(){
    delete this;
}

cloak::cloak(string name, int armorValue){
    name_=name;
    armorValue_=armorValue;
}

cloak::~cloak(){
    delete this;
}

sheild::sheild(string name, int armorValue){
    name_=name;
    armorValue_=armorValue;
}

sheild::~sheild(){
    delete this;
}

consumable::consumable(){}

consumable::~consumable(){
    delete this;
}

void consumable::setStatus(){
    //still write this code;
}

healthPotion::healthPotion(string name, int healthBonus){
    name_=name;
    healthBonus_=healthBonus;
}

healthPotion::~healthPotion(){
    delete this;
}

void healthPotion::setStatus(){
    //still write this code;
}

speedPotion::speedPotion(string name, int speedBonus){
    name_=name;
    speedBonus_=speedBonus;
}

speedPotion::~speedPotion(){
    delete this;
}

void speedPotion::setStatus(){
    //still write this code;
}

food::food(string name, int healthBonus){
    name_=name;
    healthBonus_=healthBonus;
}

food::~food(){
    delete this;
}

void food::setStatus(){
    //still write this code;
}

ammunition::ammunition(string name, int ammunitionValue){
    name_=name;
    ammunitionValue_=ammunitionValue;
}

ammunition::~ammunition(){
    delete this;
}

void ammunition::setStatus(){
    //still write this code;
}
