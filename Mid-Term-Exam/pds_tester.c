#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "pds.h"
#include "movie.h"

#define TREPORT(a1,a2) printf("Status %s: %s\n\n",a1,a2); fflush(stdout);

void process_line( char *test_case );

int main(int argc, char *argv[])
{
	FILE *cfptr;
	char test_case[50];

	if( argc != 2 ){
		fprintf(stderr, "Usage: %s testcasefile\n", argv[0]);
		exit(1);
	}

	cfptr = (FILE *) fopen(argv[1], "r");
	while(fgets(test_case, sizeof(test_case)-1, cfptr)){
		// printf("line:%s",test_case);
		if( !strcmp(test_case,"\n") || !strcmp(test_case,"") )
			continue;
		process_line( test_case );
	}
}

void process_line( char *test_case )
{
	char repo_name[30];
	char command[50], param1[50], param2[50], info[1000];
	char name_num[10];
	int id, status, rec_size, expected_status, expected_io, actual_io;
	char expected_name[50]; 
	struct Movie testMovie;

	strcpy(testMovie.name, "dummy name");
	// strcpy(expected_name, "dummy name");
	// strcpy(expected_name, "dummy number");
	

	rec_size = sizeof(struct Movie);

	sscanf(test_case, "%s%s%s", command, param1, param2);
	printf("Test case: %s", test_case); fflush(stdout);
	if( !strcmp(command,"CREATE") ){
		strcpy(repo_name, param1);
		if( !strcmp(param2,"0") )
			expected_status = MOVIE_SUCCESS;
		else
			expected_status = MOVIE_FAILURE;
		
		status = pds_create( repo_name );
		if( status == expected_status ){
			TREPORT("PASS", "");
		}
		else{
			sprintf(info,"pds_open returned status %d",status);
			TREPORT("FAIL", info);
		}
	}

	if( !strcmp(command,"OPEN") ){
		strcpy(repo_name, param1);
		if( !strcmp(param2,"0") )
			expected_status = MOVIE_SUCCESS;
		else
			expected_status = MOVIE_FAILURE;

		status = pds_open( repo_name, rec_size );
		if(status == PDS_SUCCESS)
			status = MOVIE_SUCCESS;
		else
			status = MOVIE_FAILURE;
		if( status == expected_status ){
			TREPORT("PASS", "");
		}
		else{
			sprintf(info,"pds_open returned status %d",status);
			TREPORT("FAIL", info);
		}
	}
	else if( !strcmp(command,"STORE") ){
		if( !strcmp(param2,"0") )
			expected_status = MOVIE_SUCCESS;
		else
			expected_status = MOVIE_FAILURE;

		sscanf(param1, "%d", &id);
		testMovie.id = id;
		sprintf(testMovie.name,"Name-of-%d",id);
		// sprintf(testMovie.name,"Phone-of-%d",id);
		status = add_movie( &testMovie );
		if(status == PDS_SUCCESS)
			status = MOVIE_SUCCESS;
		else
			status = MOVIE_FAILURE;
		if( status == expected_status ){
			TREPORT("PASS", "");
		}
		else{
			sprintf(info,"add_movie returned status %d",status);
			TREPORT("FAIL", info);
		}
	}
	else if( !strcmp(command,"NDX_SEARCH") ){
		if( strcmp(param2,"1") )
			expected_status = MOVIE_SUCCESS;
		else
			expected_status = MOVIE_FAILURE;

		sscanf(param1, "%d", &id);
		testMovie.id = -1;
		status = search_movie( id, &testMovie );
		if(status == PDS_SUCCESS)
			status = MOVIE_SUCCESS;
		else
			status = MOVIE_FAILURE;
		if( status != expected_status ){
			sprintf(info,"search key: %d; Got status %d",id, status);
			TREPORT("FAIL", info);
		}
		else{
			// Check if the retrieved values match
			if( expected_status == 0 ){
				sprintf(expected_name,"Name-of-%d",id);
				// sprintf(expected_name,"Phone-of-%d",id);
				if (testMovie.id == id && 
					strcmp(testMovie.name,expected_name) == 0 &&
					strcmp(testMovie.name,expected_name) == 0){
						TREPORT("PASS", "");
				}
				else{
					sprintf(info,"Movie data not matching... Expected:{%d,%s,%s} Got:{%d,%s,%s}\n",
						id, expected_name, expected_name, 
						testMovie.id, testMovie.name, testMovie.name
					);
					TREPORT("FAIL", info);
				}
			}
			else
				TREPORT("PASS", "");
		}
	}
	else if( !strcmp(command,"NON_NDX_SEARCH") ){
		if( strcmp(param2,"-1") )
			expected_status = MOVIE_SUCCESS;
		else
			expected_status = MOVIE_FAILURE;

		sscanf(param1, "%s", name_num);
		sscanf(param2, "%d", &expected_io);
		testMovie.id = -1;
		int actual_io = 0;
		status = search_movie_by_name( name_num, &testMovie, &actual_io );
		if(status == PDS_SUCCESS)
			status = MOVIE_SUCCESS;
		else
			status = MOVIE_FAILURE;
		if( status != expected_status ){
			sprintf(info,"search key: %d; Got status %d",id, status);
			TREPORT("FAIL", info);
		}
		else{
			// Check if the retrieved values match
			// Check if num block accesses match too
			// Extract the expected id from the name number
			sscanf(name_num+sizeof("Phone-of"), "%d", &id);
			sprintf(expected_name,"Name-of-%d",id);
			sprintf(expected_name,"Phone-of-%d",id);
			if( expected_status == 0 ){
				if (testMovie.id == id && 
					strcmp(testMovie.name, expected_name) == 0 &&
					strcmp(testMovie.name, expected_name) == 0 ){
						if( expected_io == actual_io ){
							TREPORT("PASS", "");
						}
						else{
							sprintf(info,"Num I/O not matching for %d... Expected:%d Got:%d\n",
								id, expected_io, actual_io
							);
							TREPORT("FAIL", info);
						}
				}
				else{
					sprintf(info,"Movie data not matching... Expected:{%d,%s,%s} Got:{%d,%s,%s}\n",
						id, expected_name, expected_name, 
						testMovie.id, testMovie.name, testMovie.name
					);
					TREPORT("FAIL", info);
				}
			}
			else
				TREPORT("PASS", "");
		}
	}
	else if( !strcmp(command,"NDX_DELETE") ){
		if( strcmp(param2,"0") == 0 )
			expected_status = MOVIE_SUCCESS;
		else
			expected_status = MOVIE_FAILURE;

		sscanf(param1, "%d", &id);
		testMovie.id = -1;
		status = delete_movie( id );
		if( status != expected_status ){
			sprintf(info,"delete key: %d; Got status %d",id, status);
			TREPORT("FAIL", info);
		}
		else{
			TREPORT("PASS", "");
		}
	}
	else if( !strcmp(command,"OVERWRITE") ){
		if( strcmp(param2,"0") == 0 )
			expected_status = MOVIE_SUCCESS;
		else
			expected_status = MOVIE_FAILURE;

		sscanf(param1, "%d", &id);
		testMovie.id = id;
		sprintf(testMovie.name,"Updated-Name-of-%d",id);
		sprintf(testMovie.name,"Updated-Phone-of-%d",id);
		status = overwrite_movie( &testMovie );
		if( status != expected_status ){
			sprintf(info,"Update id: %d; Got status %d",id, status);
			TREPORT("FAIL", info);
		}
		else{ // Update succeeded but check if really updated
			// Try to retrieve the movie
			testMovie.id = -1;
			status = search_movie( id, &testMovie );
			if(status == PDS_SUCCESS)
				status = MOVIE_SUCCESS;
			else
				status = MOVIE_FAILURE;
			if( status != MOVIE_SUCCESS ){
				sprintf(info,"search key: %d; Got status %d",id, status);
				TREPORT("FAIL", info);
			}
			else{
				// Check if the retrieved values match
				sprintf(expected_name,"Updated-Name-of-%d",id);
				sprintf(expected_name,"Updated-Phone-of-%d",id);
				if (testMovie.id == id && 
					strcmp(testMovie.name,expected_name) == 0 &&
					strcmp(testMovie.name,expected_name) == 0){
						TREPORT("PASS", "");
				}
				else{
					sprintf(info,"Updated Movie data not matching. Expected:{%d,%s,%s} Got:{%d,%s,%s}\n",
							id, expected_name, expected_name, 
							testMovie.id, testMovie.name, testMovie.name
						);
					TREPORT("FAIL", info);
				}
			}
		}
	}
	else if( !strcmp(command,"CLOSE") ){
		if( !strcmp(param1,"0") )
			expected_status = MOVIE_SUCCESS;
		else
			expected_status = MOVIE_FAILURE;

		status = pds_close();
		if(status == PDS_SUCCESS)
			status = MOVIE_SUCCESS;
		else
			status = MOVIE_FAILURE;
		if( status == expected_status ){
			TREPORT("PASS", "");
		}
		else{
			sprintf(info,"pds_close returned status %d",status);
			TREPORT("FAIL", info);
		}
	}
}


