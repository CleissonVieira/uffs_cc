#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <estruturas.h>

roteador roteador_meu;
lista_roteadores roteadores_lista;

int socket_meu, proximos[6];  // O proximos era populado no backtraking, refatorar para usar com bellman-ford distribuído

// Utilizada para de fato enviar as mensagens/pacotes
void envia_mensagem(pacote pacote_x){
    struct sockaddr_in outro_end;
    int slen = sizeof(outro_end);   
    memset((char *) &outro_end, 0, sizeof(outro_end));
    outro_end.sin_family = AF_INET;

    //dentro de próximos existe nas posições para onde deve ir para chegar no pacote_x.destino
    outro_end.sin_port = htons(roteadores_lista.roteadores[proximos[pacote_x.destino-1]].porta); // proximos
    printf("\nEnviar mensagem para %d | Objetivo: %d\n", proximos[pacote_x.destino-1]+1, pacote_x.destino); // proximos
     
    if (inet_aton(roteadores_lista.roteadores[pacote_x.destino-1].endereco , &outro_end.sin_addr) == 0) {
        fprintf(stderr, "inet_aton() failed\n");
        exit(1);
    }

    //envia a mensagem ou se der erro printa "erro sendto"
    if (sendto(socket_meu, &pacote_x, sizeof(pacote) , 0 , (struct sockaddr *) &outro_end, slen) == -1){
        printf("erro sendto\n");
    }
    printf("\nId Destinatário: ");
}

void *receptor(void *args){
    struct sockaddr_in meu_end, outro_end;
    int i, slen = sizeof(outro_end) , recv_len;
    pacote pacote_recebido;
    // Limpar estrutura meu_end
    memset((char *) &meu_end, 0, sizeof(meu_end));
     
    meu_end.sin_family = AF_INET;
    meu_end.sin_port = htons(roteador_meu.porta);
    meu_end.sin_addr.s_addr = htonl(INADDR_ANY);
     
    // Ligar o socket a porta
    if( bind(socket_meu, (struct sockaddr*)&meu_end, sizeof(meu_end) ) == -1){
        printf("erro bind");
    }
     
    // Utilizado para receber uma mensagem e encaminhar
    while(1){
        fflush(stdout);
        //Limpa buffer
        memset(&pacote_recebido,'\0', sizeof(pacote));

        // Chamada bloqueante para receber os dados
        if ((recv_len = recvfrom(socket_meu, &pacote_recebido, sizeof(pacote), 0, (struct sockaddr *) &outro_end, &slen)) == -1){
            printf("erro recvfrom()");
        } 

        // Verificar se o pacote recebido é meu ou se precisa ser reenviado
        if(pacote_recebido.destino == roteador_meu.id){
            printf("\n\nNova mensagem de %d: %s\n\nId Destinatário: ", pacote_recebido.origem, pacote_recebido.mensagem);
        }else{
            envia_mensagem(pacote_recebido);
        }
    }
    printf("\nId Destinatário: ");
    return 0;
}

// Utilizada para informar para quem vai enviar e qual mensagem enviar
void *transmissor(void *args){
    pacote novo_pacote;
    while(1){
        novo_pacote.origem = roteador_meu.id;
        printf("\nId Destinatário: ");
        scanf("%d", &novo_pacote.destino);

        printf("\nMensagem: ");
        scanf("%s", novo_pacote.mensagem);

        envia_mensagem(novo_pacote); //função para enviar
    }
}

// Identifica todos os roteadores dentro de roteador.config passando para roteadores_lista
void roteador_func(){
    FILE *file;
    roteador aux;
    int i = -1;
    file = fopen("roteador.config", "r");
    printf("Digito (id roteador 1 - 4):");
    scanf("%d", &roteador_meu.id);
    while(fscanf(file, "%d %d %s", &aux.id, &aux.porta, aux.endereco) != EOF ){
        i = roteadores_lista.tamanho++;
        roteadores_lista.roteadores[i] = aux;
        //verifica se meu roteador está dentro de roteador.config/existe e passa demais informações para roteador_meu
        if(aux.id == roteador_meu.id){ 
            roteador_meu = aux;
        }
    }
} 

// Utilizada para identificar a topologia e aplicar dijkstra
void enlace(){
    FILE *file;
    int x, y, tam;
    int matriz[roteadores_lista.tamanho][roteadores_lista.tamanho];

    file = fopen("enlace.config", "r");

    // cria matriz preenchendo com -1 e caminhos para si mesmo com 0
    for (int i = 0; i < roteadores_lista.tamanho; i++){
        for (int j = 0; j < roteadores_lista.tamanho; j++){
            matriz[i][j] = -1;
            matriz[i][i] = 0;
        }
    }
    // preenche distancias conforme enlace.config
    while(fscanf(file, "%d %d %d", &x, &y, &tam) != EOF ){
        matriz[x-1][y-1] = tam;
        matriz[y-1][x-1] = tam;
    }
    




    // for (int i = 0; i < roteadores_lista.tamanho; i++){
    //     if(i+1 == roteador_meu.id){
    //         for (int j = 0; j < roteadores_lista.tamanho; j++){
    //             roteador_meu.vizinhos[j] = matriz[i][j];
    //         }
    //     }
    // }        

    // para cada roteador_meu.id -> para cada vizinho direto
    // envia o vetor roteador_meu.vizinhos
    // 
    // o vizinho soma o vetor roteador_meu.id vetor recebido
    // se for maior ignora
    // se for menor incrementa os custos.

    // Aplica dijkstra na matriz com as distancias entre os roteadores a partir do meu roteador
    // Criando um vetor "proximos" com objetivos e onde deve enviar para alcançar tais objetivos
    // dijkstra(matriz, roteador_meu.id-1);
  
  



    printf("\nObjetivo:   | 1 | 2 | 3 | 4 |\n");
    printf("Enviar para:");
    for(int i = 0; i < roteadores_lista.tamanho; i++){
        printf("  %d ", proximos[i]+1); // proximos
    }
    printf("\n");   
}

int main(int argc, char const *argv[])
{  
    int aux;   
    if ( (socket_meu = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1){ //cria sockets
        printf("socket erro");
    }
    roteador_func();
    enlace(); 
    pthread_t thread1, thread2;
    pthread_create(&thread2, NULL, &receptor, NULL);
    pthread_create(&thread1, NULL, &transmissor, NULL);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    return 0;
}



