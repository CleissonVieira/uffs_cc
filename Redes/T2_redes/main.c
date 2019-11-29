#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <estruturas.h>
#include <unistd.h>

lista_roteadores list_rout;
roteador my_rout;

int firt = 0; // printar primeiras distancis e objetivos
int timeout = 1;
int socket_meu;

void bellman_ford();

// Utilizada para de fato enviar as mensagens/pacotes
void envia_mensagem(pacote pacote_x){
    struct sockaddr_in outro_end;
    int slen = sizeof(outro_end);
    memset((char *) &outro_end, 0, sizeof(outro_end));
    outro_end.sin_family = AF_INET;
    
    outro_end.sin_port = htons(list_rout.routs[my_rout.prox[pacote_x.destino-1]-1].porta);
     
    if (inet_aton(list_rout.routs[pacote_x.destino-1].endereco , &outro_end.sin_addr) == 0) {
        fprintf(stderr, "inet_aton() failed\n");
        exit(1);
    }

    if(pacote_x.tipo == 0){
        printf("\n-------------------------------------------------------------------------");
        printf("\nSent message to %d | Objective: %d\n",  my_rout.prox[pacote_x.destino-1], pacote_x.destino);
        printf("-------------------------------------------------------------------------\n");
    }else if(pacote_x.tipo == 1){
        printf("\n-------------------------------------------------------------------------");
        printf("\nDistance Vector sent to %d\n", pacote_x.destino);
        printf("-------------------------------------------------------------------------\n");
    }

    //envia a mensagem ou se der erro printa "erro sendto"
    if (sendto(socket_meu, &pacote_x, sizeof(pacote) , 0 , (struct sockaddr *) &outro_end, slen) == -1){
        printf("erro sendto\n");
    }
}

void envia_vetor(){ // Envia seu vetor para todos os seus vizinhos
    pacote meu_vetor;
    for(int i = 0 ; i < list_rout.tamanho; i++ ){
        // if(my_rout.tab_rout[my_rout.id-1].vizinhos[i] != 0 && my_rout.tab_rout[my_rout.id-1].vizinhos[i] != -1){
        if(my_rout.vizinhos[i] != 0 && my_rout.vizinhos[i] != -1){
            meu_vetor.origem = my_rout.id;
            meu_vetor.destino = i+1;
            meu_vetor.tipo = 1;
            memcpy(meu_vetor.vetor, my_rout.tab_rout[my_rout.id-1].vizinhos, sizeof(int)*list_rout.tamanho);
            envia_mensagem(meu_vetor);
        }
    }
}

void print_tabRout(){
    // imprime tab_rout e vetores prox e dist para teste
    printf("\n-------------------------------------------------------------------------");
    printf("\nMinha Tabela de roteamento:\n");
    for (int i = 0; i < list_rout.tamanho; i++){
        for (int j = 0; j < list_rout.tamanho; j++){
            printf(" %d ", my_rout.tab_rout[i].vizinhos[j]);
        }
        printf("\n");
    }
    printf("-------------------------------------------------------------------------\n");
}

void print_vetors(){
    // PRINTAR OBJETIVO, PRÓXIMOS E DISTANCIA
    printf("\n-------------------------------------------------------------------------");
    printf("\nObjetivo:  ");
    for (int i = 0; i < list_rout.tamanho; i++){
        printf("  %d  ", i+1);
    }
    
    printf("\nProximos:  ");
    for (int i = 0; i < list_rout.tamanho; i++){
        printf("  %d  ", my_rout.prox[i]);
    }
    printf("\nDistancia: ");
    for (int i = 0; i < list_rout.tamanho; i++){
        if(my_rout.dist[i] > 9){
            printf("  %d ", my_rout.dist[i]);
        }else{
            printf("  %d  ", my_rout.dist[i]);
        }
    }
    printf("\n-------------------------------------------------------------------------\n");
    // PRINTAR OBJETIVO, PRÓXIMOS E DISTANCIA
}

