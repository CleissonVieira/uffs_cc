#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h> //bibliotéca de acentos...
#define Nalunos 200

int teste, verifica;

typedef struct CadastroAluno{   //Struct para armazenar o cadastro dos alunos
    char nome[40];
    char matricula[10];
    char CPF[12];
    float Np1;
    float Np2;
    float Media;
}CadastroAluno;

typedef struct CadastroTurma{   //Struct para armazenas o cadastro de turmas
    int codigoturma;
    int matriculas[30];
    float Np1[30], Np2[30];
    float Media[30];
    char disciplina[25];
    int fase;
    char horario[20];
}CadastroTurma;
    //Função para fazer o cadastro do aluno
void cadastrar(CadastroAluno Estudante[]){
    int i, j, n, k, icpf[12], matri;
    int somador=0, digito1, result1, result2, digito2, valor, op;
    scanf("%d", &n);
    getchar();
    for(j=0; j<n; j++){   //loop para verificar quantos alunos desejam ser cadastrados
        system("cls");
        printf("Nome Completo do Aluno %d:\n", j+1);
        fgets(Estudante[j].nome, 40, stdin);
        system("cls");
        printf("Número da Matrícula:\n");
        scanf("%s", &Estudante[j].matricula);
        getchar();
        system("cls");
        printf("CPF do Aluno:\n");
        for(; ;){    //Loop pra verificar CPF, se válido ou não
            scanf("%s", &Estudante[j].CPF);
            getchar();
                //faz a conversao de array de char para um array de int.
                for(i=0;i<11;i++){
                    icpf[i]=Estudante[j].CPF[i]-48;
                }
                // Primeiro Digito
                for(i=0;i<9;i++){
                    somador+=icpf[i]*(10-i);
                }
                result1=somador%11;
                if((result1==0) || (result1==1)){
                    digito1=0;
                }
                else{
                    digito1 = 11-result1;
                }
                //Segundo Digito
                somador=0;
                for(i=0;i<10;i++){
                    somador+=icpf[i]*(11-i);
                }
                valor=(somador/11)*11;
                result2=somador-valor;
                if((result2==0) || (result2==1)){
                    digito2=0;
                }
                else{
                    digito2=11-result2;
                }
                //RESULTADOS DA VALIDACAO.
                if((digito1==icpf[9]) && (digito2==icpf[10])){
                    system("cls");
                    break;
                }
                else{
                    somador=0;
                    digito1=0;
                    result1=0;
                    result2=0;
                    digito2=0;
                    valor=0;
                    printf("CPF inválido, tente novamente:\n");
                }
        }
    }

}
    //função para selecionar o cadastro ou para inserir as notas dos alunos
void Menu_Alunos(CadastroAluno Estudante[]){
    int op, i, matri, cont=0;
    while(1){
        printf("Digite o número da opção desejada:\n");
        printf("1 Cadastratar Alunos:\n");
        printf("2 Voltar ao Menu Principal:\n");
        scanf("%d", &op);
        switch(op){
            case 1:
                //Cadastro
                system("cls");
                printf("Digite a quantidade de alunos a ser cadastrado: ");
                cadastrar(Estudante);
                break;
            case 2:
                system("cls");
                cont=1;
                break;
        }
        if(cont==1){
            break;
        }
    }
}

//---------------------------------------------------------------------------------------------------------------------------------------

    //Função para cadastrar turmas
void CadastrarTurma(CadastroTurma Sala[], CadastroAluno Estudante[]){
    int i, n, k, n2;
    system("cls");
    printf("Digite o número de turmas a ser cadastrado: ");
    scanf("%d", &n);
    getchar();
    for(i=0; i<n; i++){ //Loop para verificar quantas turmas vao ser cadastradas
        system("cls");
        printf("Código da Turma:\n");
        scanf("%d", &Sala[i].codigoturma);
        getchar();
        system("cls");
        printf("Componente Currícular Ministrado:\n");
        fgets(Sala[i].disciplina, 25, stdin);
        system("cls");
        printf("Fase em que a turma se encontra:\n");
        scanf("%d", &Sala[i].fase);
        getchar();
        system("cls");
        printf("Digite o horário de início e fim das aulas (exemplo: 10:30 - 12:30):\n");
        fgets(Sala[i].horario, 15, stdin);
        system("cls");
        teste=1;
        printf("Digite a quantidade de Aluno a cadastrar na turma: ");
        scanf("%d", &n2);
        getchar();
        system("cls");
        printf("Digite a Matrícula de Cada Aluno:\n");
        for(k=0; k<n2; k++){
            scanf("%d", &Sala[i].matriculas[k]);
        }
        system("cls");
        teste=1;
    }
    system("cls");
}

    //Imprimir os dados da turma X
