#define _GNU_SOURCE
#include <stdio.h>  // for printf function
#include <stdlib.h> // for exit function
#include <string.h> // for manipulating arrays of characters.
#include <errno.h>  // for error handling


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
        default:
            printf("\n\nInvalid user input\n");
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
    printf("| %-5s | %-15s | %-15s | %-15s | %-15s | %-15s  | \n","No" ,"Student Index", "Assignment 01",
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
            printf("| %-5d | %-15s | %-15.2f | %-15.2f | %-15.2f | %-15.2f  | \n",index ,student.student_index, student.assignmt01_marks, student.assignmt02_marks, student.project_marks, student.finalExam_marks);
            index++;
            
        }
    }
    printDivider();
    printf("\n");
    fclose(fd);
}

void printDivider(){
    printf("====================================================================================================\n");
}



//Function to insert new student record
void insertStd()
{
    student_marks student;
    FILE *fd; 

    //Get user input for the new student record
    printf("Enter student index (Format: EG/2018/xxxx): ");
    scanf("%s", student.student_index);
    printf("Enter assignment 01 marks (Out of 15%%): ");
    scanf("%f", &student.assignmt01_marks);
    printf("Enter assignment 02 marks (Out of 15%%) : ");
    scanf("%f", &student.assignmt02_marks);
    printf("Enter project marks (Out of 20%%): ");
    scanf("%f", &student.project_marks);
    printf("Enter final exam marks (Out of 50%%): ");
    scanf("%f", &student.finalExam_marks);

    //Open "Student_Data.txt" with append option
    fd = fopen("Student_Data.txt", "a+"); 
    if (fd == NULL) //Errro handling for fopen
    {
        printf("Student_Data.txt: could not be opened");
        perror("Student_Data.txt: \n");
        printf("The error number is: %d\n",errno);
        exit(1);
    }

    // write user input student data to "Student_Data.txt"
    int written = fwrite(&student, sizeof(student_marks), 1, fd); 

    // Error handling for fwrite function
    if (written < 0) 
    {
        printf("Student_Data.txt: could not be written into student_Data.txt");
        perror("Student_Data.txt: \n");
        printf("The error number is: %d\n",errno);
    }
    else
    {
        printf("\nStudent record successfully inserted\n");
    }
    //Close the file descriptor fd
    fclose(fd); 
}

//Function to delete a student record based on the index no
void deleteStd()
{

    FILE *fd1,*fd2; //file descriptors
    student_marks student;
    int err_No;
    char student_index[20];
    int status=0;

    //Open "Student_Data.txt" and "Student_Data_Temp.txt" files
    fd1 = fopen("Student_Data.txt", "r+");
    fd2 = fopen("Student_Data_Temp.txt","a+");
    //Error handling for fopen
    if (fd1 == NULL || fd2 == NULL) 
    {
        printf("Student_Data.txt, Student_Data_Temp.txt: failed to open file");
        perror("Student_Data.txt, Student_Data_Temp.txt : \n");
        printf("The error number is: %d\n",errno);
        exit(1);
    }


    //Get the index of the student as a user input
    printf("Enter full student index number to delete (Format: EG/2018/xxxx): ");
    scanf("%s", student_index);

    while (1)
    {
        //Read student data from "Student_Data.txt"
        fread(&student, sizeof(student_marks), 1, fd1);
        if (feof(fd1))
        {
            break;
        }
        if ((err_No = ferror(fd1)) > 0)
        {
            printf("Student_Data.txt: Failed to read from the file");
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
                
                //Error handing for fwrite
                if (written < 0) 
                {
                    printf("Student_Data_Temp.txt: Failed to write to file");
                    perror("fwrite Error: ");
                    printf("The error number is: %d\n",errno);
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
    //Closing file descriptors
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

//Function for updating a student record
void updateStd()
{
    FILE *fd;
    student_marks student;
    int err_No;
    char student_index[20];

    //Get the index of the student as a user input
    printf("Enter student full index number to update (Format: EG/2018/xxxx): ");
    scanf("%s", student_index); 


    //Open "Student_Data.txt" file with "r+" permissions
    fd = fopen("Student_Data.txt", "r+");
    if (fd == NULL) //Error handling for fopen
    {
        printf("Student_Data.txt: could not be opened");
        perror("Student_Data.txt: \n");
        printf("The error number is: %d\n",errno);
    }

    while (1)
    {
        //Read a single data record from "Student_Data.txt" file 
        fread(&student, sizeof(student_marks), 1, fd);
        if (feof(fd))
        {
            printf("Could not be updated\n");
            break;
        }
        if ((err_No = ferror(fd)) > 0)//Error handling
        {
            printf("Failed to read from the file");
            perror("Student_Data.txt: \n");
            printf("The error number is: %d\n",errno);
            exit(1);
        }
        else
        {
            //Search for the relevant student index
            if(strcmp(student.student_index,student_index) == 0)
            {
                
                fseek(fd,-sizeof(student_marks),SEEK_CUR);

                //Get the new student data as a user input
                printf("Enter new assignment 01 marks (Out of 15%%): ");
                scanf("%f", &student.assignmt01_marks);
                printf("Enter new assignment 02 marks (Out of 15%%): ");
                scanf("%f", &student.assignmt02_marks);
                printf("Enter new project marks (Out of 20%%): ");
                scanf("%f", &student.project_marks);
                printf("Enter new finals marks (Out of 50%%): ");
                scanf("%f", &student.finalExam_marks);

                // write to the file
                int written = fwrite(&student, sizeof(student_marks), 1, fd); 

                // Error handling for write
                if (written < 0) 
                {
                    printf("Student_Data.txt: failed to write to the file");
                    perror("Student_Data.txt: \n");
                    printf("The error number is: %d\n",errno);
                    exit(1);
                }
                printf("\nStudent record updated successfully\n");
                break;

            }
        }
    }
    printf("\n");
    fclose(fd); //Close the file descriptor
}