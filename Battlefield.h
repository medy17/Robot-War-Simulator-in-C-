/**********|**********|**********|
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
**********|**********|**********/

#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm> // Needed for std::remove and std::find
#include "Robot.h"

using namespace std;

class Battlefield {
private:
    int m, n, steps;
    vector<Robot *> robots;
    vector<Robot *> robotQueue;
    // A temporary list for robots to be added at the end of a step
    vector<Robot *> robotsToAdd;
    // A temporary list for robots to be removed at the end of a step
    vector<Robot *> robotsToRemove;

public:
    Battlefield(int rows, int cols, int numSteps)
        : m(rows), n(cols), steps(numSteps) {}

    ~Battlefield() {
        cout << "\nSimulation Ends!" << endl;
        for (auto robot : robots) {
            delete robot;
        }
        for (auto robot : robotQueue) {
            delete robot;
        }
        for (auto robot : robotsToAdd) { // Just in case any are left over
            delete robot;
        }
        for (auto robot : robotsToRemove) {
            delete robot;
        }
    }

    void addRobot(Robot *robot) {
        // Instead of adding immediately, queue the robot for addition at the end of the step.
        cout << robot->getName() << " is queued to enter the Battlefield at (" << robot->getX() << ", " << robot->getY() << ")" << endl;
        robotsToAdd.push_back(robot);
    }

    void simulate() {
        srand(static_cast<unsigned int>(time(nullptr)));

        // --- Initial Population ---
        // Add robots from the config file before the simulation starts
        if (!robotsToAdd.empty()) {
            for (Robot* toAdd : robotsToAdd) {
                cout << toAdd->getName() << " is entering the Battlefield at (" << toAdd->getX() << ", " << toAdd->getY() << ")" << endl;
                robots.push_back(toAdd);
            }
            robotsToAdd.clear();
        }

        for (int step = 0; step < steps; step++) {
            cout << "\nStep " << step + 1 << ":\n";

            for (size_t i = 0; i < robots.size(); ++i) {
                Robot *robot = robots[i];

                // --- ZOMBIE CHECK ---
                // If this robot was killed by another robot earlier in the same step,
                // it should not get to take its turn.
                if (std::find(robotsToRemove.begin(), robotsToRemove.end(), robot) != robotsToRemove.end()) {
                    continue; // Skip this robot's turn, it's a "zombie".
                }

                if (robot->getLives() > 0) {
                    int randX = rand() % m;
                    int randY = rand() % n;
                    robot->look(randX, randY);
                    robot->move();
                    robot->step();
                    int fireX = rand() % m;
                    int fireY = rand() % n;
                    robot->fire(fireX, fireY);
                } else {
                    cout << "Robot destroyed: " << robot->getName() << ". Adding to queue." << endl;
                    robotQueue.push_back(robot);
                    // Mark for removal instead of deleting immediately
                    robotsToRemove.push_back(robot);
                }
            }

            // --- SWEEP PHASE ---
            // Now, safely remove all the robots that were marked for deletion
            if (!robotsToRemove.empty()) {
                for (Robot* toRemove : robotsToRemove) {
                    // The erase-remove idiom is a standard way to remove elements
                    robots.erase(std::remove(robots.begin(), robots.end(), toRemove), robots.end());
                }
                // We don't delete the pointers here because they are now in the robotQueue
                robotsToRemove.clear(); // Clear the list for the next step
            }

            // --- ADDITION PHASE ---
            // Now, safely add all the new robots that were created this step (e.g., from upgrades)
            if (!robotsToAdd.empty()) {
                for (Robot* toAdd : robotsToAdd) {
                     cout << toAdd->getName() << " is now active on the Battlefield." << endl;
                    robots.push_back(toAdd);
                }
                robotsToAdd.clear(); // Clear the list for the next step
            }


            // Reactivate destroyed robots from the queue
            if (!robotQueue.empty()) {
                Robot *reactivatedRobot = robotQueue.front();
                robotQueue.erase(robotQueue.begin());

                if (reactivatedRobot->getLives() > 0) {
                    reactivatedRobot->setLives(reactivatedRobot->getLives() - 1);
                    robots.push_back(reactivatedRobot);
                    cout << reactivatedRobot->getName() << " has been reactivated!" << endl;
                } else {
                    cout << "Removing robot permanently: " << reactivatedRobot->getName() << endl;
                    delete reactivatedRobot;
                }
            }

            display();
            cout << endl;
        }
    }

    void display() const {
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                bool robotFound = false;
                for (Robot *robot : robots) {
                    if (robot->getX() == j && robot->getY() == i) {
                        cout << robot->getSymbol() << " ";
                        robotFound = true;
                        break;
                    }
                }
                if (!robotFound) {
                    cout << ". ";
                }
            }
            cout << endl;
        }
    }

    int getWidth() const { return n; }
    int getHeight() const { return m; }

    bool hasRobotAt(int x, int y) const {
        for (Robot *robot : robots) {
            if (robot->getX() == x && robot->getY() == y) {
                return true;
            }
        }
        return false;
    }

    Robot *getRobotAt(int x, int y) const {
        for (Robot *robot : robots) {
            if (robot->getX() == x && robot->getY() == y) {
                return robot;
            }
        }
        return nullptr;
    }

    // --- MODIFIED REMOVE FUNCTION ---
    // Instead of deleting, we "mark" the robot for deletion.
    void removeRobotAt(int x, int y) {
        Robot* robotToMark = nullptr;
        for (auto it = robots.begin(); it != robots.end(); ++it) {
            if ((*it)->getX() == x && (*it)->getY() == y) {
                robotToMark = *it;
                break;
            }
        }

        if (robotToMark != nullptr) {
            cout << "Marking " << robotToMark->getName() << " at (" << x << ", " << y << ") for removal." << endl;
            // Add to the list, but avoid adding duplicates
            if (std::find(robotsToRemove.begin(), robotsToRemove.end(), robotToMark) == robotsToRemove.end()) {
                robotsToRemove.push_back(robotToMark);
            }
        }
    }

    // A new, safer way to mark a robot for removal using its pointer.
    // This avoids the ambiguity of removing by coordinates during an upgrade.
    void markRobotForRemoval(Robot* robot) {
        cout << "Marking " << robot->getName() << " (" << robot << ") for removal." << endl;
        if (std::find(robotsToRemove.begin(), robotsToRemove.end(), robot) == robotsToRemove.end()) {
            robotsToRemove.push_back(robot);
        }
    }

    void updatePosition(Robot* movingRobot, int oldX, int oldY, int newX, int newY) {
        // This is now unambiguous. We know exactly which robot is moving.
        cout << movingRobot->getName() << " has moved from (" << oldX << ", " << oldY << ") to (" << newX << ", " << newY << ")" << endl;
        movingRobot->setPosition(newX, newY);
    }
};
#endif