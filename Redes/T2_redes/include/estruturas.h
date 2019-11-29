#define n_rout 4

// 0 = mensagem
// 1 =  vetor
// 2 = confirmação
typedef struct pacote{
    char mensagem[100];
    int vetor[n_rout];
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
    int prox[n_rout];
    int dist[n_rout];
    int vizinhos[n_rout];
    tabela_rout tab_rout;
}roteador;

typedef struct lista_roteadores{
  roteador routs[99]; 
  int tamanho;
}lista_roteadores;

