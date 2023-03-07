#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include "libsys.h"

// Define the global variable of libsys
struct LibsysInfo repo_handle;

//--------------------------------create()---------------------------------
int libsys_create(char *book_name, char *stud_name, char *issue_name)
{
    char *dataFileBook = (char *)malloc((strlen(book_name) + 4) * sizeof(char));
    char *dataFileStud = (char *)malloc((strlen(stud_name) + 4) * sizeof(char));
    char *dataFileIssue = (char *)malloc((strlen(issue_name) + 4) * sizeof(char));
    char *indexFileBook = (char *)malloc((strlen(book_name) + 4) * sizeof(char));
    char *indexFileStud = (char *)malloc((strlen(stud_name) + 4) * sizeof(char));

    strcpy(dataFileBook, book_name);
    strcpy(dataFileStud, stud_name);
    strcpy(dataFileIssue, issue_name);
    strcpy(indexFileBook, book_name);
    strcpy(indexFileBook, stud_name);

    strcat(dataFileBook, ".dat");
    strcat(dataFileStud, ".dat");
    strcat(dataFileIssue, ".dat");
    strcat(indexFileBook, ".ndx");
    strcat(indexFileStud, ".ndx");

    FILE *binary_dbfp = fopen(dataFileBook, "wb");
    FILE *binary_dsfp = fopen(dataFileStud, "wb");
    FILE *binary_difp = fopen(dataFileIssue, "wb");
    FILE *binary_ifp = fopen(indexFileBook, "wb");
    FILE *binary_ifp_stud = fopen(indexFileStud, "wb");

    if (binary_ifp == NULL || binary_dbfp == NULL || binary_dsfp == NULL || binary_difp == NULL || binary_ifp_stud == NULL)
    {
        return LIB_FILE_ERROR;
    }
    else
    {
        repo_handle.book_index_count = 0;
        int count = repo_handle.book_index_count;
        fwrite(&count, sizeof(count), 1, binary_ifp);
        repo_handle.student_index_count = 0;
        int count = repo_handle.student_index_count;
        fwrite(&count, sizeof(count), 1, binary_ifp_stud);
        fclose(binary_ifp);
        fclose(binary_ifp_stud);
        fclose(binary_dbfp);
        fclose(binary_dsfp);
        fclose(binary_difp);
        return LIB_SUCCESS;
    }
}
// create booksys file pointer to open a file in 'wb' mode
// handle file pointer error if value is NULL return appropriate error code referring to the error codes
// close file pointer

// create studsys file pointer to open a file in 'wb' mode
// handle file pointer error if value is NULL return appropriate error code referring to the error codes
// close file pointer

// create issuesys file pointer to open a file in 'wb' mode
// handle file pointer error if value is NULL return appropriate error code referring to the error codes
// close file pointer

// Open the index file in "wb" mode
// Initialize index file by store "0" to indicate there are zero entries in index file

// return success

//--------------------------------open()---------------------------------
int libsys_open(char *book_name, char *stud_name, char *issue_name)
{
    int status1 = 0, status2 = 0, status3 = 0;
    if (repo_handle.book_repo_status == LIB_REPO_OPEN && repo_handle.stud_repo_status == LIB_REPO_OPEN && repo_handle.issue_repo_status == LIB_REPO_OPEN)
    {
        return LIB_REPO_ALREADY_OPEN;
    }
    else
    {
        if (repo_handle.book_repo_status != LIB_REPO_OPEN)
            status1 = booksys_open(book_name);
        if (repo_handle.stud_repo_status != LIB_REPO_OPEN)
            status2 = studsys_open(stud_name);
        if (repo_handle.issue_repo_status != LIB_REPO_OPEN)
            status3 = issuesys_open(issue_name);
        if (status1 == 1 || status2 == 1 || status3 == 1)
            return LIB_FILE_ERROR;
    }
    char *indexFileBook = (char *)malloc((strlen(book_name) + 4) * sizeof(char));
    strcpy(indexFileBook, book_name);
    strcat(indexFileBook, ".ndx");
    repo_handle.book_libsys_ndx_fp = fopen(indexFileBook, "rb+");
    if (!repo_handle.book_libsys_ndx_fp)
    {
        return LIB_FILE_ERROR;
    }
    else
    {
        int count;
        fseek(repo_handle.book_libsys_ndx_fp, 0, SEEK_SET);
        fread(&count, sizeof(int), 1, repo_handle.book_libsys_ndx_fp);
        fread(repo_handle.book_index_entries, sizeof(struct LIB_NdxInfo), count, repo_handle.book_libsys_ndx_fp);
        fclose(repo_handle.book_libsys_ndx_fp);
        return LIB_SUCCESS;
    }

    char *indexFileStudent = (char *)malloc((strlen(stud_name) + 4) * sizeof(char));
    strcpy(indexFileStudent, stud_name);
    strcat(indexFileStudent, ".ndx");
    repo_handle.student_libsys_ndx_fp = fopen(indexFileStudent, "rb+");
    if (!repo_handle.student_libsys_ndx_fp)
    {
        return LIB_FILE_ERROR;
    }
    else
    {
        int count;
        fseek(repo_handle.student_libsys_ndx_fp, 0, SEEK_SET);
        fread(&count, sizeof(int), 1, repo_handle.student_libsys_ndx_fp);
        fread(repo_handle.student_index_entries, sizeof(struct Stud_NdxInfo), count, repo_handle.student_libsys_ndx_fp);
        fclose(repo_handle.student_libsys_ndx_fp);
        return LIB_SUCCESS;
    }
}
// call booksys_open()
// call studsys_open()
// call issuesys_open()