void dados_da_turma(CadastroTurma Sala[]){
    int i, n=0, t, opcao;
    char Disc[25];
    for(; ;){
        if(teste==1){
            printf("Digite a Disciplina desejada:\n");
            for(; ;){
                t=0;
                fgets(Disc, 25, stdin);
                for(i=0; i<5; i++){
                    if(Sala[i].disciplina[3]==Disc[3] && Sala[i].disciplina[1]==Disc[1]){
                        n=i;
                        t++;
                        break;
                    }
                }
                if(t<=0){
                    system("cls");
                    printf("Disciplina inexistente, tente novamente!\n");
                }
                else{
                    system("cls");
                    break;
                }
            }
                printf("Componente Currícular:\n");
                printf("%s\n", Sala[n].disciplina);
                printf("Código da Turma:\n");
                printf("%d\n\n", Sala[n].codigoturma);
                printf("Horário das Aulas:\n");
                printf("%s\n", Sala[n].horario);
                printf("Fase da Turma:\n");
                printf("%d\n", Sala[n].fase);
                system("pause");
                system("cls");
                break;
        }
        else{
            printf("Nenhuma turma cadastrada...\n");
            system("pause");
            system("cls");
            break;
        }
    }
}
    //Imprimir os alunos já cadastrados na turma X
void AlunosdaTurma(CadastroTurma Turmas[]){
    int i, j, opcao;
    for(; ;){
        if(teste==1){
            for(j=0; j<5; j++){
                if(Turmas[j].fase>0 || Turmas[j].fase<10){
                printf("%s", Turmas[j].disciplina);
                    for(i=0; i<30; i++){
                        if(Turmas[j].matriculas[i]>0){
                            printf("%d\n", Turmas[j].matriculas[i]);
                        }
                    }
                }
                printf("\n");
            }
            system("pause");
            system("cls");
            break;
        }
            printf("Nenhuma turma cadastrada...\n");
        system("pause");
        system("cls");
        break;
    }
}
    //Função para inserir NP1 e NP2
void NOTAS(CadastroTurma Turmas[]){
    int i, j, cont=0, opcao;
    float Np1, Np2;
    char disciplina[25];
    for(; ;){
        printf("Digite o nome da disciplina desejada:\n");
        fgets(disciplina, 25, stdin);
        cont=0;
        for(i=0; i<5; i++){
            if(Turmas[i].disciplina[3]==disciplina[3] && Turmas[i].disciplina[1]==disciplina[1]){
                for(j=0; j<30; j++){
                    if(Turmas[i].matriculas[j]>0){
                        printf("Notas do Aluno %d\n", Turmas[i].matriculas[j]);
                        printf("NP1:\n");
                        scanf("%f", &Turmas[i].Np1[j]);
                        getchar();
                        printf("NP2:\n");
                        scanf("%f", &Turmas[i].Np2[j]);
                        getchar();
                        cont++;
                        system("cls");
                    }
                }
            }
            if(cont>0){ //VERIFICAR SE ALGUMA NOTA FOI CADASTRADA
                break;
            }
        }
        if(cont>0){
            verifica=5;
            system("cls");
            break;
        }
        system("cls");
        printf("Essa turma não existe ou não há alunos cadastrados...\n\n");
        printf("Pressione 1 para Tentar Novamente ou 2 para voltar ao Menu:\n");
        scanf("%d", &opcao);
        getchar();
        if(opcao==2){
            system("cls");
            break;
        }
        system("cls");
    }
}
    //função para imprimir Notas e média de cada aluno da turma X
