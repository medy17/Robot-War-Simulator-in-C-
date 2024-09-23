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
    bool enemyFound;
    int enemyX, enemyY;

public:
    TerminatorRoboCop(int initX, int initY, string name, Battlefield* battlefield)
        : Robot(initX, initY, name, name[0], battlefield),  // Initialize Robot base class
          RoboCop(initX, initY, name, battlefield),         // Initialize RoboCop
          Terminator(initX, initY, name, battlefield),      // Initialize Terminator
          MovingRobot(initX, initY, name, name[0], battlefield),    // Initialize MovingRobot
          ShootingRobot(initX, initY, name, name[0], battlefield),  // Initialize ShootingRobot
          SeeingRobot(initX, initY, name, name[0], battlefield),    // Initialize SeeingRobot
          SteppingRobot(initX, initY, name, name[0], battlefield),  // Initialize SteppingRobot
          enemyFound(false), enemyX(0), enemyY(0) {}


   void upgradeToUltimateRobot(Robot*& ultimateRobot);

    // Override methods from base classes as needed
    void look(int x, int y) override {
        Terminator::look(x, y);  // Call Terminator's look method
    }

    void move() override {
        RoboCop::move();  // Call RoboCop's move method
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