// Open the index file in rb+ mode
// Read number of index entries from index file
// Load book_index_entries array by reading index entries from the index file
// Close only the index file

// check status of above functions
//  if all of them return success then return SUCCESS else return ERROR

int booksys_open(char *repo_name)
{
    char *dataFileBook = (char *)malloc((strlen(repo_name) + 4) * sizeof(char));
    strcpy(dataFileBook, repo_name);
    strcat(dataFileBook, ".dat");
    repo_handle.booksys_data_fp = fopen(dataFileBook, "rb+");
    if (!repo_handle.booksys_data_fp)
    {
        return LIB_FILE_ERROR;
    }
    else
    {
        strcpy(repo_handle.booksys_name, repo_name);
        repo_handle.book_repo_status = LIB_REPO_OPEN;
        return LIB_SUCCESS;
    }
}
// 1. assign repo handle a file pointer by opening file in 'rb+' mode
// 2. handle file pointer error if value is NULL return appropriate error code referring to the error codes in libsys.h
// 3. assign values (repo_name) to booksys_repo_handle
// 4. assign value to repo_handle.book_repo_status=LIB_REPO_OPEN;
// 5. return booksys_success

int issuesys_open(char *repo_name)
{
    char *dataFileIssue = (char *)malloc((strlen(repo_name) + 4) * sizeof(char));
    strcpy(dataFileIssue, repo_name);
    strcat(dataFileIssue, ".dat");
    repo_handle.issuesys_data_fp = fopen(dataFileIssue, "rb+");
    if (!repo_handle.issuesys_data_fp)
    {
        return LIB_FILE_ERROR;
    }
    else
    {
        strcpy(repo_handle.issuesys_name, repo_name);
        repo_handle.issue_repo_status = LIB_REPO_OPEN;
        return LIB_SUCCESS;
    }
}
// 1. assign repo handle a file pointer by opening file in 'rb+' mode
// 2. handle file pointer error if value is NULL return appropriate error code referring to the error codes in libsys.h
// 3. assign values (repo_name) to issuesys_repo_handle
// 4. assign value to repo_handle.issue_repo_status=LIB_REPO_OPEN;
// 5. return issuesys_success

int studsys_open(char *repo_name)
{
    char *dataFileStud = (char *)malloc((strlen(repo_name) + 4) * sizeof(char));
    strcpy(dataFileStud, repo_name);
    strcat(dataFileStud, ".dat");
    repo_handle.studsys_data_fp = fopen(dataFileStud, "rb+");
    if (!repo_handle.studsys_data_fp)
    {
        return LIB_FILE_ERROR;
    }
    else
    {
        strcpy(repo_handle.studsys_name, repo_name);
        repo_handle.stud_repo_status = LIB_REPO_OPEN;
        return LIB_SUCCESS;
    }
}
// 1. assign repo handle a file pointer by opening file in 'rb+' mode
// 2. handle file pointer error if value is NULL return appropriate error code referring to the error codes
// 3. assign values (repo_name) to studsys_repo_handle
// 4. assign value to repo_handle.stud_repo_status=LIB_REPO_OPEN;
// 5. return studsys_success

