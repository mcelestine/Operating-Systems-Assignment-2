/**
 * File:    ReadyQueue.h
 * Author:  Makina Celestine <mcelesti@hunter.cuny.edu>
 * Project: CSCI340 Assignment 2
 * Notes:
 *
 *
 *
 * Hunter College 2012
 */

#ifndef READYQUEUE_H
#define READYQUEUE_H
#include "QueueADT.h"



class ReadyQueue: public QueueADT
{
public:
    ReadyQueue();
    void displayStats();
};

#endif
