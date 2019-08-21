/* Lógico_2: */

CREATE TABLE EMPRESA_DE_TURISMO (
    CNPJ_Matriz integer not null constraint pk_empresa primary key,
    Inscricao_Estadual integer not null,
    Nome_da_Empresa varchar (30 not null),
    FK_Telefone_Telefone_PK integer not null,
    Email varchar (50) not null,
    Endereco varchar (50) not null;
);

CREATE TABLE GUIA_DE_TURISMO (
    CPF integer not null constraint pk_guia primary key,
    Nome_do_a__Guia ,
    FK_Telefone_Telefone_PK,
    Email,
    Endereco,
    Percentual_de_comissao,
    FK_EMPRESA_DE_TURISMO_CNPJ_Matriz,
    FK_CIDADES_ABRANGENTES_Nome_da_Cidade
);

CREATE TABLE LOJISTAS_CLIENTES (
    CNPJ integer not null constraint pk_cliente primary key,
    Nome_do_Logista,
    CPF,
    RG,
    Razao_Social,
    Nome_Fantasia,
    Bairro,
    CEP,
    Rua,
    FK_Bancos_que_utiliza__Bancos_que_utiliza__PK,
    FK_CIDADES_ABRANGENTES_Nome_da_Cidade
);

CREATE TABLE CIDADES_ABRANGENTES (
    Nome_da_Cidade integer not null constraint pk_cidade primary key,
    Estado_UF,
);

CREATE TABLE SOFTWARE_DE_GERENCIAMENTO_PARA_EMPRESAS_DE_TURISMO (
);

CREATE TABLE SHOPPING (
    CNPJ,
    Nome,
    Endereco PRIMARY KEY,
    Atributo_5,
    FK_LOJAS_CNPJ
);

CREATE TABLE LOJAS (
    CNPJ PRIMARY KEY,
    Nome,
    Andar
);

CREATE TABLE Telefone (
    Telefone_PK INT NOT NULL PRIMARY KEY,
    Telefone,
    Telefone,
    Telefone,
    Telefone
);

CREATE TABLE Telefone (
    Telefone_PK INT NOT NULL PRIMARY KEY,
    Telefone,
    Telefone
);

CREATE TABLE Bancos_que_utiliza_ (
    Bancos_que_utiliza__PK INT NOT NULL PRIMARY KEY,
    Bancos_que_utiliza_
);

CREATE TABLE Comprar (
    FK_LOJISTAS_CLIENTES_CNPJ,
    FK_LOJAS_CNPJ,
    Valor_Total
);
 
ALTER TABLE EMPRESA_DE_TURISMO ADD CONSTRAINT FK_EMPRESA_DE_TURISMO_1
    FOREIGN KEY (FK_Telefone_Telefone_PK)
    REFERENCES Telefone (Telefone_PK)
    ON DELETE CASCADE ON UPDATE CASCADE;
 
ALTER TABLE GUIA_DE_TURISMO ADD CONSTRAINT FK_GUIA_DE_TURISMO_1
    FOREIGN KEY (FK_Telefone_Telefone_PK)
    REFERENCES Telefone (Telefone_PK)
    ON DELETE CASCADE ON UPDATE CASCADE;
 
ALTER TABLE GUIA_DE_TURISMO ADD CONSTRAINT FK_GUIA_DE_TURISMO_2
    FOREIGN KEY (FK_EMPRESA_DE_TURISMO_CNPJ_Matriz)
    REFERENCES EMPRESA_DE_TURISMO (CNPJ_Matriz)
    ON DELETE RESTRICT ON UPDATE RESTRICT;
 
ALTER TABLE GUIA_DE_TURISMO ADD CONSTRAINT FK_GUIA_DE_TURISMO_3
    FOREIGN KEY (FK_CIDADES_ABRANGENTES_Nome_da_Cidade)
    REFERENCES CIDADES_ABRANGENTES (Nome_da_Cidade)
    ON DELETE RESTRICT ON UPDATE RESTRICT;
 
ALTER TABLE LOJISTAS_CLIENTES ADD CONSTRAINT FK_LOJISTAS_CLIENTES_1
    FOREIGN KEY (FK_Bancos_que_utiliza__Bancos_que_utiliza__PK)
    REFERENCES Bancos_que_utiliza_ (Bancos_que_utiliza__PK)
    ON DELETE NO ACTION ON UPDATE NO ACTION;
 
ALTER TABLE LOJISTAS_CLIENTES ADD CONSTRAINT FK_LOJISTAS_CLIENTES_2
    FOREIGN KEY (FK_CIDADES_ABRANGENTES_Nome_da_Cidade)
    REFERENCES CIDADES_ABRANGENTES (Nome_da_Cidade)
    ON DELETE RESTRICT ON UPDATE RESTRICT;
 
ALTER TABLE SHOPPING ADD CONSTRAINT FK_SHOPPING_1
    FOREIGN KEY (FK_LOJAS_CNPJ)
    REFERENCES LOJAS (CNPJ)
    ON DELETE RESTRICT ON UPDATE RESTRICT;
 
ALTER TABLE Comprar ADD CONSTRAINT FK_Comprar_0
    FOREIGN KEY (FK_LOJISTAS_CLIENTES_CNPJ)
    REFERENCES LOJISTAS_CLIENTES (CNPJ)
    ON DELETE SET NULL ON UPDATE CASCADE;
 
ALTER TABLE Comprar ADD CONSTRAINT FK_Comprar_1
    FOREIGN KEY (FK_LOJAS_CNPJ)
    REFERENCES LOJAS (CNPJ)
    ON DELETE SET NULL ON UPDATE CASCADE;