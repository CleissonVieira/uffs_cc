#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

// estrutura de cabeçalho
typedef struct Header {
    int memFree; // limpar memoria da pagina
    int next; // indica onde sera inserido o proximo elemento na página
    int qtdItems; // quantidade de itens
} header;

typedef struct Item {
    int offset;
    int totalLen; // tamanho total do elemento 
    int writed; 
} item;

typedef struct Attribute { // atributo da tabela sql, coluna da tabela sql
    char name[15]; // nome da coluna da tabela sql
    int size; // tamanho da coluna da tabela sql
    char type; //tipo da coluna da tabela sql = int, char e varchar
} attribute;

void getTableName(char *sql, char *name);

void buildHeader(char *sql, char *tableName, int qtdPages);

void getAllAtributes(char *sql, char *attributes);

void leArquivo(char *tableName);

/**
 * Separa a operação do restante da string SQL 
 * - select ou
 * - create ou
 * - insert ou
 * - delete
 */
void getOp(char *sql, char *operation) {
    char sqlCopy[1000], *token;
    char key[2] = " ";

    memset(sqlCopy, '\0', sizeof(sqlCopy));

    strcpy(sqlCopy, sql);

    token = strtok(sqlCopy, key);

    strcpy(operation, token);
}

void createPage(char *tableName, int numPage) {
    //cria pagina no disco com tamanho de 8kb
  	header head;
    head.memFree = 8180; // quantidade de memória livre na página
	head.next = 8191; // usado na criação do arquivo da pagina, para indicar onde sera inserido o proximo elemento
    head.qtdItems = 0; //usado na criação do arquivo da pagina, incialemnte cria a pagina zerada

  	struct stat stateDir = {0};

    char pageName[600]; 

    //printf("tableName: %s\n\n", tableName);
    //printf("NumPage: %d\n\n", numPage);

  	//define o nome da pagina na variavel pageName, com base nos parametros informados na função
    snprintf(pageName, sizeof(pageName), "%s/page%d.dat", tableName, numPage); 

    FILE *page = fopen(pageName, "wb"); //cria o arquivo da pagina no modo de escrita binária
    fwrite(&head.memFree, sizeof(int), 1, page);  // free
    fwrite(&head.next, sizeof(int), 1, page);     // onde inserir o proximo elemento
    fwrite(&head.qtdItems, sizeof(int), 1, page);// n elementos
    fclose(page); // fecha o arquivo
    
  	if(page == NULL) { //caso tenha ocorrido algum erro na criação da pagina
        printf("Failed to create page\n");
        return;
    }
}


void createTable(char *sql) {
	// cria cabeçalho da página
    header head;
    head.memFree = 8180; // 8kb
    head.next = 8191; // próxima página
    head.qtdItems = 0; // qtd de registros da tabela

	// delimitador de fim da página
    char special = '0';

    struct stat stateDir = {0};

	char tableName[500]; // define nome da tabela com 500 caracteres
  	char pageName[600]; // define nome da página com 500 caracteres
  	memset(tableName, '\0', sizeof(tableName)); // '\0' apos nome da tabela

	getTableName(sql, tableName); // pega o nome da tabela

	// status do arquivo -1 = tabela não existe
  	if(stat(tableName, &stateDir) == -1) {
        
		// cada tabela do banco é armazenada em um diretório com seu nome
      	if(mkdir(tableName, 0777) == 0)
            printf("Created table %s\n", tableName);
		 
        // cria arquivo do cabeçalho da tabela
        snprintf(pageName, sizeof(pageName), "%s/header.dat", tableName);
      	FILE *headerPage = fopen(pageName, "wb");
        fclose(headerPage);
        
	    // cria arquivo de página da tabela
      	snprintf(pageName, sizeof(pageName), "%s/page1.dat", tableName);  
      	FILE *page = fopen(pageName, "wb");
        fwrite(&head.memFree, sizeof(int), 1, page);  // quantidade de memória disponível
        fwrite(&head.next, sizeof(int), 1, page);     // onde inserir o proximo elemento
        fwrite(&head.qtdItems, sizeof(int), 1, page); // n elementos
        
      	// insere caracter especial ao final da página para indicar fim de página
      	// especial = '0'
      	fseek(page, 8191, SEEK_SET);
        fwrite(&special, 1, 1, page);
      	fclose(page);
        
      	if(page == NULL) {
            printf("Failed to create page\n");
            return;
        }
	
    	buildHeader(sql, tableName, 1);
    } else {
        printf("Table %s already created\n", tableName);
    }
}


