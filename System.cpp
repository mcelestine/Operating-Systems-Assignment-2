/**
 * File:    System.cpp
 * Author:  Makina Celestine <mcelesti@hunter.cuny.edu>
 * Project: CSCI340 Assignment 2
 * Notes:
 * Revisions:
 *          Reformatted displayStats to produce better looking output.
 *          File names are limited to 25 characters or less. 
 *          The output looks weird with super long file names.
 *           
 * Hunter College 2012
 */

#include "System.h"


/* runSysGen()
 * Function to set up the system.
 * Initializes/Creates the respective devices and their queues.
 * Vectors initially contain empty device queues.
 */
void System::runSysGen()
{
    cout << "----------------------------------------\n";
    cout << "SYSTEM GENERATION - SYSTEM SET UP" << endl;
    cout << "In this part of the installation, you will specify the number of devices in the system.\n";
    cout << "----------------------------------------\n";
    
    while ((cout << "How many printers are there? ")
           && !(cin >> numOfPrinters))
    {
        cout << "Invalid input. Enter an integer: " << endl;
        cin.clear();
        cin.ignore(20, '\n');
    }
    for (int i = 0; i < numOfPrinters; i++)
    {
        Printers.push_back(PrinterQueue());
    }
    
    cout << "----------------------------------------\n";
    while ((cout << "How many disks? ")
           && !(cin >> numOfDisks))
    {
        cout << "Invalid input. Enter an integer: " << endl;
        cin.clear();
        cin.ignore(20, '\n');
    }
    for (int i = 1; i <= numOfDisks; i++)
    {
        while ((cout << "How many cylinders for disk " << i <<": ")
               && !(cin >> numOfCylinders))
        {
            cout << "Invalid input. Enter an integer: " << endl;
            cin.clear();
            cin.ignore(20, '\n');
            
        }
        Disks.push_back(DiskQueue(numOfCylinders));
        
    }
    
    cout << "----------------------------------------\n";
    while ((cout << "How many CD/RW drives? ")
           && !(cin >> numOfCDRW))
    {
        cout << "Invalid input. Enter an integer: " << endl;
        cin.clear();
        cin.ignore(20, '\n');
    }
    for (int i = 0; i < numOfCDRW; i++)
    {
        CDRWs.push_back(CDRWQueue());
    }
    
    cout << "----------------------------------------\n";
    while ((cout << "Enter length (in milliseconds) of a time slice: ")
           && !(cin >> timeSlice))
    {
        cout << "Invalid input. Enter an integer: " << endl;
        cin.clear();
        cin.ignore(20, '\n');
    }
    
    cout << endl;
    cout << "THANK YOU. SYSTEM SET UP IS COMPLETE!" << endl;
    cout << "----------------------------------------\n";
}


