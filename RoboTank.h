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

#ifndef ROBOTANK_H
#define ROBOTANK_H
#include <string>
#include "Robot.h"
#include "Battlefield.h"
#include "ShootingRobot.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;


//RoboTank class
class RoboTank : public virtual ShootingRobot 
{
public:
    // Constructor and initialization
    RoboTank(int initX, int initY, string name, Battlefield* battlefield)
        : Robot(initX, initY, name, name[0], battlefield),
          ShootingRobot(initX, initY, name, name[0], battlefield) {}

    void upgradeToUltimateRobot(Robot*& ultimateRobot);
    
    // Look, move and step are empty as RoboTank does no provide the actions
    void look(int x, int y) override {}
    void move() override {}
    void step() override {}
    void fire(int x, int y) override 
    {   
        // Randomly generates targetX and targetY within the boundaries of battlefield using rand
        int targetX = rand() % battlefield->getWidth();
        int targetY = rand() % battlefield->getHeight();

        cout << name << " is firing at (" << targetX << ", " << targetY << ")" << endl;
        
        // Ensures the target is within the boundaries
        if (targetX >= 0 && targetX < battlefield->getWidth() && targetY >= 0 && targetY < battlefield->getHeight()) 
        {
            // Check if there is robot at target coordinates & if the robot it detected is itself
            // If there's robot there, it announces that RoboTank has killed the robot
            // Kills will be incremented
            if (battlefield->hasRobotAt(targetX, targetY) && battlefield->getRobotAt(targetX, targetY)->getName() != getName()) {
                cout << name << " killed " << battlefield->getRobotAt(targetX, targetY)->getName() << "!" << endl;
                kills++;
                // Removes the killed robot from the battlefield
                battlefield->removeRobotAt(targetX, targetY); // Remove the enemy robot
                
                // If it has achieved 3 or more kills, it will be upgraded to UltimateRobot
            if (kills >= 3)
          {
            resetKills();
            Robot* ultimateRobot = nullptr;
            upgradeToUltimateRobot(ultimateRobot);
          }
            }
            // Check if the robot is trying to fire at itself
             else if (battlefield->hasRobotAt(targetX, targetY) && battlefield->getRobotAt(targetX, targetY)->getName() == getName()) 
            {
                cout << name << " cannot fire at itself!" << endl;
            } 
            // Announces that the robot is firing at an empty place
            else
            {
                cout << name << " fired at an empty location." << endl;
            }
        }
            // Generates error messge if coordinate is out of battlefield's boundaries
            else 
            {
                cout << name << " cannot fire outside the battlefield boundaries." << endl;
            }
    }
};
#endif