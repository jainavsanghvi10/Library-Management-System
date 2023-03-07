#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>
#include"libsys.h"

//Your code must support menu-driven functionality.
//Function calls rollno_libsys.h

int main()
{
    int status, choice;
    char temp;
    char *stud_repo_name, *book_repo_name, *issue_repo_name;
    stud_repo_name = "Student_Menu"; book_repo_name = "Book_Menu"; issue_repo_name = "Issue_Menu";
    status = libsys_create(book_repo_name, stud_repo_name, issue_repo_name);
    if(status != LIB_SUCCESS)
    {
        printf("Could not create Library Management System database. Please try again.\n");
        return -1;
    }

    status = libsys_open(book_repo_name, stud_repo_name, issue_repo_name);
    if(status != LIB_SUCCESS)
    {
        printf("Database opening failed\n");
        return -1;
    }

    do
    {
        printf("\nMENU: \n");
        printf(" 1.Add book\n 2.Add student\n 3.Delete Book\n 4.Delete Student\n 5.Issue Book\n 6.Search Book by isbn\n 7.Search Book by title\n 8.Search student by rollno\n 9.Search student by name\n 10.Exit\n");
        printf("Please enter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
            {
                struct Book *record = (struct Book *)malloc(sizeof(struct Book));
                printf("\nEnter isbn of the book: ");
                scanf("%d", &record->isbn);
                printf("Enter Title of the Book: ");
                scanf("%c", &temp);
                scanf("%[^\n]",record->title);
                printf("Enter Author of the book: ");
                scanf("%c", &temp);
                scanf("%[^\n]",record->author);
                printf("Enter Price of the Book: ");
                scanf("%c", &temp);
                scanf("%f",&record->price);
                status = put_book_by_isbn(record->isbn, record);
                if (status == LIB_SUCCESS)
                    printf("Book added successfully\n");
                else if (status == LIB_ADD_FAILED)
                    printf("Failed to Add the Book\n");
                break;
            }

            case 2:
            {
                struct Student *record = (struct Student*)malloc(sizeof(struct Student));
                printf("Enter Roll no. of the student: ");
                scanf("%d", &record->rollno);
                printf("Enter Name of the student: ");
                 scanf("%c", &temp);
                scanf("%[^\n]s", record->name);
                printf("Enter Address of the student: ");
                 scanf("%c", &temp);
                scanf("%[^\n]s", record->address);
                printf("Enter CGPA of the student: ");
                scanf("%f", &record->cgpa);
                status = put_student_by_rollno(record->rollno, record);
                if (status == LIB_SUCCESS)
                    printf("Book added successfully\n");
                else if (status == LIB_ADD_FAILED)
                    printf("Failed to Add the Book\n");
                break;
            }

            case 3:
            {
                int isbn;
                printf("Enter ISBN of Book: ");
                scanf("%d", &isbn);
                status = delete_book_by_isbn(isbn);
                if(status == LIB_SUCCESS)
                    printf("Book Deleted: SUCCESS\n");
                else if(status == LIB_REC_NOT_FOUND){
                    printf("Book Deleted: FAILED\n");
                    printf("No such Book exists.\n");
                }
                else if(status ==  LIB_FILE_ERROR){
                    printf("Book Deleted: FAILED\n");
                    printf("Some Error Occured, Please try again.\n");
                }
                break;
            }

            case 4:
            {
                int roll_no;
                printf("Enter Roll No. of Student: ");
                scanf("%d", &roll_no);
                status = delete_student_by_rollno(roll_no);
                if(status == LIB_SUCCESS)
                    printf("Student Deleted Successfully.\n");
                else if(status == LIB_REC_NOT_FOUND)
                    printf("No such student exists\n");
                else if(status == LIB_FILE_ERROR)
                    printf("Some Error Occured, Please try again.\n");
                break;
            }

            case 5:
            {
                int roll_no, isbn;
                printf("Enter Roll No. of Student: ");
                scanf("%d", &roll_no);
                printf("Enter ISBN of the Book: ");
                scanf("%d", &isbn);
                status = issue(roll_no, isbn);
                if(status ==  LIB_SUCCESS)
                    printf("Book Issue Successfull\n");
                else if(status == LIB_ADD_FAILED)
                    printf("Book Issue Failed\n");
                else if(status == LIB_FILE_ERROR)
                    printf("Some Error Occured, Please try again.\n");
                break;
            }

            case 6:
            {
                struct Book *record = (struct Book *)malloc(sizeof(struct Book));
                int isbn;
                printf("Enter the ISBN of the Book: ");
                scanf("%d", &isbn);
                status = get_book_by_isbn(isbn, record);
                if (status == LIB_REC_NOT_FOUND)
                    printf("No such Book exists.\n");
                else if(status == LIB_REPO_NOT_OPEN)
                    printf("Some Error Occured, Please try again.\n");
                else{
                    printf("Book Details\n");
					printf("Title : %s\n", record->title);
					printf("Author : %s\n", record->author);
					printf("Price : %f Rs\n", record->price);
					printf("Isbn: %d\n", record->isbn);
                }
                break;
            }

            case 7:
            {
                struct Book *record = (struct Book *)malloc(sizeof(struct Book));
                char title[40];
                printf("Enter the title of the Book: ");
                scanf("%c", &temp);
                scanf("%[^\n]s", title);
                status = get_book_by_title(title, record);
                if (status == LIB_REC_NOT_FOUND)
                    printf("No such Book exists.\n");
                else if(status == LIB_REPO_NOT_OPEN)
                    printf("Some Error Occured, Please try again.\n");
                else{
                    printf("Book Details\n");
					printf("Title : %s\n", record->title);
					printf("Author : %s\n", record->author);
					printf("Price : %f Rs\n", record->price);
					printf("Isbn: %d\n", record->isbn);
                }
                break;
            }

            case 8:
            {
                struct Student *record = (struct Student *)malloc(sizeof(struct Student));
                int roll_no;
                printf("Enter Student Roll no.: ");
                scanf("%d", &roll_no);
                status = get_student_by_rollno(roll_no, record);
                if(status = LIB_SUCCESS)
                    printf("Student roll no.: %d\n Student Name: %s\n, Student Address: %s\n Student CGPA: %f\n", record->rollno, record->name, record->address, record->cgpa);
                else if(status == LIB_REC_NOT_FOUND)
                    printf("No such student exists\n");
                else if(status == LIB_FILE_ERROR)
                    printf("Some Error Occured, Please try again.\n");
                break;
            }

            case 9:
            {
                struct Student *record = (struct Student *)malloc(sizeof(struct Student));
                char name[40];
                printf("Enter Student Name: ");
                scanf("%c", &temp);
                scanf("%[^\n]s", name);
                status = get_student_by_name(name , record);
                if(status = LIB_SUCCESS)
                    printf("Student roll no.: %d\n Student Name: %s\n, Student Address: %s\n Student CGPA: %f\n", record->rollno, record->name, record->address, record->cgpa);
                else if(status == LIB_REC_NOT_FOUND)
                    printf("No such student exists\n");
                else if(status == LIB_FILE_ERROR)
                    printf("Some Error Occured, Please try again.\n");
                break;
            }

            case 10:
            {
                exit(0);
                break;
            }
            
            default:
            {
                printf("Invalid Input\n");
                break;
            }

            if ((choice >= 1) && (choice <= 10))
            {
                printf("\nPress Enter to move to next operation\n");
                getchar();
                getchar();
            }
        }
    } while(choice <= 10);
}