void buildHeader(char *sql, char *tableName, int qtdPages) {
    char fieldName[15], fieldType; //nome e tipo do campo
    int fieldSize, i = 0; //tamanho do campo e variavel auxiliar

    char sqlCopy[1000], attribute[50], pageName[600];  
    char *token, *tokenAttribute;

    memset(fieldName, '\0', sizeof(fieldName));  //limpa a string do field name

    strcpy(sqlCopy, sql); //cria um arquivo auxiliar para o script sql

    snprintf(pageName, sizeof(pageName), "%s/header.dat", tableName); //define o nome do arquvio de cabeçalho
    FILE *headerPage = fopen(pageName, "rb+"); //instancia o arquvio de cabeçalho em modo de escrita e leitura

    fwrite(&i, sizeof(int), 1, headerPage); //escreve o conteudo de i (0) no inicio do arquivo de cabeçalho   

	// encontra o primeiro parentese na string SQL para e separa em tokens
	// após o primeiro parentese estarão as definições de atributos da tabela
  	// ex: ( int id, varchar nome )
    token = strtok(sqlCopy, "(");  
    token = strtok(NULL, "()[], "); 

    while(token != NULL) { // enquanto existir tokens
    
        if(strcmp(token, "char") == 0) { // compara se o token é um char
            fieldType = 'C'; // define o tipo do atributo como C
            token = strtok(NULL, "()[], "); // busca o proximo token com o tamanho do atributo char 
            fieldSize = atoi(token); // converte o token com o tamanho do campo para int
            token = strtok(NULL, "()[], "); // pega o proximo token 
            strcpy(fieldName, token); // copia o nome do atributo para o fieldName
            fwrite(fieldName, 15, 1, headerPage); //escreve no arquivo de cabeçalho o nome do atributo (coluna da tabela sql)
            fwrite(&fieldSize, sizeof(int), 1, headerPage); // escreve no arquivo o tamanho, em bytes, do atributo sql
            fwrite(&fieldType, 1, 1, headerPage); // escreve o tipo do atributo sql no arquivo de cabeçalho
            i++;
          
        } else if(strcmp(token, "int") == 0) { // compara se é int
            fieldType = 'I'; // tipo do atributo 
            token = strtok(NULL, "()[], "); // move para o proximo token
            fieldSize = sizeof(int); // tamanho do atributo igual a o tamanho de um inteiro, 4bytes
            strcpy(fieldName, token); // nome do atributo
            fwrite(fieldName, 15, 1, headerPage); // escreve o nome do atributo 
            fwrite(&fieldSize, sizeof(int), 1, headerPage); // escreve o tamanho do arquivo
            fwrite(&fieldType, 1, 1, headerPage); // escreve o tipo do arquivo
            i++;
        } else if(strcmp(token, "varchar") == 0) { // compara se é varchar
            fieldType = 'V'; // tipo do atributo 
            token = strtok(NULL, "()[], "); // procura o token com o tamanho do atributo
            fieldSize = atoi(token); // seta o tamanho do atributo com base no token encontrado
            token = strtok(NULL, "()[], "); // procura o token com o nome do atributo
            strcpy(fieldName, token); // seta o fieldName com o token de nome
            fwrite(fieldName, 15, 1, headerPage); // escreve o nome
            fwrite(&fieldSize, sizeof(int), 1, headerPage); // escreve o tamanho do atributo
            fwrite(&fieldType, 1, 1, headerPage); // escreve o tipo do atributo
            i++;
        }
        token = strtok(NULL, "()[], "); // procura o fechamento do script create table
    }

    fwrite(&qtdPages, sizeof(int), 1, headerPage); // escreve no arquivo de cabeçalho, a quantidade de paginas daquela tabela 
    fseek(headerPage, 0, SEEK_SET); // move o ponteiro do arquivo para o inicio
    fwrite(&i, sizeof(int), 1, headerPage); // escreve o numero de atributos daquela tabela
    fclose(headerPage); // fecha o arquivo de cabeçalho

	leArquivo(tableName); // le o arquivo daquela tabela
}


//************************************ PAMELA PAMELA PAMELA PAMELA PAMELA PAMELA PAMELA PAMELA