void System::runSimulator()
{
    totalCPUTime = 0;
    completed = 0;
    
    int i = 0;  //used to generate PID
    string command;
    char snapshotCommand;
    int c;
    cout << endl;
    cout << "System is Now Running" << endl;
    
    do
    {
        cout << "Enter a command: ";
        getline(cin,command);
        
        if (command == "A")  //Arrival of a new process
        {
            i++;
            Process *temp = new Process(i);
            cout << '\n';
            cout << "Process was created. " << endl;
            sendToReadyQueue(temp);
            cout << "Process "<< i <<" was sent to Ready Queue." << endl;
            CPUHandler();
        }
        else if (command == "t") //Terminate currently running process
        {
            if (systemCPU.isOccupied == true)
            {
                if (systemCPU.current->processState != TERMINATED)
                {
                    cout << "Process " << systemCPU.current->PID << " is terminated.\n";
                    cout << "Total CPU time for this process: " << systemCPU.current->timeInCPU << endl;
                    cout << "Process's average Burst Time: ";
                    systemCPU.current->averageBurstTime();
                    
                    totalCPUTime += systemCPU.current->timeInCPU;
                    completed++;
                    systemCPU.terminateProcess();
                    cout << endl;
                    CPUHandler();
                }
                else
                    CPUHandler();
            }
            else
                cout << "No process to terminate." << endl;
        }
        else if (command == "T")
        {
            // signals an "end of time slice" interrupt
            // i.e the time a process has spent in the CPU so far
            // First check that there is in fact a process allocated to the CPU
            // If there is one in the CPU, send that process to the ready queue
            if (systemCPU.isOccupied == false)
            {
                cout << "No process in CPU. Interrupt failed." << endl;
            }
            else
            {
                cout << "End of time slice interrupt." << endl;
                systemCPU.current->timeInCPU += timeSlice; //time spent in CPU so far
                sendToReadyQueue(systemCPU.current);
                systemCPU.isOccupied = false;
                CPUHandler();
            }
        }
        else if (command == "S")
        {
            cout << "System's snapshot." << endl;
            cout <<"System's average total CPU time of completed processes: ";
            avgTotalCPUtime();
            cout << '\n';
            
            cout << "Waiting for second input: ";
            cin >> snapshotCommand;
            if (snapshotCommand == 'r')
            {
                cout << endl;
                if (systemReadyQueue.isEmpty() == true)
                {
                    cout << "No jobs in Ready Queue." << endl;
                }
                else
                    systemReadyQueue.displayStats();
                    cout << endl;
            }
            else if (snapshotCommand == 'p')
            {
                for (int i = 0; i < Printers.size(); i++)
                {
                    cout << "Stats for Printer " << i+1 << " : ";
                    if (Printers[i].isEmpty() == true)
                    {
                        cout << "No jobs." << endl;
                    }
                    else
                        Printers[i].printerStats();
                        cout << endl;
                }
            }
            else if (snapshotCommand == 'd')
            {
                for (int i = 0; i < Disks.size(); i++)
                {
                    cout << "Stats for Disk " << i+1 << " : ";
                    if (Disks[i].isEmpty() == true)
                    {
                        cout << "No jobs." << endl;
                    }
                    else
                        Disks[i].displayDiskStats();
                        cout << endl;
                }
            }
            else if (snapshotCommand == 'c')
            {
                for (int i = 0; i < CDRWs.size(); i++)
                {
                    cout << "Stats for CDRW " << i+1 << " : ";
                    if (CDRWs[i].isEmpty() == true)
                    {
                        cout << "No jobs." << endl;
                    }
                    else
                        CDRWs[i].displayCDRWStats();
                        cout << endl;
                }
            }
            
        }
        else
        {
            if (systemCPU.isOccupied == true)
            {
                c = command.find("p");
                if (c != command.npos)
                {
                    printerHandler(command);
                    if (systemReadyQueue.isEmpty() == false)
                        CPUHandler(); //send next process to CPU
                }
                
                c = command.find("d");
                if (c != command.npos)
                {
                    diskHandler(command);
                    if (systemReadyQueue.isEmpty() == false)
                        CPUHandler();
                }
                
                c = command.find("c");
                if (c != command.npos)
                {
                    CDRWHandler(command);
                    if (systemReadyQueue.isEmpty() == false)
                        CPUHandler();
                }
            }
            
            //"NOTE: System calls cannot be completed without a process."<< endl;
            
            c = command.find("P");
            if (c != command.npos)
            {
                printerInterrupt(command);
                if (systemReadyQueue.isEmpty() == false)
                    CPUHandler();
            }
            
            c = command.find("D");
            if (c != command.npos)
            {
                diskInterrupt(command);
                if (systemReadyQueue.isEmpty() == false)
                    CPUHandler();
            }
            
            c = command.find("C");
            if (c != command.npos)
            {
                CDRWInterrupt(command);
                if (systemReadyQueue.isEmpty() == false)
                    CPUHandler();
            }
            
        }
    }
    while (command != "Q");
}

/***********************DEVICE HANDLERS********************************/

void System::CPUHandler()
{
    if (systemCPU.isOccupied == false)
    {
        cout << "CPU is ready to accept a process." << endl;
        if (systemReadyQueue.isEmpty() == false)
        {
            systemCPU.receiveProcess(systemReadyQueue.dequeue());
        }
        else
            cout << "No jobs in Ready Queue." << endl;
    }
    else
        cout << "CPU is currently busy." << endl;
    cout << endl;
}

void System::printerHandler(string p)
{
    char holder = p[1];
    int num = holder - '0';
    if (num > numOfPrinters || num <= 0)
    {
        cout << "Cannot issue request. Printer doesn't exist\n";
    }
    else
    {
        sendPrinterRequest(num-1);
    }
}

void System::diskHandler(string d)
{
    char holder = d[1];
    int num = holder - '0';
    if (num > numOfDisks || num <= 0)
    {
        cout << "Cannot issue request. Disk doesn't exist\n";
    }
    else
    {
        sendDiskRequest(num-1);
    }
    
}

