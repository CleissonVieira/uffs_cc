CREATE or REPLACE FUNCTION somefunc() RETURNS void AS $$
DECLARE
  quantity integer := 30;
BEGIN
  raise notice 'Quantidade é %', quantity;
END; $$
LANGUAGE plpgsql;

-----------------------------------------------------------------------

create table dados (
  name varchar(50),
  salary float,
  id int
);
insert into dados values ("xxx", 100, 1);
create function selecionar(p_itemno int)
  returns table (name varchar(50), salary float) as $$
begin
  return query select s.name, s.salary from dados as s
                    where s.id = p_itemno;
end;
$$language plpgsql

---------------------------------------------------------------------------

CREATE or REPLACE FUNCTION increment(x int) RETURNS void AS $$
DECLARE
  quantity integer := x + 1;
BEGIN
  raise notice 'Parametro + 1 = %', quantity;
END; $$
LANGUAGE plpgsql;

-----------------------------------------------------------------------------

create or replace function palavras(x varchar(20)) returns varchar as $$
BEGIN
  return x;
END; $$
LANGUAGE plpgsql;

--------------------------------------------------------------------------------



create table dado (id int , name varchar(50), age int ,
address varchar(50), salary float);
insert into dado values (1,'paulo',32, 'são miguel', 2000);
insert into dado values (2,'joao',22, 'chapeco', 2300);
insert into dado values (3,'maria',62, 'chapeco', 5300);
insert into dado values (2,'pedro',42, 'chapeco', 1300);

/*FUNÇÃO AUMENTO DE 10% NO SALÁRIO*/
create or replace function aumento () returns boolean as $$
  begin
    UPDATE dado SET salary = salary * 1.1;

    RETURN FOUND;
  end; $$
LANGUAGE plpgsql;

/*FUNÇÃO AUMENTO DE % SELECIONANDO O ID DESEJADO*/
create or replace function aumentox (p float, us int) returns boolean as $$
  begin
    p = p / 100;
    UPDATE dado SET salary = salary * p + salary where dado.id = us;

    RETURN FOUND;
  end; $$
LANGUAGE plpgsql;

/*FUNÇÃO ADICIONA CAMPO USUÁRIO E DATA ATUAL JUNTO A TABELA ANTERIOR*/
alter table dado add usuario varchar(50);
alter table dado add data date;

create or replace function usuarios () returns boolean as $$
  declare
    i record; --Serve para fazer o iterador do loop
  begin
    for i in select * from dado where dado.id >= 0
    loop
      UPDATE dado set usuario = current_user where dado.id = i.id;
      UPDATE dado set data = current_date where dado.id = i.id;
    end loop;

    RETURN FOUND;
  end; $$
LANGUAGE plpgsql;

------------------------------------------------------------------------------



--TABLE
CREATE TABLE emp (
 empname text,
 salary integer,
 last_date timestamp,
 last_user text
);

--FUNÇÃO ADD USER AND TIMESTAMP AND AUMENTA 10% SALARY
CREATE OR REPLACE FUNCTION emp_time() RETURNS trigger AS $$
 BEGIN
 NEW.last_date := current_timestamp;
 NEW.last_user := current_user;
 new.salary := 1.1 * new.salary;
 RETURN NEW;
 END;
$$ LANGUAGE plpgsql;

--TRIGGER
CREATE TRIGGER emp_time BEFORE INSERT OR UPDATE ON emp
 FOR EACH ROW EXECUTE PROCEDURE emp_time();

 CREATE TABLE emp_audit(
  operation varchar(1) ,
  stamp timestamp,
  username text ,
  empname text ,
  salary integer
 );

--NEW FUNCTION
CREATE OR REPLACE FUNCTION process_emp_audit() RETURNS TRIGGER
AS $$
 BEGIN
 IF (TG_OP = 'DELETE') THEN
   INSERT INTO emp_audit values ('D', now(), current_user, OLD.*);
   RETURN OLD;
 ELSIF (TG_OP = 'UPDATE') THEN
   INSERT INTO emp_audit SELECT 'U', now(), current_user, NEW.*;
   RETURN NEW;
 ELSIF (TG_OP = 'INSERT') THEN
    INSERT INTO emp_audit values ('I', now(), current_user, NEW.empname, NEW.salary);
    RETURN NEW;
  END IF;
  RETURN NULL;
 END;
