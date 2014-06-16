/**
 * File:      CPU.cpp
 * Author:    Makina Celestine  <mcelesti@hunter.cuny.edu>
 * Project:   CSCI340 Assignment 2
 * Notes:  
 *
 *
 * Hunter College 2012
 */

#include "CPU.h"


// CPU initially doesn't have any jobs to complete
CPU::CPU() :isOccupied(false), current(0) {}


/**
 * receiveProcess takes a process 
 * and changes its state to RUNNING
 *
 */
void CPU::receiveProcess(Process *pc)
{
    cout <<"Process " << pc->PID << " is now in CPU"<< endl;
    pc->processState = RUNNING;
    current = pc; 
    isOccupied = true;
}

void CPU::terminateProcess()
{
    if (isOccupied == true)
    {
        current->processState = TERMINATED;
        delete current;
    }
    isOccupied = false;
    
}