void insertInto(char *sql, int numPage) { 
    char sqlCopy[1000], *token, tableName[500], pageName[600], attrSql[1000], attrSqlCopy[1000];
    char endVarchar = '$', special = ' ', endChar = '\0';
    int insertSize = 0, qtdFields, nextItem, intVar, nextPage, qtdEndChar = 0;
    int i = 0, countVarchar = 0;
    attribute attributes[64];
    header head;

    memset(sqlCopy, '\0', sizeof(sqlCopy)); //limpa a variavel que sera usada na copia do script sql
    strcpy(sqlCopy, sql); // script sql

    token = strtok(sqlCopy, " () ,"); // quebra o script sql em tokens
                                    //como se fosse um vetor 

    while(token != NULL) { // enquanto existirem tokens
        if(i == 2) // i == 2, o token vai ser o nome da tabela
            strcpy(tableName, token); // insert[0], into[1], aluno[2]
        token = strtok(NULL, " () ,"); // token atual = Null, realizar o loop
        i++;
    }

    // define o caminho para o cabeçalho da tabela, pageName = "tableName/header.dat"
    snprintf(pageName, sizeof(pageName), "%s/header.dat", tableName);
    
    
    FILE *headerPage = fopen(pageName, "rb+"); // abre o arquivo de cabeçalho
                                        //do caminho definido acima
                                        
	// Lê as colunas da tabela, 4 primeiros bytes do arquivo informa quant de campos/colunas/atributos
  	fread(&qtdFields, sizeof(int), 1, headerPage);

	// Lê o cabeçalho da tabela e armazena (salvar, tam bytes lido, quant tam ler, de onde ler)
    for(int i = 0; i < qtdFields; i++) {
        fread(attributes[i].name, 15, 1, headerPage);
        fread(&attributes[i].size, sizeof(int), 1, headerPage);
        fread(&attributes[i].type, 1, 1, headerPage);
    }

  	// procura no arquivo o caminho da proxima pagina (pronto próx insert)
    fread(&nextPage, sizeof(int), 1, headerPage);
  	fclose(headerPage); // fecha o cabeçalho

    strcpy(sqlCopy, sql); // faz uma nova cópia do script sql pra pegar os valores
    token = strtok(sqlCopy, "()"); // procura os valores da inserção (chega até os valores)
    token = strtok(NULL, "()"); // continua a busca de onde parou na chamada acima
                                // deixa em token os valores da inserção

//************************************ PAMELA PAMELA PAMELA PAMELA PAMELA PAMELA PAMELA PAMELA

//************************************ CLEISSON CLEISSON CLEISSON CLEISSON CLEISSON CLEISSON 

    memset(attrSql, '\0', sizeof(attrSql)); //limpa a variavel e seta o final dela
    memset(attrSqlCopy, '\0', sizeof(attrSqlCopy)); // limpa a variável e seta o final dela

    strcpy(attrSql, token); //copia o token de atributo para a variavel attrSql
    strcpy(attrSqlCopy, attrSql); // faz uma copia da variavel attrSql

    token = strtok(attrSqlCopy, ","); // quebra o token de atributos usando o delimitador de virgula

   	// incrementa o tamanho do insert baseado no tipo dos atributos inseridos
  	for(int i = 0; i < qtdFields; i++) {     	
      	if(attributes[i].type == 'C') {
            insertSize += attributes[i].size;
        } else if(attributes[i].type == 'I') {
            insertSize += attributes[i].size;
        } else if(attributes[i].type == 'V') {
            insertSize += strlen(token) + 1; // + 1 for special char of varchar '$'
            //countVarchar
        }
        token = strtok(NULL, ","); //próximo valor da inserção
    }

    strcpy(attrSqlCopy, attrSql); 

    //define o caminho da pagina com os registros da tabela "aluno/page1.dat"
    snprintf(pageName, sizeof(pageName), "%s/page%d.dat", tableName, numPage);

    FILE * page = fopen(pageName, "rb+"); // abre a pagina como modo de leitura e escrita binaria

    fread(&head.memFree, sizeof(int), 1, page); // quanto de espaço livre tem disponível naquela pagina
    fread(&head.next, sizeof(int), 1, page); // próxima 
    fread(&head.qtdItems, sizeof(int), 1, page); // quantidade de itens naquela pagina
    
  	// se valores inseridos forem menores que o espaço livre na página, insere na mesma página
    if(head.memFree > insertSize) {
        token = strtok(attrSqlCopy, ","); // separa os valores a serem inseridos 
        item newItem;                     
        newItem.offset = head.next - insertSize; // começo da page onde será inserido, a cabeça da inserção
        newItem.totalLen = insertSize;  // Tamanho total que precisa para inserir todos os elementos
        newItem.writed = 1; // se 1 valor existe, se 0 deletado

      	// calcula posição do próximo valor no cabeçalho da página 12 (header) + 12 (cada item vai ter 12 (deslocamento, tamanho e escrita)  
        nextItem = 12 + 12 * head.qtdItems; // 

		// move ponteiro do arquivo para posição do próximo valor no cabeçalho da página
        fseek(page, nextItem, SEEK_SET); //


		// insere informações do insert no cabeçalho da página
      	fwrite(&newItem.offset, sizeof(int), 1, page);
        fwrite(&newItem.totalLen, sizeof(int), 1, page);
        fwrite(&newItem.writed, sizeof(int), 1, page);

        //printf("OFFSET NEW ITEM: %d\n", newItem.offset);

//************************************ CLEISSON CLEISSON CLEISSON CLEISSON CLEISSON CLEISSON 

//************************************ ANTHONY ANTHONY ANTHONY ANTHONY ANTHONY ANTHONY ANTHONY

        fseek(page, newItem.offset, SEEK_SET);

      	// percorre os campos do inser
        for(int i = 0; i < qtdFields; i++) {

            // char
      		if(attributes[i].type == 'C') {
                fwrite(token, strlen(token), 1, page);
                qtdEndChar = attributes[i].size - strlen(token);
                fwrite(&endChar, 1, qtdEndChar, page); // endChar final da inserção, bytes que sobra fica lixo
              
            // int
            } else if(attributes[i].type == 'I') {
                intVar = atoi(token); // converte string com valor para inteiro
                fwrite(&intVar, attributes[i].size, 1, page); // insere na page
              
            // varchar
            } else if(attributes[i].type == 'V') {
                fwrite(token, strlen(token), 1, page);
                fwrite(&endVarchar, 1, 1, page);
            }
            token = strtok(NULL, ",");
        }

        head.memFree = head.memFree - insertSize;
        head.next = newItem.offset;
        head.qtdItems += 1;

        fseek(page, 0, SEEK_SET);

        fwrite(&head.memFree, sizeof(int), 1, page);
        fwrite(&head.next, sizeof(int), 1, page);
        fwrite(&head.qtdItems, sizeof(int), 1, page);

        fclose(page);

        printf("New item inserted\n");
    } else {
      	// cria uma nova pagina
        fseek(page, 8191, SEEK_SET); // move até penultimo byte da page
        fread(&special, 1, 1, page); // atribui último byte a special
        //printf("Special: %c\n", special);
        if(special == '0') { // se 0 não tem mais páginas
            //printf("Entrou special\n");
            nextPage++;
            //printf("Nome Pagina: %s\n", tableName);
            //printf("Numero pagina: %d\n", nextPage);
            //printf("SQL - %s\n", sql);
            createPage(tableName, nextPage); // cria uma nova page
            special = '1'; 
            fseek(page, 8191, SEEK_SET); 
            fwrite(&special, 1, 1, page); // escreve último byte como 1 indicando que existe próx page
            fclose(page); 
            insertInto(sql, nextPage);
        } else { // exite outra page, passa próx page e insere
            fclose(page);
            insertInto(sql, nextPage);
        }
    //************************************ ANTHONY ANTHONY ANTHONY ANTHONY ANTHONY ANTHONY ANTHONY
    }
}


