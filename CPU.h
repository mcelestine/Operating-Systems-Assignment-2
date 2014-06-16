/**
 * File:      CPU.h
 * Author:    Makina Celestine  <mcelesti@hunter.cuny.edu>
 * Project:   CSCI340 Assignment 2
 * Notes:  
 *
 *
 * Hunter College 2012
 */

#ifndef CPU_H
#define CPU_H

#include "Process.h"
#include <iostream>

class CPU 
{
public:
    friend class System;
    
    CPU();
    void receiveProcess(Process *pc);
    void terminateProcess();
    
private:
    bool isOccupied;    //Returns true if the CPU is busy
    Process *current;   //Handle on process currently in CPU
};



#endif
