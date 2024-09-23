/**********|**********|**********|
Program: BlueThunder.h
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
**********|**********|**********/

#ifndef BLUETHUNDER_H
#define BLUETHUNDER_H

#include <iostream>
#include <string>
#include "Robot.h"
#include "Battlefield.h"
#include "ShootingRobot.h"
using namespace std;

class MadBot; // Forward declaration of the MadBot class

// BlueThunder class derived from ShootingRobot
class BlueThunder : public virtual ShootingRobot {
public:
    // Constructor for BlueThunder
    BlueThunder(int initX, int initY, string name, Battlefield *battlefield)
        : Robot(initX, initY, name, name[0], battlefield), // Initialize the base Robot class
          ShootingRobot(initX, initY, name, name[0], battlefield) {} // Initialize the ShootingRobot class

    // Method to upgrade BlueThunder to MadBot
    void upgradeToMadBot(Robot*& madBot); // Pass madBot by reference to pointer

    // Override the look method (currently does nothing)
    void look(int x, int y) override {}

    // Override the move method (currently does nothing)
    void move() override {}

    // Override the step method (currently does nothing)
    void step() override {}

    // Override the fire method
    void fire(int x, int y) override {
        static int fireDirection = 0; // 0: Up, 1: Up Right, 2: Right, 3: Down Right, 4: Down, 5: Down Left, 6: Left, 7: Up Left
        int targetX = getX(); // Initial target X coordinate
        int targetY = getY(); // Initial target Y coordinate

        // Determine the firing direction
        switch (fireDirection) {
        case 0:
            targetY--; // Up
            break;
        case 1:
            targetX++; // Up Right
            targetY--;
            break;
        case 2:
            targetX++; // Right
            break;
        case 3:
            targetX++; // Down Right
            targetY++;
            break;
        case 4:
            targetY++; // Down
            break;
        case 5:
            targetX--; // Down Left
            targetY++;
            break;
        case 6:
            targetX--; // Left
            break;
        case 7:
            targetX--; // Up Left
            targetY--;
            break;
        }

        // Output the firing action
        cout << name << " is firing at (" << targetX << ", " << targetY << ")" << endl;

        // Check if the target coordinates are within the battlefield boundaries
        if (targetX >= 0 && targetX < battlefield->getWidth() && targetY >= 0 && targetY < battlefield->getHeight()) {
            // Check if there's a robot at the target location and if it's not the same robot
            if (battlefield->hasRobotAt(targetX, targetY) && battlefield->getRobotAt(targetX, targetY)->getName() != getName()) {
                cout << name << " killed " << battlefield->getRobotAt(targetX, targetY)->getName() << "!" << endl;
                kills++; // Increment the kill count
                battlefield->removeRobotAt(targetX, targetY); // Remove the enemy robot

                // Check if BlueThunder has enough kills to upgrade to MadBot
                if (kills >= 3) {
                    cout << name << " has upgraded to MadBot!" << endl;
                    resetKills(); // Reset the kill count
                    Robot* madBot = nullptr; // Initialize the MadBot pointer
                    upgradeToMadBot(madBot); // Call the upgrade function
                }
            } else if (battlefield->hasRobotAt(targetX, targetY) && battlefield->getRobotAt(targetX, targetY)->getName() == getName()) {
                // Check if BlueThunder is trying to fire at itself
                cout << name << " cannot fire at itself!" << endl;
            } else {
                // Output if BlueThunder fired at an empty location
                cout << name << " fired at an empty location." << endl;
            }
        } else {
            // Output if BlueThunder is trying to fire outside the battlefield boundaries
            cout << name << " cannot fire outside the battlefield boundaries." << endl;
        }

        // Move to the next firing direction
        fireDirection = (fireDirection + 1) % 8;
    }
};

#endif // BLUETHUNDER_H