void System::CDRWHandler(string c)
{
    char holder = c[1];
    int num = holder - '0';
    if (num > numOfCDRW || num <= 0)
    {
        cout << "Cannot issue request. CDRW device doesn't exist\n";
    }
    else
    {
        sendCDRWRequest(num-1);
    }
}

/********************************************************************/
void System::sendToReadyQueue(Process *send)
{
    send->processState = READY;
    systemReadyQueue.enqueue(send);
    
}

void System::sendPrinterRequest(int num)
{
    string file = "";
    string action = "";
    int location = 0;
    int fileLength = 0;
    int totalProcessTime = 0;
    
    Process *temp = systemCPU.current;
    
    cout << '\n';
    while ((cout << "Enter how long was the process in the CPU: ")
           && !(cin >> totalProcessTime))
    {
        cout << "Invalid input. Enter an integer: " << endl;
        cin.clear();
        cin.ignore(20, '\n');
    }
    while (totalProcessTime < 0 || totalProcessTime > timeSlice)
    {
        cout << "Enter a number between 0 and " << timeSlice << ": ";
        cin >> totalProcessTime;
    }
    
    temp->timeInCPU += totalProcessTime;
    temp->processState = WAITING;
    
    temp->write = true;
    cout << "Enter file name(25 characters or less): ";
    cin >> temp->filename;
    
    while ((cout << "Enter starting location in memory: ")
           && !(cin >> location))
    {
        cout << "Invalid input. Enter an integer: " << endl;
        cin.clear();
        cin.ignore(20, '\n');
    }
    temp->memLocation = location;
    
    while ((cout << "How long is the file? ")
           && !(cin >> fileLength))
    {
        cout << "Invalid input. Enter an integer: " << endl;
        cin.clear();
        cin.ignore(20, '\n');
    }
    temp->lengthOfFile = fileLength;
    
    temp->numOfBursts++;  //increments to signal the end of a CPU burst
    
    
    //systemCPU.current->setPrintRequestInfo();
    systemCPU.isOccupied = false;
    Printers[num].enqueue(systemCPU.current);
    cout << '\n';
    cout << "Process is out of CPU. Now in Printer Queue. " << endl;
}

void System::sendDiskRequest(int num)
{
    string file = "";
    string action = "";
    int request = 0;
    int location = 0;
    int fileLength = 0;
    int totalProcessTime = 0;
    
    Process *temp = systemCPU.current;
    temp->processState = WAITING;
    
    cout << '\n';
    while ((cout << "Enter how long the process was in the CPU: ")
           && !(cin >> totalProcessTime))
    {
        cout << "Invalid input. Enter an integer: " << endl;
        cin.clear();
        cin.ignore(20, '\n');
    }
    
    while (totalProcessTime < 0 || totalProcessTime > timeSlice)
    {
        cout << "Enter a number between 0 and " << timeSlice << ": ";
        cin >> totalProcessTime;
    }
    temp->timeInCPU += totalProcessTime;
    
    cout << "Enter file name(25 characters or less): ";
    cin >> file;
    temp->filename = file;
    
    while ((cout << "Enter starting location in memory: ")
           && !(cin >> location))
    {
        cout << "Invalid input. Enter an integer: " << endl;
        cin.clear();
        cin.ignore(20, '\n');
    }
    temp->memLocation = location;
    
    cout << "Is the requested action a read (type 'r') or write (type 'w')? ";
    cin >> action;
    if (action == "r")
    {
        temp->read = true;
        cout << "Enter cylinder to read from: ";
        
        while ((cin >> request) && (requestInBounds(num, request) == false))
        {
            cout << " Enter again: ";
        }
        temp->cylinderRequest = request;
    }
    else if (action == "w")
    {
        temp->write = true;
        cout << "Enter cylinder to write to: ";
        while ((cin >> request) && (requestInBounds(num, request) == false))
        {
            cout << " Enter again: ";
        }
        temp->cylinderRequest = request;
        
        while ((cout << "How long is the file? ")
               && !(cin >> fileLength))
        {
            cout << "Invalid input. Enter an integer: " << endl;
            cin.clear();
            cin.ignore(20, '\n');
        }
        temp->lengthOfFile = fileLength;
    }
    else
    {
        cout << "Input invalid. Default: Performing a read.";
        temp->read = true;
    }
    temp->numOfBursts++;
    
    systemCPU.isOccupied = false;
    Disks[num].enqueue(systemCPU.current); 
    cout << '\n';
    cout << "Process is out of CPU. Now in Disk Queue. " << endl;
}

