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
    
    //if any x edge overlaps with the x edges of the other actor, and any y edge overlaps with the other y edge, there is overlap.

       if(((otherX <= xMaxThis && otherX >= xPos) && ((otherY <= yMaxThis && otherY >= yPos) || (yMaxOther <= yMaxThis && yMaxOther >= yPos))) ||
          ((xMaxOther <= xMaxThis && xMaxOther >= xPos) && ((otherY <= yMaxThis && otherY >= yPos) || (yMaxOther <= yMaxThis && yMaxOther >= yPos)))) {
        return true;
    } else {
        return false;
    }
}

bool Actor::edgeOverlap(int otherX, int otherY, int otherWidth, int otherHeight) {
    int xPos = getX();
    int xMaxThis = xPos + SPRITE_WIDTH - 1;
    int xMaxOther = otherX + otherWidth - 1;
    
    if((xMaxOther > xMaxThis && !checkBlocking(otherX + 8, otherY - 8)) || (otherX < xPos && !checkBlocking(otherX - 8, otherY - 8)))
        return true;
    else
       return false;
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
bool Actor::checkEdgeOverlap(int x, int y) {
    return getWorld()->checkEdge(this, x, y, SPRITE_WIDTH, SPRITE_HEIGHT);
}


bool Actor::isAlive() {
    
    return alive;
}
void Actor::setAlive(bool status) {
    alive = status;
}

void Peach::doSomething() {
    if(!isAlive()) {
        return;
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
    return;
}

void Peach::bonk(Actor* actor) {
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

void Peach::setTicks(int power) {
    if(power == 2 )
        starTicks = 150;
}

//=====BLOCK=====//
bool Object::blocksOthers() {
    return true;
}
bool Object::isDamageable() {
    return false;
}

void Block::doSomething() {
    return;
}

void Block::bonk(Actor* actor) {
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
void Pipe::doSomething() {
    return;
}

void Pipe::bonk(Actor* actor) {
}

//======Goomba=======//

bool Creature::blocksOthers() {
    return false;
}
bool Creature::isDamageable() {
    return true;
}
void Creature::bonk(Actor* actor) {

}
void Goomba::doSomething() {
    if(!isAlive())
        return;
    if(checkPeachOverlap()) {
        getWorld()->bonkPeach();
        return;
    }
    
    int nextX;
    if(getDirection() == 0) {
        nextX = getX() + 1;
        if(checkBlocking(nextX, getY()) || checkEdgeOverlap(nextX, getY())) {
            setDirection(180);
            return;
        }
    } else {
        nextX = getX() - 1;
        if(checkBlocking(nextX, getY()) || checkEdgeOverlap(nextX, getY())) {
            setDirection(0);
            return;
        }
    }
        
    moveTo(nextX, getY());
}

//======KOOPA=======//
void Koopa::doSomething() {
}

//====PIRANHA====//
void Piranha::doSomething() {
}

//=====FLOWER=======//
bool Goodie::blocksOthers() {
    return false;
}
bool Goodie::isDamageable() {
    return false;
}

void Goodie::doSomething() {
    if(checkPeachOverlap()) {
        overlapped();
        setAlive(false);
        getWorld()->playSound(SOUND_PLAYER_POWERUP);
        return;
    }
    if(!checkBlocking(getX(), getY() - 1) || !checkBlocking(getX(), getY() - 2)) {
        moveTo(getX(), getY() - 2);
    }
    int nextX;
    if(getDirection() == 0) {
        nextX = getX() + 2;
        if(checkBlocking(nextX, getY())) {
            setDirection(180);
            return;
        }
    } else {
        nextX = getX() - 2;
        if(checkBlocking(nextX, getY())) {
            setDirection(0);
            return;
        }
    }
    moveTo(nextX, getY());
}

void Flower::overlapped() {
    getWorld()->increaseScore(50);
    getWorld()->givePeachPower(2);
    getWorld()->peachSetTicks(2);
}

void Flower::bonk(Actor* actor) {
}

//=====MUSHROOM=======//

void Mushroom::overlapped() {
    getWorld()->increaseScore(75);
    getWorld()->givePeachPower(1);

}
void Mushroom::bonk(Actor* actor) {
    
}

//=====STAR=======//
void Star::overlapped() {
    getWorld()->increaseScore(100);
    getWorld()->givePeachPower(3);
    getWorld()->peachSetTicks(2);
    
}
void Star::bonk(Actor* actor) {
    
}