/**
 *	retorna o nome da tabela
 */
void getTableName(char *sql, char *name) {
    char sqlCopy[1000];
    char *token;
    char keyParen[2] = "(";
    char keySpace[2] = " ";

    memset(sqlCopy, '\0', sizeof(sqlCopy));

    strcpy(sqlCopy, sql);

    token = strtok(sqlCopy, keyParen);

    strcpy(sqlCopy, token);

    token = strtok(sqlCopy, keySpace);

    while(token != NULL) {
        strcpy(name, token);
        token = strtok(NULL, keySpace);
    }
}

/**
 * lê cabeçalho da primeira página da tabela
 */
void leArquivo(char *tableName) {
    char pageName[600];
    char pageCoisa[600];

    snprintf(pageCoisa, sizeof(pageCoisa), "%s/page1.dat", tableName); //define o caminho da pagina de determinada tabela

    FILE *page = fopen(pageCoisa, "rb+"); // abre a pagina da tabela como leitura e escrita binária

    header head; 

    fread(&head.memFree, sizeof(int), 1, page);
    fread(&head.next, sizeof(int), 1, page);
    fread(&head.qtdItems, sizeof(int), 1, page);
    //printf("MemFree - %d; Next - %d - QtdItems - %d\n", head.memFree, head.next, head.qtdItems);

    fclose(page); // fecha a página
}


