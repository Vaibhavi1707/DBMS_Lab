#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>

#include "pds.h"
#include "bst.h"

struct PDS_RepoInfo repo_handle;


int pds_create(char *repo_name)
{
// open file 
//handle file error
//close file
//return PDS_SUCCESS
}


int pds_open(char* repo_name, int rec_size)
{
// Open the data file and index file in rb+ mode
// Update the fields of PDS_RepoInfo appropriately
// Build BST and store in pds_bst by reading index entries from the index file
// Close only the index file
}

int pds_load_ndx()
{
// Internal function used by pds_open to read index entries into BST
}

int put_rec_by_key(int key, void*rec)
{
  // Seek to the end of the data file
// Create an index entry with the current data file location using ftell
// Add index entry to BST using offset returned by ftell
// Write the key at the current data file location
// Write the record after writing the key
}

int get_rec_by_key(int key, void*rec)
{
  // Search for index entry in BST
// Seek to the file location based on offset in index entry
// Read the key at the current file location 
// Read the record after reading the key
}



int pds_close()
{
// Open the index file in wb mode (write mode, not append mode)
// Unload the BST into the index file by traversing it in PRE-ORDER (overwrite the entire index file)
// Free the BST by calling bst_destroy()
// Close the index file and data file

}
