#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>

#include "pds.h"
#include "bst.h"

struct PDS_RepoInfo repo_handle;


int pds_create(char *repo_name)
{
  FILE *pdsData = fopen(repo_name, "w+"); 
  if (!pdsData) 
      return PDS_FILE_ERROR;
  fclose(pdsData);
  return PDS_SUCCESS;
}


int pds_open(char* repo_name, int rec_size)
{
  // Open the data file and index file in rb+ mode
  FILE* dataFile = fopen(repo_name, "ab+");
  char indFileName[100];
  strcpy(indFileName, repo_name);
  strcat(indFileName, ".ind");
  FILE* ndxFile = fopen(indFileName, "wb+");
  // Update the fields of PDS_RepoInfo appropriately
  repo_handle.pds_data_fp = dataFile;
  repo_handle.pds_ndx_fp = ndxFile;
  strcpy(repo_handle.pds_name, repo_name);
  repo_handle.rec_size = rec_size;
  repo_handle.repo_status = PDS_REPO_OPEN;
  // Build BST and store in pds_bst by reading index entries from the index file
  pds_load_ndx();
  // Close only the index file
  fclose(ndxFile);
  return PDS_SUCCESS;
}

int pds_load_ndx()
{
  while (repo_handle.pds_bst && !feof(repo_handle.pds_ndx_fp)) {
    int key;
    fread(&key, sizeof(int), 1, repo_handle.pds_ndx_fp);
    int offset;
    fread(&offset, sizeof(int), 1, repo_handle.pds_ndx_fp);
    struct PDS_NdxInfo ndxInfo = { .key = key, .offset = offset };
    bst_add_node(&repo_handle.pds_bst, key, &ndxInfo);
  }

  return 0;
}

int put_rec_by_key(int key, void*rec)
{
  // check repo_status
    if (repo_handle.repo_status == PDS_REPO_CLOSED)
        return PDS_REPO_CLOSED;
    if (repo_handle.repo_status == PDS_REPO_OPEN)
        repo_handle.repo_status = PDS_REPO_ALREADY_OPEN;
    
    // set file pointer towards end of file
    fseek(repo_handle.pds_data_fp, 0, SEEK_END);
    
    // Create an index entry with the current data file location using ftell
    int offset = ftell(repo_handle.pds_data_fp);

    // Add index entry to BST using offset returned by ftell
    bst_add_node(&repo_handle.pds_bst, key, &offset);

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

int get_rec_by_key(int key, void*rec)
{
  // // Search for index entry in BST
  // struct BSTNode* found;
  // found = bst_search(&repo_handle.pds_bst, key);
  // // Seek to the file location based on offset in index entry
  // fseek(repo_handle.pds_data_fp, found->data->offset, SEEK_SET);
  // // Read the key at the current file location 
  // int stored_key;
  // fread(&stored_key, sizeof(int), 1, repo_handle.pds_data_fp);      
  // // Read the record after reading the key
  // fread(rec, repo_handle.rec_size, 1, repo_handle.pds_data_fp);
  // // return success
  // return PDS_SUCCESS;
}



int pds_close()
{
  // Open the index file in wb mode (write mode, not append mode)
  FILE* ndxFile = fopen(strcat(repo_handle.pds_name, "ndx"), "wb");
  // Unload the BST into the index file by traversing it in PRE-ORDER (overwrite the entire index file)
  // *TODO*
  // Free the BST by calling bst_destroy()
  bst_destroy(repo_handle.pds_bst);
  // Close the index file and data file
  fclose(ndxFile);
  fclose(repo_handle.pds_data_fp);
}
