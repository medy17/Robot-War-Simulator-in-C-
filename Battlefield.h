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
#include "Robot.h"

using namespace std;

class Battlefield {
private:
    int m, n, steps; // Dimensions of the battlefield and the number of simulation steps
    vector<Robot *> robots; // List of active robots
    vector<Robot *> robotQueue; // Queue of destroyed robots for potential reactivation

public:
    // Constructor to initialize battlefield dimensions and number of steps
    Battlefield(int rows, int cols, int numSteps)
        : m(rows), n(cols), steps(numSteps) {}

    // Destructor to clean up dynamically allocated robot objects
    ~Battlefield() {
        cout << "\nSimulation Ends!" << endl;
        for (auto it = robots.begin(); it != robots.end(); ++it) {
            delete *it;
        }
        for (auto it = robotQueue.begin(); it != robotQueue.end(); ++it) {
            delete *it;
        }
    }

    // Adds a robot to the battlefield
    void addRobot(Robot *robot) {
        cout << robot->getName() << " is entering the Battlefield at (" << robot->getX() << ", " << robot->getY() << ")" << endl;
        robots.push_back(robot);
    }

    // Simulates the battlefield for a given number of steps
    void simulate() {
        srand(time(nullptr)); // Seed the random number generator

        for (int step = 0; step < steps; step++) {
            cout << "\nStep " << step + 1 << ":\n";

            for (auto it = robots.begin(); it != robots.end(); ) {
                Robot *robot = *it;
                if (robot->getLives() > 0) {
                    // Simulate robot actions: look, move, step, and fire
                    int randX = rand() % m;
                    int randY = rand() % n;
                    robot->look(randX, randY);
                    robot->move();
                    robot->step();
                    int fireX = rand() % m;
                    int fireY = rand() % n;
                    robot->fire(fireX, fireY);

                    it++;
                } else {
                    // If robot is destroyed, move it to the queue for potential reactivation
                    cout << "Robot destroyed: " << robot->getName() << ". Adding to queue." << endl;
                    robotQueue.push_back(robot);
                    it = robots.erase(it);
                }
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

            display(); // Display the battlefield after each step
            cout << endl; // Add a newline for clarity between steps
        }
    }

    // Displays the current state of the battlefield
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

    // Returns the width of the battlefield
    int getWidth() const { return n; }

    // Returns the height of the battlefield
    int getHeight() const { return m; }

    // Checks if there is a robot at the given coordinates
    bool hasRobotAt(int x, int y) const {
        for (Robot *robot : robots) {
            if (robot->getX() == x && robot->getY() == y) {
                return true;
            }
        }
        return false;
    }

    // Returns the robot at the given coordinates, or nullptr if none exists
    Robot *getRobotAt(int x, int y) const {
        for (Robot *robot : robots) {
            if (robot->getX() == x && robot->getY() == y) {
                return robot;
            }
        }
        return nullptr;
    }

    // Removes the robot at the given coordinates
    void removeRobotAt(int x, int y) {
        for (auto it = robots.begin(); it != robots.end(); ++it) {
            if ((*it)->getX() == x && (*it)->getY() == y) {
                cout << "Removing robot at (" << x << ", " << y << ")" << endl;
                delete *it;
                robots.erase(it);
                return;
            }
        }
    }

    // Updates the position of the robot from old coordinates to new coordinates
    void updatePosition(int oldX, int oldY, int newX, int newY) {
        for (Robot *robot : robots) {
            if (robot->getX() == oldX && robot->getY() == oldY) {
                cout << robot->getName() << " has moved from (" << oldX << ", " << oldY << ") to (" << newX << ", " << newY << ")" << endl;
                robot->setPosition(newX, newY);
                return;
            }
        }
    }
};
#endif
