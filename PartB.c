#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>

typedef struct student_marks
{
    char student_index[20];
    float assignmt01_marks;
    float assignmt02_marks;
    float project_marks;
    float finalExam_marks;
} student_marks;

float getMax();
float getMin();
float getAvg();


int main(void)
{
    //Processes were used in following manner
    //  CC1 = Calculate Max
    //  C1  = Calculate Min
    //  CC2 = Calculate Avg
    //  C2  = Calculate the number of students less than 5%


    int FD1[2];
    int FD2[2];
    int FD3[2];
    int FD4[2];
    int p1 = pipe(FD1);
    int p2 = pipe(FD2); 
    int p3 = pipe(FD3); 
    int p4 = pipe(FD4);

    pid_t parentID = getpid();

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
        pid_t PID1 = fork();
        if(PID1==-1)
        {
            //Error
            printf("\nChild process(C1) could not be created");
            perror("\nChild process(C1): ");
            printf("\nError number is %d", errno);
            exit(0);
            
        }
        else if(PID1==0)    //C1
        {  
            //printf("\nParent: Child process(C1)created successfully");
            pid_t PID3 = fork();
            if(PID3==-1)
            { 
                //Error
                printf("\nC1: Child process(CC1) could not be created");
                perror("\nC1: Child process(CC1): ");
                printf("\nC1: Error number is %d", errno);
                exit(0);
                        
            }
            else if(PID3==0)//CC1
            {
               
                       
            }        
            else //C1
            {
                
                        
            }     
                   
        }
        else //Parent process
        {
            pid_t PID2=fork();

            if(PID2 == -1)
            {
                printf("\nChild process(C2) could not be created");
                perror("\nChild process(C2): ");
                printf("\nError number is %d", errno);
                exit(0);
            }
            else if(PID2 == 0) //C2
            {
                pid_t PID4 = fork();
                if(PID4 == -1)
                {
                    printf("\nC2: Child process(CC2) could not be created");
                    perror("\nC2: Child process(CC2): ");
                    printf("\nC2: Error number is %d", errno);
                    exit(0);
                }
                else if(PID4 == 0) //CC2
                {
                   
                }
                else //C2
                {
                   

                }

            }
            else //Parent
            {


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