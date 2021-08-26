#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "pds.h"
#include "contact.h"

void print_contact( struct Contact *c )
{
	printf("%d,%s,%s\n", c->contact_id,c->contact_name,c->phone);
}

// Use get_rec_by_key function to retrieve contact
int search_contact( int contact_id, struct Contact *c )
{
	int status;
	status = get_rec_by_key( contact_id, c );
	if( status == PDS_SUCCESS )
		status = CONTACT_SUCCESS;
	else
		status = CONTACT_FAILURE;

	return status;
}

// Add the given contact into the repository by calling put_rec_by_key
int add_contact( struct Contact *c )
{
	int status;

	status = put_rec_by_key( c->contact_id, c );

	if( status != PDS_SUCCESS ){
		fprintf(stderr, "Unable to add contact with key %d. Error %d", c->contact_id, status );
		status=CONTACT_FAILURE;
	}
	else
		status=CONTACT_SUCCESS;

	return status;
}

int import_contacts(char* filename) {
	// printf("Hello");
	FILE * contacts = fopen(filename, "r");

	if (contacts == NULL) {
		return CONTACT_FAILURE;
	}

	int status = CONTACT_SUCCESS;
	// printf("Hello");
	while (!feof(contacts)) {
		int id;
		char name[30];
		char ph_no[9];
		fscanf(contacts, "%d %s %s\n", &id, name, ph_no);
		struct Contact contact;
		contact.contact_id = id;
		strcpy(contact.contact_name, name);
		strcpy(contact.phone, ph_no);

		status = add_contact(&contact);
	}

	return status;
}

int get_contacts_by_name(char*name, struct Contact * found) {
	int status;
	status = get_rec_by_non_key(name, found);
	if( status == PDS_SUCCESS )
		status = CONTACT_SUCCESS;
	else
		status = CONTACT_FAILURE;

	return status;
}

