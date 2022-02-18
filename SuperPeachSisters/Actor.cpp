#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

/*
 It must have a constructor that initializes the object appropriately.
 It must be derived from our GraphObject class.
 It must have a member function named doSomething() that can be called to cause the actor to do something.
 You may add other public/private member functions and private data members to this base class, as you see fit.
 */

class Actor : public GraphObject {
    virtual void doSomething() = 0;
};