//------------------------------book:NO change ----------------------------
int get_book_by_isbn(int key, struct Book *rec)
{
    if (repo_handle.book_repo_status != LIB_REPO_OPEN)
        return LIB_REPO_NOT_OPEN;
    for (int i = 0; i < repo_handle.book_index_count; i++)
    {
        if (repo_handle.book_index_entries[i].key == key)
        {
            if (repo_handle.book_index_entries[i].flag == RECORD_PRESENT)
            {
                fseek(repo_handle.booksys_data_fp, repo_handle.book_index_entries[i].offset, SEEK_SET);
                fread(&key, sizeof(key), 1, repo_handle.booksys_data_fp);
                fread(rec, sizeof(*rec), 1, repo_handle.booksys_data_fp);

                fseek(repo_handle.issuesys_data_fp, 0, SEEK_SET);
                struct Issue issue;
                int flag = 0;
                while (fread(&issue, sizeof(struct Issue), 1, repo_handle.issuesys_data_fp))
                {
                    if (issue.isbn == rec->isbn)
                    {
                        flag = 1;
                        printf("Book is Issued by - \n");
                        struct Student stud;
                        get_student_by_rollno(issue.rollno, &stud);
                        printf("Name : %s\n", stud.name);
                        printf("Address : %s\n", stud.address);
                        printf("Roll Number: %d\n", stud.rollno);
                        break;
                    }
                }
                if (flag == 0)
                    printf("Book Not Issued\n");

                return LIB_SUCCESS;
            }
            else
                return LIB_REC_NOT_FOUND;
        }
    }
    return LIB_REC_NOT_FOUND;
}
int get_book_by_title(char *title, struct Book *rec)
{
    if (repo_handle.book_repo_status != LIB_REPO_OPEN)
        return LIB_REPO_NOT_OPEN;
    for (int i = 0; i < repo_handle.book_index_count; i++)
    {
        if (repo_handle.book_index_entries[i].title == title)
        {
            if (repo_handle.book_index_entries[i].flag == RECORD_PRESENT)
            {
                fseek(repo_handle.booksys_data_fp, repo_handle.book_index_entries[i].offset, SEEK_SET);
                int key;
                fread(&key, sizeof(key), 1, repo_handle.booksys_data_fp);
                fread(rec, sizeof(*rec), 1, repo_handle.booksys_data_fp);
                
                fseek(repo_handle.issuesys_data_fp, 0, SEEK_SET);
                struct Issue issue;
                int flag = 0;
                while (fread(&issue, sizeof(struct Issue), 1, repo_handle.issuesys_data_fp))
                {
                    if (issue.isbn == rec->isbn)
                    {
                        flag = 1;
                        printf("Book is Issued by - \n");
                        struct Student stud;
                        get_student_by_rollno(issue.rollno, &stud);
                        printf("Name : %s\n", stud.name);
                        printf("Address : %s\n", stud.address);
                        printf("Roll Number: %d\n", stud.rollno);
                        break;
                    }
                }
                if (flag == 0)
                    printf("Book Not Issued\n");

                return LIB_SUCCESS;
            }
            else
                return LIB_REC_NOT_FOUND;
        }
    }
    return LIB_REC_NOT_FOUND;
}
// get_rec_by_key
// check repo status
// Search for index entry in book_index_entries array
//-----use flag to read valid entries
// Seek to the file location based on offset in index entry
// Read the key at the current file location
// Read the record after reading the key

int put_book_by_isbn(int key, struct Book *rec)
{
    if (repo_handle.book_repo_status != LIB_REPO_OPEN)
        return LIB_REPO_NOT_OPEN;
    for (int i = 0; i < repo_handle.book_index_count; i++)
    {
        if (repo_handle.book_index_entries[i].key == key)
        {
            if (repo_handle.book_index_entries[i].flag == RECORD_PRESENT)
            {
                return BOOK_FAILURE;
            }
            else
            {
                fseek(repo_handle.booksys_data_fp, repo_handle.book_index_entries[i].offset, SEEK_SET);
                if (fwrite(&key, sizeof(key), 1, repo_handle.booksys_data_fp) != 1 || fwrite(rec, sizeof(*rec), 1, repo_handle.booksys_data_fp) != 1)
                    return LIB_ADD_FAILED;
                repo_handle.book_index_entries[i].flag = RECORD_PRESENT;
                return LIB_SUCCESS;
            }
        }
    }
    fseek(repo_handle.booksys_data_fp, 0, SEEK_END);
    int byteOffset = (int)ftell(repo_handle.booksys_data_fp);
    repo_handle.book_index_entries[repo_handle.book_index_count].offset = byteOffset;
    repo_handle.book_index_entries[repo_handle.book_index_count].key = key;
    strcpy(repo_handle.book_index_entries[repo_handle.book_index_count].title, rec->title);
    repo_handle.book_index_entries[repo_handle.book_index_count].flag = RECORD_PRESENT;
    if (fwrite(&key, sizeof(key), 1, repo_handle.booksys_data_fp) != 1 || fwrite(rec, sizeof(*rec), 1, repo_handle.booksys_data_fp) != 1)
        return LIB_ADD_FAILED;
    repo_handle.book_index_count++;
    return LIB_SUCCESS;
}
//-----check index file for key
//-----if key already present check for flag [flag=1 : entry is valid]
//-----if key is present but flag is 0 then just add entry at same index i.e update only offset and update flag; return status
//-----if key is present but flag is 1 return failure as data is already present
//-----if key is not prsent then proceed with following steps:

