#define n_rout 4

typedef struct pacote{
    char mensagem[100];
    int origem;
    int destino;
    int tipo;
}pacote;

typedef struct tabela_rout{
  int vizinhos[n_rout];
}tabela_rout[n_rout];

typedef struct roteador{
    int id;
    int porta;
    char endereco[32];
    tabela_rout tab_rout;
}roteador;

typedef struct lista_roteadores{
  roteador roteadores[99]; 
  int tamanho;
}lista_roteadores;

