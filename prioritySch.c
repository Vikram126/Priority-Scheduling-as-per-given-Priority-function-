#include <stdio.h> 
#include<stdbool.h>
// Process Blueprint.
struct process { 
    int pid; //Process Id.
    int arrival_time;//the time when the process arrives for execution.
	int burst_time;//estimated run time.
    bool isCompleted;//to check if the process has been executed or not
};

//main function  
void main() 
{ 
    int i, j, t;//two loop variables and integer temporary variable respectively.
	int sum_bt = 0;//to hold the sum of burst times
  	
	int size=5;//size of the array
  	//Process Array format: {pid,arrival time,burst time,isCompleted}
	struct process p[]={{0,0,3,false},
						{1,2,6,false},
						{2,4,4,false},
						{3,6,5,false},
						{4,8,2,false}};
    struct process temporary;//for holding a process temporarily.
    
	
	// calculating total burst time or expected run time
    for (i = 0; i < size; i++) { 
        sum_bt += p[i].burst_time; 
    } 
   
    // Sorting the structure by arrival times 
    for (i = 0; i < size - 1; i++) { 
       
	    for (j = i + 1; j < size; j++) { 
  
            if (p[i].arrival_time > p[j].arrival_time) { 
  
                // Swap earlier process to front 
                temporary = p[i]; 
                p[i] = p[j]; 
                p[j] = temporary; 
            } 
        } 
    } 
    
    for (t = p[0].arrival_time; t < sum_bt;) { 
  
  			float maxPriority = 0;//setting maximum priority to 0
    		float temp; //to hold a priority value temporarily 
    		int loc; // Variable to store next process selected	
        for (i = 0; i < size; i++) { 
  
            // Checking if process has arrived and is Incomplete 
            if (p[i].arrival_time <= t && !p[i].isCompleted) {  
                // Calculating priority according to the problem statement
                temp = (p[i].burst_time + (t - p[i].arrival_time)) / p[i].burst_time; 
                // highest priority
                if (maxPriority < temp) { 
                    // Storing the maximum priority process
                    maxPriority = temp; 
                    // Storing Location 
                    loc = i; 
                } 
            } 
        }
        // Updating time value 
        t += p[loc].burst_time; 
        // Updating Completion Status 
        p[loc].isCompleted = true;
        //Printing Order
        printf("p%d ",p[loc].pid);
    }
} 
