#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

using namespace std;

// here to implement job and process in structure
struct Job{
    int bursTime;
    int arrivalTime;
    int priority;
    struct Job* next;
};
//this function is for read data from the text file
struct Job* readInputFromFile(const char* fileName);

//this function is implemented for First come, First served;
void fcomeFserved(struct Job* jobs, const char* fileName);
//function to display implement Round-Robin SCheduling
void roundRobinScheduling (struct Job* jobs, int timeQuantum, const char *fileName);
//void displayAverageWaitingTime(struct Job* jobs, char schedulingMethod);
//function to display the scheduling results
void displayResults(const char* fileName);

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
    // for read the input data from the file
    struct Job* jobs= readInputFromFile(inputFile);

    // logic of the cpu scheduler(MENU PART)
 while(true){
    int selectionOption;
    cout<<" CPU SCHEDULER SIMULATOR \n";
    cout<<"1. Scheduling Method(none)\n";
    cout<<"2. Premptive Mode\n";
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
            cout<<" Option >";
            
            cin>>SchedulingOption;
            
            switch (SchedulingOption)
            {
             case 1: //first function
             break;
             case 2: fcomeFserved(jobs,outputFile);//Implement first come , first served function
             break;
             case 3: //third function
              break;
             case 4: //function
              break;
             case 5: int quantumValue;
                        cout<<"\n enter the quantum value";
                        cin>> quantumValue;
                        roundRobinScheduling(jobs,quantumValue,outputFile);       
             break;
             default:
                cout<<"please make a good choice";
              break;
            }
            break;
            case 2: //Preemptive Mode
            break;
            case 3: displayResults(outputFile);//Show Res
            break;
            case 4:cout<< "Exit the Program..\n\n";
            exit(1);
            break;
            default: cout<< "Please make a valid selection.\n\n";
            break; 
        }
 }
    // Free allocated memory for jobs

    while(jobs!=NULL){
        struct Job* temp = jobs;
        jobs = jobs->next;
        free(temp);
    }
    return 0;

}

struct Job* readInputFromFile(const char* fileName){
    FILE* inputFile= fopen(fileName, "r");
    struct Job* head= NULL;
    struct Job* tail= NULL;
    if(!inputFile){
        fprintf(stderr,"Error during opening file: %s\n", fileName);
        return head;
    }

    while(!feof(inputFile)){
        struct Job* newJob = (struct Job*)malloc(sizeof(struct Job));
        if(!newJob){
            fprintf(stderr, "we didnt allocate the memory allocation\n");
            return head;
        }

        char line[50];
        if (fgets(line, sizeof(line), inputFile) == NULL) {
            return head;
        }

        sscanf(line, "%d:%d:%d", &newJob->bursTime, &newJob->arrivalTime, &newJob->priority);
        newJob->next = NULL;

        if (!head) {
            head = newJob;
            tail = newJob;
        } 
        else {
            tail->next = newJob;
            tail = newJob;
        }
    }
 fclose(inputFile);
 return head;
}
// function to implement first come, first served

void fcomeFserved(struct Job* jobs, const char* fileName){
    //Enter the ouptfile file
    FILE*outputFile= fopen(fileName, "w");
    if(!outputFile){
        fprintf(stderr, "Error during opening output file: output.txt\n");
        return;
    }
    //initialize variable for total waiting
    int totalWaiting=0;
    int currentT=0;
    int i =0;
    //go through linked list
    struct Job* currentJob= jobs;
    fprintf(outputFile, "SCheduling method: First come, First served");
    fprintf(outputFile, "Process waiting time: \n");
    while (currentJob!=NULL){
        i++;
        int waitingT= currentT- currentJob->arrivalTime;// calculate waiting time
        if (waitingT<0){
            waitingT=0;//just to be sure that waiting time is non negative
        }

        totalWaiting += waitingT;// update
        //write proceess info in output file
        fprintf(outputFile, "P%d: %d ms\n", i, waitingT);
                
        currentT += currentJob->bursTime;

        currentJob=currentJob->next;

    }
    int nProcess=0;
    struct Job* tempJob = jobs;
    while (tempJob !=NULL){
        nProcess++;
        tempJob=tempJob->next;
    }

    if (nProcess>0){
        float avgWT=(float) totalWaiting/nProcess;
        fprintf(outputFile,"Average waiting Time: %.1f ms\n",avgWT);
    }
    else{
        cout<<"No process for calculation of average time";
    }
    fclose(outputFile);

}
//function to implement Round-Robin scheduling 
void roundRobinScheduling (struct Job* jobs, int timeQuantum, const char *fileName){
    FILE *outputFile = fopen(fileName, "a");
    if (!outputFile)
    {
        fprintf(stderr, "Error opening output file: %s\n", fileName);
        return;
    }

    // Initialize variables for total waiting time and current time
    int totalWaitingTime = 0;
    int currentTime = 0;
    int i = 0;

    fprintf(outputFile, "Scheduling Method: Round Robin Scheduling – time_quantum=%d\n", timeQuantum);
    fprintf(outputFile, "Process Waiting Times:\n");

    // Traverse the linked list to process jobs in Round Robin order
    struct Job *currentJob = jobs;
    while (currentJob != NULL)
    {
        i++;

        // Calculate waiting time for the current process
        int waitingTime = currentTime - currentJob->arrivalTime;
        if (waitingTime < 0)
        {
            waitingTime = 0; // Ensure waiting time is non-negative
        }

        // Update total waiting time
        totalWaitingTime += waitingTime;

        // Write process information to the output file
        fprintf(outputFile, "P%d: %d ms\n", i, waitingTime);

        // Update current time to the completion time of the current process
        if (currentJob->bursTime > timeQuantum)
        {
            currentTime += timeQuantum;
            currentJob->bursTime -= timeQuantum;
            // Move the current job to the end of the queue
            struct Job *temp = currentJob;
            currentJob = currentJob->next;
            temp->next = NULL;
            // Append the job to the end of the linked list
            struct Job *tempJob = jobs;
            while (tempJob->next != NULL)
            {
                tempJob = tempJob->next;
            }
            tempJob->next = temp;
        }
        else
        {
            currentTime += currentJob->bursTime;
            currentJob->bursTime = 0; // Process completed
            // Move to the next job
            currentJob = currentJob->next;
        }
    }

    // Calculate and write average waiting time to the output file
    int numberOfProcesses = 0;
    struct Job *tempJob = jobs;
    while (tempJob != NULL)
    {
        numberOfProcesses++;
        tempJob = tempJob->next;
    }

    // Avoid division by zero
    if (numberOfProcesses > 0)
    {
        float averageWaitingTime = (float)totalWaitingTime / numberOfProcesses;
        fprintf(outputFile, "Average Waiting Time: %.1f ms\n", averageWaitingTime);
    }
    else
    {
        fprintf(outputFile, "No processes to calculate average waiting time.\n");
    }

    fclose(outputFile);


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