// Seek to the end of the data file
// Create an index entry with the current data file location using ftell
// Add index entry to array using offset returned by ftell
// Write the key at the current data file location
// Write the record after writing the key
// return status

int delete_book_by_isbn(int key)
{
    if (repo_handle.book_repo_status != LIB_REPO_OPEN)
        return LIB_REPO_NOT_OPEN;
    for (int i = 0; i < repo_handle.book_index_count; i++)
    {
        if (key == repo_handle.book_index_entries[i].key)
        {
            if (repo_handle.book_index_entries[i].flag == RECORD_PRESENT)
            {
                fseek(repo_handle.issuesys_data_fp, 0, SEEK_SET);
				struct Issue issue;
				while (fread(&issue, sizeof(issue), 1, repo_handle.issuesys_data_fp))
				{
					if (issue.isbn == key)
					{
						return BOOK_FAILURE; // Cannot be deleted.
					}
				}
                repo_handle.book_index_entries[i].flag = RECORD_DELETED;
                return LIB_SUCCESS;
            }
            else
            {
                return LIB_REC_NOT_FOUND;
            }
        }
    }
    return LIB_REC_NOT_FOUND;
}
//-----delete_rec_by_key
//-----check repo status
//-----Search for index entry in book_index_entries array
//-----if key matches and flag is 1 then reset flag
//-----if key matches but flag is already reset return status
//-----if key doesn't match then return status

//-----------------------------student: additional code---------------------------
int put_student_by_rollno(int rollno_to_write, struct Student *rec)
{
    if (repo_handle.stud_repo_status != LIB_REPO_OPEN)
        return LIB_REPO_NOT_OPEN;
    for (int i = 0; i < repo_handle.student_index_count; i++)
    {
        if (repo_handle.student_index_entries[i].key == rollno_to_write)
        {
            if (repo_handle.student_index_entries[i].flag == RECORD_PRESENT)
            {
                return BOOK_FAILURE;
            }
            else
            {
                fseek(repo_handle.studsys_data_fp, repo_handle.student_index_entries[i].offset, SEEK_SET);
                if (fwrite(&rollno_to_write, sizeof(int), 1, repo_handle.studsys_data_fp) != 1 || fwrite(rec, sizeof(*rec), 1, repo_handle.studsys_data_fp) != 1)
                    return LIB_ADD_FAILED;
                repo_handle.student_index_entries[i].flag = RECORD_PRESENT;
                return LIB_SUCCESS;
            }
        }
    }
    fseek(repo_handle.studsys_data_fp, 0, SEEK_END);
    int byteOffset = (int)ftell(repo_handle.booksys_data_fp);
    repo_handle.student_index_entries[repo_handle.student_index_count].offset = byteOffset;
    repo_handle.student_index_entries[repo_handle.student_index_count].key = rollno_to_write;
    strcpy(repo_handle.student_index_entries[repo_handle.student_index_count].name, rec->name);
    repo_handle.student_index_entries[repo_handle.student_index_count].flag = RECORD_PRESENT;
    if (fwrite(&rollno_to_write, sizeof(int), 1, repo_handle.studsys_data_fp) != 1 || fwrite(rec, sizeof(*rec), 1, repo_handle.studsys_data_fp) != 1)
        return LIB_ADD_FAILED;
    repo_handle.student_index_count++;
    return LIB_SUCCESS;
}
// 1. check if repo status is closed then return return appropriate error code referring to the error codes
// 2. else continue with following action sequence
// 3. set the file pointer to end
// 4. write rollno_to_write
// 5. write Student record
// 6. if both actions are successful then return studsys_success
// 7. else return studsys_add_failed

