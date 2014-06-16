/**
 * File:    PrinterQueue.h
 * Author:  Makina Celestine <mcelesti@hunter.cuny.edu>
 * Project: CSCI340 Assignment 2
 * Notes:  
 *
 *
 *
 * Hunter College 2012
 */
#ifndef PRINTERQUEUE_H
#define PRINTERQUEUE_H
#include "QueueADT.h"


class PrinterQueue: public QueueADT
{
public:
    PrinterQueue(); 
    void printerStats();
};

#endif