void selectFrom(char *sql, int numPage) {
    char tableName[50], sqlCopy[1000], pageName[600], *token, charInFile, special = ' ';
    int i = 0, qtdFields = 0, moveItem = 0, moveTupla = 0, intInFile, stopChar;

    item readItem;
    attribute attributes[64];

    memset(sqlCopy, '\0', sizeof(sqlCopy));

    strcpy(sqlCopy, sql);

    token = strtok(sqlCopy, " "); // separa o script em sql usando o espaço como delimitador

    while(token != NULL) { // procura o nome da tabela
        // Se i == 3 então o token vai ser igual o nome da tabela
        if(i == 3) {
            token = strtok(token, "\n");
            strcpy(tableName, token);
        } else
            token = strtok(NULL, " "); 
        i++;
    }

    //printf("\nTable selected - %s\n", tableName);

    snprintf(pageName, sizeof(pageName), "%s/header.dat", tableName); // procura o arquivo do cabeçalho da tabela

    FILE *headerPage = fopen(pageName, "rb+"); // abre o arquivo do cabeçalho da tabela
    if(!headerPage) { // caso nao consiga abrir
        printf("Can not read %s/header.dat\n", tableName);
    }

    fread(&qtdFields, sizeof(int), 1, headerPage); // le a quantidade de campos

    //printf("Quantidade de campos: %d\n", qtdFields);

    for(int i = 0; i < qtdFields; i++) { // laço percorrendo a quantidade de campos (sempre vai imprimir todos os campos)
        fread(attributes[i].name, 15, 1, headerPage); // lê o nome do campo no cabeçalho
        printf("%s\t", attributes[i].name); // printa o nome do campo + tab
        fread(&attributes[i].size, sizeof(int), 1, headerPage); // le o tamanho do campo
        fread(&attributes[i].type, 1, 1, headerPage); // le o tipo do campo
    }
    printf("\n");

    fclose(headerPage);

    snprintf(pageName, sizeof(pageName), "%s/page%d.dat", tableName, numPage); // define o nome da pagina da tabela
    FILE *page = fopen(pageName, "rb+"); // abre a pagina da tabela em modo de leitura e escrita binaria

    header head;

    item items;
    fread(&head.memFree, sizeof(int), 1, page); // verifica o espaço disponivel da pagina
    fread(&head.next, sizeof(int), 1, page); // verifica onde termina a pagina
    fread(&head.qtdItems, sizeof(int), 1, page); // verifica o numero de registros da pagina

    //printf("memFree: %d - next: %d - qtdItems: %d\n", head.memFree, head.next, head.qtdItems);

    for(int i = 0; i < head.qtdItems; i++) { // laço para percorrer os itens
        fseek(page, 0, SEEK_SET); // posiciona no inicio da pagina
        moveItem = sizeof(item) * (i + 1); // define o tamanho de cada registro
        fseek(page, moveItem, SEEK_SET); // vai para o final do registro 

        fread(&readItem.offset, sizeof(int), 1, page); // le o offset do registro
        fread(&readItem.totalLen, sizeof(int), 1, page); // tamanho total do registro
        fread(&readItem.writed, sizeof(int), 1, page); // se tem algo escrito naquele registro

        //printf("offset: %d - totalLen: %d - writed: %d\n", readItem.offset, readItem.totalLen, readItem.writed);

        if(readItem.writed == 0) // se o writed estiver setado como 0, então naquele registro nada foi escrito ainda
            continue;

        fseek(page, readItem.offset, SEEK_SET); // posiciona no offset do item

      	// percorre os campos da tabela
        for(int j = 0; j < qtdFields; j++) {  
			// se o atributo for char
          	if(attributes[j].type == 'C') { 
                charInFile = ' '; // seta a variavel com espaço em branco
                stopChar = 0; // delimitador indicando se chegou no fim do campo char
                for(int k = 0; k < attributes[j].size; k++) { //laço para percorer o registro do char
                    fread(&charInFile, 1, 1, page); 
                    if(charInFile == '\0') // caracter indicando o final do campo char
                        stopChar = 1; 
                    if(!stopChar) // caso nao tenha chegado no fim do arquivo
                        printf("%c", charInFile); //imprime caracter por caracter
                }
                printf("\t"); // imprime tab

          	// se o atributo for int
            } else if(attributes[j].type == 'I') {
                fread(&intInFile, sizeof(int), 1, page);
                printf("%d\t", intInFile);
            // se o atributo for varchar
            } else if(attributes[j].type == 'V') {
                charInFile = ' ';
              	// printa caracater a caracter até encontrar $, q delimita o fim de varchar
                do {
                    fread(&charInFile, 1, 1, page);
                    if(charInFile != '$')
                        printf("%c", charInFile);
                } while(charInFile != '$');
                printf("\t");
            }
        }
        printf("\n");
    }
    fseek(page, 8191, SEEK_SET); //posiciona no final do arquivo 
    fread(&special, 1, 1, page); // le o caracter special
    if(special == '1') { // se for igual a 1, significa que ainda existe pagina
        numPage++; 
        selectFrom(sql, numPage); //continua o select na(s) proxima(s) pagina(s)
    } else
        fclose(page); // fecha a pagina
}


