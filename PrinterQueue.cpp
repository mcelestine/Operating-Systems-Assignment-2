/**
 * File:    PrinterQueue.cpp
 * Author:  Makina Celestine <mcelesti@hunter.cuny.edu>
 * Project: CSCI340 Assignment 2
 * Notes:
 *          Reformatted displayStats to produce better looking output.
 *          File names are limited to 25 characters or less. 
 *          The output looks weird with super long file names.
 *
 *
 * Hunter College 2012
 */
#include "PrinterQueue.h"


PrinterQueue::PrinterQueue()
{
    
}
void PrinterQueue::printerStats()
{
    
    queue<Process *> tempQueue;
    tempQueue = processQueue; //point to queue it's going to copy
    cout << '\n';
    cout << "PID" << right << setw(20);
    cout << "|Filename|" << right << setw(25);
    cout << "|Length of file|" << right << setw(22);
    cout << "|Starting location in memory|" << right<< setw(19);
    cout << "|CPU Burst Time|"<< right << setw(19);
    cout << "|Average burst time|" << '\n';
    
    while (!tempQueue.empty())
    {
        cout << tempQueue.front()->PID << right << setw(25);
        cout << tempQueue.front()->filename << right << setw(12);
        cout << tempQueue.front()->lengthOfFile << right << setw(20);
        cout << tempQueue.front()->memLocation << right << setw(25);
        cout << tempQueue.front()->timeInCPU << right << setw(22);
        tempQueue.front()->averageBurstTime();
        tempQueue.pop();
    }
}
