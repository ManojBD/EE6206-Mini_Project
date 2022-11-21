#define _GNU_SOURCE
#include <stdio.h>  // for printf function
#include <stdlib.h> // for exit function
#include <string.h> // for manipulating arrays of characters.
#include <errno.h>  // for error handling
#include <stdbool.h>  

void printAllData(void);
void insertStd(void);
void updateStd();
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
    int userInp;
    
     do{
        printDivider();
        printf("Module Code: ZZ6309\n");
        printf("Module Name: Linux Operating System\n");
        printDivider();
        printf("\n");
        printf("Menu:\t1.Show All Student Records\n\t2.Insert a New Student Record\n\t3.Update a Student Record\n\t4.Delete a Student Record\n\t5.Exit\n");
        printf("\nSelect the Operation : ");
        scanf("%d", &userInp);

      

        switch (userInp)
        {
        case 1:
            printAllData();
            break;
        case 2:
            printDivider();
            insertStd();
            break;
        case 3:
            printDivider();
            updateStd();
            break;
        case 4:
            printDivider();
            deleteStd();
            break;
        case 5:
            exit(0);
            break; 
        }
     }while(1);
    return 0;
}

void printAllData()
{

    FILE *fd;
    student_marks student;
    int index = 1;
    int err_No;
    
    printf("\n");
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
    printDivider();
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

//update recode
void updateStd()
{
    FILE *fd;
    student_marks student;
    int err_No;
    // get the number of records in the file
    char student_index[20];
    //get the index of the student to update
    printf("Enter student full index number to update: ");
    scanf("%s", student_index); 


    //open file with read option
    fd = fopen("Student_Data.txt", "r+");
    if (fd == NULL)
    {
        printf("Student_Data.txt: could not be opened");
        perror("Student_Data.txt: \n");
        printf("The error number is: %d\n",errno);
    }

    while (1)
    {
        //read one data from file 
        fread(&student, sizeof(student_marks), 1, fd);
        if (feof(fd))
        {
            printf("File is empty: Update Failed\n");
            break;
        }
        if ((err_No = ferror(fd)) > 0)
        {
            printf("Failed to read from the file");
            perror("Student_Data.txt: \n");
            printf("The error number is: %d\n",errno);
            exit(1);
        }
        else
        {
            //find student and update data
            if(strcmp(student.student_index,student_index) == 0)
            {
                //move to student found position
                fseek(fd,-sizeof(student_marks),SEEK_CUR);

                printf("Enter assignment 01 new marks : ");
                scanf("%f", &student.assignmt01_marks);
                printf("Enter assignment 02 new marks : ");
                scanf("%f", &student.assignmt02_marks);
                printf("Enter project new marks : ");
                scanf("%f", &student.project_marks);
                printf("Enter finals new marks : ");
                scanf("%f", &student.finalExam_marks);

                // write one student data to file
                int written = fwrite(&student, sizeof(student_marks), 1, fd); 

                // check for error in write to file
                if (written < 0) 
                {
                    printf("Student_Data.txt: failed to write to the file");
                    perror("Student_Data.txt: \n");
                    printf("The error number is: %d\n",errno);
                    exit(1);
                }
                printf("Student record updated successfully\n");
                break;

            }
        }
    }
    printf("\n");
    fclose(fd);
}