$$ LANGUAGE plpgsql;

--TRIGGER DA FUNCTION
CREATE TRIGGER emp_audit
 AFTER INSERT OR UPDATE OR DELETE ON emp
 FOR EACH ROW EXECUTE PROCEDURE process_emp_audit();

----------------------------------------------------------------

--ATIVIDADE 1

create table empregado(
  id integer primary key,
  nome varchar(50),
  cpf varchar(15),
  Num_Departamento integer,
  Salario DECIMAL(10, 2),
  Supervisor varchar(50)
);

create table Auditoria(
  empregado_ID int,
  cpf varchar(12),
  Num_Departamento integer,
  Salario DECIMAL(10, 2),
  Supervisor varchar(50),
  evento int,
  usuario text,
  data date
);

CREATE OR REPLACE FUNCTION process_auditoria() RETURNS TRIGGER
AS $$
 BEGIN
 IF (TG_OP = 'DELETE') THEN
   INSERT INTO Auditoria values (OLD.id, OLD.cpf, OLD.Num_Departamento, OLD.Salario, OLD.Supervisor, 3, current_user, current_date);
   RETURN OLD;
 ELSIF (TG_OP = 'UPDATE') THEN
   INSERT INTO Auditoria SELECT NEW.id, NEW.cpf, NEW.Num_Departamento, NEW.Salario, NEW.Supervisor, 2, current_user, current_date;
   RETURN NEW;
 ELSIF (TG_OP = 'INSERT') THEN
    INSERT INTO Auditoria values (NEW.id, NEW.cpf, NEW.Num_Departamento, NEW.Salario, NEW.Supervisor, 1, current_user, current_date);
    RETURN NEW;
  END IF;
  RETURN NULL;
 END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER Auditoria
 AFTER INSERT OR UPDATE OR DELETE ON empregado
 FOR EACH ROW EXECUTE PROCEDURE process_auditoria();

----------------------------------------------------------------------------------------

--ATIVIDADE 2


---------------------------------------------------------------------------------------

--ATIVIDADE 3

---------------------------------------------------------------------------------------

-- VISÃO

create table aluno(
	alunoid int,
	nome varchar(50),
	idade varchar(2)
);

insert into aluno values (1, 'Um', 12), 
						 (2, 'Dois', 16),
						 (3, 'Tres', 18)
						 (4, 'Tres', 19);

--CRIA UMA COPIA DA TABELA ALUNO QUE ATUALIZA DE FORMA AUTOMÁTICA E PASSA OS DADOS DESEJADOS
create view aluno_mais_18 as select * from  aluno where idade > '17';
select * from aluno_mais_18;

--CRIA UMA COPIA DA TABELA ALUNO DOS DADOS DESEJADOS, A CADA NOVA INSERÇÃO PRECISA ATUALIZAR
create materialized view aluno_mais_18_mat as select * from  aluno where idade > '17';
refresh materialized view aluno_mais_18_mat;
select * from aluno_mais_18_mat;


--TESTANDO CRIAR VIEW COM JOIN
create table view10(
	viewid int,
	timid int
);

create table view20(
	joinid int,
	timid int
);

insert into view10 values (5, 10);
insert into view20 values (7, 10);

create view with_join as select * from view10 natural join view20;

--EXERCÍCIO 5
create table Projeto(
	codProj int,
	tipo varchar(20), 
	descricao varchar(50)
);‏
create table ProjetoEmpregado(
	codProj int, 
	codEmp int, 
	dataInicial date, 
	dataFinal date
);
create table Empregado(
	codEmp int, 
	nome varchar(20), 
	categoria varchar(20), 
	salario integer
);

Create view vAltoEscalao as   
select codEmp, nome, salario from empregado   where salario>10000

           --TERMINAR