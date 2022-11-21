#define _GNU_SOURCE
#include <stdio.h>  // for printf function
#include <stdlib.h> // for exit function
#include <string.h> // for manipulating arrays of characters.
#include <errno.h>  // for error handling
#include <stdbool.h>  

#define ACTION_H_
#define RANDOM_H_
#define STUDENT_H_



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
            // Divider();
            // insertStudent();
            break;
        case 2:
            // readAllRecords();
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

