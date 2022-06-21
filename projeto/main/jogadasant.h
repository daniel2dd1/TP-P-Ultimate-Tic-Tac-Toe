#ifndef JOGADASANT_H
#define JOGADASANT_H

#define LINHAS 3
#define COLUNAS 3

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct jogadas no, *jgant;
struct jogadas{
    char *jogada_anterior;
    int jogada;
    int idjogador;
    int num_minitab;
    int x;
    int y;
    jgant prox;
};


//assim que o jogador executar uma jogada armazena para que possa ativar a função de visualizar a jogada anterior
jgant inserejogada(jgant j, char **p, int jogada, int num_minitab, int jogador_atual, int x, int y); // recebe a lista o tabuleiro atual e o numero da jogada

//preenche os campos da nova struct inserida
void preenche(jgant t, char **p,int jogada,int atual_minitab, int jogador_atual, int x, int y);

//assim que acabar o jogo limpar tudo
void remove_tudo(jgant t);

//mostra jogadas anteriores entre 1 e 10
void mostraJogadasAnteriores(jgant t, int totaljogadasfeitas, int retornax);

//invoca funcao acima
void deseja_rever_jogadas(jgant t, int totaljogadas_feitas);


#endif
