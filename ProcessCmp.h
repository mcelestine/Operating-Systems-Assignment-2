/**
 * File:    ProcessCmp.h
 * Author:  Makina Celestine <mcelesti@hunter.cuny.edu>
 * Project: CSCI340 Assignment 2
 * Notes:
 *         -This class implementation is NOT credited to me.
 *          All credits go to the author of this blog here:
 *          "Sorting a vector of pointers to objects using STL and functors"
 *          http://garajeando.blogspot.com/2011/11/sorting-vector-of-pointer-to-objects.html
 *         -This helped me sort the requests in my disk queue.
 *
 * Hunter College 2012
 */

//
#ifndef PROCESSCMP_H
#define PROCESSCMP_H

#include "Process.h"


class CompareByCylinder
{
public:
    bool operator() (Process *lhs, Process *rhs)
    {
        return lhs->getCylinder() < rhs->getCylinder();
    }
    
};

#endif
