drop table if exists reserve;
drop table if exists sailor;
drop table if exists boat;
drop table if exists tplevel;
drop table if exists tpboat;
drop table if exists tstatus;
--
create table tplevel (
  lid  integer not null constraint pk_tplevel primary key,
  dsc varchar(30) not null
);
create table sailor (
   sid  integer not null constraint pk_sailor primary key,
   name varchar(30) not null,
   email varchar(30) not null,
   dbirth date not null,
   level integer not null,
   constraint fk_sailor_tplevel foreign key (level) references tplevel(lid)
);
create table tpboat (
   tbid  integer not null constraint pk_tpboat primary key,
   tbdsc varchar(30) not null
);
create table tstatus (
    tsid integer not null constraint pk_tstatus primary key,
    tsdsc varchar(20) not null
);
create table boat (
   bid integer not null constraint pk_boat primary key,
   name varchar(20) not null,
   len  integer not null,
   horses integer not null,
   year integer not null,
   weight float not null,
   nsail integer not null,
   tbid   integer not null,
   tsboat integer not null,
   constraint fk_boat_tpboat foreign key (tbid) references tpboat(tbid),
   constraint fk_boat_tstatus foreign key (tsboat) references tstatus(tsid)
);
create table reserve (
   sid integer not null,
   bid integer not null,
   dtres timestamp not null,
   nhours float,
   constraint pk_reserve primary key (sid,bid,dtres),
   constraint fk_reserve_sailor foreign key (sid) references sailor(sid),
   constraint fk_reserve_boat foreign key (bid) references boat(bid)
);
      
insert into tplevel(lid,dsc) values (1,'Amateur'),(2,'Beginner'),
                                        (3,'Junior'),(4,'Professional'),(5,'Master'),(6, 'senior');
--
insert into sailor (sid,name,email,dbirth, level) values (1,'Almir Klink','klink@gmail.com','10/03/1963',5),
                                                         (2,'Lars Grael','grael@gmail.com','12/07/1970',5),
                                                         (3,'Robert Scheidt','scheidt@gmail.com','25/08/1971',5),
                                              	 	 (4,'Carinha','carinha@gmail.com','02/04/1983',3),
                                                   	 (5,'Alan Turing','turing@gmail.com','23/06/1912',1),
                                                  	 (6,'Edgar Codd','codd@gmail.com','23/08/1923',2),
						  	                                     (10,'Jack','jack@gmail.com','10/02/2000',2),
                                                         (15,'Chris','chrisy@gmail.com','07/08/1982',1),
                                                  	 (35,'Mary','mary@gmail.com','21/02/1994',4),
                                                         (45,'Amanda','amanda@gmail.com','17/11/1985',2),
                                                  	 (13,'John','john@gmail.com','01/09/1974',5),
                                                     (7, 'Alan Turing', 'turing@gmail.com', '23/06/1912', 6),
                                                     (8, 'Edgar Codd', 'codd@gmail.com', '23/08/1923', 5),
                                                     (9, 'Edsger Dijkstra', 'dijkstra@gmail.com', '11/05/1930', 3);
--
insert into tpboat (tbid,tbdsc) values (1,'catboat'),(2,'laser'),(3,'bowrider'),(4,'catmaran'),(5,'dinghy'),(6,'scooner'),(7, 'cutter');
--
insert into tstatus (tsid, tsdsc) values (1,'navegando'),(2,'estaleiro'),(3,'teste'),(4,'sucata');
--
insert into boat (bid, name,len,horses,year,weight,nsail,tbid, tsboat) 
                                             values (1,'Avante',23,15,2011,50,1,1,1), (2,'Furious',20,18,2015,45,1,1,3),
                                                    (3,'Sea',8,10,2012,20,1,2,1),  (4,'Faster',12,20,2016,27,1,2,3),
                                                    (5,'Collie',10,10,2016,100,0,3,1), (6,'Silver',5,45,2014,100,2,4,2),
						                                        (100,'Speed',20,50,2016,200,0,3,1),(200,'Smooth',10,35,2017,150,0,3,1),
						                                         (300,'Nail',10,30,2017,123,3,6,2),(400,'Vintage',25,60,2016,201,0,3,1),
                                                    (500,'Tomato',18,35,2017,45,1,1,1),(7, 'black shark', 40, 13, 2010, 100, 2, 7, 2),
                                                    (8, 'white swan', 34, 15, 2012, 85, 3, 6, 2),(9, 'arrow', 15, 20, 2013, 40, 1, 1, 1);
--
insert into reserve (bid,sid,dtres,nhours) values (1,1,'01/01/2013',13.5),(1,4,'05/01/2013',10.1),
                           (2,2,'02/02/2013',13.5),(2,5,'04/04/1936',7.6), (2,6,'06/07/1941',5.5),
                           (3,1,'10/03/2013',10.3),(3,3,'08/03/2013',14.5),(400,15,'10/10/2010',4),
                           (400,13,'12/10/2010',8),(100,10,'10/10/2010',2),(300,35,'10/10/2010',3),
                           (200,15,'13/10/2010',NULL),(500,13,'13/10/2010',NULL),(1,3,'10/03/2013',NULL),
                           (400,45,'13/10/2010',NULL),(100,35,'12/10/2010',8);   

