/**********|**********|**********|
Program: RoboCop.cpp
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

#include "RoboCop.h"
#include "TerminatorRoboCop.h"
#include <iostream>
using namespace std;

// Method to upgrade RoboCop to TerminatorRoboCop
void RoboCop::upgradeToTerminatorRoboCop(Robot* terminatorRoboCop) {
    // Create a new TerminatorRoboCop object with the current RoboCop's position and name
    terminatorRoboCop = new TerminatorRoboCop(getX(), getY(), getName(), battlefield);
    cout << name << " has upgraded to TerminatorRoboCop!" << endl;

    resetKills(); // Reset the number of kills for the upgraded robot

    // Copy the number of lives and kills from the current RoboCop to the new TerminatorRoboCop
    terminatorRoboCop->setLives(getLives());
    terminatorRoboCop->setKills(getKills());

    // Replace the current RoboCop with the new TerminatorRoboCop on the battlefield
    battlefield->removeRobotAt(getX(), getY()); // Remove the current RoboCop
    battlefield->addRobot(terminatorRoboCop);   // Add the new TerminatorRoboCop

    delete this; // Delete the current RoboCop object as it is now replaced
}
