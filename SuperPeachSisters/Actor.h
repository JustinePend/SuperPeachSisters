#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

class Actor : public GraphObject {
public:
    Actor(int imageID, int startX, int startY, StudentWorld* world, int dir = 0, int depth = 0, double size = 1.0)
     : GraphObject(imageID, startX, startY, dir, depth, size), m_world(world) {
    }
    virtual bool doSomething() = 0;
    virtual void bonk() = 0;
    StudentWorld* getWorld();
    bool actorOverlap(int otherX, int otherY, int otherWidth, int otherHeight);
    bool checkOverlap();

private:
    StudentWorld* m_world;
};

class Creature : public Actor {
public:
    Creature(int imageID, int startX, int startY, StudentWorld* world, int dir = 0, int depth = 0, double size = 1.0)
    : Actor(imageID, startX, startY, world, dir, depth, size) {
        }
    bool isAlive();
    void setAlive(bool status);
    int getHitPoints();
    void setHitPoints(int val);
    
private:
    bool alive = false;
    int hitPoints = 0;
};

class Peach : public Creature {
public:
    Peach(int startX, int startY, StudentWorld* world) : Creature(IID_PEACH, startX, startY, world), tempInvincibility(false), starPower(false), shootPower(false), jumpPower(false), starTicks(0), tempTicks(0), fireTicks(0){
        setAlive(true);
        setHitPoints(1);
    }
    bool doSomething();
    
private:
    bool tempInvincibility;
    bool starPower;
    bool shootPower;
    bool jumpPower;
    int starTicks;
    int tempTicks;
    int fireTicks;
};
//==================================================================================//
class Object : public Actor {

};

class Block : public Actor {
public:
//    void doSomething() {
//
//    }
};



#endif // ACTOR_H_
