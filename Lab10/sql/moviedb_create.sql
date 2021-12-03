CREATE DATABASE `moviedb`;

USE moviedb;

CREATE TABLE `director` (
	`dir_id` INT NOT NULL,
	`fname` VARCHAR(255) NOT NULL,
	`lname` VARCHAR(255),
	`gender` VARCHAR(255),
	`country` VARCHAR(255),
	PRIMARY KEY (`dir_id`)
);

CREATE TABLE `movie` (
	`movie_id` INT NOT NULL,
	`name` VARCHAR(255) NOT NULL,
	`year_of_release` INT NOT NULL,
	`length_in_min` INT NOT NULL,
	`language` VARCHAR(255),
	`description` TEXT,
	`genre` VARCHAR(255),
	`directed_by` INT,
	PRIMARY KEY (`movie_id`)
);

CREATE TABLE `worked_in` (
	`worked_in_id` INT NOT NULL,
	`movie_id` INT NOT NULL,
	`actor_id` INT NOT NULL,
	PRIMARY KEY (`movie_id`,`actor_id`)
);

CREATE TABLE `watched_by` (
	`watched_by_id` INT NOT NULL,
	`movie_id` INT NOT NULL,
	`watcher_id` INT NOT NULL,
	`rating` FLOAT,
	`no_of_watches` INT NOT NULL,
	PRIMARY KEY (`movie_id`,`watcher_id`)
);

CREATE TABLE `actor` (
	`actor_id` INT NOT NULL,
	`fname` VARCHAR(255) NOT NULL,
	`lname` VARCHAR(255),
	`gender` VARCHAR(255),
	`country` VARCHAR(255),
	PRIMARY KEY (`actor_id`)
);

CREATE TABLE `watcher` (
	`watcher_id` INT NOT NULL,
	`fname` VARCHAR(255) NOT NULL,
	`lname` VARCHAR(255),
	`gender` VARCHAR(255),
	`country` VARCHAR(255),
	PRIMARY KEY (`watcher_id`)
);