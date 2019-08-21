


/*POSTGRES sem indice*/

/*OTIMIZADA*/
EXPLAIN ANALYZE SELECT first_name, last_name FROM actors JOIN roles on id = actor_id WHERE role = 'Han Solo';
/*NÃO OTIMIZADA*/
EXPLAIN ANALYZE SELECT first_name, last_name FROM (select * from actors, roles) as tabela 
where tabela.id = tabela.actor_id and role = (select distinct role from roles where role = 'Han Solo');


--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

/*POSTGRES com indice*/

/*OTIMIZADA*/
EXPLAIN ANALYZE SELECT * FROM movies_genres JOIN movies on id = movie_id WHERE name = 'Titanic';
/*NÃO OTIMIZADA*/
EXPLAIN ANALYZE SELECT genre FROM (select * from movies, movies_genres) as tabela 
WHERE name = (select distinct name from movies where name = 'Titanic') and tabela.id = tabela.movie_id;


--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

/*POSTGRES*/

/*OTIMIZADA*/
EXPLAIN ANALYZE SELECT directors.first_name, directors.last_name 
FROM directors join movies_directors on directors.id = movies_directors.director_id join movies on movies.id = movies_directors.movie_id 
WHERE movies.rank = (SELECT max(rank) from movies);
/*NÃO OTIMIZADA*/


