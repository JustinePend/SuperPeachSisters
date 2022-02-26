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
    int yMaxThis = yPos + SPRITE_HEIGHT - 1;
    int xMaxOther = otherX + otherWidth - 1;
    int yMaxOther = otherY + otherHeight - 1;
    
    //peach is other
    
    //if any x edge overlaps with the x edges of the other actor, and any y edge overlaps with the other y edge, there is overlap.

       if(((otherX <= xMaxThis && otherX >= xPos) && ((otherY <= yMaxThis && otherY >= yPos) || (yMaxOther <= yMaxThis && yMaxOther >= yPos))) ||
          ((xMaxOther <= xMaxThis && xMaxOther >= xPos) && ((otherY <= yMaxThis && otherY >= yPos) || (yMaxOther <= yMaxThis && yMaxOther >= yPos)))) {
        return true;
    } else {
        return false;
    }
}

//bool Actor::checkBonk() {
//    Actor* object = getWorld()->overlap(this);
//    if(object != nullptr) {
//        object->bonk();
//        return true;
//    }
//    return false;
//}

Actor* Peach::checkBonk(int x, int y) {
    Actor* object = getWorld()->overlap(this, x, y, SPRITE_WIDTH, SPRITE_HEIGHT);
    if(object != nullptr) {
        object->bonk();
    }
    return object;
}

bool Actor::isAlive() {
    
    return alive;
}
void Actor::setAlive(bool status) {
    alive = status;
}
int Creature::getHitPoints() {
    return hitPoints;
}
void Creature::setHitPoints(int val) {

    hitPoints = val;
    if(hitPoints <= 0)
        setAlive(false);
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
    if(checkBonk(getX(), getY()) != nullptr) {
        bonk();
    }
    
    int targetY = getY() + 4;
    if(!checkBonk(getX(), targetY) && remaining_jump_distance > 0 && hasJumped == true) {
        moveTo(getX(), targetY);
        remaining_jump_distance --;
    } else {
        remaining_jump_distance = 0;
        hasJumped = false;
    }
    
    if(!hasJumped) {
        bool below = false;
        for(int i = 0; i <= 3; i++) {
            if(checkBonk(getX(), getY() - i) != nullptr) {
                below = true;
                break;
            }
        }
        if(!below)
            moveTo(getX(), getY() - 4);
    }

    int key;
    if(getWorld()->getKey(key)) {
        if(key == KEY_PRESS_LEFT) {
            setDirection(180);
            int nextX = getX() - 4;
            int bonked = checkBonk(nextX, getY()) != nullptr; // pass in possible future of bonk
            if(!bonked)
                moveTo(nextX, getY());
        } else if(key == KEY_PRESS_RIGHT) {
            setDirection(0);
            int nextX = getX() + 4;
            int bonked = checkBonk(nextX, getY()) != nullptr;
            if(!bonked)
                moveTo(nextX, getY());
        } else if(key == KEY_PRESS_UP) {
            hasJumped = true;
            if(checkBonk(getX(), getY() - 1) != nullptr) {
                if(!jumpPower)
                    remaining_jump_distance = 8;
                else
                    remaining_jump_distance = 12;
                getWorld()->playSound(SOUND_PLAYER_JUMP);
            }
        }
    }
    return false;
}

void Peach::bonk() {
    int i = 0;
    i++;
}

bool Peach::blocksOthers() {
    return false;
}

bool Block::doSomething() {
    return false;
}

void Block::bonk() {
}
bool Block::blocksOthers() {
    return true;
}
Actor* Block::checkBonk(int x, int y) {
    Actor* actor = nullptr;
    return actor;
}


