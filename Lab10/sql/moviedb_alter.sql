ALTER TABLE `movie` 
ADD CONSTRAINT `movie_fk` 
FOREIGN KEY (`directed_by`) 
REFERENCES `director`(`dir_id`);

ALTER TABLE `worked_in` 
ADD CONSTRAINT `worked_in_movie` 
FOREIGN KEY (`movie_id`) 
REFERENCES `movie`(`movie_id`);

ALTER TABLE `worked_in` 
ADD CONSTRAINT `worked_actor` 
FOREIGN KEY (`actor_id`) 
REFERENCES `actor`(`actor_id`);

ALTER TABLE `watched_by` 
ADD CONSTRAINT `watched_movie` 
FOREIGN KEY (`movie_id`) 
REFERENCES `movie`(`movie_id`);

ALTER TABLE `watched_by` 
ADD CONSTRAINT `watched_by_watcher` 
FOREIGN KEY (`watcher_id`) 
REFERENCES `watcher`(`watcher_id`);