void deleteFrom(char *sql, int numPage) {
    char tableName[50], sqlCopy[1000], pageName[600], *token, charInFile, attributeName[20], intInput[20], special = ' ';
    int i = 0, k = 0, qtdFields = 0, moveItem = 0, moveTupla = 0, intInFile, stopChar, delete = 0, inputDelete, count = 0;

    item readItem;
    attribute attributes[64];

    memset(sqlCopy, '\0', sizeof(sqlCopy));

    strcpy(sqlCopy, sql);

    token = strtok(sqlCopy, " ");

    while(token != NULL) { ////enquanto existir token
        // Se i == 2, o token vai ser o nome da tabela
        if(i == 2) {
            strcpy(tableName, token);
        } else if(i == 5) { // se i == 5, é o atributo a ser comparado na clausula where
            strcpy(attributeName, token);
        } else if(i == 8) { 
            break;
        } else
            token = strtok(NULL, " ");
        i++;
    }
    token = strtok(token, "\n");

    //printf("\nTable selected - %s\n", tableName);
    //printf("\nAttribute selected - %s\n", attributeName);
    //printf("\nAttribute value - %s\n", token);


    snprintf(pageName, sizeof(pageName), "%s/header.dat", tableName); //define o caminho do arquivo de cabeçalho da tabela

    FILE *headerPage = fopen(pageName, "rb+"); //abre o arquivo em modo de leitura e escrita binária
    if(!headerPage) { //se não conseguiu abrir o arquivo de cabeçalho
        printf("Can not read %s/header.dat\n", tableName);
    }

    fread(&qtdFields, sizeof(int), 1, headerPage); // le o numero de campos daquela tabela

    for(int i = 0; i < qtdFields; i++) { //laço para percorrer os campos e salvar suas informações (nome, tamanho, tipo)
        fread(attributes[i].name, 15, 1, headerPage);
        fread(&attributes[i].size, sizeof(int), 1, headerPage);
        fread(&attributes[i].type, 1, 1, headerPage);
    }
    printf("\n");

    fclose(headerPage);

    snprintf(pageName, sizeof(pageName), "%s/page%d.dat", tableName, numPage); //define o caminho da página da tabela
    FILE *page = fopen(pageName, "rb+"); // abre a pagina 

    header head;

    item items;
    fread(&head.memFree, sizeof(int), 1, page); // espaço disponivel na pagina
    fread(&head.next, sizeof(int), 1, page); // posição da proxima pagina
    fread(&head.qtdItems, sizeof(int), 1, page); // quantidade de itens na pagina

    for(int i = 0; i < head.qtdItems; i++) {
        fseek(page, 0, SEEK_SET); // posiciona no inicio do arquivo
        moveItem = sizeof(item) * (i + 1); // define a posição do item
        fseek(page, moveItem, SEEK_SET); // posiciona o ponteiro do arquivo no item

        fread(&readItem.offset, sizeof(int), 1, page); // le e armazena o offset 
        fread(&readItem.totalLen, sizeof(int), 1, page);
        fread(&readItem.writed, sizeof(int), 1, page);

        if(readItem.writed == 0)
            continue;

        fseek(page, readItem.offset, SEEK_SET);

        for(int j = 0; j < qtdFields; j++) {
            delete = 1;
            if(attributes[j].type == 'C') {
                charInFile = ' ';
                stopChar = 0;
                if(j > 0)
                    fread(&charInFile, 1, 1, page); // Read '\0' varchar
              	// percorre até o final do valor('\0' delimita fim do char)
                for(int l = 0; l < attributes[j].size; l++) {
                    fread(&charInFile, 1, 1, page);
                    if(delete == 1 && charInFile == '\0')
                        stopChar = 1;
                    //printf("%c = %c\n", charInFile, token[l]);
                    if(charInFile != token[l] && !stopChar)
                        delete = 0;
                }
                if(delete && !(strcmp(attributeName, attributes[j].name))) {
                    fseek(page, moveItem, SEEK_SET);
                    readItem.writed = 0;
                    fwrite(&readItem.offset, sizeof(int), 1, page);
                    fwrite(&readItem.totalLen, sizeof(int), 1, page);
                    fwrite(&readItem.writed, sizeof(int), 1, page);
                    printf("Attribute deleted\n");
                    count++;
                    break;
                } else if(j > 0)
                    fseek(page, -1, SEEK_CUR); // Read '\0' varchar
            } else if(attributes[j].type == 'I') {
                if(j > 0)
                    fread(&charInFile, 1, 1, page); // Read '\0' varchar
              
                fread(&intInFile, sizeof(int), 1, page);
                //printf("From file: %d\n", intInFile);
                inputDelete = atoi(token);
                if(intInFile != inputDelete)
                    delete = 0;
                if(delete && !(strcmp(attributeName, attributes[j].name))) {
                    fseek(page, moveItem, SEEK_SET);
                    readItem.writed = 0;
                    fwrite(&readItem.offset, sizeof(int), 1, page);
                    fwrite(&readItem.totalLen, sizeof(int), 1, page);
                    fwrite(&readItem.writed, sizeof(int), 1, page);
                    printf("Attribute deleted\n");
                    count++;
                    break;
                } else if(j > 0)
                    fseek(page, -1, SEEK_CUR); // Read '\0' varchar
            } else if(attributes[j].type == 'V') {
                k = 0;
                if(j > 0)
                    fread(&charInFile, 1, 1, page); // Read '\0' varchar
                while(charInFile != '$') {
                    fread(&charInFile, 1, 1, page);
                    //printf("%c = %c\n", charInFile, token[k]);
                    if(delete == 1 && charInFile == '$')
                        break;
                    if(charInFile != token[k])
                        delete = 0;
                    k++;
                }
                if(delete && !(strcmp(attributeName, attributes[j].name))) {
                    fseek(page, moveItem, SEEK_SET);
                    readItem.writed = 0;
                    fwrite(&readItem.offset, sizeof(int), 1, page);
                    fwrite(&readItem.totalLen, sizeof(int), 1, page);
                    fwrite(&readItem.writed, sizeof(int), 1, page);
                    printf("Attribute deleted\n");
                    count++;
                    break;
                } else if(j > 0)
                    fseek(page, -1, SEEK_CUR); // Read '\0' varchar
            }
        }
        fseek(page, 0, SEEK_SET);
    }
    printf("Attributes deleted = %d\n", count);
    fseek(page, 8191, SEEK_SET);
    fread(&special, 1, 1, page);
    if(special == '1') {
        numPage++;
        fclose(page);
        deleteFrom(sql, numPage);
    } else
        fclose(page);
    //fclose(page);
}

int main() {
    char sql[1000], operation[10], attributes[500];

    do {
        printf(">> ");
        fgets(sql, 1000, stdin);
        getOp(sql, operation); //Pega a operação a ser realizada (create, insert, delete)

        if(strcmp(operation, "create") == 0) {
            createTable(sql);
        } else if(strcmp(operation, "delete") == 0) {
            deleteFrom(sql, 1);
        } else if(strcmp(operation, "insert") == 0) {
            insertInto(sql, 1);
        } else if(strcmp(operation, "select") == 0) {
            selectFrom(sql, 1);
        } else {
            printf("Something went wrong");
        }
    } while(strcmp(operation, "quit") != 0);

    return 0;
}