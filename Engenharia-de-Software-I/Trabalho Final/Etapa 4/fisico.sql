DROP DATABASE IF EXISTS onemorestep;

CREATE DATABASE onemorestep DEFAULT CHARACTER SET utf8 COLLATE utf8_general_ci;

USE onemorestep;

DROP USER IF EXISTS 'admOneMoreStep'@'localhost';

CREATE USER 'admOneMoreStep'@'localhost' IDENTIFIED BY '123456'; 

GRANT SELECT, INSERT, UPDATE, DELETE ON managermore.* TO 'admOneMoreStep'@'localhost';

create table GESTORES(
    CNPJempresa integer not null primary key,
    cpfGes integer not null,
    nomeGes varchar(30) not null,
    enderecoGes varchar(50) not null,
    emailGes varchar(50) not null,
    telefoneGes varchar(20) not null
);

create table TEC_EXTENSIONISTA(
    cpfTec integer not null primary key,
    nomeTec varchar(30) not null,
    enderecoTec varchar(50) not null,
    emailTec varchar(50) not null,
    telefoneTec varchar(20) not null,
    CNPJempresa integer not null,
    foreign key (CNPJempresa) references GESTORES (CNPJempresa)
);
 
create table CONSULTORES(
    cnpjCon integer not null primary key,
    cpfCon integer not null,
    nomeCon varchar(30) not null,
    enderecoCon varchar(50) not null,
    emailCon varchar(50) not null,
    telefoneCon varchar(20) not null
);

create table CHECKLISTS(
    idCheck integer auto_increment primary key,
    nomeFormulario varchar(30) not null,
    dataHora timestamp,
    CNPJempresa integer not null,
    cpfTec integer,
    cnpjCon integer,
    cnpj_or_cpf integer,
    foreign key (CNPJempresa) references GESTORES (CNPJempresa),
    foreign key (cpfTec) references TEC_EXTENSIONISTA (cpfTec),
    foreign key (cnpjCon) references CONSULTORES (cnpjCon)
);

create table LOCALV(
    idLocal integer auto_increment primary key,
    nomeLocal varchar(50) not null,
    cidade varchar(50) not null,
    bairro varchar(50) not null,
    rua varchar(50) not null,
    cep integer not null
);

create table VISITAS(
    idVisita integer auto_increment primary key,
    nomeVisita varchar(30) not null,
    dataHora timestamp,
    observacao varchar(100),
    cpfTec integer not null,
    idLocal integer not null,
    cnpjCon integer not null,
    foreign key (cpfTec) references TEC_EXTENSIONISTA (cpfTec),
    foreign key (idLocal) references LOCALV (idLocal),
    foreign key (cnpjCon) references CONSULTORES (cnpjCon)
);

create table EXECUTAR(
    idVisita integer not null,
    idCheck integer not null,
    foreign key (idVisita) references VISITAS (idVisita),
    foreign key (idCheck) references CHECKLISTS (idCheck)
);