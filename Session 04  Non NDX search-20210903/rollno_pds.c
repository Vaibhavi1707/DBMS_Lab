#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>

#include "pds.h"
#include "bst.h"

struct PDS_RepoInfo repo_handle;


int pds_create(char *repo_name) // Small changes to accomodate running test cases again
{
  char filename[30], indexfile[30];
  strcpy(filename,repo_name);
  strcpy(indexfile,repo_name);
  strcat(filename,".dat");
  strcat(indexfile,".ndx");
  FILE *fp = fopen(filename,"wb+");
  FILE *ifp = fopen(indexfile,"wb+");
  if(fp  == NULL || ifp == NULL) return PDS_FILE_ERROR;\
  fclose(fp);
  fclose(ifp);
  
  return PDS_SUCCESS;
}


int pds_open(char* repo_name, int rec_size) // Same as before
{
// Open the data file and index file in rb+ mode
// Update the fields of PDS_RepoInfo appropriately
// Build BST and store in pds_bst by reading index entries from the index file
// Close only the index file
}

int pds_load_ndx() // Same as before
{
// Internal function used by pds_open to read index entries into BST
}

int put_rec_by_key(int key, void*rec) // Same as before
{
  // Seek to the end of the data file
// Create an index entry with the current data file location using ftell
// Add index entry to BST using offset returned by ftell
// Write the key at the current data file location
// Write the record after writing the key
}

int get_rec_by_ndx_key(int key, void*rec) // Only Function Rename 
{
  // Search for index entry in BST
// Seek to the file location based on offset in index entry
// Read the key at the current file location 
// Read the record after reading the key
}



int pds_close() // Same as before
{
// Open the index file in wb mode (write mode, not append mode)
// Unload the BST into the index file by traversing it in PRE-ORDER (overwrite the entire index file)
// Free the BST by calling bst_destroy()
// Close the index file and data file

}

int get_rec_by_non_ndx_key(void *key, void *rec, int (*matcher)(void *rec, void *key), int *io_count)
{
  // Seek to beginning of file
  // Perform a table scan - iterate over all the records
  //   Read the key and the record
  //   Increment io_count by 1 to reflect count no. of records read
  //   Use the function in function pointer to compare the record with required key
  // Return success when record is found
}