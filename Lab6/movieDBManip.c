#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "pds.h"
#include "movie.h"

int show_options() {
    printf("Enter your choice\n");
    printf("1. Create a new database\n");
    printf("2. Insert a new record\n");
    printf("3. Update a record\n");
    printf("4. Read a record by indexed key\n");
    printf("5. Read a record by non indexed key\n");
    printf("6. Delete a record by indexed key\n");
}

int insertMovie(char* dbname) {
    int rec_size = sizeof(struct Movie);

    pds_open(dbname, rec_size);

    int id;
    printf("Enter movie id: \n");
    scanf("%d", &id);

    char name[50];
    printf("Enter movie name: \n");
    scanf("%s", name);

    int year;
    printf("Enter movie year: \n");
    scanf("%d", &year);
    
    float star_rating; 
    printf("Enter movie rating: \n");
    scanf("%f", &star_rating);
    
    char genre[100];
    printf("Enter movie genre: \n");
    scanf("%s", genre);
    
    int length;
    printf("Enter movie length: \n");
    scanf("%d", &length);

    struct Movie* movie = malloc(sizeof(struct Movie));
    movie->id = id;
    strcpy(movie->name, name);
    movie->year = year;
    movie->star_rating = star_rating;
    strcpy(movie->genre, genre);
    movie->length = length;

    int status = add_movie(movie);

    if (status == MOVIE_SUCCESS) return MOVIE_SUCCESS;
    return MOVIE_FAILURE;
}

int searchMovieByID(char* dbname) {
    int rec_size = sizeof(struct Movie);
    pds_open(dbname, rec_size);
    int id;
    printf("Enter id to be searched\n");
    scanf("%d", &id);

    struct Movie* foundMovie = malloc(sizeof(struct Movie)); 
    
    int status = search_movie(id, foundMovie);

    if (status == MOVIE_NOT_FOUND || status == MOVIE_FAILURE) return status;

    printf("ID: %d\n NAME: %s\n YEAR: %d\n RATING: %f\n GENRE: %s\n LENGTH: %d\n",
    foundMovie->id, foundMovie->name, foundMovie->year, foundMovie->star_rating,
    foundMovie->genre, foundMovie->length);

    return MOVIE_SUCCESS;
}

int updateMovie(char *dbname) {
    int rec_size = sizeof(struct Movie);
    pds_open(dbname, rec_size);
    int id;
    printf("Enter id to be updated\n");
    scanf("%d", &id);

    char name[50];
    printf("Enter new movie name: \n");
    scanf("%s", name);

    int year;
    printf("Enter new movie year: \n");
    scanf("%d", &year);
    
    float star_rating; 
    printf("Enter new movie rating: \n");
    scanf("%f", &star_rating);
    
    char genre[100];
    printf("Enter new movie genre: \n");
    scanf("%s", genre);
    
    int length;
    printf("Enter new movie length: \n");
    scanf("%d", &length);

    struct Movie* updatedMovie = malloc(sizeof(struct Movie));
    updatedMovie->id = id;
    strcpy(updatedMovie->name, name);
    updatedMovie->year = year;
    updatedMovie->star_rating = star_rating;
    strcpy(updatedMovie->genre, genre);
    updatedMovie->length = length;
    
    int status = overwrite_movie(updatedMovie);

    if (status == MOVIE_NOT_FOUND || status == MOVIE_FAILURE) return status;

    printf("Movie updated.\n");

    return MOVIE_SUCCESS;
}

int searchMovieByName(char* dbname) {
    int rec_size = sizeof(struct Movie);
    pds_open(dbname, rec_size);
    char name[30];
    printf("Enter name to be searched\n");
    scanf("%s", name);

    struct Movie* foundMovie = malloc(sizeof(struct Movie)); 
    
    int* iterCount;
    *iterCount = 0; 
    int status = search_movie_by_name(name, foundMovie, iterCount);

    if (status == MOVIE_NOT_FOUND || status == MOVIE_FAILURE) return status;

    printf("ID: %d\n NAME: %s\n YEAR: %d\n RATING: %f\n GENRE: %s\n LENGTH: %d\n",
    foundMovie->id, foundMovie->name, foundMovie->year, foundMovie->star_rating,
    foundMovie->genre, foundMovie->length);

    return MOVIE_SUCCESS;
}

int deleteMovieByID(char* dbname) {
    int rec_size = sizeof(struct Movie);
    pds_open(dbname, rec_size);

    int id;
    printf("Enter id to be deleted\n");
    scanf("%d", &id);
    
    int status = delete_movie(id);

    if (status == MOVIE_FAILURE) {
        printf("Movie already deleted\n");
    }

    if (status == MOVIE_NOT_FOUND) return status;

    printf("Deleted movie\n");

    return MOVIE_SUCCESS;
} 

int processTask(int option) {
    char dbname[50] = "moviedb";
    switch(option) {
        case 1: {
            int status = pds_create(dbname);
            if (status == PDS_SUCCESS) return 0;
            else return 2;
        }
        break;
        case 2: return insertMovie(dbname);
        break;
        case 3: return updateMovie(dbname);
        break;
        case 4: return searchMovieByID(dbname);
        break;
        case 5: return searchMovieByName(dbname);
        break;
        case 6: return deleteMovieByID(dbname);
        break;
        default: return MOVIE_FAILURE;
    }

    return MOVIE_SUCCESS;
}

int main() {
    show_options();

    int option;
    scanf("%d", &option);

    while (option != 0) {
        int status = processTask(option);

        if (status == MOVIE_FAILURE) {
            printf("Error occured.\n");
        }

        if (status == MOVIE_NOT_FOUND) {
            printf("Movie not found.\n");
        }

        printf("Done? Enter 0 to quit or any of above options.\n");
        scanf("%d", &option);
    }

    if (option != 1) pds_close();

    return 0;
}