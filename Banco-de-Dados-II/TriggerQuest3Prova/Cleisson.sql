create table empregado(
    operacao varchar(3),
    usuario varchar(30) NOT NULL,
    data date,
    cpf char(12) NOT NULL,
    num_departamento smallint not null,
    nome varchar(30) NULL,
    data_nascimento date null,
    endereco varchar(40) null,
    sexo char(1) null,
    salario decimal(10,2) null,
    supervisor char(12) null
);

insert into empregado (usuario, num_departamento, salario, cpf) values ('UserMin', 01, 1000.0, '123');
insert into empregado (usuario, num_departamento, salario, cpf) values ('UserMax', 10, 20000.0, '321');
insert into empregado (usuario, num_departamento, salario, cpf) values ('UserTest1', 11, 21000.0, '213');
insert into empregado (usuario, num_departamento, salario, cpf) values ('UserTest2', 22, 800.0, '312');
insert into empregado (usuario, num_departamento, salario, cpf) values ('UserTest3', 33, 5000.0, '231');

create or replace FUNCTION faixa_salarial() returns trigger AS $$
    BEGIN
        if (NEW.salario < (select min(salario) from empregado)) then
            Raise notice 'salario abaixo do permitido';
            RETURN NULL;
        elseIF (NEW.salario > (select max(salario) from empregado)) then
            Raise notice 'Salario acima do permitido';
            RETURN NULL;
        else
            Raise notice 'Ação realizada com sucesso!';
        RETURN NEW;
        end IF;
    END; 
$$ LANGUAGE plpgsql;

create trigger manter_faixa_salarial before
insert on empregado for each row
execute procedure faixa_salarial
();