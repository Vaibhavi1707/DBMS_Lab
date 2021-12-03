-- director
insert into `director`(`dir_id`, `fname`, `lname`, `gender`, `country`) values
(1, 'ffa', 'lla', 'M', 'India'),
(2, 'ffb', 'llb', 'F', 'USA'),
(3, 'ffc', 'llc', 'F', 'Spain'),
(4, 'ffd', 'lld', 'M', 'USA');

-- movie
insert into `movie`(`movie_id`, `name`, `year_of_release`, `length_in_min`, `language`, `description`, `genre`, `directed_by`) values
(1, 'ABC', 1990, 120, 'English', 'Good movie', 'romedy', 1),
(2, 'CDE', 1990, 120, 'English', 'okayish', 'comedy', 1),
(3, 'EFG', 1990, 120, 'Spanish', 'great', 'thriller', 2),
(4, 'HIJ', 1990, 120, 'Spanish', 'awesome', 'horror', 3),
(5, 'KLM', 1990, 120, 'English', 'happy feel', 'romedy', 2),
(6, 'NOP', 1990, 120, 'English', 'thriller', 'horror', 4),
(7, 'QRS', 1990, 120, 'Hindi', 'cartoon movie', 'kids', 3),
(8, 'TUV', 1990, 120, 'Hindi', 'good', 'action', 4),
(9, 'WXY', 1990, 120, 'Hindi', 'sad', 'romance', 1);

-- actor
insert into `actor`(`actor_id`, `fname`, `lname`, `gender`, `country`) values
(1, 'FA', 'LA', 'M', 'India'),
(2, 'FB', 'LB', 'M', 'India'),
(3, 'FC', 'LC', 'M', 'USA'),
(4, 'FD', 'LD', 'F', 'Spain'),
(5, 'FE', 'LE', 'F', 'USA');

-- watcher
insert into `watcher`(`watcher_id`, `fname`, `lname`, `gender`, `country`) values
(1, 'fA', 'lA', 'M', 'India'),
(2, 'fB', 'lB', 'M', 'India'),
(3, 'fC', 'lC', 'F', 'Spain'),
(4, 'fD', 'lD', 'M', 'USA'),
(5, 'fE', 'lE', 'F', 'USA'),
(6, 'fF', 'lF', 'F', 'India'),
(7, 'fG', 'lG', 'F', 'USA'),
(8, 'fH', 'lH', 'M', 'India');

-- worked_in
insert into `worked_in`(`worked_in_id`, `movie_id`, `actor_id`) values
(1, 1, 5),
(2, 1, 4),
(3, 2, 3),
(4, 2, 4),
(5, 3, 5),
(6, 3, 1),
(7, 4, 2),
(8, 9, 4),
(9, 8, 1),
(10, 5, 2),
(11, 7, 4),
(12, 6, 1);

-- watched_by 
insert into `watched_by`(`watched_by_id`, `movie_id`, `watcher_id`, `rating`, `no_of_watches`) values
(1, 1, 5, 2.4, 4556),
(2, 1, 6, 4.2, 6478),
(3, 2, 3, 4.5, 7800),
(4, 2, 4, 5, 8900),
(5, 3, 5, 3.4, 1000),
(6, 3, 1, 2.6, 4500),
(7, 4, 2, 3.6, 7800),
(8, 9, 4, 4.5, 2300),
(9, 8, 7, 4.8, 9000),
(10, 5, 8, 3.2, 4512),
(11, 7, 8, 2.3, 4890),
(12, 6, 1, 3.5, 12345);