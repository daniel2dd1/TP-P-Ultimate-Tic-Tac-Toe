#ifndef GUARDAJOGO_H
#define GUARDAJOGO_H

#include <stdlib.h>
#include <stdio.h>

#include "matdin.h"
#include "jogadasant.h"

typedef struct guardar_info save;
typedef struct coordenadasGuardadas saveInfoJogagada;

struct coordenadasGuardadas{
    int n_minitab;          //numero do minitab
    int x;                  //coordenada x
    int y;                  //coordenada y
    int xtabgrande;         //coordenada x no tabuleiro grande
    int ytabgrande;         //coordenada y no tabuleiro grande
    char car;               //X se j1 O se j2 ou PC
};

struct guardar_info{
    int total_jogadas;           //armazena o numero total de jogadas
    int prox_minitab;           //armazena o numero do proximo minitab
    int id_proximo_jogador;     //o se Jogador 1 e 1 se jogador 2 ou PC
    saveInfoJogagada minitabsinfo[81];      //guarda info de cada jogada que depois é usado para retomr um jogo guardado ou escrever num ficheiro de texto
    int modoJogo;       //0 se jogador contra PC 1 se jogador contra jogador
    int retorna;        //é 1 caso o ficheiro exista e o jogador queira retornar o jogo
};

//guarda o jogo num ficheiro binario
void guardajogo(jgant t,save sve, tabul tab, minitabuleiro minitab,int jogadas_feitas, int jogador_atual, int modo_jogo, int prox_minitab);

//verifica se é possivel o acesso ao ficheiro que mantem o jogo guardado e questiona o utilizador se pretende continuar caso queira entao retorna toda a informação necessaria para preencher o tabuleiro do jogo guardado
save retomajogo(save s);

//escreve todo o tabuleiro que está guardado no ficheiro binario  e retorna então o tabuleiro de jogo para que possa ser retomado esse jogo
tabul preencheJogoGuardado(save s, tabul tab, jgant t);

//a cada jogada vai guardando as coordenadas e o numero do minitabuleiro
save guardaCoordenadas(save s,int c1, int c2, int c1grande, int c2grande, int nminit, int njogada, char c);

//escreve as jogadas todas
void escreveJogadas(save s, FILE *f);

//escreve num ficheiro de texto todas as jogadas e outras informaçoes
void texto(int id_vencedor, save sve, tabul tab);



#endif

