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

#include "Terminator.h"
#include "TerminatorRoboCop.h"
#include "Battlefield.h"
#include <iostream>
using namespace std;

// Function to upgrade terminator into terminatorRoboCop
void Terminator::upgradeToTerminatorRoboCop(Robot*& terminatorRoboCop) 
{
    // Checks if pointer is not null to make sure i thas been initialized and points to a valid
    // memory locatio
    if (terminatorRoboCop) 
    {
        //Creates new TerminatorRoboCop object using the current Terminator's coordinates
        // and battlefield reference
        terminatorRoboCop = new TerminatorRoboCop(getX(), getY(), getName(), battlefield);

        // the current Terminator number of lives and kills to the new TerminatorRoboCop object
        terminatorRoboCop->setLives(getLives());
        terminatorRoboCop->setKills(getKills());

        // Notify and perform upgrade in battlefield
        cout << getName() << " has upgraded to TerminatorRoboCop!" << endl;
        battlefield->removeRobotAt(getX(), getY()); // Remove the old Terminator
        battlefield->addRobot(terminatorRoboCop);   // Add the new TerminatorRoboCop

        // Reset kills for the new upgraded robot
        resetKills();
    } 
    // Prints error message if terminator is not initialized correctly
    else 
    {
        cout << "Error: TerminatorRoboCop not initialized!" << endl;
    }
}
