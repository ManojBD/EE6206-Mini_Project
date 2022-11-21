#define _GNU_SOURCE
#include <stdio.h>  // for printf function
#include <stdlib.h> // for exit function
#include <string.h> // for manipulating arrays of characters.
#include <errno.h>  // for error handling
#include <stdbool.h>  

#define ACTION_H_
#define RANDOM_H_
#define STUDENT_H_

void printAllData(void);
void insertStd(void);
void deleteStd();
void printDivider(void);

// structure definition of Student Data
typedef struct student_marks
{
    char student_index[20];
    float assignmt01_marks;
    float assignmt02_marks;
    float project_marks;
    float finalExam_marks;
} student_marks;

void addRecord(student_marks student);

int main(int argc, char const *argv[])
{
    int p;
    
     do{
        printDivider();
        printf("Module Code: ZZ6309\n");
        printf("Module Name: Linux Operating System\n");
        printDivider();
        printf("Menu:\t1.Insert New Student Record\n\t2.Show All Records\n\t3.Generate Records\n\t4.Update a Student Record\n\t5.Delete a Record\n\t6.Exit\n");
        printf("\nEnter Your Choice : ");
        scanf("%d", &p);

      

        switch (p)
        {
        case 1:
            printDivider();
            insertStd();
            break;
        case 2:
            printAllData();
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
            printDivider();
            deleteStd();
            break;
        case 6:
            exit(0);
            break;
        }
     }while(1);
    return 0;
}

void printAllData()
{
    printDivider();

    FILE *fd;
    student_marks student;
    int index = 1;
    int err_No;
    

    printDivider();
    printf("| %-6s | %-20s | %-20s | %-20s | %-20s | %-20s  | \n","No" ,"Student Index", "Assignment 01",
                   "Assignment 02", "Project Marks", "Final Marks");
    printDivider();

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

void printDivider(){
    printf("******************************************************************************************************************************\n");
}



//Function to insert new student
void insertStd()
{
    student_marks student;

    printf("Enter student index : ");
    scanf("%s", student.student_index);
    printf("Enter assignment 01 marks : ");
    scanf("%f", &student.assignmt01_marks);
    printf("Enter assignment 02 marks : ");
    scanf("%f", &student.assignmt02_marks);
    printf("Enter project marks : ");
    scanf("%f", &student.project_marks);
    printf("Enter final exam marks : ");
    scanf("%f", &student.finalExam_marks);
    addRecord(student);
};

//write student data to file
void addRecord(student_marks student)
{
    FILE *fd;

    //Open "Student_Data.txt" with append
    fd = fopen("Student_Data.txt", "a+"); 
    if (fd == NULL)
    {
        printf("Student_Data.txt: could not be opened");
        perror("Student_Data.txt: \n");
        printf("The error number is: %d\n",errno);
        exit(1);
    }

    // write student data to Student_Data.txt
    int written = fwrite(&student, sizeof(student_marks), 1, fd); 

    // Error handling in write function
    if (written < 0) 
    {
        printf("Student_Data.txt: could not be written into student_Data.txt");
        perror("Student_Data.txt: \n");
        printf("The error number is: %d\n",errno);

    }

    //Close the file descriptor
    fclose(fd); 
}

//Function for delete a student record based on the index no
void deleteStd()
{

    FILE *fd1,*fd2;
    student_marks student;
    int err_No;
    char student_index[20];
    //read student index number
    printf("Enter full student index number to delete: ");
    scanf("%s", student_index);
    int status=0;

    //open file with read write options
    fd1 = fopen("Student_Data.txt", "r+");
    fd2 = fopen("Student_Data_Temp.txt","a+");
    if (fd1 == NULL || fd2 == NULL)
    {
        printf("Student_Data.txt, Student_Data_Temp.txt: failed to open file");
        perror("Student_Data.txt, Student_Data_Temp.txt : \n");
        printf("The error number is: %d\n",errno);
        exit(1);
    }

    while (1)
    {
        //read student data from "Student_Data.txt"
        fread(&student, sizeof(student_marks), 1, fd1);
        if (feof(fd1))
        {
            break;
        }
        if ((err_No = ferror(fd1)) > 0)
        {
            printf("Failed to read from the file");
            perror("Student_Data.txt: \n");
            printf("The error number is: %d\n",errno);
            exit(1);
        }
        else
        {
            //Find the relevant index in "Student_Data.txt"
            if(strcmp(student.student_index,student_index) != 0)
            {
                //Copy student data to "Student_Data_Copied.txt"
                int written = fwrite(&student, sizeof(student_marks), 1, fd2); 
                
                //Error handing for write
                if (written < 0) 
                {
                    printf("The error number is: %d\n",errno);
                    perror("fwrite Error: ");
                    exit(1);
                } 
            }
            else
            {
                status = 1;
            }
        }
    }
    printf("\n");
    fclose(fd1);
    fclose(fd2);
    
    //Removing "Student_Data.txt" and error handling
    if(remove("Student_Data.txt") != 0) 
    {
        perror("File could not be removed: ");
        printf("The error No is: %d\n", errno);
        exit(1);
    }

    //Renaming "Student_Data_Temp.txt" into "Student_Data.txt" and error handling
    if(rename("Student_Data_Temp.txt","Student_Data.txt") != 0) 
    {
        perror("File could not be renamed: ");
        printf("The error no is: %d\n", errno);
        exit(1);
    }

    if(status){
        printf("Student deleted successfully\n");
    }else{
        printf("Delete unsuccessful\n");
    }
    
}