#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "pds.h"
#include "movie.h"

// Load all the movies from a CSV file
int store_movies( char *movie_data_file )
{
	FILE *cfptr;
	char movie_line[500], token;
	struct Movie movie, dummy;

	cfptr = (FILE *) fopen(movie_data_file, "r");
	while(fgets(movie_line, sizeof(movie_line)-1, cfptr)){
		//printf("line:%s",movie_line);
		sscanf(movie_line, "%d%s%d%f%s%d", &(movie.id), movie.name, &(movie.year), &(movie.star_rating), 
        movie.genre, &(movie.length));
		print_movie( &movie );
		add_movie( &movie );
	}
}

void print_movie( struct Movie *movie )
{
	printf("%d\t%s\t%d\t%f\t%s\t%d", movie->id, movie->name, movie->year, movie->star_rating, 
        movie->genre, movie->length);
}

// Use get_rec_by_key function to retrieve movie
int search_movie( int movie_id, struct Movie *movie )
{
	return get_rec_by_ndx_key( movie_id, movie );
}

// Add the given movie into the repository by calling put_rec_by_key
int add_movie( struct Movie *movie )
{
	int status;

	status = put_rec_by_key( movie->id, movie );

	if( status != PDS_SUCCESS ){
		fprintf(stderr, "Unable to add movie with id %d. Error %d", movie->id, status );
		return MOVIE_FAILURE;
	}
	return status;
}

// Use get_rec_by_non_ndx_key function to retrieve movie
int search_movie_by_name( char *name, struct Movie *movie, int *io_count )
{
	// Call function
	return get_rec_by_non_ndx_key(name, movie, &match_movie_name, io_count);
}

/* Return 0 if phone of the movie matches with phone parameter */
/* Return 1 if phone of the movie does NOT match */
/* Return > 1 in case of any other error */
int match_movie_name( void *rec, void *key )
{
	// Store the rec in a struct movie pointer
	struct Movie * movie = rec;
    
	// Store the key in a char pointer
	char * movie_key = key;
    
	// Compare the phone values in key and record
	// Return 0,1,>1 based on above condition
	if (!key || !movie) {
		return 2;
	}
	if (strcmp(movie_key, movie->name) == 0) {
		return 0;
	}
	return 1;
}

// Function to delete a record based on ndx_key
int delete_movie ( int movie_id )
{
	// Call the delete_movie_ndx_key function
	int status = delete_rec_by_ndx_key(movie_id);
	
	// Return MOVIE_SUCCESS or MOVIE_FAILURE based on status of above call
	if (status == PDS_SUCCESS) return MOVIE_SUCCESS;
	return MOVIE_FAILURE;
}

int overwrite_movie(struct Movie *movie) {
	int status = pds_overwrite(movie->id, movie);

	if (status == PDS_SUCCESS) return MOVIE_SUCCESS;
	return MOVIE_FAILURE;
}