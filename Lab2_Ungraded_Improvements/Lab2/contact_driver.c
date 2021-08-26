#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "pds.h"
#include "contact.h"

// You can use the following macro to report test result
// Do NOT put a semicolon after calling the macro (see examples below)

#define TREPORT(tid,result) { printf("Test-case-id %s:%s\n",tid,result); fflush(stdout); }

int main()
{
	char *repo_name = "demo.dat";
	pds_create(repo_name);
	int status, rec_size;
	struct Contact testContact;
	struct Contact testContact1;
	char *test_case_id;

	char *repo_name1 = "start.dat";
	pds_create(repo_name1);
	// int status1, rec_size1;
	struct Contact test1;


	test1.contact_id = 1;
	strcpy(test1.contact_name, "Me");
	strcpy(test1.phone, "myph_no");

	testContact.contact_id = 10000;
	strcpy(testContact.contact_name, "dummy name");
	strcpy(testContact.phone, "dummy number");

	testContact1.contact_id = 10001;
	strcpy(testContact1.contact_name, "dummy name");
	strcpy(testContact1.phone, "dummy number");

	rec_size = sizeof(struct Contact);

	test_case_id = "01";
	status = pds_open( repo_name, rec_size);
	if( status == PDS_SUCCESS ){
		TREPORT(test_case_id,"SUCCESS")
	}
	else{
		TREPORT(test_case_id,"FAIL")
		exit(status);
	}

	// read_file();

	test_case_id = "02";
	testContact.contact_id = 10000;
	status = add_contact( &testContact );
	if( status == CONTACT_SUCCESS )
		TREPORT(test_case_id,"SUCCESS")
	else
		TREPORT(test_case_id,"FAIL")

	test_case_id = "14";
	testContact.contact_id = 10000;
	status = add_contact( &testContact1 );
	if( status == CONTACT_SUCCESS )
		TREPORT(test_case_id,"SUCCESS")
	else
		TREPORT(test_case_id,"FAIL")

	// read_file();

	test_case_id = "03";
	testContact.contact_id = -1;
	status = search_contact( 10000, &testContact );
	if( status == CONTACT_SUCCESS )
		TREPORT(test_case_id,"SUCCESS")
	else
		TREPORT(test_case_id,"FAIL")

	test_case_id = "04";
	
	if( testContact.contact_id == 10000  && 
		strcmp(testContact.contact_name,"dummy name") == 0 &&
		strcmp(testContact.phone,"dummy number") == 0 )
	{
		// printf("%d %d %d",testContact.contact_id,strcmp(testContact.contact_name,"dummy name"),strcmp(testContact.contact_name,"dummy number"));
		// print_contact(&testContact);
		TREPORT(test_case_id,"SUCCESS")
	}
	else
		TREPORT(test_case_id,"FAIL")

	test_case_id = "05";
	status = pds_close();
	if( status == PDS_SUCCESS ){
		TREPORT(test_case_id,"SUCCESS")
	}
	else{
		TREPORT(test_case_id,"FAIL")
		exit(status);
	}

	test_case_id = "06";
	status = pds_open( repo_name, rec_size);
	if( status == PDS_SUCCESS ){
		TREPORT(test_case_id,"SUCCESS")
	}
	else{
		TREPORT(test_case_id,"FAIL")
		exit(status);
	}

	test_case_id = "07";
	testContact.contact_id = -1;
	status = search_contact( 10000, &testContact );
	// printf("Search status %d\n", status);
	if( status == CONTACT_SUCCESS )
		TREPORT(test_case_id,"SUCCESS")
	else
		TREPORT(test_case_id,"FAIL")

	test_case_id = "08";
		
	if( testContact.contact_id == 10000 && 
		strcmp(testContact.contact_name,"dummy name") == 0 &&
		strcmp(testContact.phone,"dummy number") == 0 )

		TREPORT(test_case_id,"SUCCESS")
	else
		TREPORT(test_case_id,"FAIL")

	test_case_id = "09";
	status = pds_close();
	if( status == PDS_SUCCESS ){
		TREPORT(test_case_id,"SUCCESS")
	}
	else{
		TREPORT(test_case_id,"FAIL")
		exit(status);
	}

	pds_create(repo_name1);

	test_case_id = "10";
	status = pds_open(repo_name1, rec_size);
	if (status == PDS_SUCCESS) {
		TREPORT(test_case_id, "SUCCESS");
	}
	else {
		TREPORT(test_case_id, "FAIL");
	}

	test_case_id = "11";
	status = add_contact(&test1);
	if (status == PDS_SUCCESS) {
		TREPORT(test_case_id, "SUCCESS");
	}
	else {
		TREPORT(test_case_id, "FAIL");
	}

	test_case_id = "12";
	test1.contact_id = -1;
	status = search_contact(1, &test1);
	
	if (test1.contact_id == 1 && 
		strcmp(test1.contact_name, "Me") == 0 && 
		strcmp(test1.phone, "myph_no") == 0) { 
		TREPORT(test_case_id, "SUCCESS");
	}
	else {
		TREPORT(test_case_id, "FAIL");
	}

	// Test for importing contacts
	test_case_id = "17";
	char *contactFile = "myContacts.txt";
	status = import_contacts(contactFile);
	if( status == CONTACT_SUCCESS ){
		TREPORT(test_case_id,"SUCCESS")
	}
	else{
		TREPORT(test_case_id,"FAIL")
		exit(status);
	}

	// Test for retrieving nth record
	test_case_id = "18";
	struct Contact test2;
	status = pds_get_nth_rec(2, &test2);
	printf("%d %s %s\n", test2.contact_id, test2.contact_name, test2.phone);
	if( status == PDS_SUCCESS ){
		TREPORT(test_case_id,"SUCCESS")
	}
	else{
		TREPORT(test_case_id,"FAIL")
		exit(status);
	}

	// Tests for searching contacts by name
	test_case_id = "19";
	struct Contact found[100];
	status = get_contacts_by_name("A", found);
	if( status == PDS_SUCCESS ){
		TREPORT(test_case_id,"SUCCESS")
	}
	else{
		TREPORT(test_case_id,"FAIL")
		exit(status);
	}

	test_case_id = "13";
	status = pds_close();
	if( status == PDS_SUCCESS ){
		TREPORT(test_case_id,"SUCCESS")
	}
	else{
		TREPORT(test_case_id,"FAIL")
		exit(status);
	}


	return 0;
}


