#ifndef MOVIE_H
#define MOVIE_H

#define MOVIE_SUCCESS 0
#define MOVIE_FAILURE 1
#define MOVIE_NOT_FOUND 4
 
struct Movie{
	int id;
	char name[50];
	int year;
    float star_rating; // Movie rating in stars i.e 1 star for a bad movie and 5 star for a great movie
    char genre[100];
    int length; // length of the movie in min
};

extern struct PDS_RepoInfo *repoHandle;

// Add the given Movie into the repository by calling put_rec_by_key
int add_movie( struct Movie *movie );

// Overwite existing Movie with the given Movie pds_overwrite
// Hint: call the PDS function as follows
// pds_overwrite(c->Movie_id, c);
int overwrite_movie( struct Movie *movie);

// Display Movie info in a single line as a CSV without any spaces
void print_movie( struct Movie *movie);

// Use get_rec_by_key function to retrieve Movie
int search_movie( int movie_id, struct Movie *movie);

// Load all the Movies from a CSV file
int store_movies( char *movie_data_file );

// Use get_rec_by_non_ndx_key function to retrieve Movie
int search_movie_by_name( char *phone, struct Movie *movie, int *io_count );

/* Return 0 if phone of the Movie matches with phone parameter */
/* Return 1 if phone of the Movie does NOT match */
/* Return > 1 in case of any other error */
int match_movie_name( void *rec, void *key );

// Function to delete Movie by ID
int delete_movie ( int movie_id );

#endif
