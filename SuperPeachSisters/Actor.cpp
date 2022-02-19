#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

/*
 It must have a constructor that initializes the object appropriately.
 It must be derived from our GraphObject class.
 It must have a member function named doSomething() that can be called to cause the actor to do something.
 You may add other public/private member functions and private data members to this base class, as you see fit.
 */


StudentWorld* Actor::getWorld() {
    return m_world;
}

bool Actor::actorOverlap(int otherX, int otherY, int otherWidth, int otherHeight) {
    int xPos = getX();
    int yPos = getY();
    int xMaxThis = xPos + SPRITE_WIDTH - 1;
    int yMaxThis = xPos + SPRITE_HEIGHT - 1;
    int xMaxOther = otherX + otherWidth - 1;
    int yMaxOther = otherY + otherHeight - 1;
    
    //if any x edge overlaps with the x edges of the other actor, and any y edge overlaps with the other y edge, there is overlap.
    if(((xPos < xMaxOther || xPos > otherX) || (xMaxThis < xMaxOther || xMaxThis > otherX)) &&
       ((yPos < yMaxOther || yPos > otherY) || (yMaxThis < yMaxOther || yMaxThis > otherY))) {
        return true;
    } else {
        return false;
    }
}

bool Actor::checkBonk() {
    Actor* object = getWorld()->overlap(getX(), getY(), SPRITE_WIDTH, SPRITE_HEIGHT);
    if(object != nullptr) {
        object->bonk();
        return true;
    }
    return false;
}

bool Creature::isAlive() {
    
    return alive;
}
void Creature::setAlive(bool status) {
    alive = status;
}
int Creature::getHitPoints() {
    return hitPoints;
}
void Creature::setHitPoints(int val) {

    hitPoints = val;
    if(hitPoints <= 0)
        alive = false;
}


bool Peach::doSomething() {
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
    checkBonk();
    
    int key;
    getWorld()->getKey(key);
    if(getWorld()->getKey(key)) {
        if(key == KEY_PRESS_LEFT) {
            setDirection(180);
            int nextX = getX() - 4;
            int bonked = checkBonk();
            if(!bonked)
                moveTo(nextX, getY());
        } else if(key == KEY_PRESS_RIGHT) {
            setDirection(0);
            int nextX = getX() + 4;
            int bonked = checkBonk();
            if(!bonked)
                moveTo(nextX, getY());
        }
    }
    return false;
}

void Peach::bonk() {
    int i = 0;
    i++;
}
