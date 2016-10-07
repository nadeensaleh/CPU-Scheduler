//
//  Process.h
//  FCFS
//
//  Created by Nadeen Saleh on 10/10/15.
//  Copyright © 2015 Nadeen Saleh. All rights reserved.
//

#ifndef Process_h
#define Process_h
using namespace std;

class Process {
public:
    string name; // ex. "P1"
    int rtime = 0; // response time
    int wtime = 0; // wait time
    int ttime = 0; // turnaround time
    int index = 0; // index in vector
    int currentio = 0;
    int currentburst = 0;
    vector<int> vec;
    
    static void PrintReadyQueue(deque<Process> ready){
        Process tempq; // Ready queue temp
        cout << left << setw(20) << setfill(' ') <<  "Ready Queue:";
        cout << left << setw(10) << setfill(' ') <<  "Process";
        cout << left << setw(10) << setfill(' ') <<  "Burst";
        cout << endl;
        for (deque<Process>::iterator it = ready.begin(); it!=ready.end(); ++it){
            tempq = *it;
            cout << right << setw(22) << setfill(' ') << tempq.name;
            cout << right << setw(10) << setfill(' ') << tempq.vec[tempq.index];
            cout << endl;
        }
        cout << left << setw(39) << setfill('.') << ".";
        cout << endl << endl;
    }
    
    static void PrintIO(vector<Process> io){
        Process tempi; // I/O vector temp
        cout << left << setw(20) << setfill(' ') <<  "Now in I/O:";
        cout << left << setw(10) << setfill(' ') <<  "Process";
        cout << left << setw(10) << setfill(' ') <<  "Remaining";
        cout << endl;
        for (int i = 0; i < io.size(); i++){
            tempi = io[i];
            cout << right << setw(22) << setfill(' ') << tempi.name;
            cout << right << setw(10) << setfill(' ') << tempi.currentio;
            cout << endl;
        }
        cout << left << setw(39) << setfill('.') << ".";
        cout << endl << endl;
    }
    
    static void PrintTerminated(vector<Process> terminated){
        cout << "Completed: ";
        for (int i = 0; i < terminated.size(); i++){
            cout << terminated[i].name + " ";
        }
        cout << endl << endl;
        cout << left << setw(39) << setfill('.') << "." << endl;
        cout << left << setw(39) << setfill('.') << ".";
        cout << endl << endl;
    }
    
    static void FinalPrint(vector<Process> terminated){
        double avgRtime, avgTtime, avgWtime;
        int s = 0;
        cout << left << setw(10) << setfill(' ') <<  "Process:";
        cout << left << setw(10) << setfill(' ') <<  "RT";
        cout << left << setw(10) << setfill(' ') <<  "TT";
        cout << left << setw(10) << setfill(' ') <<  "WT";
        cout << endl;
        for (int i = 0; i < terminated.size(); i++){
            cout << left << setw(10) << setfill(' ') << terminated[i].name;
            cout << left << setw(10) << setfill(' ') << terminated[i].rtime;
            cout << left << setw(10) << setfill(' ') << terminated[i].ttime;
            cout << left << setw(10) << setfill(' ') << terminated[i].wtime;
            cout << endl;
        }
        while (s < terminated.size()){
            avgRtime += terminated[s].rtime;
            avgTtime += terminated[s].ttime;
            avgWtime += terminated[s].wtime;
            s++;
        }
        avgRtime = avgRtime/9;
        avgTtime = avgTtime/9;
        avgWtime = avgWtime/9;
        cout << left << setw(35) << setfill('-') << "-" << endl;
        cout << left << setw(10) << setfill(' ') << " ";
        cout << left << setw(10) << setfill(' ') << setprecision(4) << avgRtime;
        cout << left << setw(10) << setfill(' ') << setprecision(4) << avgTtime;
        cout << left << setw(10) << setfill(' ') << setprecision(4) << avgWtime;
        cout << endl << endl;
    }
    
    static void PrintIdle(deque<Process> ready, vector<Process> io, vector<Process> terminated, int time){
        cout << left << setw(20) << setfill(' ') << "Current Time:";
        cout << left << setw(10) << setfill(' ') << time;
        cout << endl;
        cout << left << setw(20) << setfill(' ') << "Now Running:";
        cout << left << setw(10) << setfill(' ') << "[idle]" << endl;
        cout << left << setw(39) << setfill('.') << "." << endl << endl;
        PrintReadyQueue(ready);
        PrintIO(io);
        PrintTerminated(terminated);
    }
    
};
#endif /* Process_h */
