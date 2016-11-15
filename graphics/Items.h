//
//  Items.hpp
//  Group Project
//
//  Created by Thatcher Lane on 11/5/16.
//  Copyright © 2016 Thatcher Lane. All rights reserved.
//

#ifndef Items_h
#define Items_h
#include <iostream> 
using std::string;

class item {
public:
//    item();
protected:
    string name_;
};

class weapon : public item{
public:
    weapon();
    ~weapon();
    virtual int getDamage();
protected:
    int damage_;
    int speed_;
    int mass_;
};

class rangedWeapon : public weapon{
public:
    rangedWeapon();
    ~rangedWeapon();
    virtual int getDamage();
protected:
    int ammunition_;
    int projectileSpeed_;
};

class bow : public rangedWeapon{
public:
    bow(string name="bow", int ammunition=10, int projectileSpeed=1);
    ~bow();
    virtual int getDamage();
private:
    string name_;
    int ammunition_;
    int projectileSpeed_;
};

class meleWeapon : public weapon{
public:
    meleWeapon();
    ~meleWeapon();
    virtual int getDamage();
protected:
    int reach_;
    int cleave_;
    int attackSpeed_;
};

class longBlade : public meleWeapon{
public:
    longBlade(string name="sword", int damage=2, int speed=0, int reach=1, int cleave=3);
    ~longBlade();
    virtual int getDamage();
private:
};

class shortBlade : public meleWeapon{
public:
    shortBlade(string name="dagger", int damage=10, int speed=0, int reach=1, int cleave=1);
    ~shortBlade();
    virtual int getDamage();
private:
};

class polearm : public meleWeapon{
public:
    polearm(string name="polearm", int damage=2, int speed=0, int reach=2, int cleave=1);
    ~polearm();
    virtual int getDamage();
private:
    
};

class axe : public meleWeapon{
public:
    axe(string name="axe", int damage=2, int speed=0, int reach=1, int cleave=3);
    ~axe();
    virtual int getDamage();
private:
};

class impactWeapon : public meleWeapon{
public:
    impactWeapon(string name="impact weapon", int damage=2, int speed=0, int reach=1, int cleave=1);
    ~impactWeapon();
    virtual int getDamage(); 
private:
};

class modifier : public item{
public:
    modifier();
    ~modifier();
protected:
};

class armor : public modifier{
public:
    armor();
    ~armor();
protected:
    int armorValue_;
};

class bodyArmor : public armor{
public:
    bodyArmor(string name, int armorValue);
    ~bodyArmor();
private:
};

class gloves : public armor{
public:
    gloves(string name, int armorValue);
    ~gloves();
private:
};

class boots : public armor{
public:
    boots(string name, int armorValue);
    ~boots();
private:
};

class headGear : public armor{
public:
    headGear(string name, int armorValue);
    ~headGear();
private:
};

class cloak : public armor{
public:
    cloak(string name, int armorValue);
    ~cloak();
private:
};

class sheild : public armor{
public:
    sheild(string name, int armorValue);
    ~sheild();
private:
};

class consumable : public item{
public:
    consumable(); 
    ~consumable();
protected:
    virtual void setStatus();
};

class healthPotion : public consumable{
public:
    healthPotion(string name, int healthBonus);
    ~healthPotion();
private:
    int healthBonus_;
    virtual void setStatus();
};

class speedPotion : public consumable{
public:
    speedPotion(string name, int speedBonus);
    ~speedPotion();
private:
    int speedBonus_;
    virtual void setStatus();
};

class food : public consumable{
public:
    food(string name, int healthBonus);
    ~food();
private:
    int healthBonus_;
    virtual void setStatus();
};

class ammunition : public consumable{
public:
    ammunition(string name, int ammunitionValue);
    ~ammunition();
private:
    int ammunitionValue_;
    virtual void setStatus();
};

#endif /* Items_h */
