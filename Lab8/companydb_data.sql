insert into employee(fname, minit, lname, ssn, bdate, address,
sex, salary, super_ssn, dno)
VALUES('John','B','Smith','123456789','1965-01-09','731,
Fondren, Houston, TX','M',30000,NULL,NULL);
insert into employee(fname, minit, lname, ssn, bdate, address,
sex, salary, super_ssn, dno)
VALUES('Franklin','T','Wong','333445555','1965-01-09','731,
Fondren, Houston, TX','M',30000,NULL,NULL);
insert into employee(fname, minit, lname, ssn, bdate, address,
sex, salary, super_ssn, dno)
VALUES('Alicia','J','Zelaya','999887777','1965-01-09','731,
Fondren, Houston, TX','M',30000,NULL,NULL);
insert into employee(fname, minit, lname, ssn, bdate, address,
sex, salary, super_ssn, dno)
VALUES('Jennifer','S','Wallace','987654321','1965-01-09','731,
Fondren, Houston, TX','M',30000,NULL,NULL);
insert into employee(fname, minit, lname, ssn, bdate, address,
sex, salary, super_ssn, dno)
VALUES('Ramesh','K','Narayan','666884444','1965-01-09','731,
Fondren, Houston, TX','M',30000,NULL,NULL);
insert into employee(fname, minit, lname, ssn, bdate, address,
sex, salary, super_ssn, dno)
VALUES('Joyce','A','English','453453453','1965-01-09','731,
Fondren, Houston, TX','M',30000,NULL,NULL);
insert into employee(fname, minit, lname, ssn, bdate, address,
sex, salary, super_ssn, dno)
VALUES('Ahmed','V','Jabbar','987987987','1965-01-09','731,
Fondren, Houston, TX','M',30000,NULL,NULL);
insert into employee(fname, minit, lname, ssn, bdate, address,
sex, salary, super_ssn, dno)
VALUES('James','E','Borg','888665555','1965-01-09','731,
Fondren, Houston, TX','M',30000,NULL,NULL);

insert into department(dname, dnumber, mgr_ssn, mgr_start_date)
VALUES('Research', 5, '333445555', '1988-05-22');
insert into department(dname, dnumber, mgr_ssn, mgr_start_date)
VALUES('Administration', 4, '987654321', '1995-01-01');
insert into department(dname, dnumber, mgr_ssn, mgr_start_date)
VALUES('Headquarters', 1, '888665555', '1981-06-19');

insert into dept_locations(dnumber, dlocation)
VALUES(1, 'Houston');
insert into dept_locations(dnumber, dlocation)
VALUES(4, 'Stafford');
insert into dept_locations(dnumber, dlocation)
VALUES(5, 'Bellare');
insert into dept_locations(dnumber, dlocation)
VALUES(5, 'Sugarland');
insert into dept_locations(dnumber, dlocation)
VALUES(5, 'Houston');

insert into project(pname, pnumber, plocation, dnum)
VALUES('ProductX', 1, 'Bellare', 5);
insert into project(pname, pnumber, plocation, dnum)
VALUES('ProductY', 2, 'Sugarland', 5);
insert into project(pname, pnumber, plocation, dnum)
VALUES('ProductZ', 3, 'Houston', 5);
insert into project(pname, pnumber, plocation, dnum)
VALUES('Computerization', 10, 'Stafford', 4);
insert into project(pname, pnumber, plocation, dnum)
VALUES('Reorganisation', 20, 'Houston', 1);
insert into project(pname, pnumber, plocation, dnum)
VALUES('Newbenefits', 30, 'Stafford', 4);

insert into works_on(essn, pno, hours)
VALUES('123456789', 1, 32.5);
insert into works_on(essn, pno, hours)
VALUES('123456789', 2, 7.5);
insert into works_on(essn, pno, hours)
VALUES('666884444', 3, 40.0);
insert into works_on(essn, pno, hours)
VALUES('453453453', 1, 20.0);
insert into works_on(essn, pno, hours)
VALUES('453453453', 2, 20.0);
insert into works_on(essn, pno, hours)
VALUES('333445555', 2, 20.0);
insert into works_on(essn, pno, hours)
VALUES('333445555', 3, 10.0);
insert into works_on(essn, pno, hours)
VALUES('333445555', 10, 10.0);
insert into works_on(essn, pno, hours)
VALUES('333445555', 20, 10.0);
insert into works_on(essn, pno, hours)
VALUES('999887777', 30, 30.0);
insert into works_on(essn, pno, hours)
VALUES('999887777', 10, 10.0);
insert into works_on(essn, pno, hours)
VALUES('987987987', 10, 35.0);
insert into works_on(essn, pno, hours)
VALUES('987987987', 30, 5.0);
insert into works_on(essn, pno, hours)
VALUES('987654321', 30, 20.0);
insert into works_on(essn, pno, hours)
VALUES('987654321', 20, 15.0);
insert into works_on(essn, pno, hours)
VALUES('888665555', 20, NULL);

insert into dependent(essn, dependent_name, sex, bdate, relationship)
VALUES('333445555', 'Alice', 'F', '1986-04-05', 'Daughter');
insert into dependent(essn, dependent_name, sex, bdate, relationship)
VALUES('333445555', 'Theodore', 'M', '1986-04-05', 'Son');
insert into dependent(essn, dependent_name, sex, bdate, relationship)
VALUES('333445555', 'Joy', 'F', '1986-04-05', 'Spouse');
insert into dependent(essn, dependent_name, sex, bdate, relationship)
VALUES('987654321', 'Abner', 'M', '1986-04-05', 'Spouse');
insert into dependent(essn, dependent_name, sex, bdate, relationship)
VALUES('123456789', 'Michael', 'M', '1986-04-05', 'Son');
insert into dependent(essn, dependent_name, sex, bdate, relationship)
VALUES('123456789', 'Alice', 'F', '1986-04-05', 'Daughter');
insert into dependent(essn, dependent_name, sex, bdate, relationship)
VALUES('123456789', 'Elizabeth', 'F', '1986-04-05', 'Spouse');

update employee
set super_ssn = '333445555', dno=5
where ssn='123456789';
update employee
set super_ssn = '888665555', dno=5
where ssn='333445555';
update employee
set super_ssn = '987654321', dno=5
where ssn='999887777';
update employee
set super_ssn = '888665555', dno=5
where ssn='987654321';
update employee
set super_ssn = '333445555', dno=5
where ssn='666884444';
update employee
set super_ssn = '333445555', dno=5
where ssn='453453453';
update employee
set super_ssn = '987654321', dno=5
where ssn='987987987';