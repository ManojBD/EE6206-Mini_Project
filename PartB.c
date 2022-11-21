#include <stdio.h> //For printf and scanf
#include <stdlib.h> //Functions like "exit" is defined in here
#include <unistd.h> //For fork()
#include <errno.h> //For error handling
#include <sys/wait.h> //For waitpid
#include <sys/types.h> //For system calls

//Defining student_marks structure
typedef struct student_marks
{
    char student_index[20];
    float assignmt01_marks;
    float assignmt02_marks;
    float project_marks;
    float finalExam_marks;
} student_marks;

//Defining functions
float getMax();
float getMin();
float getAvg();
int getLessThan5Count();

int main(void)
{
    //Processes were used in following manner
    //  CC1 = Calculate Max
    //  C1  = Calculate Min
    //  CC2 = Calculate Avg
    //  C2  = Calculate the number of students less than 5%

    //Defile file descriptors
    int FD1[2];
    int FD2[2];
    int FD3[2];
    int FD4[2];

    //Create pipes
    int p1 = pipe(FD1);
    int p2 = pipe(FD2); 
    int p3 = pipe(FD3); 
    int p4 = pipe(FD4);

    //Error handling for all pipes
    if((p1==-1)||(p2==-1)||(p3==-1)||(p4==-1))
    {
        printf("\nPipe could not be created");
        perror("\nPipe: ");
        printf("\nError number is %d", errno);
        exit(0);
    }
    else 
    {
        //printf("\nParent: Pipes created successfully");
        pid_t PID1 = fork();//fork

        //Error handling for fork
        if(PID1==-1)
        {
            printf("\nChild process(C1) could not be created");
            perror("\nChild process(C1): ");
            printf("\nError number is %d", errno);
            exit(0);
            
        }
        //C1
        else if(PID1==0)    
        {  
            //printf("\nParent: Child process(C1)created successfully");
            pid_t PID3 = fork();//fork 

            //Error handling for fork
            if(PID3==-1)
            { 
                printf("\nC1: Child process(CC1) could not be created");
                perror("\nC1: Child process(CC1): ");
                printf("\nC1: Error number is %d", errno);
                exit(0);
                        
            }
            //CC1
            else if(PID3==0)
            {
                //printf("\nC1: Child process(CC1)created successfully");
                        
                float max = getMax();//Get the maximum value
                
                close(FD1[0]);
                //write data in to the pipe, FD1
                int bytes_written = write(FD1[1],&max,sizeof(max));
                close(FD1[1]);

                //Error handling for write
                if(bytes_written == -1)
                {
                    printf("\nCC1: Writing to pipe is failed");
                    perror("\nCC1: Writing: ");
                    printf("\nCC1: Error number is %d", errno);
                }
                       
            }  
            //C1      
            else 
            {
                float min = getMin();//Get the minimum value
            
                close(FD2[0]);
                //write data in to the pipe, FD2
                int bytes_written = write(FD2[1],&min,sizeof(min));
                close(FD2[1]);

                //Error handling for write
                if(bytes_written == -1)
                {
                    printf("\nC1: Writing to pipe is failed");
                    perror("\nC1: Writing: ");
                    printf("\nC1: Error number is %d", errno);
                }
                        
            }     
                   
        }
        //Parent process
        else 
        {
            pid_t PID2=fork();//fork

            //Error handling for fork
            if(PID2 == -1)
            {
                printf("\nChild process(C2) could not be created");
                perror("\nChild process(C2): ");
                printf("\nError number is %d", errno);
                exit(0);
            }
            //C2
            else if(PID2 == 0) 
            {
                pid_t PID4 = fork();//fork

                //Error handling for fork
                if(PID4 == -1)
                {
                    printf("\nC2: Child process(CC2) could not be created");
                    perror("\nC2: Child process(CC2): ");
                    printf("\nC2: Error number is %d", errno);
                    exit(0);
                }
                 //CC2
                else if(PID4 == 0)
                {
                    //printf("\nC2: Child process(CC2)created successfully");

                    float avg = getAvg();//Geth the average value
            
                    close(FD3[0]);
                    //write data in to the pipe, FD3
                    int bytes_written = write(FD3[1],&avg,sizeof(avg));//write data in to file descriptor
                    close(FD3[1]);

                    //Error handling for write
                    if(bytes_written == -1)
                    {
                        printf("\nCC2: Writing to pipe is failed");
                        perror("\nCC2: Writing: ");
                        printf("\nCC2: Error number is %d", errno);
                    }

                }
                //C2
                else 
                {
                    int lessThan5 = getLessThan5Count();//Get the number of students who has less than 5% marks
            
                    close(FD4[0]);
                    //write data in to the pipe, FD4
                    int bytes_written = write(FD4[1],&lessThan5,sizeof(lessThan5));//write data in to file descriptor
                    close(FD4[1]);

                    //Error handling for write
                    if(bytes_written == -1)
                    {
                        printf("\nC2: Writing to pipe is failed");
                        perror("\nC2: Writing: ");
                        printf("\nC2: Error number is %d", errno);
                    }

                }

            }
            //Parent
            else 
            {
                float min, max, avg;
                int lessThan5Count;

                sleep(0.01);

                //Read from pipe FD1
                close(FD1[1]);
                int bytes_read1 = read(FD1[0], &max, sizeof(max));
                close(FD1[0]);
                
                //Error handling for read
                if(bytes_read1==-1)
                {
                    printf("\nParent: Read from pipe1 is failed");
                    perror("\nParent: Reading: ");
                    printf("\nParent: Error number is %d", errno);
                    exit(0);
                }

                //Read from pipe FD2
                close(FD2[1]);
                int bytes_read2 = read(FD2[0], &min, sizeof(min));
                close(FD2[0]);
                
                //Error handling for read
                if(bytes_read2==-1)
                {
                    printf("\nParent: Read from pipe2 is failed");
                    perror("\nParent: Reading: ");
                    printf("\nParent: Error number is %d", errno);
                    exit(0);
                }
                
                //Read from pipe FD3
                close(FD3[1]);
                int bytes_read3 = read(FD3[0], &avg, sizeof(avg));
                close(FD3[0]);
                
                //Error handling for read
                if(bytes_read3==-1)
                {
                    printf("\nParent: Read from pipe3 is failed");
                    perror("\nParent: Reading: ");
                    printf("\nParent: Error number is %d", errno);
                    exit(0);
                }

                //Read from pipe FD4
                close(FD4[1]);
                int bytes_read4 = read(FD4[0], &lessThan5Count, sizeof(lessThan5Count));
                close(FD4[0]);

                //Error handling for read 
                if(bytes_read4 ==-1)
                {
                    printf("\nParent: Read from pipe4 is failed");
                    perror("\nParent: Reading: ");
                    printf("\nParent: Error number is %d", errno);
                    exit(0);
                }

                printf("\n\nAnalyzing Assignment 01 Marks\n");
                printf("=============================\n");
                printf("\nMaximum mark = %.2f\nMinimum mark =  %.2f\nAverage = %.2f\nNo of students less than 5%% = %d\n",max,min,avg,lessThan5Count);
                printf("\n");
                printf("=============================\n");


            }

        }

    }
    return (0);
}