void bellman_ford(){
    int change = 0;
    my_rout.prox[my_rout.id-1] = my_rout.id;
    memcpy(my_rout.dist, my_rout.tab_rout[my_rout.id-1].vizinhos, sizeof(int)*list_rout.tamanho);
    for (int i = 0; i < list_rout.tamanho; i++){
        // if para verificar se é meu vizinho ou se sou eu mesmo, se nenhum dos dois continua
        if(my_rout.tab_rout[i].vizinhos[i] != -2 && i != my_rout.id-1){
            for(int j = 0; j < list_rout.tamanho; j++){
                if(my_rout.tab_rout[i].vizinhos[j] != -1 && my_rout.dist[j] > my_rout.dist[i] + my_rout.tab_rout[i].vizinhos[j]){
                    my_rout.tab_rout[my_rout.id-1].vizinhos[j] = my_rout.dist[i] + my_rout.tab_rout[i].vizinhos[j]; 
                    my_rout.dist[j] = my_rout.dist[i] + my_rout.tab_rout[i].vizinhos[j];
                    my_rout.prox[j] = i+1;
                    change = 1;
                }else if(my_rout.dist[j] == -1){
                    my_rout.tab_rout[my_rout.id-1].vizinhos[j] = my_rout.dist[i] + my_rout.tab_rout[i].vizinhos[j];
                    my_rout.dist[j] = my_rout.dist[i] + my_rout.tab_rout[i].vizinhos[j];
                    my_rout.prox[j] = i+1;
                    change = 1;
                }
            }
        }
    }
 
    print_tabRout(); // imprime tabela de roteamento

    if(change == 1){
        print_vetors(); // imprime vetor Distancia, Próximo e Objetivo
        envia_vetor();
    }else if(firt == 0){
        print_vetors();
        firt = 1;
    }
}

void *receptor(void *args){
    struct sockaddr_in meu_end, outro_end;
    int i, slen = sizeof(outro_end) , recv_len;
    pacote pacote_recebido;
    // Limpar estrutura meu_end
    memset((char *) &meu_end, 0, sizeof(meu_end));
     
    meu_end.sin_family = AF_INET;
    meu_end.sin_port = htons(my_rout.porta);
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
        if(pacote_recebido.destino == my_rout.id){
            if(pacote_recebido.tipo == 0){
                printf("\n\nNova mensagem de %d: %s\n", pacote_recebido.origem, pacote_recebido.mensagem);
                pacote confirmacao;
                strcpy(confirmacao.mensagem, "mensagem recebida!");
                confirmacao.origem = pacote_recebido.destino;
                confirmacao.destino = pacote_recebido.origem;
                confirmacao.tipo = 2;
                envia_mensagem(confirmacao);
                printf("\nId Destinatário: ");
            }else if(pacote_recebido.tipo == 1){
                if (my_rout.tab_rout[pacote_recebido.origem-1].vizinhos[my_rout.id-1] == -2){
                    envia_vetor(); // verifica se é a primeira vez que recebe vetor de x, se sim reenvia seu vetor dist para vizinhos
                }
                memcpy(my_rout.tab_rout[pacote_recebido.origem-1].vizinhos, pacote_recebido.vetor, sizeof(int)*list_rout.tamanho);       
                printf("\nPacket Recieved from Router %d\n", pacote_recebido.origem);
                for (int i = 0; i < n_rout; ++i){
                    printf("%d ",pacote_recebido.vetor[i]);
                }
                bellman_ford();
                printf("\nId Destinatário: ");
            }else if(pacote_recebido.tipo == 2){
                timeout = 0;
            }
        }else{
            envia_mensagem(pacote_recebido);
        }
    }
    return 0;
}

