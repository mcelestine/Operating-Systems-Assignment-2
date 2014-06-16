/**
 * File:    System.h
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

#ifndef SYSTEM_H
#define SYSTEM_H


#include <vector>
#include <sstream>
#include <ctype.h>
#include "PrinterQueue.h"
#include "DiskQueue.h"
#include "CPU.h"
#include "CDRWQueue.h"
#include "ReadyQueue.h"

using namespace std;

class System
{
public:
    friend class CPU;
    
    void runSysGen();
    void runSimulator();
    
    void CPUHandler();
    void printerHandler(string);
    void diskHandler(string);
    void CDRWHandler(string);
    
    void sendToReadyQueue(Process *);
    void sendPrinterRequest(int);
    void sendDiskRequest(int);
    void sendCDRWRequest(int);
    
    void printerInterrupt(string);
    void diskInterrupt(string);
    void CDRWInterrupt(string);
    
    void displayReadyQueue();
    void avgTotalCPUtime();
    bool requestInBounds(int, int);
private:
    int numOfPrinters;
    int numOfDisks;
    int numOfCDRW;
    int numOfCylinders;
    
    int timeSlice;
    int totalCPUTime;  //cpu times of processes completed
    int completed;  //increments everytime a process is terminated
    
    vector<PrinterQueue> Printers;
    vector<DiskQueue> Disks;
    vector<CDRWQueue> CDRWs;
    ReadyQueue systemReadyQueue;
    CPU systemCPU;
};

#endif

