/***|***|****|
Program: Battlefield.h
Course: Object Oriented Programming and Data Structures
Trimester: 2410
Name: Adriana binti Meor Azman
ID: 1211111079
Email: 1211111079@student.mmu.edu.my
Phone: 016-7199579
Name: Issye Lailiyah Binti Sopingi  
ID: 1231303279  
Email: 1231303279@student.mmu.edu.my
Phone: 014-3277626
Name: Zulaikha Afzan Binti Bee Wan  
ID: 1221102418  
Email: 1221102418@student.mmu.edu.my
Phone: 014-9738597
Name: Rahaf Khalid Hamed Mohamed Khier  
ID: 1221303108 
Email: 1221303108@student.mmu.edu.my
Phone: 011-62164425
Lecture Section: TC1L
Tutorial Section: TT4L
***|***|****/

#ifndef TERMINATORROBOCOP_H
#define TERMINATORROBOCOP_H

#include <iostream>
#include <string>
#include "Battlefield.h"
#include "Robot.h"
#include "RoboCop.h"
#include "Terminator.h"
#include "MovingRobot.h"
#include "ShootingRobot.h"
#include "SeeingRobot.h"
#include "SteppingRobot.h"

class UltimateRobot;

class TerminatorRoboCop : public RoboCop, public Terminator {
private:
    // This class no longer needs its own enemyFound variables,
    // it will use the protected ones from the Terminator parent class.

public:
    TerminatorRoboCop(int initX, int initY, string name, Battlefield* battlefield)
        : Robot(initX, initY, name, name[0], battlefield),  // Initialize Robot base class
          RoboCop(initX, initY, name, battlefield),         // Initialize RoboCop
          Terminator(initX, initY, name, battlefield),      // Initialize Terminator
          MovingRobot(initX, initY, name, name[0], battlefield),    // Initialize MovingRobot
          ShootingRobot(initX, initY, name, name[0], battlefield),  // Initialize ShootingRobot
          SeeingRobot(initX, initY, name, name[0], battlefield),    // Initialize SeeingRobot
          SteppingRobot(initX, initY, name, name[0], battlefield) {} // Initialize SteppingRobot


   void upgradeToUltimateRobot(Robot*& ultimateRobot);

    // Override methods from base classes as needed
    void look(int x, int y) override {
        Terminator::look(x, y);  // Call Terminator's look method
    }

    void move() override { // Implement a new "smarter" move method
        if (enemyFound) {
            // If look() found an enemy, use the Terminator's move logic to step on it.
            int oldX = getX();
            int oldY = getY();
            // Important: Check if a robot is actually there before trying to get its name
            if (battlefield->hasRobotAt(enemyX, enemyY)) {
                enemyName = battlefield->getRobotAt(enemyX, enemyY)->getName();
                battlefield->removeRobotAt(enemyX, enemyY);
            }
            cout << name << " moved to (" << enemyX << ", " << enemyY << ")" << endl;
            battlefield->updatePosition(this, oldX, oldY, enemyX, enemyY);
        } else {
            // Otherwise, move randomly like a RoboCop.
            RoboCop::move();
        }
    }

   void fire(int x, int y) override {
    RoboCop::fire(x, y); // Call RoboCop's fire method with the provided coordinates
}


    void step() override {
        Terminator::step();  // Call Terminator's step method
        if (kills >= 3){
            resetKills();
            Robot* ultimateRobot = nullptr;
            upgradeToUltimateRobot(ultimateRobot);
        }
    }
};

#endif