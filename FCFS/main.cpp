//
//  main.cpp
//  FCFS
//
//  Created by Nadeen Saleh on 10/10/15.
//  Copyright © 2015 Nadeen Saleh. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include <deque>
#include <vector>
#include "Process.h"
using namespace std;

int main() {
    int index = 0;
    int time = 0;
    int negCPU = 0;
    double CPUtilization = 0;
    Process P1,P2,P3,P4,P5,P6,P7,P8,P9;
    Process pcurrent; // Running process
    vector <Process> I_O; // I/O
    vector <Process> Terminated; // Terminated processes
    deque <Process> Ready; // Ready queue
    
    P1.name = "P1"; P1.vec = {7,19,8,13,17,13,19,19,44,15,29,51,14,68,15,49,14}; Ready.push_back(P1);
    P2.name = "P2"; P2.vec = {9,52,12,42,24,31,24,21,26,43,14,31,23,32,15}; Ready.push_back(P2);
    P3.name = "P3"; P3.vec = {25,51,43,53,44,21,15,31,24,29,31,34,12}; Ready.push_back(P3);
    P4.name = "P4"; P4.vec = {6,29,5,22,6,24,8,27,5,25,6,24,8,26,9, 22, 8}; Ready.push_back(P4);
    P5.name = "P5"; P5.vec = {5,66,6,82,5,71,6,43,4,26,6,51,3,77,4,61,3,42,5}; Ready.push_back(P5);
    P6.name = "P6"; P6.vec = {9,35,8,41,11,33,13,32,8,41,16,29,11}; Ready.push_back(P6);
    P7.name = "P7"; P7.vec = {5,28,6,21,5,39,8,16,7,29,5,31,4,22,6,24,5}; Ready.push_back(P7);
    P8.name = "P8"; P8.vec = {20,26,19,23,18,42,27,43,19,37,26,43,35,55,21}; Ready.push_back(P8);
    P9.name = "P9"; P9.vec = {6,35,5,41,6,33,4,32,8,31,4,29,5,16,3,32,4}; Ready.push_back(P9);
    
    while (Terminated.size() != 9)
    {
        cout << left << setw(20) << setfill(' ') << "Current Time:";
        cout << left << setw(10) << setfill(' ') << time << endl;
        
        pcurrent = Ready.front();               // Current process
        Ready.pop_front();                      // Remove process from queue
        if (pcurrent.index == 0)                // Set response time for time of first burst
            pcurrent.rtime = time;
        
        cout << left << setw(20) << setfill(' ') << "Now Running:";
        cout << left << setw(10) << setfill(' ') << pcurrent.name;
        cout << endl;
        
        cout << left << setw(39) << setfill('.') << "." << endl << endl;
        
        pcurrent.currentburst = pcurrent.vec[pcurrent.index]; // Set variable for remaining burst time
        index = pcurrent.index;                 // Burst value index
        time += pcurrent.vec[index];            // Increment time with burst length
        pcurrent.index++;                       // Increment spot in vector (burst -> I/O)
        pcurrent.currentio = pcurrent.vec[pcurrent.index]; // Set variable for remaining I/O time
        

        Process::PrintReadyQueue(Ready);
        Process::PrintIO(I_O);
        Process::PrintTerminated(Terminated);
        
        
        // Burst running
        while(pcurrent.currentburst > 0){
            for (deque<Process>::iterator it = Ready.begin(); it!=Ready.end(); ++it){
                    (*it).wtime++; // Increment wait time for all Ready queue processes while burst is running
                }
            for (int i = 0; i < I_O.size(); i++){
                I_O[i].currentio--; // Decrement all I/O's remaining time
            }
            for (int j = 0; j < I_O.size(); j++){
                if (I_O[j].currentio == 0){
                    I_O[j].index++;
                    Ready.push_back(I_O[j]);
                    I_O.erase(I_O.begin() + j);
                    j--; // Account for deleting object
                }
            }
            pcurrent.currentburst--;
        }

        // Check if process is finished (termination)
        if(pcurrent.index < pcurrent.vec.size()){
            I_O.push_back(pcurrent); // Move to I/O
        } else{
            pcurrent.ttime = time - pcurrent.rtime; // Once terminated, calculate turnaround time
            Terminated.push_back(pcurrent);
        }
        
        // IDLE
        if(Ready.empty() == true && I_O.empty() == false){
            Process::PrintIdle(Ready, I_O, Terminated, time);
            while(Ready.empty() == true){ // Decrement I/O remaining times until process moves to Ready
                for (int i = 0; i < I_O.size(); i++){
                    I_O[i].currentio--;
                }
                for (int j = 0; j < I_O.size(); j++){
                    if (I_O[j].currentio == 0){
                        I_O[j].index++;
                        Ready.push_back(I_O[j]);
                        I_O.erase(I_O.begin() + j);
                        j--; // Account for deleting object
                    }
                }
                negCPU++; // Count time that CPU is not being utilized
                time++; //Also increment time while waiting to get out of I/O
            }
        }
    }
    
    Process::FinalPrint(Terminated);
    cout << "Final time: ";
    cout << time << endl;
    cout << "CPU Utilization: ";
    CPUtilization = (time - negCPU);
    cout << (CPUtilization/time) * 100;
    cout << "%" << endl;
    
    return 0;
}