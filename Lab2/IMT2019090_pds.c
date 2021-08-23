#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>

#include "pds.h"

// Define the global variable
struct PDS_RepoInfo repo_handle;

/**
 * Creates a new file to store data
 * @arg repo_name Name of file where data is stored.
 * @return status 0 if successful, 1 if file open failed. 
 */
int pds_create(char *repo_name)
{
    FILE *pdsData = fopen(repo_name, "w+"); 
    if (!pdsData) 
        return PDS_FILE_ERROR;
    fclose(pdsData);
    return PDS_SUCCESS;
}

/**
 * Opens the file where data is stored
 * @arg repo_name Name of the file where data is stored
 * @arg rec_size Total storage size of the data entity stored
 * @return status 0 if successful, 1 if file open failed
 */
int pds_open( char *repo_name, int rec_size )
{
    // open file and store pointer to repo_handle
    repo_handle.pds_data_fp = fopen(repo_name, "a+");
    
    // handle file pointer error
    if (!repo_handle.pds_data_fp) 
        return PDS_FILE_ERROR;
    if (repo_handle.repo_status == PDS_REPO_ALREADY_OPEN)
        return PDS_SUCCESS;

    // if successful update pds_name
    strcpy(repo_handle.pds_name, repo_name);
    
    // update repo_status
    repo_handle.repo_status = PDS_REPO_OPEN;
    
    // update rec_size
    repo_handle.rec_size = rec_size;
    
    return PDS_SUCCESS;
}

/**
 * Stores a record with it's key in the file
 * @arg key Index of the record
 * @arg rec Record to be stored
 * @return status 0 if successful, 11 if repo closed, 2 if addition to the file failed
 */
int put_rec_by_key( int key, void *rec )
{
    // check repo_status
    if (repo_handle.repo_status == PDS_REPO_CLOSED)
        return PDS_REPO_CLOSED;
    if (repo_handle.repo_status == PDS_REPO_OPEN)
        repo_handle.repo_status = PDS_REPO_ALREADY_OPEN;
    
    // set file pointer towards end of file
    fseek(repo_handle.pds_data_fp, 0, SEEK_END);
    
    // write key to file
    int status_key_write = fwrite(&key, sizeof(int), 1, repo_handle.pds_data_fp);
    
    // write record to file
    int status_rec_write = fwrite(rec, repo_handle.rec_size, 1, repo_handle.pds_data_fp);
    
    // if write is successful return PDS_SUCCESS 
    if (status_key_write == 0 && status_rec_write == 0) 
        return PDS_ADD_FAILED;
    
    // Else return error status accordingly
    return PDS_SUCCESS;
}

/**
 * Linearly searches a record according to an index (key) passed
 * @arg key Index of the record to be searched
 * @arg rec The record, if found, is stored in this pointer
 * @return status 0 if record is found else returns 3. Returns 11 if PDS repo is closed
 */
int get_rec_by_key( int key, void *rec )
{

    // check repo status
    if (repo_handle.repo_status == PDS_REPO_CLOSED) {
        return PDS_REPO_CLOSED;
    }

    // read file from begining
    fseek(repo_handle.pds_data_fp, 0, SEEK_SET);
    while (!feof(repo_handle.pds_data_fp)) {
        // read key
        int stored_key;
        fread(&stored_key, sizeof(int), 1, repo_handle.pds_data_fp);
        
        // compare key 
        // if key is found read the record into rec
        if (stored_key == key) {
            fread(rec, repo_handle.rec_size, 1, repo_handle.pds_data_fp);

            // return success
            return PDS_SUCCESS;
        } 
    }
    // else return error
    return PDS_REC_NOT_FOUND;
}

/**
 * Close the pds repo and file 
 * @return 0 if successful. Returns 11 if already closed.
 */
int pds_close()
{

    // check repo status
    if (repo_handle.repo_status == PDS_REPO_CLOSED)
        return PDS_REPO_CLOSED;

    // close file
    fclose(repo_handle.pds_data_fp);

    // reset repo_handle name
    strcpy(repo_handle.pds_name, "");
    
    // update repo_status
    repo_handle.repo_status = PDS_REPO_CLOSED;
    
    return PDS_SUCCESS;
}

