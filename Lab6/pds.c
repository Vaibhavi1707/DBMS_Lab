#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>

#include "pds.h"
#include "bst.h"

struct PDS_RepoInfo repo_handle;


int pds_create(char *repo_name) 
{
  // printf("Hello\n");
  char filename[30], indexfile[30];
  strcpy(filename,repo_name);
  strcpy(indexfile,repo_name);
  strcat(filename,".dat");
  strcat(indexfile,".ndx");

  // printf("Initialised data file name and index file name\n");

  FILE *fp = fopen(filename,"wb+");
  FILE *ifp = fopen(indexfile,"wb+");

  // printf("Opened data and index files\n");

  if(fp  == NULL || ifp == NULL) return PDS_FILE_ERROR;
  fclose(fp);
  fclose(ifp);

  // printf("Closed files\n");
  
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
    ndxInfo->is_deleted = 0;
    if (status > 0 && b_status > 0) {
      bst_add_node(&repo_handle.pds_bst, key, ndxInfo);
    }
  }

  return PDS_SUCCESS;
}

int put_rec_by_key(int key, void*rec)
{
  // printf("Heloo");
  // check repo_status
  if (repo_handle.repo_status == PDS_REPO_CLOSED)
      return PDS_REPO_CLOSED;

  // printf("Seeking the file location\n"); 
  // set file pointer towards end of file
  fseek(repo_handle.pds_data_fp, 0, SEEK_END);
  
  // printf("Create an index entry\n");
  // Create an index entry with the current data file location using ftell
  int offset = ftell(repo_handle.pds_data_fp);
  struct PDS_NdxInfo *ndxInfo = malloc(sizeof(struct PDS_NdxInfo));
  ndxInfo->key = key;
  ndxInfo->offset = offset;
  ndxInfo->is_deleted = 0; // ENSURE is_deleted is set to 0 when creating index entry
  
  // printf("Index entry created\n");
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
  
  // printf("Record entered\n");
  // write record to file
  int status_rec_write = fwrite(rec, repo_handle.rec_size, 1, repo_handle.pds_data_fp);
  
  // printf("Failure status return\n");
  // if write is successful return PDS_SUCCESS 
  if (status_key_write == 0 && status_rec_write == 0) 
      return PDS_ADD_FAILED;
  
  // Else return error status accordingly
  return PDS_SUCCESS;
}

int get_rec_by_ndx_key(int key, void*rec)
{
  if (repo_handle.repo_status == PDS_REPO_CLOSED) return PDS_REPO_CLOSED;
  
  // Search for index entry in BST
  struct PDS_NdxInfo* ndxInfo = malloc(sizeof(struct PDS_NdxInfo));
  
  struct BST_Node* found = bst_search(repo_handle.pds_bst, key);

  if (found == NULL) {
    return PDS_REC_NOT_FOUND;
  }
  ndxInfo = found->data;

  // Check if the entry is deleted and if it is deleted, return PDS_REC_NOT_FOUND
  if (ndxInfo->is_deleted == 1) 
    return PDS_REC_NOT_FOUND;
  
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
  if (ndx_info->is_deleted == 0) {
    int key = ndx_info->key;
    int write_key = fwrite(&key, sizeof(int), 1, fp);
    int offset = ndx_info->offset;
    int write_offset = fwrite(&offset, sizeof(int), 1, fp);

    if (write_key == 0 || write_offset == 0) return PDS_FILE_ERROR;
  }

  int left_status = rewriteNdx(root->left_child, fp);
  int right_status = rewriteNdx(root->right_child, fp);

  if (left_status != 0) return left_status;
  return right_status;
}

int pds_close() 
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

  // NEW Ignore the index entries that have already been deleted. 

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
    //  Read the key and the record
    int rec_key;
    int status_read_key = fread(&rec_key, sizeof(int), 1, repo_handle.pds_data_fp);

    int status_read_rec = fread(rec, repo_handle.rec_size, 1, repo_handle.pds_data_fp);

    if (status_read_key == 0 || status_read_rec == 0) return PDS_REC_NOT_FOUND;

    //   Increment io_count by 1 to reflect count no. of records read
    (*io_count) ++;
    
    // NEW Check the entry of the record in the BST and see if it is deleted. If so, return PDS_REC_NOT_FOUND
  
  // Return success when record is found
    if (matcher(rec, search_key) == 0) {
        struct BST_Node* record_found = malloc(sizeof(struct BST_Node)); 
        record_found = bst_search(repo_handle.pds_bst, rec_key);
        if (record_found == NULL) {
          return PDS_REC_NOT_FOUND;
        }
        struct PDS_NdxInfo* ndxInfo = malloc(sizeof(struct PDS_NdxInfo));
        ndxInfo = record_found->data;
        if (ndxInfo->is_deleted == 1) 
          return PDS_REC_NOT_FOUND;
        return PDS_SUCCESS;
    } 
  }
  return PDS_REC_NOT_FOUND;
}

int delete_rec_by_ndx_key( int key) // New Function
{
  // Search for the record in the BST using the key
  struct BST_Node* record = bst_search(repo_handle.pds_bst, key);
  
  // If record not found, return PDS_DELETE_FAILED
  if (record == NULL) return PDS_REC_NOT_FOUND;
  
  // If record is found, check if it has already been deleted, if so return PDS_DELETE_FAILED
  struct PDS_NdxInfo* ndxInfo = malloc(sizeof(struct PDS_NdxInfo));
  ndxInfo = record->data;
  if (ndxInfo->is_deleted == 1) 
    return PDS_DELETE_FAILED;
  
  // Else, set the record to deleted and return PDS_SUCCESS
  ndxInfo->is_deleted = 1;
  return PDS_SUCCESS;
}

int pds_overwrite(int key, void *rec) {
  if (repo_handle.repo_status == PDS_REPO_CLOSED) return PDS_REPO_CLOSED;
  
  struct BST_Node* record = bst_search(repo_handle.pds_bst, key);
  if (record == NULL) return PDS_REC_NOT_FOUND;

  struct PDS_NdxInfo* ndxInfo = malloc(sizeof(struct PDS_NdxInfo));
  ndxInfo = record->data;
  if (ndxInfo->is_deleted == 1) 
    return PDS_REC_NOT_FOUND;

  int seek_status = fseek(repo_handle.pds_data_fp, ndxInfo->offset, SEEK_SET);
  if (seek_status != 0) return PDS_FILE_ERROR; 

  int status_key_write = fwrite(&key, sizeof(int), 1, repo_handle.pds_data_fp);

  int status_rec_write = fwrite(rec, repo_handle.rec_size, 1, repo_handle.pds_data_fp);

  if (status_key_write == 0 || status_rec_write == 0) return PDS_UPDATE_FAILED;

  return PDS_SUCCESS;
}