float getMax()
{
    FILE *fd;
    student_marks student;
    float max =0;
    int err_No;
    
    //open file "Student_Data.txt" with read option
    fd = fopen("Student_Data.txt", "r");
    if (fd == NULL)
    {
        printf("Student_Data.txt: File could not be opened ");
        perror("Student_Data.txt: ");
        printf("The error number is: %d\n", errno);
        exit(1);
    }
    while (1)
    {
        //read a single data record from file 
        fread(&student, sizeof(student_marks), 1, fd);
        if (feof(fd))
        {
            break;
        }
        if ((err_No = ferror(fd)) > 0)
        {
            perror("fread Student_Data.txt ");
            printf("ferror: %d\n", err_No);
            exit(1);
        }
        else
        {
            if(student.assignmt01_marks>max)
            {
                max = student.assignmt01_marks;
            }
            
        }
    }
    
    fclose(fd);
    return max;
}

float getMin()
{
    FILE *fd;
    student_marks student;
    float min =0;
    float result =0;
    int err_No;
    
    //open file "Student_Data.txt" with read option
    fd = fopen("Student_Data.txt", "r");
    if (fd == NULL)
    {
        printf("Student_Data.txt: File could not be opened ");
        perror("Student_Data.txt: ");
        printf("The error number is: %d\n", errno);
        exit(1);
    }
    while (1)
    {
        //read a single data record from file 
        fread(&student, sizeof(student_marks), 1, fd);
        if (feof(fd))
        {
            break;
        }
        if ((err_No = ferror(fd)) > 0)
        {
            perror("fread Student_Data.txt ");
            printf("ferror: %d\n", err_No);
            exit(1);
        }
        else
        {
            if(student.assignmt01_marks<min)
            {
                min = student.assignmt01_marks;
            } 
           
        }
    }
    
    fclose(fd);
    return result;
}

float getAvg()
{
    FILE *fd;
    student_marks student;
    float sum =0;
    int stdCount=0;
    float avg=0;
    int err_No;
    
    //open file "Student_Data.txt" with read option
    fd = fopen("Student_Data.txt", "r");
    if (fd == NULL)
    {
        printf("Student_Data.txt: File could not be opened ");
        perror("Student_Data.txt: ");
        printf("The error number is: %d\n", errno);
        exit(1);
    }
    while (1)
    {
        //read a single data record from file 
        fread(&student, sizeof(student_marks), 1, fd);
        if (feof(fd))
        {
            break;
        }
        if ((err_No = ferror(fd)) > 0)
        {
            perror("fread Student_Data.txt ");
            printf("ferror: %d\n", err_No);
            exit(1);
        }
        else
        {
            stdCount++;
            sum += student.assignmt01_marks;
        }
    }
    
    avg = sum/stdCount; 
    fclose(fd);
    return avg;
}

int getLessThan5Count()
{
    FILE *fd;
    student_marks student;
    int stdCount=0;
    int err_No;
    
    //open file "Student_Data.txt" with read option
    fd = fopen("Student_Data.txt", "r");
    if (fd == NULL)
    {
        printf("Student_Data.txt: File could not be opened ");
        perror("Student_Data.txt: ");
        printf("The error number is: %d\n", errno);
        exit(1);
    }
    while (1)
    {
        //read a single data record from file 
        fread(&student, sizeof(student_marks), 1, fd);
        if (feof(fd))
        {
            break;
        }
        if ((err_No = ferror(fd)) > 0)
        {
            perror("fread Student_Data.txt ");
            printf("ferror: %d\n", err_No);
            exit(1);
        }
        else
        {
            if((student.assignmt01_marks*100/15)<5.0000)
            {
                    stdCount++;
            }
        }
    }
    
    fclose(fd);
    return stdCount;
}
