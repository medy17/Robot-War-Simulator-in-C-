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

#ifndef TERMINATOR_H
#define TERMINATOR_H

#include <string>
#include "Robot.h"
#include "MovingRobot.h"
#include "SteppingRobot.h"
#include "SeeingRobot.h"
#include "Battlefield.h"
#include <iostream>
using namespace std;

// Forward declares TerminatorRoboCop (To show it will be defined later)
class TerminatorRoboCop;

class Terminator : public virtual MovingRobot, public virtual SteppingRobot, public virtual SeeingRobot {
private:
    // Store the enemy's name
    string enemyName;
    // Flag to inficate enemy has been found
    bool enemyFound;
    // Coordinate of the enemy
    int enemyX, enemyY;

public:
    Terminator(int initX, int initY, string name, Battlefield* battlefield)
        : Robot(initX, initY, name, name[0], battlefield),
          MovingRobot(initX, initY, name, name[0], battlefield),
          SteppingRobot(initX, initY, name, name[0], battlefield),
          SeeingRobot(initX, initY, name, name[0], battlefield),
          enemyFound(false), enemyX(0), enemyY(0) {}

    void upgradeToTerminatorRoboCop(Robot*& terminatorRoboCop);

    // Look method to scan a 3x3 grid around Terminator
    void look(int x, int y) override {
        int startX = getX() - 1;
        int startY = getY() - 1;
        int endX = getX() + 1;
        int endY = getY() + 1;

        // Check if the 3x3 grid is within the battlefield boundaries
        if (startX < 0) startX = 0;
        if (startY < 0) startY = 0;
        if (endX >= battlefield->getWidth()) endX = battlefield->getWidth() - 1;
        if (endY >= battlefield->getHeight()) endY = battlefield->getHeight() - 1;

        // Check if the 3x3 grid has an enemy robot
        enemyFound = false;
        for (int i = startX; i <= endX; i++) {
            for (int j = startY; j <= endY; j++) {
                if (battlefield->hasRobotAt(i, j) && battlefield->getRobotAt(i, j)->getName() != getName()) {
                    cout << name << " is looking around and found enemy robot " << battlefield->getRobotAt(i, j)->getName() << endl;
                    enemyFound = true;
                    enemyY = j;
                    break; // Exit the inner loop if an enemy is found
                }
            }
            if (enemyFound) {
                enemyX = i;
                break; // Exit the outer loop if an enemy is found
            }
        }

        if (!enemyFound) {
            cout << name << " is looking around its immediate neighborhood." << endl;
        }
    }

    void move() override {
        int newX = getX();
        int newY = getY();
        int direction;

        if (enemyFound)
         { // If an enemy was found during look()
            newX = enemyX;
            newY = enemyY;
            enemyName = battlefield->getRobotAt(enemyX,enemyY)->getName();
            battlefield->removeRobotAt(enemyX, enemyY);
        } else { // If no enemy was found, move randomly
            do {
                direction = rand() % 8; // Generate a random number between 0 and 7

                switch (direction) {
                    case 0:
                        newY--; // Up
                        break;
                    case 1:
                        newY++; // Down
                        break;
                    case 2:
                        newX--; // Left
                        break;
                    case 3:
                        newX++; // Right
                        break;
                    case 4:
                        newX--; // Up Left
                        newY--;
                        break;
                    case 5:
                        newX++; // Up Right
                        newY--;
                        break;
                    case 6:
                        newX--; // Down Left
                        newY++;
                        break;
                    case 7:
                        newX++; // Down Right
                        newY++;
                        break;
                }
                // Check if the new position is within the battlefield boundaries
            } while (newX < 0 || newX >= battlefield->getWidth() || newY < 0 || newY >= battlefield->getHeight());
        }
        // If a valid move is found, update the robot's position
        cout << name << " moved to (" << newX << ", " << newY << ")" << endl;
        
        battlefield->updatePosition(getX(), getY(), newX, newY);
    }

    void step() override {
    if (enemyFound) {
        cout << name << " is stepping over enemy robot " << enemyName << endl;
        kills++;

        if (kills >= 3) {
            resetKills();
            Robot* terminatorRoboCop = nullptr; // Initialize pointer
            upgradeToTerminatorRoboCop(terminatorRoboCop); // Call the upgrade function
        }
    }
}



    void fire(int x, int y) override {
        // Terminator doesn't fire, so this can be left empty
    }
};
#endif