// Utilizada para informar para quem vai enviar e qual mensagem enviar
void *transmissor(void *args){
    pacote novo_pacote;
    novo_pacote.tipo = 0;
    envia_vetor(); // envia o primeiro dist vector para seus vizinhos // verificar se necessario outra thread
    			   // Envia apenas uma vez, não entra em loop.
    while(1){
        novo_pacote.origem = my_rout.id;
        printf("\n\nId Destinatário: ");
        scanf("%d", &novo_pacote.destino);

        printf("\nMensagem: ");
        scanf("%s", novo_pacote.mensagem);
        
        printf("\nAguardando confirmação...\n");
        for (int count = 0; count < 3; count++){
            envia_mensagem(novo_pacote); //função para enviar o pacote com mensagem
            sleep(3);
            if(timeout == 0){
                printf("\nMensagem de roteador %d para roteador %d enviada com sucesso!\n", my_rout.id, novo_pacote.destino);
                timeout = 1;
                break;
            }else if(count == 2){
                printf("\nErro ao enviar mensagem, três tentativas sem sucesso.\n");
            }
        }
    }
}

// Identifica todos os roteadores dentro de roteador.config passando para list_rout
void roteador_func(){
    FILE *file;
    roteador aux;
    int i = -1;
    file = fopen("config/roteador.config", "r");
    printf("Digite (id roteador 1 - 4):");
    scanf("%d", &my_rout.id);
    while(fscanf(file, "%d %d %s", &aux.id, &aux.porta, aux.endereco) != EOF ){
        i = list_rout.tamanho++;
        list_rout.routs[i] = aux;
        //verifica se meu roteador está dentro de roteador.config/existe e passa demais informações para my_rout
        if(aux.id == my_rout.id){ 
            my_rout = aux;
        }
    }
} 

// Utilizada para identificar a topologia e aplicar dijkstra
void enlace(){
    FILE *file;
    int x, y, tam;
    int matriz[list_rout.tamanho][list_rout.tamanho];

    file = fopen("config/enlace.config", "r");

    // preenche vetores de vizinhos da tab_rout com -2, indicando que não está preenchida
    // preenche vetor de próximos e dist com -2 indicando que está vazio
    for (int i = 0; i < list_rout.tamanho; i++){
        for (int j = 0; j < list_rout.tamanho; j++){
            my_rout.tab_rout[i].vizinhos[j] = -2;   
        }
        my_rout.prox[i] = i+1;
        my_rout.dist[i] = -2;
    }

    // cria matriz preenchendo com -1 e caminhos para si mesmo com 0
    for (int i = 0; i < list_rout.tamanho; i++){
        for (int j = 0; j < list_rout.tamanho; j++){
            matriz[i][j] = -1;
            matriz[i][i] = 0;
        }
    }
    // preenche distancias conforme enlace.config
    while(fscanf(file, "%d %d %d", &x, &y, &tam) != EOF ){
        matriz[x-1][y-1] = tam;
        matriz[y-1][x-1] = tam;
    }
   
    // Para cada roteador preenche o vetor dos vizinhos conforme percorre a matriz (próprio vetor)
    for (int i = 0; i < list_rout.tamanho; i++){
        if(i+1 == my_rout.id){
            for (int j = 0; j < list_rout.tamanho; j++){
                my_rout.tab_rout[my_rout.id-1].vizinhos[j] = matriz[i][j];
            }
        }
    }
    // Printa os vizinhos do roteador
    printf("Vetor de vizinhos:\n ");
    for (int i = 0; i < list_rout.tamanho; i++){
        printf("%d ", my_rout.tab_rout[my_rout.id-1].vizinhos[i]);
    }
    printf("\n");
    memcpy(my_rout.vizinhos , my_rout.tab_rout[my_rout.id-1].vizinhos, sizeof(int)*list_rout.tamanho);
}

int main(int argc, char const *argv[]){  
    int aux;   
    if ( (socket_meu = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1){ //cria sockets
        printf("\nErro no Socket\n");
    }
    roteador_func();
    enlace(); 
    pthread_t thread1, thread2;
    // pthread_create(&thread3, NULL, &bellman_ford, NULL);
    pthread_create(&thread2, NULL, &receptor, NULL);
    pthread_create(&thread1, NULL, &transmissor, NULL);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    // pthread_join(thread3, NULL);
    return 0;
}



