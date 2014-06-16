/**
 * File:      DiskQueue.cpp
 * Author:    Makina Celestine <mcelesti@hunter.cuny.edu>
 * Project:   CSCI340 Assignment 2
 * Notes:     
 *            Reformatted displayStats to produce better looking output.
 *            File names are limited to 25 characters or less. 
 *            The output looks weird with super long file names.
 *             
 * Hunter College 2012
 */

#include "DiskQueue.h"


DiskQueue::DiskQueue(int cylinders)
{
    totCylinders = cylinders;
    headInitialized = false;
}

void DiskQueue::displayDiskStats()
{
    cout << '\n';
    cout << "PID" << right << setw(20);
    cout << "|Filename|" << right << setw(25);
    cout << "|Length of file|" << right << setw(22);
    cout << "|Starting location in memory|" << right << setw(19);
    cout << "|Cylinder location|" << right << setw(19);
    cout << "|CPU burst time|"<< right << setw(19);
    cout << "|Average burst time|";
    cout << '\n';
    
    for (int i = 0 ; i < requestQueue.size(); i++)
    {
        cout << requestQueue[i]->PID  << right << setw(25);
        cout << requestQueue[i]->filename << right << setw(12);
        cout << requestQueue[i]->lengthOfFile << right << setw(20);
        cout << requestQueue[i]->memLocation << right << setw(25);
        cout << requestQueue[i]->cylinderRequest << right << setw(25);
        cout << requestQueue[i]->timeInCPU << right << setw(20);
        requestQueue[i]->averageBurstTime();
    }
    
}
bool DiskQueue::isEmpty()const
{
    return requestQueue.empty();
}

bool DiskQueue::compare(Process *a, Process *b)
{
    return (a->cylinderRequest < b->cylinderRequest);
}

void DiskQueue::enqueue(Process *object)
{
    requestQueue.push_back(object);
}


//Performs CLOOK
Process* DiskQueue::dequeue()
{
    if (isEmpty())
    {
        cout << "No requests to service. Queue is empty." << endl;
    }
    else
    {
        sort();
        
        //If head has not been initialized, set it to the cylinder number
        //of first process in the queue, and service that process
        if (headInitialized == false)
        {
            head = requestQueue.front()->cylinderRequest;
            headInitialized = true;
            
            Process *temp = requestQueue.front();
            requestQueue.erase(requestQueue.begin());
            cout << "Request for cylinder " << temp->cylinderRequest << " completed.";
            return temp;
        }
        else //Assuming headInitialized is now true
        {
            int max = findMaxCylinder();
            int index = 0; //look at first request in queue
            while (index < requestQueue.size())
            {
                if ((requestQueue[index]->cylinderRequest <= head) && (head < max))
                {
                    index++;
                }
                else if ((requestQueue[index]->cylinderRequest <= head) && (head = max))
                {
                    head = requestQueue[index]->cylinderRequest;
                    Process *temp = requestQueue[index];
                    requestQueue.erase(requestQueue.begin()+index);
                    cout << "Request for cylinder " << temp->cylinderRequest << " completed.";
                    return temp;
                }
                else if ((requestQueue[index]->cylinderRequest < head) && (head > max))
                {
                    //go back and start at that request
                    head = requestQueue[index]->cylinderRequest;
                    Process *temp = requestQueue[index];
                    requestQueue.erase(requestQueue.begin()+index);
                    cout << "Request for cylinder " << temp->cylinderRequest << " completed.";
                    return temp;
                             
                }
                else if ((requestQueue[index]->cylinderRequest > head))
                {
                    if (requestQueue[index]->cylinderRequest <= max)
                    {
                        head = requestQueue[index]->cylinderRequest;
                        Process *temp = requestQueue[index];
                        requestQueue.erase(requestQueue.begin()+index);
                        cout << "Request for cylinder " << temp->cylinderRequest << " completed.";
                        return temp;
                    }
                }
              
            }
        }
    }
}

void DiskQueue::sort()
{
    std::sort(requestQueue.begin(), requestQueue.end(), CompareByCylinder());
}

int DiskQueue::findMaxCylinder()
{
    int largest = 0;
    for (int i = 0; i < requestQueue.size(); i++)
    {
        if (requestQueue[i]->cylinderRequest > largest)
        {
            largest = requestQueue[i]->cylinderRequest;
        }
    }
    return largest;
}
