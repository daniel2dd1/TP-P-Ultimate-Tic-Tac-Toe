#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "jogadasant.h"
#include "matdin.h"

jgant inserejogada(jgant j, char **p, int jogada, int num_minitab, int jogador_atual, int x, int y)
{
    jgant novo, aux;
    novo = malloc(sizeof(no));          //alocar memoria do no já que não se pode alocar ponteiros
    if(novo == NULL)
    {
        printf("\nErro na alocação de memoria!\n");
        return j;
    }
    preenche(novo, p, jogada, num_minitab, jogador_atual,x, y);
    if(j == NULL || novo->jogada < j->jogada)
    {
        novo->prox = j;
        j=novo;
    }
    else
    {
        aux=j;
        while(aux->prox != NULL && novo->jogada > aux->prox->jogada)
            aux=aux->prox;
        novo->prox = aux->prox;
        aux->prox = novo;
    }
    return j;
}

void preenche(jgant t, char **p, int jogada, int atual_minitab, int jogador_atual, int x, int y)
{
    t->jogada_anterior = p;
    t->jogada = jogada;
    t->num_minitab = atual_minitab;
    t->idjogador = jogador_atual;
    t->x = x;
    t->y = y;
    t->prox=NULL;
}

void mostraJogadasAnteriores(jgant t,int totaljogadasfeitas, int retornax)
{
    int auxiliar;                                       //auxiliarm vai funcionar como um id
    auxiliar=totaljogadasfeitas-retornax;
    while(t != NULL && t->jogada != auxiliar+1)
        t=t->prox;
    if(t != NULL)                                       //assim que achar entao a lista com o mesmo valor de jogada q auxiliar
    {
        for(int i=0; i<retornax; i++)                 //comecar com um ciclo que comece a imprimir o numero de vezes que o utilizador pediu
        {
            printf("\nJogador %d fez \tJogada numero: %d\tMinitabuleiro: %d\nx: %d\ty: %d\n",t->idjogador+1, t->jogada, t->num_minitab+1, t->x+1, t->y+1);
            mostraMat(t->jogada_anterior, LINHAS, COLUNAS);
            t=t->prox;
            printf("\n");
        }
    }

}

void remove_tudo(jgant t)
{
    jgant aux;
    while(t != NULL)
    {
        aux = t;
        t = t->prox;
        free(aux);
    }
}

void deseja_rever_jogadas(jgant t, int totaljogadas_feitas)
{
    int valor_desejado;
    printf("\nQuantas jogadas deseja retornar?\nValor: ");
    scanf("%d", &valor_desejado);
    while((valor_desejado<1 && valor_desejado>10) || valor_desejado>totaljogadas_feitas)
    {
        printf("\nInsira outro valor ate %d ou entre 1 e 10!\nValor: ", totaljogadas_feitas);
        scanf("%d", &valor_desejado);
    }
    mostraJogadasAnteriores(t, totaljogadas_feitas, valor_desejado);
}


