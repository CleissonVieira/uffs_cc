DROP TABLE IF EXISTS  actors ;
CREATE TABLE IF NOT EXISTS  actors  (
   id  int NOT NULL DEFAULT 0,
   first_name  varchar(100) DEFAULT NULL,
   last_name  varchar(100) DEFAULT NULL,
   gender  char(1) DEFAULT NULL,
  PRIMARY KEY ( id )
);

DELETE FROM  actors ;



DROP TABLE IF EXISTS  directors ;
CREATE TABLE IF NOT EXISTS  directors  (
   id  int NOT NULL DEFAULT 0,
   first_name  varchar(100) DEFAULT NULL,
   last_name  varchar(100) DEFAULT NULL,
  PRIMARY KEY ( id )
);

CREATE INDEX directors_first_name
ON directors(first_name);

CREATE INDEX directors_last_name
ON directors(last_name);

DELETE FROM  directors ;



DROP TABLE IF EXISTS  directors_genres ;
CREATE TABLE IF NOT EXISTS  directors_genres  (
   director_id  int NOT NULL,
   genre  varchar(100) NOT NULL,
   prob  float DEFAULT NULL,
  PRIMARY KEY ( director_id , genre ),
  CONSTRAINT  directors_genres_ibfk_1  FOREIGN KEY ( director_id ) REFERENCES  directors  ( id ) ON DELETE CASCADE ON UPDATE CASCADE
);
CREATE INDEX directors_genres_director_id
ON directors_genres(director_id);

DELETE FROM  directors_genres ;



DROP TABLE IF EXISTS  movies ;
CREATE TABLE IF NOT EXISTS  movies  (
   id  int NOT NULL DEFAULT 0,
   name  varchar(100) DEFAULT NULL,
   year  int DEFAULT NULL,
   rank  float DEFAULT NULL,
  PRIMARY KEY ( id )
);
CREATE INDEX movies_name 
ON movies(name);

DELETE FROM  movies ;



DROP TABLE IF EXISTS  movies_directors ;
CREATE TABLE IF NOT EXISTS  movies_directors  (
   director_id  int NOT NULL,
   movie_id  int NOT NULL,
  PRIMARY KEY ( director_id , movie_id ),
  CONSTRAINT  movies_directors_ibfk_1  FOREIGN KEY ( director_id ) REFERENCES  directors  ( id ) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT  movies_directors_ibfk_2  FOREIGN KEY ( movie_id ) REFERENCES  movies  ( id ) ON DELETE CASCADE ON UPDATE CASCADE
);
CREATE INDEX movies_directors_director_id 
ON movies_directors(director_id);
CREATE INDEX movies_directors_director_id 
ON movies_directors(movie_id);

DELETE FROM  movies_directors ;



DROP TABLE IF EXISTS  movies_genres ;
CREATE TABLE IF NOT EXISTS  movies_genres  (
   movie_id  int NOT NULL,
   genre  varchar(100) NOT NULL,
  PRIMARY KEY ( movie_id , genre ),
  CONSTRAINT  movies_genres_ibfk_1  FOREIGN KEY ( movie_id ) REFERENCES  movies  ( id ) ON DELETE CASCADE ON UPDATE CASCADE
);
CREATE INDEX movies_genres_movie_id  
ON movies_genres(movie_id);

DELETE FROM  movies_genres ;



DROP TABLE IF EXISTS  roles ;
CREATE TABLE IF NOT EXISTS  roles  (
   actor_id  int NOT NULL,
   movie_id  int NOT NULL,
   role  varchar(100) NOT NULL,
  PRIMARY KEY ( actor_id , movie_id , role ),
  CONSTRAINT  roles_ibfk_1  FOREIGN KEY ( actor_id ) REFERENCES  actors  ( id ) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT  roles_ibfk_2  FOREIGN KEY ( movie_id ) REFERENCES  movies  ( id ) ON DELETE CASCADE ON UPDATE CASCADE
);


DELETE FROM  roles ;