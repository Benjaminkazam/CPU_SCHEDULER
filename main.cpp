#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <limits.h>

using namespace std;

// here to implement job and process in structure
struct Job{
    int bursTime;
    int arrivalTime;
    int priority;
};
//this function is for read data from the text file
int readInputFromFile(struct Job* jobs,const char* fileName);
//this function is implemented for First come, First served;
void fcomeFserved(struct Job* jobs, const char* fileName, const char* outputFile);
//function to display implement Round-Robin SCheduling
void roundRobinScheduling (struct Job* jobs, int timeQuantum, const char *fileName, const char* outputFile);
//this function calculate and display average
void displayAndCalculateAvg(const char* fileName, const char* methode,int waitingTime[],int n);
//function to display the scheduling results
void displayResults(const char* fileName);
//function to count lines into input file
int countLines(const char* fileName);
//function to implement shortest job first preemptive
void sJFPreemptive(struct Job* jobs,const char *fileName, const char *outputFile);
// this function is to implement
void sJFNonPreemptive(struct Job* jobs, const char* fileName, const char *outputFile);
int main (int argc, char *argv[]){
    // i wanna check if the correct command line is provide
    if (argc!=5){
        fprintf(stderr,"use this format for running the code : %s -f input.txt -o output.txt\n", argv[0]);
        return 1;
    }
    // to take all the command line arguments

    const char* inputFile;
    const char* outputFile;

    for (int i=1 ; i< argc; i+=2){
        if (strcmp (argv[i],"-f")==0){
            inputFile= argv[i+1];
        }
        else if (strcmp (argv[i], "-o")==0){
            outputFile= argv[i+1];
        }
    }
    int size= countLines(inputFile);
    struct Job jobs[size];

    string preemptive ="off";
    string methodScheduling= "None";

    // logic of the cpu scheduler (MENU PART)
 while(true){
    int selectionOption;
    cout<<" CPU SCHEDULER SIMULATOR \n";
    cout<<"1. Scheduling Method "<<"("<<methodScheduling<<")"<<"\n";
    cout<<"2. Premptive Mode "<<"("<<preemptive<<")"<<"\n";
    cout<<"3. Show Result\n";
    cout<<"4. End Program\n";
    cout<<"Choose Option > ";

    cin>> selectionOption;
           
        switch(selectionOption){
            case 1:  
            int SchedulingOption;
            cout<<" Choose what you want to do: \n";
            cout<<"1. None method Scheduling\n";
            cout<<"2. First come,First Served Schedulin\n";
            cout<<"3. Shortest Job First Scheduling\n";
            cout<<"4. Priority Scheduling\n";
            cout<<"5. Round Robin Scheduling\n";
            cout<<" Option > ";
            
            cin>>SchedulingOption;
            
            switch (SchedulingOption)
            {
             case 1: cout<<"None method Scheduling choosen\n"; 
             methodScheduling= "None";//first function
             break;
             case 2: fcomeFserved(jobs,inputFile,outputFile);
             methodScheduling="First come, first  served";//Implement first come , first served function
             break;
             case 3: if(preemptive=="On"){
                sJFPreemptive(jobs,inputFile,outputFile);//implement shortest job first preemptive
                methodScheduling="shortest Job First Preemptive";
             }
             else{
                 methodScheduling="shortest Job First No-Preemptive";
                }
              break;
             case 4: //function
              break;
             case 5: int quantumValue;
                        cout<<"\n enter the quantum value ";
                        cin>> quantumValue;
                        roundRobinScheduling(jobs,quantumValue,inputFile,outputFile);
                        methodScheduling="Round Robin Scheduling ";       
             break;
             default:
                cout<<"please make a good choice \n";
              break;
            }
            break;
            case 2: //Preemptive Mode
                if(preemptive== "off"){
                    preemptive= "On";
                    cout<<"the preemptive mode is on";
                }
                else{
                    preemptive== "off";
                    cout<< "the preemptive mode is off";
                }
            break;
            case 3: displayResults(outputFile);//Show Result
            break;
            case 4:
            cout<<" All of Scheduling Resultts: \n";
            displayResults(outputFile);
            cout<< "Exit the Program..\n\n";
            exit(1);
            break;
            default: cout<< "Please make a valid selection.\n\n";
            break; 
        }
 }
    return 0;

}

int readInputFromFile(struct Job* jobs,const char* fileName){
    FILE* inputFile= fopen(fileName, "r");
    
    if(!inputFile){
        cout<<"Error during opening file: "<<fileName<<"\n";
        return 0;
    }
    int n= 0;
    while(!feof(inputFile)){
        fscanf(inputFile, "%d: %d:%d", &jobs[n].bursTime,&jobs[n].arrivalTime,&jobs[n].priority);
        n++;
       
    }
 fclose(inputFile);
 return n;
}
// function to implement first come, first served

