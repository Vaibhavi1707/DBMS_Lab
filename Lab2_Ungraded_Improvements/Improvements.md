# Improvements

## Improvement 1
Write a function in contact.c to store multiple records at a time by reading data from a text file containing contact information. You can call this function ```import_contacts(char *import_file_name)```.

## Improvement 2
Write a function in pds.c to retrieve n-th record from the repository. You can call this ```pds_get_nth_rec(int n, void *rec)```

## Improvement 3
Write a function in contact.c to retrieve multiple contacts based on non-key attribute (e.g., city). You can call it get_contacts_by_city(). Considering that the function could return multiple records, what would be the appropriate function prototype?

int get_contacts_by_name(char*name, struct Contact * found)
// name to be searched and the array where all contacts are stored is passed. The function returns status.