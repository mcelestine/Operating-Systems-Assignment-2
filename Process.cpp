/**
 * File:    Process.cpp
 * Author:  Makina Celestine <mcelesti@hunter.cuny.edu>
 * Project: CSCI340 Assignment 2
 * Notes:
 *
 *
 *
 * Hunter College 2012
 */

#include "Process.h"

Process::Process(int p)
{
    processState = NEW;
    PID = p;
    filename = "";
    memLocation = 0;
    action ="";
    lengthOfFile = 0;
    read = false;
    write = false;
    timeInCPU = 0;
    numOfBursts = 0;
    cylinderRequest = 0;
}

void Process::setPrintRequestInfo()
{
    processState = WAITING;
    
    write = true;
    cout << "Enter file name(25 characters or less): ";
    cin >> filename;
    
    while ((cout << "Enter starting location in memory: ")
           && !(cin >> memLocation))
    {
        cout << "Invalid input. Enter an integer: " << endl;
        cin.clear();
        cin.ignore(20, '\n');
    }
    
    while ((cout << "How long is the file? ")
           && !(cin >> lengthOfFile))
    {
        cout << "Invalid input. Enter an integer: " << endl;
        cin.clear();
        cin.ignore(20, '\n');
    }
    
    numOfBursts++;  //increments to signal the end of a CPU burst
}



void Process::setCDRWRequestInfo()
{
    processState = WAITING;
       
    cout << "Enter file name(25 characters or less): ";
    cin >> filename;
    
    while ((cout << "Enter starting location in memory: ")
           && !(cin >> memLocation))
    {
        cout << "Invalid input. Enter an integer: " << endl;
        cin.clear();
        cin.ignore(20, '\n');
    }
    
    cout << "Is the requested action a read (type 'r') or write (type 'w')? ";
    cin >> action;
    if (action == "r")
    {
        read = true;
    }
    else if (action == "w")
    {
        write = true;
        while ((cout << "How long is the file? ")
               && !(cin >> lengthOfFile))
        {
            cout << "Invalid input. Enter an integer: " << endl;
            cin.clear();
            cin.ignore(20, '\n');
        }
    }
    else
    {
        cout << "Input invalid. Default: Performing a read.";
        read = true;
    }
    numOfBursts++;
}

int Process::getPID()
{
    return PID;
}

int Process::getCylinder()
{
    return cylinderRequest;
}

void Process::averageBurstTime()
{
    if (numOfBursts == 0)
    {
        cout << '\n';
        //cout << "Cannot compute average burst time for this process.";
        //cout << "CPU burst for this process has not ended yet.";
    }
    else
    {
        float avg = 0;
        avg = timeInCPU / numOfBursts;
        cout << avg << '\n';
    }
}


