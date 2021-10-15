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

int processTask(int option) {
    switch(option) {
        case 1: // Create a new db
        break;
        case 2: // Insert a new record
        break;
        case 3: // Update a record
        break;
        case 4: // Read a record by indexed key
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
    scanf("%d", option);

    while (option != 0) {
        int choiceInvalid = processTask(option);

        if (choiceInvalid) {
            printf("Invalid choice!\n");
        }

        printf("Done? Enter 0 to quit.\n");
        scanf("%d", option);
    }

    return 0;
}