
typedef struct pacote{
    char mensagem[100];
    int origem;
    int destino;
}pacote;

typedef struct roteador{
    int id;
    int porta;
    char endereco[32];
}roteador;

typedef struct lista_roteadores{
  roteador roteadores[99]; 
  int tamanho;
}lista_roteadores;