void Exibir_Media(CadastroTurma Turmas[]){
    int i, j, cont=0;
    char disciplina[25];
    for(; ;){
        if(verifica==5){
            printf("Digite o nome da disciplina desejada:\n");
            fgets(disciplina, 25, stdin);
            for(i=0; i<5; i++){
                if(Turmas[i].disciplina[3]==disciplina[3] && Turmas[i].disciplina[1]==disciplina[1]){
                    for(j=0; j<30; j++){
                        if(Turmas[i].matriculas[j]>0){ //VERIFICANDO SE TEM UMA MATRÍCULA CADASTRADA
                            printf("Notas do Aluno %d\n", Turmas[i].matriculas[j]);
                            printf("NP1:\n");
                            printf("%.2f\n", Turmas[i].Np1[j]);
                            printf("NP2:\n");
                            printf("%.2f\n", Turmas[i].Np2[j]);
                            Turmas[i].Media[j]=(Turmas[i].Np1[j]+Turmas[i].Np2[j])/2;
                            printf("Média Final: ");
                            printf("%.2f\n\n", Turmas[i].Media[j]);
                            cont++;
                        }
                    }
                }
                if(cont>0){
                    break;
                }
            }
        }
        else{
            printf("Nenhuma nota cadastrada...\n");
            system("pause");
            system("cls");
            break;
        }
        printf("\n");
        system("pause");
        system("cls");
        break;
    }
}
    //OPÇÃO DE TURMAS
void Menu_turmas(CadastroTurma Turmas[], CadastroAluno Estudantes[]){
    int opcao, cont=0;
    while(1){
        system("cls");
        printf("Digite o número da opção desejada:\n");
        printf("1 Cadastrar Turma\n");
        printf("2 Verificar Alunos cadastrados:\n");
        printf("3 Dados da Turma:\n");
        printf("4 Inserção de Notas da Turma:\n");
        printf("5 Exibir notas parciais e médias dos alunos:\n");
        printf("6 Voltar ao Menu Principal:\n");
        scanf("%d", &opcao);
        getchar();
        system("cls");
            switch(opcao){
                case 1:
                    CadastrarTurma(Turmas, Estudantes);
                    break;
                case 2:
                    AlunosdaTurma(Turmas);
                    break;
                case 3:
                    dados_da_turma(Turmas);
                    break;
                case 4:
                    NOTAS(Turmas);
                    break;
                case 5:
                    Exibir_Media(Turmas);
                    break;
                case 6:
                    cont=1;
                    break;
            }
            if(cont=1){
                break;
            }
        }
}
    //FUNÇÃO FINAL
void Encerrar_Diario(CadastroTurma Turmas[]){
    int i, j;
    for(i=0; i<5; i++){
        if(Turmas[i].fase>0){
            printf("COMPONENTE CURRÍCULAR:\n");
            printf("%s\n", Turmas[i].disciplina);
            printf("ALUNOS:\n");
            for(j=0; j<30; j++){ //imprimir todos os alunos da turma i e dizer se aprovado ou reprovado
                if(Turmas[i].matriculas[j]>0){
                    printf("Matrícula %d\n", Turmas[i].matriculas[j]);
                    printf("NP1: ");
                    printf("%.2f\n", Turmas[i].Np1[j]);
                    printf("NP2: ");
                    printf("%.2f\n", Turmas[i].Np2[j]);
                    Turmas[i].Media[j]=(Turmas[i].Np1[j]+Turmas[i].Np2[j])/2;
                    printf("Média Final: ");
                    printf("%.2f\n", Turmas[i].Media[j]);
                    if(Turmas[i].Media[j]>=6){
                        printf("APROVADO\n\n");
                    } else{
                        printf("REPROVADO\n\n");
                    }
                }
            }
        }
        else{
            system("pause");
            break;
        }
    }
}
    //MENU PRINCPIPAL
void Menu(){
    CadastroAluno Alunos[Nalunos];
    CadastroTurma Turmas[5];
	int opcao;
	while(opcao<3){
        printf("Digite o número da opção desejada:\n");
        printf("1 Turmas\n");
        printf("2 Alunos\n");
        printf("3 Encerrar Diário\n");
        scanf("%d", &opcao);
        switch(opcao){
            case 1:
                Menu_turmas(Turmas, Alunos);
                break;
            case 2:
                system("cls");
                Menu_Alunos(Alunos);
                break;
            case 3:
                system("cls");
                Encerrar_Diario(Turmas);
                break;
        }
	}
}

int main(){
    setlocale(LC_ALL, "portuguese"); //comando para o programa aceitar acentos
    Menu();
    return 0;
}
