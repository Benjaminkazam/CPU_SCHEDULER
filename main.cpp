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
void fcomeFserved();

int main (int argc, char *argv[]){
    //i wanna check if the correct command line is provide
    if (argc!=5){
        fprintf(stderr, "You must use this format for running the code : %s -f input.txt -o output.txt\n", argv[0]);
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
    cout<<"CPU SCHEDULER SIMULATOR\n";
    cout<<"1. Scheduling Method(none)\n";
    cout<<"2. Preemptive Mode\n";
    cout<<"3. Show Result\n";
    cout<<"4. End Program\n";
    cout<<"Choose Option > ";

    cin>> selectionOption;
           
        switch(selectionOption){
            case 1:  
            int SchedulingOption;
            cout<<" Choose what you want to do: \n";
            cout<<"1. None method\n";
            cout<<"2. First come,First Served\n";
            cout<<"3. Shortest Job First\n";
            cout<<"4. Priority Scheduling\n";
            cout<<"5. Round Robin\n";
            
            cin>>SchedulingOption;
            
                switch (SchedulingOption)
            {
             case 1: /* constant-expression */
             break;
             case 2: /* constant-expression */
             break;
             case 3: /* constant-expression */
              break;
             case 4: /* constant-expression */
              break;
             case 5: /* constant-expression */
             break;
             default:
                cout<<"please make a good choice";
              break;
            }
            break;
            case 2: //Preemptive Mode
            break;
            case 3: //Show Result
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
    if(!inputFile){
        fprintf(stderr,"Error during opening file: %s\n", fileName);
        exit(1);
    }
    struct Job* head= NULL;
    struct Job* tail= NULL;

    while(!feof(inputFile)){
        struct Job* newJob = (struct Job*)malloc(sizeof(struct Job));
        if(!newJob){
            fprintf(stderr, "we didnt allocate the memory allocation\n");
            exit(1);
        }

        char line[50];
        if (fgets(line, sizeof(line), inputFile) == NULL) {
            break;
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

void fcomeFserved(struct Job* jobs){
    //initialize the time
    int totalWaiting=0;
    int currentT=0;
    //go through linked list
    struct Job* currentJob= jobs;
    while (currentJob!=NULL){
        int waitingT= currentT- currentJob->arrivalTime;
        if (waitingT<0){
            waitingT=0;//just to be sure that waiting time is non negative
        }

        totalWaiting += waitingT;
        cout<<"P" <<currentJob->arrivalTime<<":" <<waitingT<< "ms\n";
        
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
        float avgWT= totalWaiting/nProcess;
        cout<<"Average waiting time is: "<<avgWT<<" ms\n";
    }
    else{
        cout<<"No process for calculation of average time";
    }






}