int get_student_by_rollno(int rollno_to_read, struct Student *rec)
{
    if (repo_handle.stud_repo_status != LIB_REPO_OPEN)
        return LIB_REPO_NOT_OPEN;
    for (int i = 0; i < repo_handle.student_index_count; i++)
    {
        if (repo_handle.student_index_entries[i].key == rollno_to_read)
        {
            if (repo_handle.student_index_entries[i].flag == RECORD_PRESENT)
            {
                fseek(repo_handle.studsys_data_fp, repo_handle.student_index_entries[i].offset, SEEK_SET);
                fread(&rollno_to_read, sizeof(int), 1, repo_handle.studsys_data_fp);
                fread(rec, sizeof(*rec), 1, repo_handle.studsys_data_fp);
                return LIB_SUCCESS;
            }
            else
                return LIB_REC_NOT_FOUND;
        }
    }
    return LIB_REC_NOT_FOUND;
}
int get_student_by_name(char *name, struct Student *rec)
{
    if (repo_handle.stud_repo_status != LIB_REPO_OPEN)
        return LIB_REPO_NOT_OPEN;
    for (int i = 0; i < repo_handle.student_index_count; i++)
    {
        if (repo_handle.student_index_entries[i].name == name)
        {
            if (repo_handle.student_index_entries[i].flag == RECORD_PRESENT)
            {
                fseek(repo_handle.studsys_data_fp, repo_handle.student_index_entries[i].offset, SEEK_SET);
                int rollno;
                fread(&rollno, sizeof(int), 1, repo_handle.studsys_data_fp);
                fread(rec, sizeof(*rec), 1, repo_handle.studsys_data_fp);
                return LIB_SUCCESS;
            }
            else
                return LIB_REC_NOT_FOUND;
        }
    }
    return LIB_REC_NOT_FOUND;
}
// 1. check if repo status is closed then  return appropriate error code referring to the error codes
// 2. else continue with following action sequence
// 3.1 read rollno
// 3.2 check if rollno is equal to the rollno_to_read
// 3.3 if yes then read entire record of a Student and return studsys_success
// 3.4 else skip the record and read next rollno of the Student
// 4. Repeat step 3.1 to 3.4 till end of file
// 5. Return record not found : appropriate error code referring to the error codes

int delete_student_by_rollno(int rollno)
{
    if (repo_handle.stud_repo_status != LIB_REPO_OPEN)
        return LIB_REPO_NOT_OPEN;
    for (int i = 0; i < repo_handle.student_index_count; i++)
    {
        if (rollno == repo_handle.student_index_entries[i].key)
        {
            if (repo_handle.student_index_entries[i].flag == RECORD_PRESENT)
            {
                repo_handle.student_index_entries[i].flag = RECORD_DELETED;
                return LIB_SUCCESS;
            }
            else
            {
                return LIB_REC_NOT_FOUND;
            }
        }
    }
    return LIB_REC_NOT_FOUND;
}

//--------------------------------issue()---------------------------------
int issue(int rollno, int isbn)
{
    if (repo_handle.stud_repo_status != LIB_REPO_OPEN || repo_handle.book_repo_status != LIB_REPO_OPEN || repo_handle.issue_repo_status != LIB_REPO_OPEN)
        return LIB_REPO_NOT_OPEN;
    struct Student student;
    struct Book book;
    int status1 = get_book_by_isbn(isbn, &book);
    int status2 = get_student_by_rollno(rollno, &student);
    if (status1 == 0 && status2 == 0)
    {
        struct Issue issue;
        issue.rollno = rollno;
        issue.isbn = isbn;
        fseek(repo_handle.issuesys_data_fp, 0, SEEK_END);
        if (fwrite(&issue, sizeof(struct Issue), 1, repo_handle.issuesys_data_fp) == 1)
            return LIB_SUCCESS;
        else
            return LIB_ADD_FAILED;
    }
    else
    {
        return LIB_ADD_FAILED;
    }
}
// check if book repo status is closed then return return appropriate error code referring to the error codes
// else continue with following action sequence
// check if student repo status is closed then return return appropriate error code referring to the error codes
// else continue with following action sequence
// check if issue repo status is closed then return return appropriate error code referring to the error codes
// else continue with following action sequence

// declare student and book variables

// get book by isbn and store status in status1
// get student by rollno and store status in status2

