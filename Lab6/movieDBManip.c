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

    printf("Hello \n");
    int status = add_movie(movie);
    printf("Movie added\n");
    if (status == MOVIE_SUCCESS) return 0;
    return 2;
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
        case 3: // Update a record
        break;
        case 4: {
            int rec_size = sizeof(struct Movie);
            pds_open(dbname, rec_size);
            int id;
            printf("Enter id to be searched\n");
            scanf("%d", &id);

            struct Movie* foundMovie = malloc(sizeof(struct Movie)); 
            
            int status = search_movie(id, foundMovie);

            if (status == MOVIE_FAILURE) return 2;

            printf("ID: %d\n NAME: %s\n YEAR: %d\n RATING: %f\n GENRE: %s\n LENGTH: %d\n",
            foundMovie->id, foundMovie->name, foundMovie->year, foundMovie->star_rating,
            foundMovie->genre, foundMovie->length);
            
            return 0;
        }
        break;
        case 5: // Read a record by non indexed key
        break;
        case 6: // Delete a record by indexed key
        break;
        default: return 1;
    }

    return 0;
}

int main() {
    show_options();

    int option;
    scanf("%d", &option);

    while (option != 0) {
        int status = processTask(option);

        if (status == 1) {
            printf("Invalid choice!\n");
        }

        if (status == 2) {
            printf("Error occured.\n");
        }

        printf("Done? Enter 0 to quit.\n");
        scanf("%d", &option);
    }

    return 0;
}