void System::sendCDRWRequest(int num)
{
    string file = "";
    string action = "";
    int location = 0;
    int fileLength = 0;
    int totalProcessTime = 0;
    
    Process *temp = systemCPU.current;
    cout << '\n';
    while ((cout << "Enter how long was the process in the CPU: ")
           && !(cin >> totalProcessTime))
    {
        cout << "Invalid input. Enter an integer: " << endl;
        cin.clear();
        cin.ignore(20, '\n');
    }
    while (totalProcessTime < 0 || totalProcessTime > timeSlice)
    {
        cout << "Enter a number between 0 and " << timeSlice << ": ";
        cin >> totalProcessTime;
    }
    temp->timeInCPU += totalProcessTime;
    
    temp->processState = WAITING;
    
    cout << "Enter file name(25 characters or less): ";
    cin >> file;
    temp->filename = file;
    
    while ((cout << "Enter starting location in memory: ")
           && !(cin >> location))
    {
        cout << "Invalid input. Enter an integer: " << endl;
        cin.clear();
        cin.ignore(20, '\n');
    }
    temp->memLocation = location;
    
    cout << "Is the requested action a read (type 'r') or write (type 'w')? ";
    cin >> action;
    if (action == "r")
    {
        temp->read = true;
    }
    else if (action == "w")
    {
        temp->write = true;
        while ((cout << "How long is the file? ")
               && !(cin >> fileLength))
        {
            cout << "Invalid input. Enter an integer: " << endl;
            cin.clear();
            cin.ignore(20, '\n');
        }
        temp->lengthOfFile = fileLength;
    }
    else
    {
        cout << "Input invalid. Default: Performing a read.";
        temp->read = true;
    }
    temp->numOfBursts++;

    //systemCPU.current->setCDRWRequestInfo();
    systemCPU.isOccupied = false;
    CDRWs[num].enqueue(systemCPU.current);
    cout << '\n';
    cout << "Process is out of CPU. Now in CDRW Queue. " << endl;
}

/********************************************************************/
//Interrupts: Signals completion of I/O request

void System::printerInterrupt(string pI)
{
    char holder = pI[1];
    int num = holder - '0'; //Convert ascii value to the right integer
    if (Printers[num-1].isEmpty() == false)
    {
        cout << endl;
        cout << "Printer request completed." << endl;
        cout << "Now sending process to Ready Queue." << endl;
        sendToReadyQueue(Printers[num-1].dequeue());
    }
    else
        cout << "Device queue is empty. Cannot complete request." << endl;
}

void System::diskInterrupt(string dI)
{
    char holder = dI[1];
    int num = holder - '0';
    if (Disks[num-1].isEmpty() == false)
    {
        cout << endl;
        //cout << "Disk request completed." << endl;
        //
        sendToReadyQueue(Disks[num-1].dequeue());
        cout << " Now sending process to Ready Queue." << endl;
    }
    else
        cout << "No jobs for this device. Cannot complete request." << endl;
    
}

void System::CDRWInterrupt(string cI)
{
    char holder = cI[1];
    int num = holder - '0';
    //Dequeue from queue
    //Enqueue to Ready Queue
    if (CDRWs[num-1].isEmpty() == false)
    {
        cout << endl;
        cout << "CDRW request completed." << endl;
        cout << "Now sending process to Ready Queue." << endl;
        sendToReadyQueue(CDRWs[num-1].dequeue());
    }
    else
        cout << "Device queue is empty. Cannot complete request." << endl;
}

/********************************************************************/
void System::displayReadyQueue()
{
    systemReadyQueue.displayStats();
}


void System::avgTotalCPUtime()
{
    if (completed == 0)
    {
        cout << endl;
        cout << "Cannot compute average burst time. No completed processes." << endl;
    }
    else
    {
        float avg = 0;
        avg = totalCPUTime / completed;
        cout << avg << endl;
    }
}

bool System::requestInBounds(int diskNum, int req)
{
    int diskCylinders = Disks[diskNum].totCylinders;
    if ((req <= 0) || (req >= diskCylinders))
    {
        cout << "Cylinder request is out of range." << '\n';
        cout << "Enter a number between 0 and " << diskCylinders-1 << ".";
        
        return false;
    }
    else
        return true;
    
}
