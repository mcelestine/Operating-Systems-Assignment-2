/**
 * File:    main.cpp
 * Author:  Makina Celestine <mcelesti@hunter.cuny.edu>
 * Project: CSCI340 Assignment 2
 * Notes:  
 *
 *
 *
 * Hunter College 2012
 */

#include <iostream>
#include "System.h"
#include <sstream>
#include <iomanip>

using namespace std;


int main ()
{
    
    // Create a new system
    System simulator;
    
    // Start the simulation
    simulator.runSysGen();
    simulator.runSimulator();
    
    return 0;
}

