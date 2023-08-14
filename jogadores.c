#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 5

typedef struct{ //struct para jogador
char nome[50];
int pontos;
} jogador;

FILE *abre_arquivo();
void    muda_ranking(FILE *arq, jogador novo, int posicao);
int posicao_jogador_novo(FILE *arq, jogador novo_jogador);

int main(){

    jogador jogadores[MAX];
    jogador jogador_novo;
    int i;
    int posicao=0;
    FILE *arq;

    printf("Digite o nome do novo jogador:  ");
    fgets(jogador_novo.nome, 50, stdin);
    jogador_novo.nome[strlen(jogador_novo.nome) - 1] = '\0';                             // limpar o \n ao ler a string, para ficar organizado na tabela

    printf("Digite a pontuacao do novo jogador:   ");
    scanf("%d",&jogador_novo.pontos);

    arq = abre_arquivo();
    fread(&jogadores, sizeof(jogador), MAX, arq);                                       //ler o arquivo apos abrir/criar ele


    if(jogador_novo.pontos<jogadores[4].pontos){                                        //verificar se o novo jogador tem pontuacao suficiente para entrar no rank dos 5 melhores

        printf("Voce nao entrou no rankin\n\n");

    }else{
        posicao = posicao_jogador_novo(arq , jogador_novo);                             // chama a  funcao para verificar a posicao que o jogador deve entrar
        muda_ranking(arq , jogador_novo, posicao);                                      // chama a funcao para atualizar o ranking
        printf("\n\nParabens, voce entrou no ranking na posicao: %d \n\n", posicao+1);
    }
    rewind (arq);
    fread(&jogadores, sizeof(jogador), MAX, arq);


    printf(" ______________________________________\n");
    printf("| POSICAO | NOME DO JOGADOR | PONTOS   |\n");
    printf("|--------------------------------------|\n");
    for (int i = 0; i < MAX; i++) {
    printf("| %d ------> %-10s ------ %-9d|\n",i+1, jogadores[i].nome, jogadores[i].pontos);
    }
    printf("|______________________________________|\n");


    fclose(arq);


    return 0 ;
}



FILE *abre_arquivo(){                    // abertura do arquivo, testando se ele ja existe, se nao existir criar um

    char nome_arquivo[] = "ranking.bin";
    FILE *arq = fopen(nome_arquivo, "rb+");
    if(arq == NULL){


        jogador  jogadores[MAX]= {{"Jogador 1",95},{"Jogador 2",85},{"Jogador 3",60},{"Jogador 4",45},{"Jogador 5",30}};//define os 5 nomes genericos e seus pontos para botar no arquivo caso ele nao exista
        printf("Arquivo nao existe, criando arquivo.... \n\n");
        arq = fopen(nome_arquivo, "wb+");
        fwrite(&jogadores, sizeof(jogadores), MAX, arq);
        rewind (arq);

    }

    return arq;
}


void    muda_ranking(FILE *arq, jogador novo, int posicao){             //funcao para mudar o ranking dependendo da posicao que o novo jogador tiver, e atualizar todo ranking
    jogador auxiliar1, auxiliar2;
    int i=posicao;
    jogador jogadores[MAX];
    rewind (arq);
    fread(&jogadores, sizeof(jogador), MAX, arq);
    auxiliar1 = jogadores[i];
    jogadores[i]= novo;

    for(i=posicao+1; i<MAX; i++){
        auxiliar2=jogadores[i];
        jogadores[i]=auxiliar1;
        auxiliar1=auxiliar2;
    }
    rewind (arq);
    fwrite(&jogadores, sizeof(jogadores), (MAX - posicao), arq);
    rewind (arq);
}

int posicao_jogador_novo(FILE *arq, jogador novo_jogador){
    int i;
    int posicao = 0;
    jogador jogadores[MAX];
    rewind (arq);
    fread(&jogadores, sizeof(jogador), MAX , arq);
    for (i = 0; i < MAX; i++) {
        if (jogadores[i].pontos > novo_jogador.pontos) {
            posicao++;
        }
    }
    rewind (arq);
    return posicao;
}


