/**********|**********|**********|
Program: main.cpp
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

#include <iostream>
#include <fstream>    // For file operations
#include <sstream>    // For string stream operations
#include <string>
#include <cstdlib>    // For rand() and srand()
#include <ctime>      // For time() to seed the random number generator
#include <vector>
#include "Battlefield.h"
#include "Robot.h"
#include "TerminatorRoboCop.h"
#include "RoboCop.h"
#include "Terminator.h"
#include "BlueThunder.h"
#include "MadBot.h"
#include "RoboTank.h"
#include "UltimateRobot.h"
#include "MovingRobot.h"
#include "SteppingRobot.h"
#include "ShootingRobot.h"
#include "SeeingRobot.h"

using namespace std;

int main() {
    // Open the configuration file "config.txt"
    ifstream configFile("config.txt");
    if (!configFile.is_open()) {
        cerr << "Error opening config.txt" << endl;
        return 1; // Exit if the file cannot be opened
    }

    int m, n, steps, numRobots;
    string line;

    // Read battlefield dimensions
    getline(configFile, line);
    if (sscanf(line.c_str(), "M by N : %d %d", &m, &n) != 2) {
        cerr << "Error reading battlefield dimensions" << endl;
        return 1; // Exit if the dimensions cannot be read
    }

    // Read number of steps for the simulation
    getline(configFile, line);
    if (sscanf(line.c_str(), "steps: %d", &steps) != 1) {
        cerr << "Error reading number of steps" << endl;
        return 1; // Exit if the number of steps cannot be read
    }

    // Read number of robots
    getline(configFile, line);
    if (sscanf(line.c_str(), "robots: %d", &numRobots) != 1) {
        cerr << "Error reading number of robots" << endl;
        return 1; // Exit if the number of robots cannot be read
    }

    // Create the battlefield with the given dimensions and steps
    Battlefield battlefield(m, n, steps);

    // Read robot information from the configuration file and create robot objects
    for (int i = 0; i < numRobots; ++i) {
        getline(configFile, line);
        istringstream iss(line);
        string robotType, name;
        string xStr, yStr;
        int x, y;

        // Parse robot type, name, and coordinates
        if (!(iss >> robotType >> name >> xStr >> yStr)) {
            cerr << "Error reading robot information: " << line << endl;
            return 1; // Exit if robot information cannot be read
        }

        // Determine x-coordinate
        if (xStr == "random") {
            x = rand() % m; // Generate random x-coordinate within battlefield width
        } else {
            x = stoi(xStr); // Convert string to integer
        }

        // Determine y-coordinate
        if (yStr == "random") {
            y = rand() % n; // Generate random y-coordinate within battlefield height
        } else {
            y = stoi(yStr); // Convert string to integer
        }

        // Create robot based on the type and add to the battlefield
        if (robotType == "TerminatorRoboCop") {
            battlefield.addRobot(new TerminatorRoboCop(x, y, name, &battlefield));
        } else if (robotType == "RoboCop") {
            battlefield.addRobot(new RoboCop(x, y, name, &battlefield));
        } else if (robotType == "Terminator") {
            battlefield.addRobot(new Terminator(x, y, name, &battlefield));
        } else if (robotType == "BlueThunder") {
            battlefield.addRobot(new BlueThunder(x, y, name, &battlefield));
        } else if (robotType == "MadBot") {
            battlefield.addRobot(new MadBot(x, y, name, &battlefield));
        } else if (robotType == "RoboTank") {
            battlefield.addRobot(new RoboTank(x, y, name, &battlefield));
        } else if (robotType == "UltimateRobot") {
            battlefield.addRobot(new UltimateRobot(x, y, name, &battlefield));
        } else {
            cerr << "Invalid robot type: " << robotType << endl;
            return 1; // Exit if an invalid robot type is encountered
        }
    }

    configFile.close(); // Close the configuration file

    srand(time(0)); // Seed the random number generator
    battlefield.simulate(); // Start the battlefield simulation

    return 0;
}
