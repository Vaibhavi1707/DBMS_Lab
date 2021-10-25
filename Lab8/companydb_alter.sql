alter table employee
add foreign key (dno)
references department(dnumber);

alter table employee
add foreign key (super_ssn)
references employee(ssn);

alter table department
add foreign key (mgr_ssn)
references employee(ssn);

alter table dept_locations
add foreign key (dnumber)
references department(dnumber);

alter table project
add foreign key (dnum)
references department(dnumber);

alter table works_on
add foreign key (essn)
references employee(ssn);

alter table works_on
add foreign key (pno)
references project(pnumber);

alter table dependent
add foreign key (essn)
references employee(ssn);