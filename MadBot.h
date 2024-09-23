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

#ifndef MADBOT_H
#define MADBOT_H

#include <string>

#include "Robot.h"
#include "Battlefield.h"
#include "ShootingRobot.h"
#include <iostream>
using namespace std;

class UltimateRobot;

// MadBot class
class MadBot : public virtual ShootingRobot {
public:
    MadBot(int initX, int initY, string name, Battlefield* battlefield)
        : Robot(initX, initY, name, name[0], battlefield),
          ShootingRobot(initX, initY, name, name[0], battlefield) {}

    // Upgrading to ultimateRobot
    void upgradeToRoboTank(Robot*& roboTank);

    void look(int x, int y) override {}
    void move() override {}
    void step() override {}
    void fire(int x, int y) override {
        static int fireDirection = 0; // 0: Up, 1: Up Right, 2: Right, 3: Down Right, 4: Down, 5: Down Left, 6: Left, 7: Up Left
        int targetX = getX();
        int targetY = getY();

        switch (fireDirection) {
            case 0: targetY--; // Up
                break;
            case 1: targetX++; // Up Right
                targetY--;
                break;
            case 2: targetX++; // Right
                break;
            case 3: targetX++; // Down Right
                targetY++;
                break;
            case 4: targetY++; // Down
                break;
            case 5: targetX--; // Down Left
                targetY++;
                break;
            case 6: targetX--; // Left
                break;
            case 7: targetX--; // Up Left
                targetY--;
                break;
        }

        cout << name << " is firing at (" << targetX << ", " << targetY << ")" << endl;

        if (targetX >= 0 && targetX < battlefield->getWidth() && targetY >= 0 && targetY < battlefield->getHeight()) {
            if (battlefield->hasRobotAt(targetX, targetY) && battlefield->getRobotAt(targetX, targetY)->getName() != getName()) {
                cout << name << " killed " << battlefield->getRobotAt(targetX, targetY)->getName() << "!" << endl;
                kills++;
                battlefield->removeRobotAt(targetX, targetY); // Remove the enemy robot

                if (kills >= 3) {
                    cout << name << " has upgraded to RoboTank!" << endl;
                    resetKills(); // Reset kills
                    // Upgrade to RoboTank
                    Robot* roboTank = nullptr;
                    upgradeToRoboTank(roboTank);
                    
                }
            } else if (battlefield->hasRobotAt(targetX, targetY) && battlefield->getRobotAt(targetX, targetY)->getName() == getName()) {
                cout << name << " cannot fire at itself!" << endl;
            } else {
                cout << name << " fired at an empty location." << endl;
            }
        } else {
            cout << name << " cannot fire outside the battlefield boundaries." << endl;
        }

        fireDirection = (fireDirection + 1) % 8; // Move to the next firing direction
    }
};
#endif