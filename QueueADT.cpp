/**
 * File:    QueueADT.cpp
 * Author:  Makina Celestine <mcelesti@hunter.cuny.edu>
 * Project: CSCI340 Assignment 2
 * Notes:   
 *          BASE CLASS FOR THE DEVICE QUEUES.
 *          USES STL QUEUE CLASS.
 *          EACH DERIVED CLASS OF THIS BASE CLASS WILL HAVE
 *          A PROCESS QUEUE
 *
 * Hunter College 2012
 */
#include "QueueADT.h"


bool QueueADT::isEmpty()const
{
    return (processQueue.empty());
}

void QueueADT::enqueue(Process *object)
{
    processQueue.push(object);
}

Process* QueueADT::dequeue()
{
    if (isEmpty())
    {
        cout << "Dequeue failed. Queue is empty." << endl;
    }
    else
    {
        Process *temp = processQueue.front();
        processQueue.pop();
        return temp;
    }
}