void fcomeFserved(struct Job* jobs, const char* fileName, const char* outputFile){
    //Enter the ouptfile file
    int n= readInputFromFile(jobs,fileName);
    int totalTime=0, waitingTime[n]={0};
    for(int i=0;i<n;i++){
        if(totalTime>=jobs[i].arrivalTime){
            waitingTime[i]=totalTime-jobs[i].arrivalTime;
        }
        else{
            waitingTime[i]=0;
        }
        totalTime+=jobs[i].bursTime;
    }
    cout<<"Scheduling Method: First come, First served\n Process waiting time: \n";
    displayAndCalculateAvg(outputFile,"Scheduling Method: First come, First served\n Process waiting time: \n", waitingTime,n);

    
}
//function to implement Round-Robin scheduling 
void roundRobinScheduling (struct Job* jobs, int timeQuantum, const char *fileName, const char* outputFile){
    int n= readInputFromFile(jobs, fileName);
    int i=0, total= 0,x, counter =0, waitingTime[n]={0}, temp[n];
    x=n;
    for(i=0; i<n; i++){
        temp[i]= jobs[i].bursTime;
     }
    for (total = 0, i=0;x!=0;)
     {
        if(temp[i]<= timeQuantum && temp[i]>0){
            total+= temp[i];
            temp[i]=0;
            counter = 1;
        } 
        else if(temp[i]>0){
            temp[i]= temp [i]- timeQuantum;
            total+= timeQuantum;
        }    
        if (temp[i]==0 && counter ==1){
            x--;
            waitingTime[i]= waitingTime[i]+total -jobs[i].arrivalTime- jobs[i].bursTime;
            counter=0;
        }
        if (i==n-1){
            i=0;
        }
        else if (jobs[i+1].arrivalTime<=total)
        {
            i++;
        }
        else{
            i=0;
        }
        
     }
     cout<<"Round Robin SCheduling - time_quantum = "<<timeQuantum<<"\nProcess waiting time: \n";
     displayAndCalculateAvg(outputFile, "Round Robin SCheduling - time_quantum = 2\nProcess waiting time: \n", waitingTime,n); 
}
//function to count line into input file
int countLines(const char* fileName){
    FILE* file= fopen(fileName, "r");
    if (file==NULL){
        cout<<"Error opening file: "<<fileName;
        return -1;
    }
    int lineCount= 0;
    int cha; //number of character

    while((cha= fgetc(file)) !=EOF){
        if (cha == '\n'){
            lineCount++;
        }
    }
    fclose (file);
    return lineCount;
}

// Function to display the scheduling results
void displayResults(const char* fileName)
{
     FILE* inputFile = fopen(fileName, "r");
    if (!inputFile) {
        fprintf(stderr, "Error opening file: %s\n", fileName);
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), inputFile)) {
        printf("%s", line);
    }

    fclose(inputFile);
}
void displayAndCalculateAvg(const char* fileName, const char* methode,int waitingTime[],int n){
    FILE* output= fopen(fileName,"a");
    if(output==NULL){
        cout<<"Error opening the output: " << fileName;
        return;
    }
    fprintf(output,"%s",methode);
    for (int i = 0; i < n; ++i){
        cout<<"P"<<i +1<< ": "<<waitingTime[i]<< " ms\n";
        fprintf(output, "P%d: %d ms\n", i+1, waitingTime[i]);
    }
    int totalWaitingTime=0;
    for (int i=0; i<n; i++){
        totalWaitingTime+= waitingTime[i];
    }
    double average = totalWaitingTime / n;
    cout<< "Average waiting time: "<< average<< " ms\n";
    fprintf(output, "Average waiting time: %.1f ms\n", average);

    fclose(output);
}
void sJFPreemptive(struct Job* jobs,const char *fileName, const char *outputFile){
    int n= readInputFromFile(jobs, fileName);
    int currentT=0, completedJobs=0, waitingTime[n], remainingTime[n];

    for(int i =0; i<n; i++){
        remainingTime[i]= jobs[i].bursTime;
        waitingTime[i]=0; //rendre cela a zero dans l'array
    }
    while(completedJobs<n){
        int sJobIndex = -1, sTime= INT_MAX;
        for (int i=0; i<n; i++){
            if(jobs[i].arrivalTime<= currentT && remainingTime[i]< sTime && remainingTime[i]>0){
                sJobIndex=i;
                sTime= remainingTime[i];
            }
        }
        if (sJobIndex==-1){
            currentT++;
            continue;
        }
        for (int i= 0; i<n; i++){
            if(i!= sJobIndex && jobs[i].arrivalTime<= currentT&& remainingTime[i]>0){
                waitingTime[i]++;
            }
        }
        remainingTime[sJobIndex]--;
        if(remainingTime[sJobIndex]==0){
            completedJobs++;
            currentT++;
        }
        else{
            currentT++;
        }
    }
    cout<<"Scheduling method: shortest job First -preemptive\nProcess waiting time: \n";
    displayAndCalculateAvg(outputFile, "Scheduling method: shortest job First -preemptive\nProcess waiting time: \n", waitingTime,n);
}
void sJFNonPreemptive(struct Job* jobs, const char* fileName, const char *outputFile){
    
}