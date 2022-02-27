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

void Actor::bonkPoint(int x, int y) {
    getWorld()->bonkAllAtPoint(this, x, y, SPRITE_WIDTH, SPRITE_HEIGHT);
}

bool Actor::checkBlocking(int x, int y) {
    return getWorld()->checkWithBlocking(this, x, y, SPRITE_WIDTH, SPRITE_HEIGHT);
}

bool Actor::checkPeachOverlap() {
    return getWorld()->overlapWithPeach(this);
}
bool Actor::isAlive() {
    
    return alive;
}
void Actor::setAlive(bool status) {
    alive = status;
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
    bonkPoint(getX(), getY());
    
    int targetY = getY() + 4;
    if(!checkBlocking(getX(), targetY) && remaining_jump_distance > 0 && hasJumped == true) {
        moveTo(getX(), targetY);
        remaining_jump_distance --;
    } else {
        bonkPoint(getX(), targetY);
        remaining_jump_distance = 0;
        hasJumped = false;
    }
    
    if(!hasJumped) {
        bool below = false;
        for(int i = 0; i <= 3; i++) {
            if(checkBlocking(getX(), getY() - i)) {
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
            if(!checkBlocking(nextX, getY()))
                moveTo(nextX, getY());
        } else if(key == KEY_PRESS_RIGHT) {
            setDirection(0);
            int nextX = getX() + 4;
            if(!checkBlocking(nextX, getY()))
                moveTo(nextX, getY());
        } else if(key == KEY_PRESS_UP) {
            hasJumped = true;
            if(checkBlocking(getX(), getY() - 1)) {
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

bool Peach::isDamageable() {
    return false;
}

int Peach::getHitPoints() {
    return hitPoints;
}
void Peach::setHitPoints(int val) {

    hitPoints = val;
    if(hitPoints <= 0)
        setAlive(false);
}

void Peach::setPower(int power) {
    //1 is mushroom, 2 is flower, 3 is star
    if(power == 1)
        jumpPower = true;
    if(power == 2)
        shootPower = true;
    if(power == 3)
        starPower = true;
}

//=====BLOCK=====//
bool Object::blocksOthers() {
    return true;
}
bool Object::isDamageable() {
    return false;
}

bool Block::doSomething() {
    return false;
}

void Block::bonk() {
    if(m_goodie == 0) {
        getWorld()->playSound(SOUND_PLAYER_BONK);
    } else {
        getWorld()->playSound(SOUND_POWERUP_APPEARS);
        switch(m_goodie) {
                //1 is mushroom, 2 is flower, 3 is star
            case 1: {
                Mushroom* mushroom = new Mushroom(getX(), getY() + 8, getWorld());
                getWorld()->addToActors(mushroom);
                break;
            } case 2: {
                Flower* flower = new Flower(getX(), getY() + 8, getWorld());
                getWorld()->addToActors(flower);
                break;
            } case 3: {
                Star* star = new Star(getX(), getY() + 8, getWorld());
                getWorld()->addToActors(star);
                break;
            }
        }
        m_goodie = 0;
    }
}


//===PIPE===//
bool Pipe::doSomething() {
    return false;
}

void Pipe::bonk() {
}

//======Goomba=======//

bool Creature::blocksOthers() {
    return false;
}
bool Creature::isDamageable() {
    return true;
}
void Creature::bonk() {
    
}
bool Goomba::doSomething() {
    return false;
}

//======KOOPA=======//
bool Koopa::doSomething() {
    return false;
}

//====PIRANHA====//
bool Piranha::doSomething() {
    return false;
}

//=====FLOWER=======//
bool Goodie::blocksOthers() {
    return false;
}
bool Goodie::isDamageable() {
    return false;
}

bool Flower::doSomething() {
    if(checkPeachOverlap()) {
        getWorld()->increaseScore(50);
    }
}

void Flower::bonk() {
    
}

//=====MUSHROOM=======//

bool Mushroom::doSomething() {
    return false;
}
void Mushroom::bonk() {
    
}

//=====STAR=======//
bool Star::doSomething() {
    return false;
}
void Star::bonk() {
    
}
