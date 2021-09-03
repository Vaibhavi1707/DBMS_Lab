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
  if (repo_handle.repo_status == PDS_REPO_OPEN) return PDS_REPO_ALREADY_OPEN;
  // Open the data file and index file in rb+ mode
  char datFile[100];
  strcpy(datFile, repo_name);
  strcat(datFile, ".dat");
  FILE* dataFile = fopen(datFile, "r+b");
  if (!dataFile) return PDS_FILE_ERROR;

  char ndxFile[100];
  strcpy(ndxFile, repo_name);
  strcat(ndxFile, ".ndx");

  FILE* ndxFilePtr = fopen(ndxFile, "rb+");
  if (!ndxFilePtr) return PDS_FILE_ERROR;

  // Update the fields of PDS_RepoInfo appropriately
  repo_handle.pds_data_fp = dataFile;
  repo_handle.pds_ndx_fp = ndxFilePtr;
  strcpy(repo_handle.pds_name, repo_name);
  repo_handle.rec_size = rec_size;
  repo_handle.repo_status = PDS_REPO_OPEN;

  // Build BST and store in pds_bst by reading index entries from the index file
  pds_load_ndx();
  
  // Close only the index file
  fclose(repo_handle.pds_ndx_fp);
  return PDS_SUCCESS;
}

int pds_load_ndx() // Same as before
{
  while (!feof(repo_handle.pds_ndx_fp)) {
    int key;
    int status = fread(&key, sizeof(int), 1, repo_handle.pds_ndx_fp);
    
    int offset;
    int b_status = fread(&offset, sizeof(int), 1, repo_handle.pds_ndx_fp);

    if (status == 0 || b_status == 0) return PDS_FILE_ERROR;

    struct PDS_NdxInfo* ndxInfo = malloc(sizeof(struct PDS_NdxInfo));
    ndxInfo->key = key;
    ndxInfo->offset = offset;
    if (status > 0 && b_status > 0) {
      bst_add_node(&repo_handle.pds_bst, key, ndxInfo);
    }
  }

  return PDS_SUCCESS;
}

int put_rec_by_key(int key, void*rec) // Same as before
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
    struct PDS_NdxInfo *ndxInfo = malloc(sizeof(struct PDS_NdxInfo));
    ndxInfo->key = key;
    ndxInfo->offset = offset;

    // Add index entry to BST using offset returned by ftell
    int status = bst_add_node(&repo_handle.pds_bst, key, ndxInfo);
    
    if (status == BST_DUP_KEY) {
      return BST_DUP_KEY;
    }
    if (status == BST_NULL) {
      return BST_NULL;
    }

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

int get_rec_by_ndx_key(int key, void*rec) // Only Function Rename 
{
  if (repo_handle.repo_status == PDS_REPO_CLOSED) return PDS_REPO_CLOSED;
  // Search for index entry in BST
  struct PDS_NdxInfo* ndxInfo = malloc(sizeof(struct PDS_NdxInfo));
  
  struct BST_Node* found = bst_search(repo_handle.pds_bst, key);
  if (found == NULL) {
    return PDS_REC_NOT_FOUND;
  }
  ndxInfo = found->data;
  
  // Seek to the file location based on offset in index entry
  fseek(repo_handle.pds_data_fp, ndxInfo->offset, 0);
  
  // Read the key at the current file location 
  int stored_key;
  int read_key = fread(&stored_key, sizeof(int), 1, repo_handle.pds_data_fp);      
  if (read_key == 0) return PDS_FILE_ERROR;

  // Read the record after reading the key
  int read_offset = fread(rec, repo_handle.rec_size, 1, repo_handle.pds_data_fp);
  if (read_offset == 0) return PDS_FILE_ERROR;

  // return success
  return PDS_SUCCESS;
}

int rewriteNdx(struct BST_Node* root, FILE* fp) 
{
  if (!root) {
    return PDS_SUCCESS;
  }
  struct PDS_NdxInfo* ndx_info = root->data;
  int key = ndx_info->key;
  int write_key = fwrite(&key, sizeof(int), 1, fp);

  int offset = ndx_info->offset;
  int write_offset = fwrite(&offset, sizeof(int), 1, fp);

  if (write_key == 0 || write_offset == 0) return PDS_FILE_ERROR;

  int left_status = rewriteNdx(root->left_child, fp);
  int right_status = rewriteNdx(root->right_child, fp);

  if (left_status != 0) return left_status;
  return right_status;
}

int pds_close() // Same as before
{
if (repo_handle.repo_status == PDS_REPO_CLOSED) return PDS_REPO_CLOSED;
  // Open the index file in wb mode (write mode, not append mode)
  char ndxFile[100];
  strcpy(ndxFile, repo_handle.pds_name);
  strcat(ndxFile, ".ndx");
  FILE* ndxFilePtr = fopen(ndxFile, "wb");

  // Unload the BST into the index file by traversing it in PRE-ORDER (overwrite the entire index file)
  rewriteNdx(repo_handle.pds_bst, ndxFilePtr);
  repo_handle.pds_bst = NULL;

  // Free the BST by calling bst_destroy()
  bst_destroy(repo_handle.pds_bst);
  
  // Close the index file and data file
  fclose(ndxFilePtr);
  fclose(repo_handle.pds_data_fp);
}

int get_rec_by_non_ndx_key(void *search_key, void *rec, int (*matcher)(void *rec, void *key), int *io_count)
{
  // Seek to beginning of file
  fseek(repo_handle.pds_data_fp, 0, SEEK_SET);
  // Perform a table scan - iterate over all the records
  while (!feof(repo_handle.pds_data_fp)) {
    //   Read the key and the record
    int rec_key;
    fread(&rec_key, sizeof(int), 1, repo_handle.pds_data_fp);
    fread(rec, repo_handle.rec_size, 1, repo_handle.pds_data_fp);

    //   Increment io_count by 1 to reflect count no. of records read
    (*io_count) ++;
    // Use the function in function pointer to compare the record with required key
    // Return success when record is found
    char * key = (char *) search_key;
    if (matcher(rec, search_key) == 0) 
      return PDS_SUCCESS;
  }
  return PDS_REC_NOT_FOUND;
}