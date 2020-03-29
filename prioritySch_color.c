#include <stdio.h> 
#include<stdbool.h>
#include<windows.h>
// Process Blueprint.
struct process { 
    int pid; //Process Id.
    int arrival_time;//the time when the process arrives for execution.
	int burst_time;//estimated run time.
	int wait_time;//0 as default. calculated as arrival time - burst time
	int turnaround_time;//time interval from the time of submission of a process to the time of the completion of the process.
    bool isCompleted;//to check if the process has been executed or not
};

void SetColor(int ForgC)
	{
		WORD wColor = ((0 & 0x0F) << 4) + (ForgC & 0x0F);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);		
	}

//main function  
void main() 
{ 
    int i, j, t;//two loop variables and integer temporary variable respectively.
	int sum_bt = 0;//to hold the sum of burst times
  	float average_wait=0,average_tt=0;
	int size=5;//size of the array
  	//Process Array format: {pid,arrival time,burst time,wait time,turnaround time,isCompleted}
	struct process p[]={{1,0,6,0,0,false},
						{2,0,2,0,0,false},
						{3,0,8,0,0,false},
						{4,0,3,0,0,false},
						{5,0,4,0,0,false}};
						
					/*	Test case 1========Normal Case
						{{0,0,3,0,0,false},
						{1,2,5,0,0,false},
						{2,4,4,0,0,false},
						{3,6,1,0,0,false},
						{4,8,2,0,0,false}}
						
						Test case 2=========Same Arrival Times
						{{0,5,3,0,0,false},
						{1,5,5,0,0,false},
						{2,5,4,0,0,false},
						{3,5,1,0,0,false},
						{4,5,2,0,0,false}}
						
						Test case 3=========Idle time case
						{{0,5,4,0,0,false},
						{1,5,6,0,0,false},
						{2,5,3,0,0,false},
						{3,20,1,0,0,false},
						{4,5,2,0,0,false}}
						
						*/
						
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
	
    printf("\nOrder :\t");
    
    for (t = p[0].arrival_time; t < sum_bt;) { 
  
  			float maxPriority = 0;//setting maximum priority to 0
    		float temp; //to hold a priority value temporarily 
    		int loc; // Variable to store next process selected	
        for (i = 0; i < size; i++) { 
  
            // Checking if process has arrived and is Incomplete 
            if (p[i].arrival_time <= t && !p[i].isCompleted) {  
                // Calculating priority according to the problem statement
                temp = (float)(p[i].burst_time + t-p[i].arrival_time) / p[i].burst_time; 
                //printf("%f\n",temp);
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
         // Calculation of waiting time 
        p[loc].wait_time = t - p[loc].arrival_time - p[loc].burst_time; 
        SetColor(9);
		//Printing Order
        printf("p%d",p[loc].pid);
        SetColor(15);
        printf("\t====>\t ");
        // Sum Waiting Time for average 
        average_wait += p[loc].wait_time;
        // Calculation of Turn Around Time 
        p[loc].turnaround_time = t - p[loc].arrival_time; 
        // Sum Turn Around Time for average 
        average_tt += p[loc].turnaround_time; 
    }
    //Special Condition========> when arrival time is same, a process is skipped.
    //For better understanding disable the for-loop below and run the code.
    for(i=0;i<size;i++)
    {
    	if(p[i].isCompleted==false)
    	{
    		p[i].isCompleted=true;
    		t+=p[i].burst_time;
    		p[i].wait_time=t-p[i].arrival_time-p[i].burst_time;
    		SetColor(9);
    		printf("p%d\t====>\t ",p[i].pid); 
    		SetColor(15);
        	average_wait += p[i].wait_time;
        	p[i].turnaround_time = t - p[i].arrival_time;
		}
	}
    
    
    printf("Completed\n\n\t");
    	SetColor(11);
    printf("Table to visualsise the Gantt Chart\n");
    	SetColor(15);
    printf("\r\r\t===================================");
    //Average waiting time is calculated as sum of individual waiting times / number of process
    printf("\n\tAverage waiting time : %.2f",average_wait/size);
    printf("\n\tAverage TurnAround time : %.2f",average_tt/size);
    printf("\n\nPid\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\t\tStatus"); 
	for(i=0;i<size;i++)
    {
	
        printf("\np%i\t\t%d\t\t", p[i].pid, p[i].arrival_time); 
        printf("%d\t\t%d\t\t%d\t\t", p[i].burst_time, p[i].wait_time,p[i].turnaround_time);
        SetColor(2);
        printf("%s",p[i].isCompleted?"Completed":"Failed");
        SetColor(15);
    }
} 
