create database imt2019090_companydb;

use imt2019090_companydb;

create table employee (
    fname varchar(50) not null,
    minit char(1),
    lname varchar(70),
    ssn varchar(10) primary key not null,
    bdate date,
    address varchar(80),
    sex char(1),
    salary int,
    super_ssn varchar(10),
    dno int
);

create table department (
    dname varchar(20) not null,
    dnumber int primary key not null,
    mgr_ssn varchar(10) not null,
    mgr_start_date date
);

create table dept_locations (
    dnumber int not null,
    dlocation varchar(30) not null,
    primary key(dnumber, dlocation)
);

create table project (
    pname varchar(20) not null,
    pnumber int primary key not null,
    plocation varchar(30),
    dnum int
);

create table works_on (
    essn varchar(10) not null,
    pno int not null,
    hours decimal(10, 2),
    primary key(essn, pno)
);

create table dependent (
    essn varchar(10) not null,
    dependent_name varchar(30) not null,
    sex char(1),
    bdate date,
    relationship varchar(20),
    primary key(essn, dependent_name)
);
