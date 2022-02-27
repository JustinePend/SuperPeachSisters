#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class StudentWorld;

class Actor : public GraphObject {
public:
    Actor(int imageID, int startX, int startY, StudentWorld* world, int dir = 0, int depth = 0, double size = 1.0)
     : GraphObject(imageID, startX, startY, dir, depth, size), m_world(world) {
    }

    virtual bool doSomething() = 0;
    virtual void bonk() = 0;
    StudentWorld* getWorld();
    bool actorOverlap(int otherX, int otherY, int otherWidth, int otherHeight);
    bool isAlive();
    void setAlive(bool status);
    virtual bool blocksOthers() = 0;
    virtual bool isDamageable() = 0;
    virtual Actor* checkBonk(int x, int y) = 0;


private:
    StudentWorld* m_world;
    bool alive = false;
};

//============================//


class Peach : public Actor {
public:
    Peach(int startX, int startY, StudentWorld* world, int dir = 0, int depth = 0, double size = 1.0)
    : Actor(IID_PEACH, startX, startY, world, dir, depth, size), tempInvincibility(false), starPower(false), shootPower(false), jumpPower(false), hasJumped(false), remaining_jump_distance(0), starTicks(0), tempTicks(0), fireTicks(0), hitPoints(0){
        setAlive(true);
        setHitPoints(1);
    }
    virtual Actor* checkBonk(int x, int y);
    void bonkPoint(int x, int y);
    bool checkBlocking(int x, int y);
    
    virtual bool doSomething();
    virtual void bonk();
    virtual bool blocksOthers();
    virtual bool isDamageable();
    int getHitPoints();
    void setHitPoints(int val);
    
private:
    bool tempInvincibility;
    bool starPower;
    bool shootPower;
    bool jumpPower;
    bool hasJumped;
    int remaining_jump_distance;
    int starTicks;
    int tempTicks;
    int fireTicks;
    int hitPoints;

};
//==================================================================================//
class Object : public Actor {
public:
    Object(int imageID, int startX, int startY, StudentWorld* world, int dir = 0, int depth = 2, double size = 1.0) : Actor(imageID, startX, startY, world, dir, depth, size) {
        }
    virtual bool isDamageable();
    virtual bool blocksOthers();

};

class Block : public Object {
public:
    Block(int startX, int startY, StudentWorld* world, int goodie) : Object(IID_BLOCK, startX, startY, world){
        m_goodie = goodie;
        setAlive(true);
    }
    virtual bool doSomething();
    virtual void bonk();
    virtual Actor* checkBonk(int x, int y);
private:
    int m_goodie;
};

class Pipe : public Object {
public:
    Pipe(int startX, int startY, StudentWorld* world) : Object(IID_PIPE, startX, startY, world) {
        setAlive(true);
    }
    virtual bool doSomething();
    virtual void bonk();
    virtual Actor* checkBonk(int x, int y);
};
//===========================//
class Creature: public Actor {
public:
    Creature(int imageID, int startX, int startY, StudentWorld* world, int dir = 0, int depth = 0, double size = 1.0) : Actor(imageID, startX, startY, world, dir, depth, size) {
    }
    virtual void bonk();
    virtual bool blocksOthers();
    virtual bool isDamageable();

};

class Goomba: public Creature {
public:
    Goomba(int startX, int startY, StudentWorld* world) : Creature(IID_GOOMBA, startX, startY, world) {
        setAlive(true);
    }
    virtual bool doSomething();
    virtual Actor* checkBonk(int x, int y);
};

class Koopa: public Creature {
public:
    Koopa(int startX, int startY, StudentWorld* world) : Creature(IID_KOOPA, startX, startY, world) {
        setAlive(true);
    }
    virtual bool doSomething();
    virtual Actor* checkBonk(int x, int y);
};

class Piranha: public Creature {
public:
    Piranha(int startX, int startY, StudentWorld* world) : Creature(IID_PIRANHA, startX, startY, world) {
        setAlive(true);
    }
    virtual bool doSomething();
    virtual Actor* checkBonk(int x, int y);
};
//===========================//

class Goodie : public Actor {
public:
    Goodie(int imageID, int startX, int startY, StudentWorld* world, int dir = 0, int depth = 0, double size = 1.0) : Actor(imageID, startX, startY, world, dir, depth, size) {
    }
    virtual bool blocksOthers();
    virtual bool isDamageable();
};

class Flower : public Goodie {
public:
    Flower(int startX, int startY, StudentWorld* world) : Goodie(IID_FLOWER, startX, startY, world) {
        setAlive(true);
    }
    virtual bool doSomething();
    virtual void bonk();
    virtual Actor* checkBonk(int x, int y);
};

class Mushroom : public Goodie {
public:
    Mushroom(int startX, int startY, StudentWorld* world) : Goodie(IID_MUSHROOM, startX, startY, world) {
        setAlive(true);
    }
    virtual bool doSomething();
    virtual void bonk();
    virtual Actor* checkBonk(int x, int y);
};

class Star : public Goodie {
public:
    Star(int startX, int startY, StudentWorld* world) : Goodie(IID_STAR, startX, startY, world) {
        setAlive(true);
    }
    virtual bool doSomething();
    virtual void bonk();
    virtual Actor* checkBonk(int x, int y);
};

//================//
//
//class Projectile : public Actor {
//public:
//    Projectile(int imageID, int startX, int startY, StudentWorld* world, int dir = 0, int depth = 2, double size = 1.0) : Actor(imageID, startX, startY, world, dir, depth, size) {
//    }
//    virtual bool doSomething();
//    virtual void bonk();
//    virtual bool blocksOthers();
//    virtual Actor* checkBonk(int x, int y);
//};
//
//class Fireball: public Projectile {
//    Fireball(int startX, int startY, StudentWorld* world) : Projectile(IID_PIRANHA_FIRE, startX, startY, world) {
//        setAlive(true);
//    }
//    virtual bool doSomething();
//    virtual void bonk();
//    virtual bool blocksOthers();
//    virtual Actor* checkBonk(int x, int y);
//};
//
//class PeachFireball: public Projectile {
//    PeachFireball(int startX, int startY, StudentWorld* world) : Projectile(IID_PEACH_FIRE, startX, startY, world) {
//        setAlive(true);
//    }
//    virtual bool doSomething();
//    virtual void bonk();
//    virtual bool blocksOthers();
//    virtual Actor* checkBonk(int x, int y);
//};
//
//class Shell: public Projectile {
//    Shell(int startX, int startY, StudentWorld* world) : Projectile(IID_SHELL, startX, startY, world) {
//        setAlive(true);
//    }
//    virtual bool doSomething();
//    virtual void bonk();
//    virtual bool blocksOthers();
//    virtual Actor* checkBonk(int x, int y);
//};

#endif // ACTOR_H_
