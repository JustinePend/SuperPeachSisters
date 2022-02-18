#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

class Actor : public GraphObject {
public:
   
    Actor(int imageID, int startX, int startY, int dir = 0, int depth = 0, double size = 1.0)
     : GraphObject(imageID, startX, startY, dir, depth, size) {
    
    }

    virtual bool doSomething() = 0;
    
    bool actorOverlap(int otherX, int otherY, int otherWidth, int otherHeight) {
        int xPos = getX();
        int yPos = getY();
        int xMaxThis = xPos + SPRITE_WIDTH - 1;
        int yMaxThis = xPos + SPRITE_HEIGHT - 1;
        int xMaxOther = otherX + otherWidth - 1;
        int yMaxOther = otherY + otherHeight -1;
        
        //if any x edge overlaps with the x edges of the other actor, and any y edge overlaps with the other y edge, there is overlap.
        if(((xPos < xMaxOther || xPos > otherX) || (xMaxThis < xMaxOther || xMaxThis > otherX)) &&
           ((yPos < yMaxOther || yPos > otherY) || (yMaxThis < yMaxOther || yMaxThis > otherY))) {
            return true;
        } else {
            return false;
        }
    }
};

class Creature : public Actor {
public:
    Creature(int imageID, int startX, int startY, int dir = 0, int depth = 0, double size = 1.0)
    : Actor(imageID, startX, startY, dir, depth, size) {
        
    }
    bool isAlive() {
        return alive;
    }
    void setAlive(bool status) {
        alive = status;
    }
    int getHitPoints() {
        return hitPoints;
    }
    void setHitPoints(int val) {
        hitPoints = val;
        if(hitPoints <= 0)
            alive = false;
    }
    
private:
    bool alive = false;
    int hitPoints = 0;
    
};

class Peach : public Creature {
public:
    Peach(int startX, int startY) : Creature(IID_PEACH, startX, startY), tempInvincibility(false), starPower(false), shootPower(false), jumpPower(false), starTicks(0), tempTicks(0), fireTicks(0){
        setAlive(true);
        setHitPoints(1);
    
        
    }
    bool doSomething() {
        if(!isAlive()) {
            return false;
        }
        if(starPower) {
            starTicks --;
            if(starTicks <= 0)
                starPower = false;
        }
        if(tempInvincibility) {
            tempTicks --;
            if(tempTicks <= 0)
                tempInvincibility = false;
        }
        if(fireTicks > 0) {
            fireTicks --;
        }
        if(actorOverlap()) {
            
        }
    }
    
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
    void doSomething() {
        
    }
};

#endif // ACTOR_H_
