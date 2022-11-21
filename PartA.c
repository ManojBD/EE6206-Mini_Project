#define _GNU_SOURCE
#include <stdio.h>  // for printf function
#include <stdlib.h> // for exit function
#include <string.h> // for manipulating arrays of characters.
#include <errno.h>  // for error handling
#include <stdbool.h>  

#define ACTION_H_
#define RANDOM_H_
#define STUDENT_H_

void allData(void);
void Divider();

// structure definition of Student Data
typedef struct student_marks
{
    char student_index[20];
    float assignmt01_marks;
    float assignmt02_marks;
    float project_marks;
    float finalExam_marks;
} student_marks;

void writeStudentRecord(student_marks student);

int main(int argc, char const *argv[])
{
    int p;
    
     do{
        Divider();
        printf("Module Code: ZZ6309\n");
        printf("Module Name: Linux Operating System\n");
        Divider();
        printf("Menu:\t1.Insert New Student Record\n\t2.Show All Records\n\t3.Generate Records\n\t4.Update a Student Record\n\t5.Delete a Record\n\t6.Exit\n");
        printf("\nEnter Your Choice : ");
        scanf("%d", &p);

      

        switch (p)
        {
        case 1:
            //Divider();
            //insertStudent();
            break;
        case 2:
            allData();
            break;
        case 3:
            // Divider();
            // generateRecords();
            break;
        case 4:
            // Divider();
            // updateRecord();
            break;
        case 5:
            // Divider();
            // deleteRecord();
            break;
        case 6:
            exit(0);
            break;
        }
     }while(1);
    return 0;
}

void allData()
{
    Divider();

    FILE *fd;
    student_marks student;
    int index = 1;
    int err_No;
    

    Divider();
    printf("| %-6s | %-20s | %-20s | %-20s | %-20s | %-20s  | \n","No" ,"Student Index", "Assignment 01",
                   "Assignment 02", "Project Marks", "Final Marks");
    Divider();

    //open file with read option
    fd = fopen("Student_Data.txt", "r");
    if (fd == NULL)
    {
        printf("Student_Data.txt: could not read the file ");
        perror("Student_Data.txt: ");
        printf("The error number is: %d\n", errno);
        exit(1);
    }
    while (1)
    {
        //read one data from file 
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
            //print records
            printf("| %-6d | %-20s | %-20.2f | %-20.2f | %-20.2f | %-20.2f  | \n",index ,student.student_index, student.assignmt01_marks, student.assignmt02_marks, student.project_marks, student.finalExam_marks);
            index++;
            
        }
    }
    
    printf("\n");
    fclose(fd);
}

void Divider(){
    printf("******************************************************************************************************************************\n");
}