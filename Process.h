/**
 * File:    Process.h
 * Author:  Makina Celestine <mcelesti@hunter.cuny.edu>
 * Project: CSCI340 Assignment 2
 * Notes:
 *
 *        
 *
 * Hunter College 2012
 */

#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include <iostream>

using namespace std;

enum STATE {NEW, READY, RUNNING, WAITING, TERMINATED};

class Process
{
public:
    friend class PrinterQueue;
    friend class DiskQueue;
    friend class CDRWQueue;
    friend class ReadyQueue;
    friend class System;
    friend class CPU;
    friend class ProcessCmp;  //Comparator class
    
    Process(int p);
    void setPrintRequestInfo();
    void setCDRWRequestInfo();
    
    int getPID();
    int getCylinder();
    void averageBurstTime();
    
private:
    STATE processState;
    int PID;

    // For print processes
    string filename;
    int memLocation;
    string action;
    int lengthOfFile;
    bool read;
    bool write;
    
    int timeInCPU;     //time spent in CPU so far i.e CPU burst
    int numOfBursts;  //used to calculate average Burst Time
    int cylinderRequest;
        
};

#endif
