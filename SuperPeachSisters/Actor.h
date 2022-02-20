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
//    ~Actor() {
//
//    }
    virtual bool doSomething() = 0;
    virtual void bonk() = 0;
    StudentWorld* getWorld();
    bool actorOverlap(int otherX, int otherY, int otherWidth, int otherHeight);
    bool checkBonk();
    bool isAlive();
    void setAlive(bool status);

private:
    StudentWorld* m_world;
    bool alive = false;
};

class Creature : public Actor {
public:
    Creature(int imageID, int startX, int startY, StudentWorld* world, int dir = 0, int depth = 0, double size = 1.0)
    : Actor(imageID, startX, startY, world, dir, depth, size) {
        }


    int getHitPoints();
    void setHitPoints(int val);
    
private:

    int hitPoints = 0;
};

class Peach : public Creature {
public:
    Peach(int startX, int startY, StudentWorld* world) : Creature(IID_PEACH, startX, startY, world), tempInvincibility(false), starPower(false), shootPower(false), jumpPower(false), starTicks(0), tempTicks(0), fireTicks(0){
        setAlive(true);
        setHitPoints(1);
    }
    virtual bool doSomething();
    virtual void bonk();
    
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
public:
    Object(int imageID, int startX, int startY, StudentWorld* world, int dir = 0, int depth = 2, double size = 1.0) : Actor(imageID, startX, startY, world, dir, depth, size) {

        }

};

class Block : public Object {
public:
    Block(int startX, int startY, StudentWorld* world) : Object(IID_BLOCK, startX, startY, world) {
        setAlive(true);
    }
    virtual bool doSomething();
    virtual void bonk();
};



#endif // ACTOR_H_
