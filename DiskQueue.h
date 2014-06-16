/**
 * File:      DiskQueue.h
 * Author:    Makina Celestine <mcelesti@hunter.cuny.edu>
 * Project:   CSCI340 Assignment 2
 * Notes:
 *            -Each disk has a different amount of cylinders.
 *            C-Look disk scheduling
 *            Assumes that disk head starts at first cylinder.
 *            Most likely I will have to reimplement this.
 *            -I had trouble finding a way to sort a vector of object pointers by the
 *            cylinder number.
 *            -After browsing the web for tutorials on this issue,
 *             I found a solution by implementing the ProcessCmp class.
 *             Credits to this solution goes to:
 *             http://garajeando.blogspot.com/2011/11/sorting-vector-of-pointer-to-objects.html
 *             Ultimately this article helped.
 *             The STL sort function sorts in ascending order
 *
 *
 * Hunter College 2012
 */

#ifndef DISKQUEUE_H
#define DISKQUEUE_H

#include "Process.h"
#include "ProcessCmp.h"
#include <vector>
#include <iostream>
#include <iomanip>
#include <algorithm>


class DiskQueue
{
public:
    friend class System;
    friend class CPU;
    friend class ProcessCmp;
    
    DiskQueue(int cylinders);
    void displayDiskStats();
    bool isEmpty()const;
    void enqueue(Process *);
    Process* dequeue();    //Performs CLOOK
    bool compare(Process *, Process *);
    void sort();          //function used to sort requests.
    int findMaxCylinder();
    
private:
    int head;           //disk head
    bool headInitialized; //true if head started to move
    int totCylinders;
    vector<Process *> requestQueue;
    vector<Process *> serviced;

};


#endif
