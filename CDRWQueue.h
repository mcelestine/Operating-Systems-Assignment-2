/**
 * File:      CDRWQueue.h
 * Author:    Makina Celestine  <mcelesti@hunter.cuny.edu>
 * Project:   CSCI340 Assignment 2
 * Notes:  
 *
 *
 * Hunter College 2012
 */

#ifndef CDRWQUEUE_H
#define CDRDQUEUE_H
#include "QueueADT.h"

class CDRWQueue: public QueueADT
{
public:
    CDRWQueue();
    void displayCDRWStats();
};

#endif