// if status1 and status2 are successful then continue with following action sequence else return error

// create Issue object and assign rollno and isbn
// set the file pointer to end
// write issue record

// if both actions are successful then return success
// else return failed

//----------------------------------close()---------------------------------
int libsys_close()
{
    int status1 = booksys_close();
    int status2 = studsys_close();
    int status3 = issuesys_close();
    if (status1 == 0 && status2 == 0 && status3 == 0)
        return LIB_SUCCESS;
    else
    {
        return LIB_REPO_NOT_OPEN;
    }

    char *Book_IndexFile = (char *)malloc((strlen(repo_handle.booksys_name) + 4) * sizeof(char));
    strcpy(Book_IndexFile, repo_handle.booksys_name);
    strcat(Book_IndexFile, ".ndx");
    repo_handle.book_libsys_ndx_fp = fopen(Book_IndexFile, "wb");

    int count = repo_handle.book_index_count;
    fseek(repo_handle.book_libsys_ndx_fp, 0, SEEK_SET);
    fwrite(&count, sizeof(count), 1, repo_handle.book_libsys_ndx_fp);
    fwrite(repo_handle.book_index_entries, sizeof(struct LIB_NdxInfo), repo_handle.book_index_count, repo_handle.book_libsys_ndx_fp);
    fclose(repo_handle.book_libsys_ndx_fp);
    

    char *Student_IndexFile = (char *)malloc((strlen(repo_handle.studsys_name) + 4) * sizeof(char));
    strcpy(Student_IndexFile, repo_handle.studsys_name);
    strcat(Student_IndexFile, ".ndx");
    repo_handle.student_libsys_ndx_fp = fopen(Student_IndexFile, "wb");

    int count = repo_handle.student_index_count;
    fseek(repo_handle.student_libsys_ndx_fp, 0, SEEK_SET);
    fwrite(&count, sizeof(count), 1, repo_handle.student_libsys_ndx_fp);
    fwrite(repo_handle.student_index_entries, sizeof(struct Stud_NdxInfo), repo_handle.student_index_count, repo_handle.student_libsys_ndx_fp);
    fclose(repo_handle.student_libsys_ndx_fp);
}
// call booksys_close()
// call studsys_close()
// call issuesys_close()

// Open the index file in wb mode (write mode, not append mode)
// Write number of index entries at the beginning of index file
// Unload the index array into the index file (overwrite the entire index file)
// Close the index file and data file

// check status of above functions
//  if all of them return success then return SUCCESS else return ERROR

int booksys_close()
{
    if (repo_handle.book_repo_status != LIB_REPO_OPEN)
        return LIB_REPO_NOT_OPEN;
    fclose(repo_handle.booksys_data_fp);
    strcpy(repo_handle.booksys_name, "");
    repo_handle.book_repo_status == LIB_REPO_CLOSED;
    return LIB_SUCCESS;
}
// 1. check if repo status is closed then  return appropriate error code referring to the error codes in libsys.h
// 2. else continue with following action sequence
// 3. close file pointer
// 4. set booksys_name as ""
// 5. set book_repo_status=LIB_REPO_CLOSED
// 6. return LIB_SUCCESS;

int studsys_close()
{
    if (repo_handle.stud_repo_status != LIB_REPO_OPEN)
        return LIB_REPO_NOT_OPEN;
    fclose(repo_handle.studsys_data_fp);
    strcpy(repo_handle.studsys_name, "");
    repo_handle.stud_repo_status == LIB_REPO_CLOSED;
    return LIB_SUCCESS;
}

// 1. check if repo status is closed then  return appropriate error code referring to the error codes
// 2. else continue with following action sequence
// 3. close file pointer
// 4. set studsys_name as ""
// 5. set stud_repo_status=LIB_REPO_CLOSED
// 6. return LIB_SUCCESS;

int issuesys_close()
{
    if (repo_handle.issue_repo_status != LIB_REPO_OPEN)
        return LIB_REPO_NOT_OPEN;
    fclose(repo_handle.issuesys_data_fp);
    strcpy(repo_handle.issuesys_name, "");
    repo_handle.issue_repo_status == LIB_REPO_CLOSED;
    return LIB_SUCCESS;
}

// 1. check if repo status is closed then  return appropriate error code referring to the error codes
// 2. else continue with following action sequence
// 3. close file pointer
// 4. set issuesys_name as ""
// 5. set issue_repo_status=LIB_REPO_CLOSED
// 6. return LIB_SUCCESS;