/**********|**********|**********|
Program: BlueThunder.cpp
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

#include "BlueThunder.h"
#include "MadBot.h"
#include "Battlefield.h"
#include <iostream>
#include <string>
using namespace std;

// Method to upgrade a BlueThunder robot to a MadBot
void BlueThunder::upgradeToMadBot(Robot*& madBot) {
    Robot* oldRobot = this;

    // Create a new MadBot at the current position of the BlueThunder robot
    madBot = new MadBot(getX(), getY(), getName(), battlefield);

    // Transfer the lives from the current BlueThunder robot to the new MadBot
    madBot->setLives(getLives());

    // Output a message indicating the upgrade
    cout << name << " has upgraded to MadBot!" << endl;

    // Queue the new robot for addition and mark the old one for removal.
    battlefield->addRobot(madBot);
    battlefield->markRobotForRemoval(oldRobot);
}